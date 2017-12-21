 
//
// Created by jordy on 12/04/17.
//

#include "vector"
#include "Disciplina.h"
#include "Sala.h"
#include "Estudante.h"
#include "Docente.h"

#ifndef ALGORITMOGENETICO_ELEMENTO_H
#define ALGORITMOGENETICO_ELEMENTO_H
using namespace std;

class Elemento{

private:
    int disciplina_id;
	int docentes_id;
    int sala_id;
    vector<int> estudantes_ids;
public:
	virtual ~Elemento();

public:
	Elemento(int disciplina_id, int docentes_id, int sala_id, const vector<int> estudantes_ids);

public:
	int getDisciplina_id() const;

	void setDisciplina_id(int disciplina_id);

	int getDocentes_id() const;

	void setDocentes_id(int docentes_id);

	int getSala_id() const;

	void setSala_id(int sala_id);

	const vector<int> &getEstudantes_ids() const;

	void setEstudantes_ids(const vector<int> &estudantes_ids);

};
#endif 
