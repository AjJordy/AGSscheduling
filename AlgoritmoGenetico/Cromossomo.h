//
// Created by jordy on 12/04/17.
//

#ifndef ALGORITMOGENETICO_CROMOSSOMO_H
#define ALGORITMOGENETICO_CROMOSSOMO_H

#include <string>
#include "Elemento.h"
#define MAX_TIMESLOT 167


class Cromossomo {

    vector<Elemento>* horario =  new vector<Elemento>[MAX_TIMESLOT]; // Vetor[MAX_TIMESLOT] de listas de elementos(professor,sala,turma,disciplina,alunos)
    int fitness;                                                     // Pontuação do indivíduo

public:

    int gerarFitness();

    string toString();
    Cromossomo(vector<Elemento> *horario);
    virtual ~Cromossomo();
    vector<Elemento> *getHorario() const;
    void setHorario(vector<Elemento> *horario);


};


#endif //ALGORITMOGENETICO_CROMOSSOMO_H
