//
// Created by jordy on 12/04/17.
//

#ifndef ALGORITMOGENETICO_DISCIPLINA_H
#define ALGORITMOGENETICO_DISCIPLINA_H

#include "vector"

class Disciplina{

private:
    int id;
	int curso_id;
	int periodo;
    int carga_horaria_teorica;
	int tipo_t;
    int carga_horaria_pratica;
	int tipo_p;
	std::vector<int> restricoes;

public:
	std::vector<int> &getRestricoes() {
		return restricoes;
	}

	void setRestricoes(std::vector<int> &restricoes) {
		Disciplina::restricoes = restricoes;
	}

	int getCurso_id() const {
		return curso_id;
	}

	void setCurso_id(int curso_id) {
		Disciplina::curso_id = curso_id;
	}

	int getPeriodo() const {
		return periodo;
	}

	void setPeriodo(int periodo) {
		Disciplina::periodo = periodo;
	}

	int getTipo_t() const {
		return tipo_t;
	}

	void setTipo_t(int tipo_t) {
		Disciplina::tipo_t = tipo_t;
	}

	int getTipo_p() const {
		return tipo_p;
	}

	void setTipo_p(int tipo_p) {
		Disciplina::tipo_p = tipo_p;
	}
//	vector<int> restricoes;         // horários permitidos para a Disciplina

public:
    Disciplina(int id, int curso_id, int periodo, int cht, int tipo_t, int chp, int tipo_p) :
			id(id), curso_id(curso_id), periodo(periodo),
			carga_horaria_teorica(cht), tipo_t(tipo_t), carga_horaria_pratica(chp), tipo_p(tipo_p) {}

    virtual ~Disciplina();

    int getId() const;

    void setId(int id);

    int getCarga_horaria_teorica() const;

    void setCarga_horaria_teorica(int carga_horaria_teorica);

    int getCarga_horaria_pratica() const;

    void setCarga_horaria_pratica(int carga_horaria_pratica);

//    const vector<int> &getRestricoes() const;

//	void setRestricoes(const vector<int> &restricoes);

};

#endif //ALGORITMOGENETICO_DISCIPLINA_H
