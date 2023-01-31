#include "grafo.h"
#include "Data.hpp"
#include <iostream>
#include <stdio.h>
#include <cstring>  


int main(){
	//grafo g = le_grafo();
	//escreve_grafo(g);
    Data data[30]; 
	char line[100];
	int i = 0;
    while(std::cin.getline(line,100)){
    	char *ptr = strtok (line, " ");
		std::cout << " Split string using strtok() function: " << std::endl;  
    	// use while loop to check ptr is not null  
			
		std::cout << std::stoi(ptr)  << std::endl; // print the string token  
		data[i].time = std::stoi(ptr); 
		ptr = strtok (NULL, " ");
		std::cout << std::stoi(ptr)  << std::endl; // print the string token  
		data[i].origem = std::stoi(ptr);  
		ptr = strtok (NULL, " ");
		std::cout << ptr  << std::endl; // print the string token  
		data[i].operacao = ptr[0];  
		ptr = strtok (NULL, " ");
		std::cout << ptr  << std::endl; // print the string token  
		data[i].dado = ptr[0];   
		i++;
    }  
	int tam = i--;
	grafo g = agopen("grafo", Agdirected, nullptr);
	for (i = 0; i < tam; i++){
		
	}
	

	for (; i >= 0; --i){
		std::cout << data[i].time << " " << data[i].origem << " " << data[i].operacao << " " << data[i].dado << "\n";
	}
	
}