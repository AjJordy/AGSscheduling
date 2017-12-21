#include "files.h"
#include <vector>
using namespace std;

Files::Files(string arquivo) {
	file.open(arquivo);
}

Files::~Files() {
}

string Files::get_line(){
	string linha;
	getline(file,linha);
	skip_comment();
	return linha;
}

void Files::print(int num_itens){
	int num_linhas = count_lines();
	string** dados = get_data(num_itens);
	for(int i = 0; i < num_linhas; i++) {
		cout << "Linha " << i << ": " << endl;
		for(int j = 0; j < num_itens; j++) {
			cout << "Posicao " << j << ": " << dados[i][j] << endl;
		}
	}
}

void Files::read_file() {
	ifstream file;
	string line;

	file.open("text.txt");

	if(file.is_open()) {
		int num_linhas = count_lines();
		string** dados = get_data(4);

		for(int i = 0; i < num_linhas; i++) {
			cout << "Linha " << i << ": " << endl;
			for(int j = 0; j < 4; j++) {
				cout << "Posicao " << j << ": " << dados[i][j] << endl;
			}
		}
	}
}

// Pula comentarios
string Files::skip_comment(){
	int x = 0, posicao;
	string linha;
   	getline(file, linha);
	x++;
	do {
		posicao = file.tellg();
		getline(file, linha);
		x++;
	} while (linha[0] == '/');
//	cout << x << endl;
	file.clear();
	file.seekg(posicao);
	return linha;
}

// Retorna um vetor de vetores, com um vetor para cada linha,
// contendo o conteudo delas. Comeca na posicao atual e vai até
// o proximo '/'
string** Files::get_data(int num_itens) {
	string **data, line;
	int i = 0, num_linhas = count_lines();

	data = new string*[num_linhas];
//	int posicao = file.tellg();
	while(i < num_linhas) {
		getline(file, line);
		data[i++] = split_line(line.c_str(), num_itens);
	}
//	file.clear();
//	file.seekg(posicao);
	skip_comment();

	return data;
}

// Retorna um vetor de strings com o conteudo da linha
string* Files::split_line(const char* line, int num_itens) {
	int i = 0; 
	string *data = new string[num_itens];

	while(i < num_itens) {
		string temp;
		while(*line == ',') line++;
		while(*line != ',' && *line != '\0') {
			temp += *line;
			line++;
		}
		data[i++] = temp;
	}

	return data;
}

vector<int>* Files::get_data_vector(int starting_char) {
	vector<int> *data;
	string line;
	int i = 0, num_linhas = count_lines();

	data = new vector<int>[num_linhas];
//	int posicao = file.tellg();
	while(i < num_linhas) {
		getline(file, line);
		data[i++] = split_line_vector(line.c_str(), starting_char);
	}
//	file.clear();
//	file.seekg(posicao);
	skip_comment();

	return data;
}

vector<int> Files::split_line_vector(const char* line, int start) {
	vector<int> data;
	int i = 0;

	while(*line != '\0') {
		string temp;
		while(*line == ',') line++;
		while(*line != ',' && *line != '\0') {
			temp += *line;
			line++;
		}
		if(i++ >= start) data.push_back(atoi(temp.c_str()));
	}

	return data;
}


// Conta o numero de linhas da posicao atual até o proximo '/'
int Files::count_lines(){
	string line;
	int count = 0;

	int posicao = file.tellg();
	while(getline(file, line)) {
		if(line[0] == '/') break;	
		count++;
	}
	file.clear();
	file.seekg(posicao);

	return count;
}

int Files::get_position() { 
	return file.tellg();
}

void Files::go_to_position(int posicao) { 
	file.clear();
	file.seekg(posicao);
}
