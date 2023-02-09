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
			std::cout << data[m].origem;
			if (controle_operacao.size() > 0 ){
				std::cout << ',';
			}else{
				std::cout << ' ';
			}
		}
		//std::cout << controle_operacao.size() << "\n";
		if(controle_operacao.size() == 0){
			// i == inicio dos elementos nao processados 
			// m == fim dos elementos nao processados
			//std::cout << "teste "<< i << m <<"\n";
			int n = i;
			for (; n < m; n++){
				for (int j = n + 1; j < m; j++){
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
			if(n_vertices(g) == decompoe(g)){
				std::cout <<  "SS";
			}
			else{
				std::cout <<  "NS";
			}


			// coloque seu algoritmo aqui 

			// next_permutation() google pesquisar

			// termine seu codigo aqui
			
			std::cout << "\n";

			
			flag = 1;
			i = m; // inicio = final
		}
	}
}	