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

	std::cout << algorithmFW.toStringBeforeMatrixD() << std::endl;

	std::cout << algorithmFW.toStringBeforeMatrixPath() << std::endl;

	//std::cout << c.toString() << std::endl;
	
	return 0;
}