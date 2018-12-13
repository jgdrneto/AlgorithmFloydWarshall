#ifndef _ALGORITHM_FLOYD_WARSHALL_
#define _ALGORITHM_FLOYD_WARSHALL_

#include <string>
#include <climits>
#include <vector>

enum
{
	BEFORE,
	ACTUAL,
	QUANT_MATRIX_D
};

class AlgorithmFloydWarshall{

	std::string toStringMatrix(int*** m,std::string name, int period){
		std::string result="";

		for(unsigned int i =0;i<this->numberVertices*2;i++){
			result += "-"; 
		}

		result+=name;

		for(unsigned int i =0;i<this->numberVertices*2;i++){
			result += "-"; 
		}

		result+="\n";

		int valor = 0;
		for(unsigned int i=0;i<this->numberVertices;i++){
			for(unsigned int j=0;j<this->numberVertices;j++){

				valor = m[i][j][BEFORE];

				if(valor==INT_MAX){

					if(m==this->d){
						result += " INF" ;
					}else{
						result += " NIL" ;
					}	
				}else{
					if(valor>=0){
						result += " ";
					}
					result += " " +  std::to_string(valor) + " ";
				}
			}
			result+="\n";
		}

		for(unsigned int i=0;i<this->numberVertices*4+name.size();i++){
			result += "-"; 
		}

		return result;
	}


public:
	unsigned int numberVertices;
	int*** d;
	int*** path;
	
	AlgorithmFloydWarshall(unsigned int nNumberVertices, std::vector<int> nEdges){
		this->numberVertices = nNumberVertices;

		//INIT matrices d's and path
		this->d = new int**[this->numberVertices];
		this->path =  new int**[this->numberVertices];
		
		for(unsigned int i=0;i<this->numberVertices;i++){
			d[i] = new int*[this->numberVertices];
			path[i] =  new int*[this->numberVertices];
			for(unsigned int j=0;j<this->numberVertices;j++){
				d[i][j] = new int[QUANT_MATRIX_D];
				path[i][j] = new int[QUANT_MATRIX_D];
				for(unsigned int k=0;k<QUANT_MATRIX_D;k++){
					if(k==BEFORE){
						d[i][j][BEFORE] = nEdges[(i*this->numberVertices)+j];
						if(i==j || d[i][j][BEFORE] == INT_MAX){
							path[i][j][BEFORE] = INT_MAX;
						}else{
							path[i][j][BEFORE] = i+1;
						}
					}else{
						d[i][j][k] = 0;
					}
				}
			}
		}
	}

	virtual ~AlgorithmFloydWarshall(){
		for (unsigned int i = 0; i < this->numberVertices; i++){
    		for (unsigned int j = 0; j < this->numberVertices; j++){
        		delete[] d[i][j];
        		delete[] path[i][j];
        	}
        	delete[] path[i];	
    		delete[] d[i];
		}
		delete[] d;
		delete[] path;
	}

	std::string toStringBeforeMatrixD(){
		return this->toStringMatrix(this->d,"Matrix D Before",BEFORE);
	}

	std::string toStringBeforeMatrixPath(){

		return this->toStringMatrix(this->path,"Matrix Path Before",BEFORE);
	}

	std::string toString(){
		std::string result = "";
		return result;
	}

};

#endif