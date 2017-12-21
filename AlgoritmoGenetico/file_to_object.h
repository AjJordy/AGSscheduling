#ifndef ALGORITMOGENETICO_FILE_TO_OBJECT_H
#define ALGORITMOGENETICO_FILE_TO_OBJECT_H

#include "files.h"
#include "Curso.h"
#include "Sala.h"
#include "Disciplina.h"
#include "Estudante.h"
#include "Docente.h"
#define MAX_TIMESLOT 140


class File_to_object {

private:
    Files file;
    vector<Curso> cursos;
    vector<Sala> salas;
    vector<Disciplina> disciplinas;
    vector<Estudante> estudandes;
    vector<Docente> docentes;
	string **timeslots;
	vector<int>* restricoes_disciplina;
	vector<int>* restricoes_docente;
	vector<int>* restricoes_sala;

public:
    File_to_object(std::string arquivo) : file(arquivo) {}
	void ler_restricoes();
    void file_to_object();

	//  Getters e Setters
	const vector<Curso> &getCursos() const;
	void setCursos(const vector<Curso> &cursos);
	const vector<Sala> &getSalas() const;
	void setSalas(const vector<Sala> &salas);
	const vector<Disciplina> &getDisciplinas() const;
	void setDisciplinas(const vector<Disciplina> &disciplinas);
	const vector<Estudante> &getEstudandes() const;
	void setEstudandes(const vector<Estudante> &estudandes);
	const vector<Docente> &getDocentes() const;
	void setDocentes(const vector<Docente> &docentes);
	string** getTimeslots() { return timeslots; }
};
//	)
#endif
