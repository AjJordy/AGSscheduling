//
// Created by jordy on 12/04/17.
//

#ifndef ALGORITMOGENETICO_ESTUDANTE_H
#define ALGORITMOGENETICO_ESTUDANTE_H

#include "Disciplina.h"

#include "vector"

using namespace std;
class Estudante{

//	vector<Disciplina> enteresses;

    int id;
	vector<int> disciplinas;
	
//	Turma turma;
//	Curso curso;


public:
	Estudante(int id_est, vector<int> disc_desejadas) {
		id = id_est;
		disciplinas = disc_desejadas;
	}
	vector<int> get_disciplinas() {return disciplinas;}


};

#endif //ALGORITMOGENETICO_ESTUDANTE_H
