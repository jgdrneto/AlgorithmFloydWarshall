#include <sstream>
#include <iterator>
#include <fstream>

#include "include/Command.cpp"

namespace Reader{

	std::vector<std::string> readfile(std::string filename){

		std::vector<std::string> v;
		std::ifstream inFile;
		std::string sLine;

		inFile.open(filename);

		if (!inFile) {
    		std::cerr << "Unable to open file " + filename;
    		exit(1);   
		}

		while (!inFile.eof()){
			getline(inFile, sLine);
			v.push_back(sLine);
		}

		inFile.close();

		return v;
	}
}

namespace Interpreter{

	std::vector<std::string> split(std::string str){

		std::vector<std::string> cont;

    	std::istringstream iss(str);
    	std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(cont));
		
		return cont;
	}

	Command createCommand(std::vector<std::string> commands){

		unsigned int vertices=0;
		std::vector<int> edges;

		for(std::string line : commands){

			std::vector<std::string> words = split(line);

			if(words.empty()){
				continue;
			}else{
				if(vertices==0){
					vertices=std::stoul(words[0]);
				}else{
					if(words.size()!=vertices){
						std::cerr << "Bad formatted instruction 2" << std::endl;
						exit(1);
					}else{
						for(std::string edge : words){
							if(edge=="INF"){
								edges.push_back(INT_MAX);
							}else{
								edges.push_back(std::stoi(edge));
							}
						}
					}
				}
			}
		}

		return Command(vertices,edges);
	}

	Command createCommandFromFile(std::string filename){
		return createCommand(Reader::readfile(filename));
	}
}