//
// Created by jordy on 04/04/17.
//

#include <iostream>
#include <algorithm>
#include "Ag.h"

using namespace std;




//=========================== Funções auxiliares =================================

template <class tipo>
vector<int> Ag::get_random_id_vector(vector<tipo> vetor) {
	vector<int> ids;
	while(!vetor.empty()) {
		int random_index = (int) (rand() % vetor.size());
		ids.push_back(vetor.at(random_index).getId());
		vetor.erase(vetor.begin() + random_index);
	}
	return ids;
}

template <class tipo>
vector<tipo> Ag::get_random_vector(vector<tipo> vetor) {
	vector<tipo> random_vector;
	while(!vetor.empty()) {
		int random_index = (int) (rand() % vetor.size());
		random_vector.push_back(vetor.at(random_index));
		vetor.erase(vetor.begin() + random_index);
	}
	return random_vector;
}

int Ag::get_random_int_and_remove(vector<int> &vetor){
	int random_index = (int) (rand() % vetor.size());
	int random_value = vetor.at((unsigned long) random_index);
	vetor.erase(vetor.begin() + random_index);
	return random_value;
}

int Ag::get_random_int(vector<int> &vetor){
	int random_index = (int) (rand() % vetor.size());
	int random_value = vetor.at((unsigned long) random_index);
	return random_value;
}

template <class tipo>
tipo* Ag::get_pointer_by_id(int id, vector<tipo> &vetor){
	tipo *ponteiro = nullptr;
	for (int i = 0; i < vetor.size(); ++i) {
		if(vetor.at(i).getId() == id){
			ponteiro = &vetor.at(i);
			break;
		}
	}
	return ponteiro;
}

template <class tipo>
vector<tipo>* Ag::clone_vector(vector<tipo> vetor){
	vector<tipo>* vetores = new vector<tipo>[MAX_TIMESLOT];
	for (int i = 0; i < MAX_TIMESLOT; ++i) {
		vetores[i] = vetor;
	}
	return vetores;
}

template <class tipo>
vector<int>* Ag::get_multiple_random_id_vector(vector<tipo> vetor){
	vector<int>* vetores = new vector<int>[MAX_TIMESLOT];
	for (int i = 0; i < MAX_TIMESLOT; ++i) {
		vetores[i] = get_random_id_vector(vetor);
	}
	return vetores;
}

vector<sala_timeslot> Ag::get_salas_e_timeslots(vector<int> timeslots_docente, vector<int> *salas_disponiveis,
												vector<int> &timeslots_disponiveis,
												int cht, int tipo_t, int chp, int tipo_p) {
	vector<sala_timeslot> s_t;
	for (int j = 0; j < timeslots_disponiveis.size(); ++j) {
		int timeslot = timeslots_disponiveis.at(j);

		if (find(timeslots_docente.begin(), timeslots_docente.end(), timeslot) == timeslots_docente.end()) {

			for (int i = 0; i < salas_disponiveis[timeslot].size(); ++i) {
				int sala_id = salas_disponiveis[timeslot].at(i);
				Sala *sala = get_pointer_by_id(sala_id, salas);
				int tipo_sala = sala->getTipo();

				if (cht != 0 && tipo_sala == tipo_t) {
					s_t.push_back({i, j});
					cht--;
					j++;
					break;
				} else if (chp != 0 && tipo_sala == tipo_p) {
					s_t.push_back({i, j});
					chp--;
					j++;
					break;
				} else if ((cht + chp) == 0) {
					return s_t;
				}
			}
		}
	}
	return s_t;
}

/**Converte as horas de 07:00 para 7*/
int converter_horas(string string_horas) {
	string horas;
   	horas += string_horas[0];
   	horas += string_horas[1];
	return stoi(horas);
}


/**Descarta os timeslots referentes aos finais de semana e as madrugadas, almoço e janta*/
vector<int> Ag::get_timeslots_possiveis(){
	vector<int> timeslots_possiveis;
	for (int i = 0; i < MAX_TIMESLOT; ++i) {
		int dia = stoi(lista_timeslot[i][1]);
		int hora = converter_horas(lista_timeslot[i][2]);

//		Ignora sabados, domingos, entre 22:00 e 7:00, as 12:00 e as 18:00
		if(dia != 1 && dia != 7 &&
				hora > 7 && hora < 22 && hora != 12 && hora != 18) {
			timeslots_possiveis.push_back(i);
		}
	}
	return timeslots_possiveis;
}


//==================================== Funções do Agorítmo Genético =================================

/** É gerado uma população de cromossomos validos de tamanho definido pelo usuário*/
void Ag::gerarPopulacao(int tamanho_da_populacao){
	//TODO testar
	num_individuos = 0;
	while (num_individuos < tamanho_da_populacao){
		vector<Elemento>* horario = criaIndividuo();// Cria o cromossomo viável

		Cromossomo cromossomo = Cromossomo(horario);
		populacao.push_back(cromossomo);            // Acrescente individuos à população
		num_individuos++;
	}
    for (int i = 0; i < num_individuos; ++i) {
        populacao[i].gerarFitness();
    }
}


/**Cria um indivíduo valido, primeiro selecionando aleatóriamente um professor, depois escolhendo uma disciplina que ele
 * ministre, aleatóriamente, e tenta distribuir as cargas horárias dessa diciplina em outros timeslots.
 * Quando as diciplinas do professor acabam, ele é removido da lista de professores disponiveis.
 * Se não houver nenhum professor disponível em determinado timeslot, o timeslot em questão é removido da lista de disponiveis*/
vector<Elemento>* Ag::criaIndividuo(){
	srand((unsigned int) time(0));
	vector<Elemento>* horario = new vector<Elemento>[MAX_TIMESLOT];
	vector<int>* salas_disponiveis = get_multiple_random_id_vector(salas);
	vector<int> timeslots_possiveis = get_random_vector(get_timeslots_possiveis());
	vector<Docente> docentes_disponiveis = get_random_vector(docentes);

	while(!timeslots_possiveis.empty() && !docentes_disponiveis.empty()) {

		Docente &docente = docentes_disponiveis.back();
		int docente_id = docente.getId();

		int disciplina_id = get_random_int_and_remove(docente.get_disciplinas());
		Disciplina* disciplina = get_pointer_by_id(disciplina_id, disciplinas);

		vector<sala_timeslot> s_t = get_salas_e_timeslots(docente.getTimeslots_adicionado(), salas_disponiveis,
														  timeslots_possiveis,
														  disciplina->getCarga_horaria_teorica(),
														  disciplina->getTipo_t(),
														  disciplina->getCarga_horaria_pratica(),
														  disciplina->getTipo_p());

		if(s_t.size() == disciplina->getCarga_horaria_pratica() + disciplina->getCarga_horaria_teorica()) {
			while(s_t.size() > 0) {
				int indice_timeslot = s_t.back().timeslot;
				int timeslot = timeslots_possiveis.at((unsigned long) indice_timeslot);

				int indice_sala = s_t.back().sala;
				int sala_id = salas_disponiveis[timeslot].at((unsigned long) indice_sala);

				vector<int> estudantes;

				Elemento elemento(disciplina_id, docente_id, sala_id, estudantes);
				horario[timeslot].push_back(elemento);

				salas_disponiveis[timeslot].erase(salas_disponiveis[timeslot].begin() + indice_sala);
				if(salas_disponiveis[timeslot].empty())
					timeslots_possiveis.erase(timeslots_possiveis.begin() + s_t.back().timeslot);

				s_t.pop_back();

				docente.getTimeslots_adicionado().push_back(timeslot);
			}
		}

		if(docente.get_disciplinas().empty()) {
			docentes_disponiveis.pop_back();				// Remove docente que não esteja mais disponível
		}
		docentes_disponiveis = get_random_vector(docentes_disponiveis);
	}
	return horario;
}


bool Ag::validar_restricoes_disc(int timeslot,vector<Elemento> lista,vector<vector<int>> restricoes_disc){
    bool isValido = true;
    int aux = 0;
    for (int i = 0; i < lista.size(); ++i) {
        for (int j = 0; j < restricoes_disc.size(); ++j) {
            //Verificia se a diciplina se encontra na lista de restrições
            if(std::find(restricoes_disc.begin(), restricoes_disc.end(),lista.at(i).getDisciplina_id())
               != restricoes_disc.end()){
                aux = j;                    //Contem o elemento
                //Verifica se a dada diciplina tem restição para o timeslot específico
                if(std::find(restricoes_disc[j].begin(), restricoes_disc[j].end(),timeslot)
                   != restricoes_disc[j].end()){
                    isValido = false;       // Contem o elemento
                }
            }
        }
    }
    return isValido;
}


void Ag::reproduzir(){
	/** Cria copia dos pais, troca as listas dos timeslot pares e então substitui esses filhos pelos piores da população*/
    //TODO testar
	for (int j = 0; j < (num_individuos*this->recombinacao); j++){
		Cromossomo pai = aleatorio_melhores();
		Cromossomo mae = aleatorio_melhores();

		for(int i = 0; i < MAX_TIMESLOT; i = i+2) {
			swap(pai.getHorario()[i],mae.getHorario()[i]); //Troca as listas entre os cromossomos pai e mãe
		}
	}
}


/**Este método vai receber a probabilidade de ocorrer a mutação na população e calcular quantos individuos vão mutar
 * Com isso irá gerá um numero aleatório para saber quem irá mutar
 * Sabendo que indivíduos iram mutar, é escolhido na lista de timeslots possiveis dois valores aleatórios
 * Que seram usados nas posições do vetor que serão trocadas*/
void Ag::mutarCromossomo(){
    //TODO Testar
    int n_mutacoes = (int) this->mutacao*num_individuos/*/100*/;
    vector<int> time_slots_possiveis = get_timeslots_possiveis();
    int time_slot1;
    int time_slot2;
    for (int i = 0; i < n_mutacoes; ++i) {
        int individuo =  rand() % num_individuos;
        time_slot1 = get_random_int(time_slots_possiveis);
        time_slot2 = get_random_int(time_slots_possiveis);
        std::swap(populacao[individuo].getHorario()[time_slot1],populacao[individuo].getHorario()[time_slot2]);
    }
}



/**Retorna um cromossomo aleatório dentre os melhores*/
Cromossomo Ag::aleatorio_melhores(){
    //TODO testar

	int melhores = int(num_individuos*recombinacao);
    ordenar_por_fitness();
    int num_aleatorio =  rand() % melhores;
    return populacao[num_aleatorio];
}

bool Ag::wayToSort(Cromossomo cromossomo1, Cromossomo cromossomo2) {
    return cromossomo1.gerarFitness() >= cromossomo2.gerarFitness();
}

/**Retorna um lista dos melhores indivíduos ordenados */
vector<Cromossomo> Ag::ordenar_por_fitness(){
    //TODO testar
    //ordena a lista pelo fitness
    int num_melhores = int (num_individuos*recombinacao);
    std::sort (populacao.begin(), populacao.end(), [this](Cromossomo c1, Cromossomo c2) { return wayToSort(c1, c2); });
    vector<Cromossomo> lista_melhores;
    for(int i=0;i < num_melhores;i++){
        lista_melhores.push_back((Cromossomo)populacao.at(i)); //TODO Fazer isso funcionar
    }

    return lista_melhores;
}

/**Retorna o melhor individuo da população*/
Cromossomo Ag::retorna_melhor(){
    //TODO Testar
    ordenar_por_fitness();
    return populacao.front();
}

//=================== Getters and Setters ==============================

int Ag::getNum_individuos() const {
	return num_individuos;
}

void Ag::setNum_individuos(int num_individuos) {
	Ag::num_individuos = num_individuos;
}

int Ag::getGeracao() const {
	return geracao;
}

void Ag::setGeracao(int geracao) {
	Ag::geracao = geracao;
}

double Ag::getMutacao() const {
	return mutacao;
}

void Ag::setMutacao(double mutacao) {
	Ag::mutacao = mutacao;
}

double Ag::getRecombinacao() const {
	return recombinacao;
}

void Ag::setRecombinacao(double recombinacao) {
	Ag::recombinacao = recombinacao;
}

const vector<Docente> &Ag::getDocentes() const {
	return docentes;
}

void Ag::setDocentes(const vector<Docente> &docentes) {
	Ag::docentes = docentes;
}

const vector<Estudante> &Ag::getEstudantes() const {
	return estudantes;
}

void Ag::setEstudantes(const vector<Estudante> &estudantes) {
	Ag::estudantes = estudantes;
}

const vector<Sala> &Ag::getSalas() const {
	return salas;
}

void Ag::setSalas(const vector<Sala> &salas) {
	Ag::salas = salas;
}

const vector<Disciplina> &Ag::getDisciplinas() const {
	return disciplinas;
}

void Ag::setDisciplinas(const vector<Disciplina> &disciplinas) {
	Ag::disciplinas = disciplinas;
}

string **Ag::getLista_timeslot() const {
	return lista_timeslot;
}

void Ag::setLista_timeslot(string **lista_timeslot) {
	Ag::lista_timeslot = lista_timeslot;
}

const vector<Cromossomo> &Ag::getPopulacao() const {
	return populacao;
}

void Ag::setPopulacao(const vector<Cromossomo> &populacao) {
	Ag::populacao = populacao;
}

Ag::Ag(int num_individuos, int geracao, double mutacao, double recombinacao, const vector<Docente> &docentes,
	   const vector<Estudante> &estudantes, const vector<Sala> &salas, const vector<Disciplina> &disciplinas,
	   string **lista_timeslot) : num_individuos(num_individuos), geracao(geracao),
																	   mutacao(mutacao), recombinacao(recombinacao),
																	   docentes(docentes), estudantes(estudantes),
																	   salas(salas), disciplinas(disciplinas),
																	   lista_timeslot(lista_timeslot) {}

Ag::~Ag() {

}
