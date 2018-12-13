#ifndef _COMMAND_
#define _COMMAND_

#include <string>
#include <climits>
#include <vector>

class Command{

public:
	unsigned int numberVertices;
	std::vector<int> edges;
	
	Command(unsigned int nNumberVertices, std::vector<int> nEdges){
		this->numberVertices = nNumberVertices;
		this->edges = nEdges;
	}

	std::string toString(){
		std::string result = "( Number of vertices : " + std::to_string(this->numberVertices) + " )\n";
		
		for(unsigned int i =0;i<this->numberVertices*2;i++){
			result += "-"; 
		}

		result+="Matrix";

		for(unsigned int i =0;i<this->numberVertices*2;i++){
			result += "-"; 
		}

		result+="\n";

		for(unsigned int i=0;i<this->edges.size();i++){
			
			if(this->edges[i]==INT_MAX){
				result += " INF" ;
			}else{
				if(this->edges[i]>=0){
					result += " ";
				}
				result += " " + std::to_string(this->edges[i]) + " ";
			}

			if((i+1)%this->numberVertices==0){
				result+="\n";
			}
		}

		for(unsigned int i =0;i<this->numberVertices*4+6;i++){
			result += "-"; 
		}

		return result;

	}

};

#endif