//
// Created by jordy on 12/04/17.
//

#ifndef ALGORITMOGENETICO_SALA_H
#define ALGORITMOGENETICO_SALA_H

#include <vector>

class Sala{
    
    int id;
    int tipo;// sala normal, lab EE, lab EC, lab EM
	int capacidade;
    std::vector<int> restricoes;

public:
	std::vector<int> &getRestricoes(){
		return restricoes;
	}

	void setRestricoes(std::vector<int> &restricoes) {
		Sala::restricoes = restricoes;
	}

    Sala(int id) : id(id) {}
    Sala(int id, int tipo, int capacidade) : id(id), tipo(tipo), capacidade(capacidade) {}
    virtual ~Sala() {}
    int getId() const {
        return id;
    }
    void setId(int id) {
        Sala::id = id;
    }
    int getTipo() const {
        return tipo;
    }
    void setTipo(int tipo) {
        Sala::tipo = tipo;
    }
    int getCapacidade() const {
        return capacidade;
    }
    void setCapacidade(int capacidade) {
        Sala::capacidade = capacidade;
    }
};

#endif //ALGORITMOGENETICO_SALA_H
