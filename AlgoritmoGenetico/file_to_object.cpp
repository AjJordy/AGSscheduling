#include "file_to_object.h"
using namespace std;

void File_to_object::file_to_object() {
	string** dados;
	ler_restricoes();

	file.skip_comment();
	string linha = file.get_line();
	timeslots =  file.get_data(4);

	cout << file.get_line() << endl;

//	Preenche vector de cursos
	int num_linhas = file.count_lines();
	dados = file.get_data(1);
	for(int i = 0; i < num_linhas; i++) {
		int id = atoi(dados[i][0].c_str());
		cursos.push_back(Curso(id));
	}

	cout << file.get_line() << endl;
	file.get_data(1);
	cout << file.get_line() << endl;

//	Preenche vector de salas
	num_linhas = file.count_lines();
	dados = file.get_data(5);
	for(int i = 0; i < num_linhas; i++) {
		int id = atoi(dados[i][0].c_str());
		int tipo = atoi(dados[i][3].c_str());
		int capacidade = atoi(dados[i][4].c_str());
		salas.push_back(Sala(id, tipo, capacidade));
	}

//	Preenche restricoes de salas;
	for (int j = 0; j < 19; ++j) {
		int id = restricoes_sala[j].at(0);
		restricoes_sala[j].erase(restricoes_sala[j].begin());
		salas.at((unsigned long) (id - 1)).setRestricoes(restricoes_sala[j]);
		int x = 0;
	}

	cout << file.get_line() << endl;

//	Faz vector de disciplinas que tem restricoes
	vector<int> id_disc_com_rest;
	for (int j = 0; j < 35; ++j) {
		int id = restricoes_disciplina[j].at(0);
		id_disc_com_rest.push_back(id);
		restricoes_disciplina[j].erase(restricoes_disciplina[j].begin());
	}

//	Preenche vector de disciplinas
	num_linhas = file.count_lines();
	dados = file.get_data(9);
	int j = 0;
	for(int i = 0; i < num_linhas; i++) {
		int id = atoi(dados[i][0].c_str());
		int curso_id = atoi(dados[i][1].c_str());
		int periodo = atoi(dados[i][2].c_str());
		int cht = atoi(dados[i][5].c_str());
		int tipo_t = atoi(dados[i][6].c_str());
		int chp = atoi(dados[i][7].c_str());
		int tipo_p = atoi(dados[i][8].c_str());
		disciplinas.push_back(Disciplina(id, curso_id, periodo, cht, tipo_t, chp, tipo_p));

		if (!id_disc_com_rest.empty() && id_disc_com_rest.at(0) == id) {
			disciplinas.at(i).setRestricoes(restricoes_disciplina[j++]);
			id_disc_com_rest.erase(id_disc_com_rest.begin());
		}
	}

	cout << file.get_line() << endl;

	// Preenche vector de estudantes
	num_linhas = file.count_lines();
	int posicao = file.get_position();
	dados = file.get_data(1);
	file.go_to_position(posicao);
	vector<int>* disciplinas_desejadas = file.get_data_vector(2);

	for(int i = 0; i < num_linhas; i++) {
		int id = atoi(dados[i][0].c_str());
		vector<int> disc_desejadas = disciplinas_desejadas[i];
		estudandes.push_back(Estudante(id,disc_desejadas));
	}

	cout << file.get_line() << endl;


//	Preenche o vector de docentes
	num_linhas = file.count_lines();
	posicao = file.get_position();
	dados = file.get_data(1);
	file.go_to_position(posicao);
	vector<int>* disciplinas_ministraveis = file.get_data_vector(3);

	for(int i = 0; i < num_linhas; i++) {
		int id = atoi(dados[i][0].c_str());
		vector<int> disc_minist = disciplinas_ministraveis[i];
		docentes.push_back(Docente(id,disc_minist));
	}

//	Preenche restricoes de docentes;
	for (int j = 0; j < 40; ++j) {
		int id = restricoes_docente[j].at(0);
		restricoes_docente[j].erase(restricoes_docente[j].begin());
		docentes.at((unsigned long) (id - 1)).setRestricoes(restricoes_docente[j]);
	}
}

void File_to_object::ler_restricoes(){
	Files *file_rest = new Files("../ag-restricoes.csv");
	string linha;

	file_rest->skip_comment();
	linha = file_rest->get_line();
	restricoes_disciplina = file_rest->get_data_vector(0);
	linha = file_rest->get_line();
	restricoes_docente = file_rest->get_data_vector(0);
	linha = file_rest->get_line();
	restricoes_sala = file_rest->get_data_vector(0);
	int x = 0;
}

const vector<Curso> &File_to_object::getCursos() const {
    return cursos;
}

void File_to_object::setCursos(const vector<Curso> &cursos) {
    File_to_object::cursos = cursos;
}

const vector<Sala> &File_to_object::getSalas() const {
    return salas;
}

void File_to_object::setSalas(const vector<Sala> &salas) {
    File_to_object::salas = salas;
}

const vector<Disciplina> &File_to_object::getDisciplinas() const {
    return disciplinas;
}

void File_to_object::setDisciplinas(const vector<Disciplina> &disciplinas) {
    File_to_object::disciplinas = disciplinas;
}

const vector<Estudante> &File_to_object::getEstudandes() const {
    return estudandes;
}

void File_to_object::setEstudandes(const vector<Estudante> &estudandes) {
    File_to_object::estudandes = estudandes;
}

const vector<Docente> &File_to_object::getDocentes() const {
    return docentes;
}

void File_to_object::setDocentes(const vector<Docente> &docentes) {
    File_to_object::docentes = docentes;
}
