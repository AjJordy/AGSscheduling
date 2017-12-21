
#include "Elemento.h"

int Elemento::getDisciplina_id() const {
    return disciplina_id;
}

void Elemento::setDisciplina_id(int disciplina_id) {
    Elemento::disciplina_id = disciplina_id;
}

int Elemento::getDocentes_id() const {
    return docentes_id;
}

void Elemento::setDocentes_id(int docentes_id) {
    Elemento::docentes_id = docentes_id;
}

int Elemento::getSala_id() const {
    return sala_id;
}

void Elemento::setSala_id(int sala_id) {
    Elemento::sala_id = sala_id;
}

const std::vector<int, std::allocator<int>> &Elemento::getEstudantes_ids() const {
    return estudantes_ids;
}

void Elemento::setEstudantes_ids(const std::vector<int, std::allocator<int>> &estudantes_ids) {
    Elemento::estudantes_ids = estudantes_ids;
}

Elemento::Elemento(int disciplina_id, int docentes_id, int sala_id, const vector<int> estudantes_ids) : disciplina_id(
        disciplina_id), docentes_id(docentes_id), sala_id(sala_id), estudantes_ids(estudantes_ids) {}

Elemento::~Elemento() {

}
