//
// Created by jordy on 12/04/17.
//

#ifndef ALGORITMOGENETICO_CURSO_H
#define ALGORITMOGENETICO_CURSO_H




using namespace std;

class Curso{
    int id;

    //vector<Turma> turmas;

public:
    Curso(int id) : id(id) {}
    virtual ~Curso() {}
    int getId() const {
        return id;
    }
    void setId(int id) {
        Curso::id = id;
    }
};

#endif //ALGORITMOGENETICO_CURSO_H
