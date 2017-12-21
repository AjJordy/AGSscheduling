//
// Created by jordy on 12/04/17.
//
#ifndef ALGORITMOGENETICO_DOCENTE_H
#define ALGORITMOGENETICO_DOCENTE_H
#include "Disciplina.h"
#include "vector"
using namespace std;

class Docente{
    int id;
	vector<int> disciplinas;
	vector<int> restricoes;
	vector<int> timeslots_adicionado;
public:
	vector<int> &getRestricoes() {
		return restricoes;
	}

	void setRestricoes(vector<int> &restricoes) {
		Docente::restricoes = restricoes;
	}

	const vector<int> &getDisciplinas() const {
		return disciplinas;
	}

	void setDisciplinas(const vector<int> &disciplinas) {
		Docente::disciplinas = disciplinas;
	}

	vector<int> &getTimeslots_adicionado() {
		return timeslots_adicionado;
	}

	void setTimeslots_adicionado(const vector<int> &timeslots_adicionado) {
		Docente::timeslots_adicionado = timeslots_adicionado;
	}

    virtual ~Docente() {}
	Docente(int id, vector<int> disciplinas) : id(id), disciplinas(disciplinas){}


    int getId() const {
        return id;
    }
    void setId(int id) {
        Docente::id = id;
    }
	vector<int> &get_disciplinas() {return disciplinas;}
};
#endif //ALGORITMOGENETICO_DOCENTE_H
