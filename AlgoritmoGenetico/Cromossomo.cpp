//
// Created by jordy on 12/04/17.
//

#include <sstream>
#include "Cromossomo.h"

Cromossomo::Cromossomo(vector<Elemento> *horario) : horario(horario) {}

Cromossomo::~Cromossomo() {}
// -- Funções --


/**Calcula a função de fitness de um indivíduo dado a quantidade de elementos válidos inseridos na lista
 * Ou seja, f(x) = Somatório dos tamanhos das listas*/
int Cromossomo::gerarFitness(){
    this->fitness = 0;
    int i = 0;
    while (i < MAX_TIMESLOT){
        this->fitness += horario[i].size();
        i++;
    }
    //TODO IMPLEMENTAR A SUBTRAÇÃO DA QUANTIDADE DE ALUNOS DISPONÍVEIS
    return fitness;
};


string Cromossomo::toString() {
//Disciplina, timeslot, professor, sala
// TODO Testar
    string stg;
    stringstream saida;
    for (int i = 0; i < horario->size(); ++i) {
        while(!horario[i].empty()){
            Elemento temp = horario[i].back();
            saida << temp.getDisciplina_id() << ","
                  << i << ","
                  << temp.getDocentes_id() << ","
                  << temp.getSala_id() << "\n" ;
        }
    }
    stg = saida.str();
    return stg;
}


//================= Getters and Setters =======================

vector<Elemento> *Cromossomo::getHorario() const {
    return horario;
}
void Cromossomo::setHorario(vector<Elemento> *horario) {
    Cromossomo::horario = horario;
}
