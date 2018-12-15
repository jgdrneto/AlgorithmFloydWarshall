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

	int interaction = 0;

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

				valor = m[i][j][period];

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

	int sum(int left, int right){
		if(left==INT_MAX || right==INT_MAX){
			return INT_MAX;
		}else{
			return left+right;
		}
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
			this->d[i] = new int*[this->numberVertices];
			this->path[i] =  new int*[this->numberVertices];
			for(unsigned int j=0;j<this->numberVertices;j++){
				this->d[i][j] = new int[QUANT_MATRIX_D];
				this->path[i][j] = new int[QUANT_MATRIX_D];

				this->d[i][j][ACTUAL] = nEdges[(i*this->numberVertices)+j];
				
				if(i==j || d[i][j][ACTUAL] == INT_MAX){
					this->path[i][j][ACTUAL] = INT_MAX;
				}else{
					this->path[i][j][ACTUAL] = i+1;
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

	void updateMatrixes(int*** d, int*** path){
		for(unsigned int x=0;x<numberVertices;x++){
			for(unsigned int y=0;y<numberVertices;y++){
				d[x][y][BEFORE] = d[x][y][ACTUAL];
				path[x][y][BEFORE] = path[x][y][ACTUAL];
			}
		}
	}

	bool execute(){

		std::cout << "------------------" <<"Iteraction 0" << "------------------\n" << std::endl;

		std::cout << this->toStringMatrix(this->d, "Matrix D 0", ACTUAL) << std::endl;

		std::cout << this->toStringMatrix(this->path, "Matrix Path 0", ACTUAL) << std::endl;
		
		std::cout << "" << std::endl;

		int result=0;
		for(unsigned int k=0;k<numberVertices;k++){

			this->updateMatrixes(d,path);

			for(unsigned int i=0;i<numberVertices;i++){
				for(unsigned int j=0;j<numberVertices;j++){

					result = this->sum(d[i][k][BEFORE],d[k][j][BEFORE]);

					if(this->d[i][j][BEFORE]<=result){
						this->d[i][j][ACTUAL] = this->d[i][j][BEFORE];
						this->path[i][j][ACTUAL] = this->path[i][j][BEFORE];
					}else{
						this->d[i][j][ACTUAL] = result;
						this->path[i][j][ACTUAL] = this->path[k][j][BEFORE];
					}
				}
			}

			std::cout << "------------------" <<"Iteraction " << (k+1) << "------------------\n" << std::endl;

			std::cout << this->toStringMatrix(this->d, "Matrix D " + std::to_string(k+1),ACTUAL) << std::endl;

			std::cout << this->toStringMatrix(this->path, "Matrix Path " + std::to_string(k+1),ACTUAL) << std::endl;
		
			std::cout << "" << std::endl;
		}
	
		for(unsigned int l=0;l<this->numberVertices;l++){
			if(d[l][l][ACTUAL]<0){
				return true;
			}
		}

		return false;
	}
};

#endif