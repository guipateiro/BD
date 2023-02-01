#include "grafo.h"
#include "Data.hpp"
#include <iostream>
#include <stdio.h>
#include <cstring>  
#include <vector>


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
	
	std::vector<int> carlos(50);
	char nome[256];
    snprintf(nome, sizeof(nome), "grafo");
	grafo g = agopen(nome, Agdirected, nullptr);
	for (i = 0; i < tam; i++){
		char tempstrint[128];
		//std::cout << "'" << data[i].origem << "'" <<'\n';
		std::sprintf(tempstrint,"%i", data[i].origem);
  		//std::printf("n_char: '%s' \n",tempstrint);
		agnode(g, tempstrint, TRUE);
	}
	for (i = 0; i < tam; i++){
		for (int j = i; j < tam; j++){
			if(data[i].operacao == 'R' && (data[i].dado == data[j].dado) && data[j].operacao == 'W'){
				char tempstrint[128];
				std::sprintf(tempstrint,"%i", data[i].origem);
  				//std::printf("n_char: %s \n",tempstrint);
				vertice s = agnode(g, tempstrint, FALSE);
				std::sprintf(tempstrint,"%i", data[j].origem);
  				//std::printf("n_char: %s \n",tempstrint);
				vertice n = agnode(g, tempstrint, FALSE);
				agedge(g,s,n,NULL,TRUE);
			}
			if(data[i].operacao == 'W' && (data[i].dado == data[j].dado) && data[j].operacao == 'R'){
				char tempstrint[128];
				std::sprintf(tempstrint,"%i", data[i].origem);
  				//std::printf("n_char: %s \n",tempstrint);
				vertice s = agnode(g, tempstrint, FALSE);
				std::sprintf(tempstrint,"%i", data[j].origem);
  				//std::printf("n_char: %s \n",tempstrint);
				vertice n = agnode(g, tempstrint, FALSE);
				agedge(g,s,n,NULL,TRUE);
			}
			if(data[i].operacao == 'W' && (data[i].dado == data[j].dado) && data[j].operacao == 'W'){
				char tempstrint[128];
				std::sprintf(tempstrint,"%i", data[i].origem);
  				//std::printf("n_char: %s \n",tempstrint);
				vertice s = agnode(g, tempstrint, FALSE);
				std::sprintf(tempstrint,"%i", data[j].origem);
  				//std::printf("n_char: %s \n",tempstrint);
				vertice n = agnode(g, tempstrint, FALSE);
				agedge(g,s,n,NULL,TRUE);
			}
		}
	}

	//while
	decompoe(g);
	

	//feito pelo tikara (nao deletar)
	/*vector<vector<int>> g(MAXN);

	g[a].push_back(b);
	g[b].push_back(a);
	g[a].remove(b);

	int g[MAXV][MAXV] = {};

	g[a][b] = 1;
	g[b][a] = 1;

	g[a][b] = 0;*/

	/*for (i = 0; i < tam; i++){
		std::cout << data[i].time << " " << data[i].origem << " " << data[i].operacao << " " << data[i].dado << "\n";
	}8*/

	
	
	//escreve_grafo(g);

}