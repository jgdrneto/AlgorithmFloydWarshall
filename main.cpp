#include <iostream>

#include "functions.cpp"
#include "include/AlgorithmFloydWarshall.cpp"

int main(int argc, char const *argv[]){	
	
	if(argc<2){
		std::cerr << "Enter the filename";
    	exit(1);
	}
	
	Command c = Interpreter::createCommandFromFile(argv[1]);

	AlgorithmFloydWarshall algorithmFW(c.numberVertices,c.edges); 

	bool negativeCicle = algorithmFW.execute();

	if(negativeCicle){
		std::cout << "This graph has negative cycle" << std::endl;
	}else{
		std::cout << "This graph has no negative cycle" << std::endl;
	}

	return 0;
}