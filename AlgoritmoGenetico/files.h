#ifndef ALGORITMOGENETICO_FILES_H
#define ALGORITMOGENETICO_FILES_H

#include <iostream>
#include <fstream>
#include <vector>

class Files {

	std::ifstream file;

	public: 
		Files(std::string arquivo);
		virtual ~Files();
		void print(int num_itens);
		std::string skip_comment();
		std::string get_line();
		std::string* split_line(const char* line, int num_itens);
		int count_lines();
		std::string** get_data(int num_itens);
		void read_file(); 
		std::vector<int> split_line_vector(const char* line, int start);
		std::vector<int>* get_data_vector(int starting_char);
		int get_position(); 
		void go_to_position(int posicao);

};
#endif
