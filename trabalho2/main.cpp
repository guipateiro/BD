#include "grafo.h"
#include "Data.hpp"
#include <iostream>
#include <stdio.h>
#include <cstring>  
#include <vector>
#include <algorithm>
#include <list>

int main(){
	//grafo g = le_grafo();
	//escreve_grafo(g);
    Data data[300]; 
	char line[100];
	int i = 0;
    while(std::cin.getline(line,100)){
		//std::cout << line << "\n";
    	char *ptr = strtok (line, " ");
		//std::cout << " Split string using strtok() function: " << std::endl;  
    	// use while loop to check ptr is not null  
			
		data[i].time = std::stoi(ptr); 
		//std::cout << data[i].time  << std::endl; // print the string token  
		ptr = strtok (NULL, " ");
		data[i].origem = std::stoi(ptr);  
		//std::cout << data[i].origem  << std::endl; // print the string token  
		ptr = strtok (NULL, " ");
		data[i].operacao = ptr[0];  
		//std::cout << data[i].operacao  << std::endl; // print the string token  
		ptr = strtok (NULL, " ");
		data[i].dado = ptr[0];   
		//std::cout << data[i].dado  << std::endl; // print the string token  
		
		//std::cout << "INPUT SALVO: "<< data[i].time << " " << data[i].origem << " " << data[i].operacao << " " << data[i].dado << "\n";
		i++;
    }  
	int tam = i--;
	i = 0;
	std::list<int> controle_operacao;
	int num = 1;
	bool flag = 0;
	std::cout << num << " ";
	for(int m = 0; m < tam; m++){
		if(flag){
			std::cout << num++ << " ";
			flag = 0;
		}
		char nome[256];
		snprintf(nome, sizeof(nome), "grafo");
		grafo g = agopen(nome, Agdirected, nullptr);
		char tempstrint[128];
		//std::cout << "'" << data[m].origem << "'" <<'\n';
		if(data[m].operacao != 'C'){
			controle_operacao.push_front(data[m].origem);
			//std::cout << "colocado\n";
			std::sprintf(tempstrint,"%i", data[m].origem);
			//agnode(g, tempstrint, TRUE);
		}
		else{
			controle_operacao.remove(data[m].origem);
/*			std::cout << data[m].origem;
			if (controle_operacao.size() > 0 ){
				std::cout << ',';
			}else{
				std::cout << ' ';
			}
*/		}
		//std::cout << controle_operacao.size() << "\n";
		if(controle_operacao.size() == 0){
			// i == inicio dos elementos nao processados 
			// m == fim dos elementos nao processados
			//std::cout << "teste "<< i << m <<"\n";
			int n = i;
			int j;
			for (; n <= m; n++){
				for (j = n + 1; j < m; j++){
					if((data[n].dado == data[j].dado) && ((data[n].operacao == 'R' && data[j].operacao == 'W') || (data[n].operacao == 'W' && data[j].operacao == 'W') || (data[n].operacao == 'W' && data[j].operacao == 'R'))){
						char tempstrint[128];
						std::sprintf(tempstrint,"%i", data[n].origem);
						//std::printf("n_char: %s \n",tempstrint);
						vertice s = agnode(g, tempstrint, TRUE);
						std::sprintf(tempstrint,"%i", data[j].origem);
						//std::printf("n_char: %s \n",tempstrint);
						vertice ns = agnode(g, tempstrint, TRUE);
						agedge(g,s,ns,NULL,TRUE);
					}
				}
			}
			


			// *** Início de Equivalência por Imagem ***

			// Monta lista de origens de um conflito
			// Junta lista de dados utilizados
			std::vector<int> permutations;
			std::vector<char> data_list;
			for (n = i; n <= m; n++){
				permutations.push_back(data[n].origem);
				data_list.push_back(data[n].dado);
			} 
			sort(permutations.begin(), permutations.end());
			permutations.erase(unique(permutations.begin(), permutations.end()), permutations.end());
			//std::cout << "\n\n";
			for (unsigned int perm_index = 0; perm_index < permutations.size(); perm_index++){
				std::cout << permutations[perm_index];
				if (perm_index != permutations.size()-1)
					std::cout << ',';
			}
			std::cout << " ";

			if(n_vertices(g) == decompoe(g)){
				std::cout <<  "SS ";
			}
			else{
				std::cout <<  "NS ";
			}

			sort(data_list.begin(), data_list.end());
			data_list.erase(unique(data_list.begin(), data_list.end()), data_list.end());

			// Cria permutações dos dados em copy_data
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

				// Regra 2
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

				if (!equivalente)
					continue;

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

				if (!equivalente)
					continue;
				
				// Regra 3: Fazer lista de variáveis.
				// Achar o último write de cada variável.
				// Ver se ele coincide com o último write da S'.
				
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
				

				if (equivalente){
					/*std::cout << "Time inicial: " << data[i].time << ", Time final: " << data[m].time << "\nO vetor:\n";
					for (int teste = i; teste <= m; teste++){
					std::cout << "Data = " << data[teste].time << ", " << data[teste].origem << ", " << data[teste].operacao << ", " << data[teste].dado << "\n";
				}
					std::cout << "É equivalente com: \n";
					for (int teste = 0; teste < size; teste++){
					std::cout << "Copy = " << copy_data[teste].time << ", " << copy_data[teste].origem << ", " << copy_data[teste].operacao << ", " <<  copy_data[teste].dado << "\n";
				}*/
					break;
				}
/*
				for (int teste = i; teste <= m; teste++){
					std::cout << "Data = " << data[teste].time << ", " << data[teste].origem << ", " << data[teste].operacao << ", " << data[teste].dado << "\n";
				}
				for (int teste = 0; teste < size; teste++){
					std::cout << "Copy = " << copy_data[teste].time << ", " << copy_data[teste].origem << ", " << copy_data[teste].operacao << ", " <<  copy_data[teste].dado << "\n";
				}
				std::cout << "\n";
*/
			} while (std::next_permutation(permutations.begin(),permutations.end()));

			//std::cout << "Equivalência = " << equivalente;

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