//
// Created by jordy on 20/04/17.
//

#include "Disciplina.h"

//Disciplina::Disciplina(int id, int carga_horaria, int carga_horaria_lab, const vector<int> &restricoes,
//                       const Turma &turma) : id(id), carga_horaria(carga_horaria), carga_horaria_lab(carga_horaria_lab),
 //                                            restricoes(restricoes), turma(turma) {}

Disciplina::~Disciplina() {

}

int Disciplina::getId() const {
    return id;
}

void Disciplina::setId(int id) {
    Disciplina::id = id;
}

int Disciplina::getCarga_horaria_teorica() const {
    return carga_horaria_teorica;
}

void Disciplina::setCarga_horaria_teorica(int carga_horaria_pratica) {
    Disciplina::carga_horaria_pratica = carga_horaria_pratica;
}

int Disciplina::getCarga_horaria_pratica() const {
    return carga_horaria_pratica;
}

void Disciplina::setCarga_horaria_pratica(int carga_horaria_pratica) {
    Disciplina::carga_horaria_pratica = carga_horaria_pratica;
}

//const vector<int> &Disciplina::getRestricoes() const {
//    return restricoes;
//}

//void Disciplina::setRestricoes(const vector<int> &restricoes) {
//    Disciplina::restricoes = restricoes;
//}

//const Turma &Disciplina::getTurma() const {
//    return turma;
//}

//void Disciplina::setTurma(const Turma &turma) {
//    Disciplina::turma = turma;
//}
