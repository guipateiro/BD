#include "grafo.h"
#include "Data.hpp"
#include <iostream>
#include <stdio.h>
#include <cstring>  
#include <vector>
#include <algorithm>
#include <list>

int main(){
    Data data[30000]; 
	char line[100];
	int i = 0;
	//le uma linha da entrada e divide ela em tokens
    while(std::cin.getline(line,100)){
    	char *ptr = strtok (line, " ");	
		data[i].time = std::stoi(ptr); 
		ptr = strtok (NULL, " ");
		data[i].origem = std::stoi(ptr);  
		ptr = strtok (NULL, " ");
		data[i].operacao = ptr[0];  
		ptr = strtok (NULL, " ");
		data[i].dado = ptr[0];   
		i++;
    }  
	
	int tam = i--;  //tamanho total gerado pela entrada
	i = 0;  		//contador
	std::list<int> controle_operacao;
	int num = 1;
	bool flag = 0;
	std::cout << num << " ";
	//for de 0 ao tamanho de data
	for(int m = 0; m < tam; m++){
		if(flag){
			std::cout << num++ << " ";
			flag = 0;
		}
		char nome[256];
		//gera um grafor com os vetices onde o nome do vertice é o nome da 'tread' da operação
		snprintf(nome, sizeof(nome), "grafo");
		grafo g = agopen(nome, Agdirected, nullptr);
		char tempstrint[128];
		if(data[m].operacao != 'C'){
			//empilha a 'tread' para verificar se a operação terminou
			controle_operacao.push_front(data[m].origem);
			std::sprintf(tempstrint,"%i", data[m].origem);
		}
		else{
			//desempilha a 'tread' para verificar se a operação terminou
			controle_operacao.remove(data[m].origem);
		}
		//se a pilha de 'treads' ativas é zero entao as operações terminaras e podem ser processadas
		if(controle_operacao.size() == 0){
			// i == inicio dos elementos nao processados 
			// m == fim dos elementos nao processados
			int n = i;
			int j;
			for (; n <= m; n++){
				for (j = n + 1; j < m; j++){
					// para cada 2 operações verifica se elas caem em uma das 3 regras
					if((data[n].dado == data[j].dado) && ((data[n].operacao == 'R' && data[j].operacao == 'W') || (data[n].operacao == 'W' && data[j].operacao == 'W') || (data[n].operacao == 'W' && data[j].operacao == 'R'))){
						char tempstrint[128];
						//pega um vertice
						std::sprintf(tempstrint,"%i", data[n].origem);
						vertice s = agnode(g, tempstrint, TRUE);
						//pega outro vertice
						std::sprintf(tempstrint,"%i", data[j].origem);
						vertice ns = agnode(g, tempstrint, TRUE);
						//cria aresta 
						agedge(g,s,ns,NULL,TRUE);
					}
				}
			}
			//grafo pronto


			// *** Início de Equivalência por Imagem ***

			// Monta lista de origens de um conflito
			// Junta lista de dados do conflito pra uso posterior
			std::vector<int> permutations;
			std::vector<char> data_list;
			for (n = i; n <= m; n++){
				permutations.push_back(data[n].origem);
				data_list.push_back(data[n].dado);
			} 


			// Ordena ambos os vetores e remove dados duplicados
			sort(permutations.begin(), permutations.end());
			permutations.erase(unique(permutations.begin(), permutations.end()), permutations.end());
			sort(data_list.begin(), data_list.end());
			data_list.erase(unique(data_list.begin(), data_list.end()), data_list.end());

			
			// Imprime as origens presentes no conflito
			for (unsigned int perm_index = 0; perm_index < permutations.size(); perm_index++){
				std::cout << permutations[perm_index];
				if (perm_index != permutations.size()-1)
					std::cout << ',';
			}
			std::cout << " ";
			

			// Imprime a saída do primeiro teste
			// se numero de vertices == numero de componentes, não ha ciclo no grafo
			if(n_vertices(g) == decompoe(g)){
				std::cout <<  "SS ";
			}
			else{
				std::cout <<  "NS ";
			}


			// Início do do-while para permutações
			// Logo no começo, cria-se um vetor copy_data
			// Nele, está presente S', uma cópia de S seriabilizada
			// Em cada laço um S' diferente é criado, respeitando as permutações
			// Como são os mesmos dados de S, todo S' cumpre a regra 1
			int size = m-i+1;
			Data copy_data[size];
			bool equivalente;
			do {
				equivalente = true;
				int pos = 0;
				for (unsigned int perm_index = 0; perm_index < permutations.size(); perm_index++){
					for (n = i; n <= m; n++){
						if (data[n].origem == permutations[perm_index]){
							std::copy(data+n, data+n+1, copy_data+pos);
							pos++;
						}
					}
				}

				// Regra 2: Se houver leitura, checar se há escrita prévia
				// Para facilitar, foi implementado checando primeiro a escrita
				// A cada escrita, checa-se se houve leitura posterior do mesmo dado
				// Se houve, analisa-se se no vetor S' a ordem das operações permanece a mesma (escrita antes de leitura)
				// Caso a leitura venha antes, não é equivalente por visão
				for (n = i; n <= m; n++){
					if (data[n].operacao == 'W'){
						for (j = n+1; j <= m; j++){
							if (data[j].operacao == 'R' && data[n].dado == data[j].dado && data[n].origem != data[j].origem){
								int i_copia = 0;
								while (copy_data[i_copia].time != data[n].time && copy_data[i_copia].time != data[j].time)
									i_copia++;
								if (copy_data[i_copia].time == data[j].time)
									equivalente = false;
							}
							if (!equivalente)
								break;
						}
					}
					if (!equivalente)
						break;
				}

				// Se não cumpriu a regra, vamos pro próximo S'
				if (!equivalente)
					continue;

				// Agora, inverte-se a ordem de 'R' e 'W'.
				// Isso é equivalente a analisar se existe um 'W' antes de 'R' no S' e comparar no S, tratando S' como Ti e S como Tj
				for (n = i; n <= m; n++){
					if (data[n].operacao == 'R'){
						for (j = n+1; j <= m; j++){
							if (data[j].operacao == 'W' && data[n].dado == data[j].dado && data[n].origem != data[j].origem){
								int i_copia = 0;
								while (copy_data[i_copia].time != data[n].time && copy_data[i_copia].time != data[j].time)
									i_copia++;
								if (copy_data[i_copia].time == data[j].time)
									equivalente = false;
							}
							if (!equivalente)
								break;
						}
					}
					if (!equivalente)
						break;
				}

				// Se não cumpriu a regra, vamos pro próximo S'
				if (!equivalente)
					continue;
				
				// Regra 3: Checar se a última escrita ainda é a mesma
				// Primeiro, roda-se o vetor de variáveis utilizadas feito previamente (data_list)
				// Procura-se no segundo "for", de baixo pra cima, a última escrita
				// Se não houver escrita, passa pra próxima variável
				// Se houver escrita, roda o copy_data de baixo pra cima em busca do último write
				// Se for a mesma transação é equivalente, caso contrário não é
				for (unsigned int i_ele = 0; i_ele < data_list.size(); i_ele++){
					for (n = m; n >= i; n--){
						if (data[n].operacao == 'W' && data[n].dado == data_list[i_ele])
							break;
					}
					if (n == i-1)
						continue;
					for (j = size-1; j >= 0; j--){
						if (copy_data[j].operacao == 'W' && copy_data[j].dado == data[n].dado){
							if (copy_data[j].time == data[n].time)
								break;
							else{
								equivalente = false;
								break;
							}
						}
					}
					if (!equivalente)
						break;
				}
				

				// Se cumpriu ambas as regras, paramos de analisar as permutações pois achamos um S' equivalente
				if (equivalente)
					break;


			} while (std::next_permutation(permutations.begin(),permutations.end()));


			// Imprime a saída da equivalência por imagem
			if (equivalente)
				std::cout << "SV";
			else
				std::cout << "NV";

			// *** Fim de Equivalência por Imagem ***
			
			std::cout << "\n";

			
			flag = 1;
			i = m + 1; // inicio = final
		}
	}
}	