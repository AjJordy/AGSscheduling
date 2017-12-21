//
// Created by jordy on 04/04/17.
//

#ifndef ALGORITMOGENETICO_AG_H
#define ALGORITMOGENETICO_AG_H

#include "Docente.h"
#include "Estudante.h"
#include "Cromossomo.h"
#include "Disciplina.h"


using namespace std;

struct sala_timeslot {
	int sala;
	int timeslot;
};

class Ag {
    int num_individuos; //numero de cromossomos
    int geracao;        //numero de gerações
    double mutacao;     //taxa de mutação
    double recombinacao;//taxa de recombinação

	vector<Docente> docentes;
	vector<Estudante> estudantes;
	vector<Sala> salas;
	vector<Disciplina> disciplinas;


public:
	virtual ~Ag();

	Ag(int num_individuos, int geracao, double mutacao, double recombinacao, const vector<Docente> &docentes,
	   const vector<Estudante> &estudantes, const vector<Sala> &salas, const vector<Disciplina> &disciplinas,
	   string **lista_timeslot);

private:
	vector<Cromossomo> populacao;
	string** lista_timeslot;

public:
	//====================Metodos do algoritmo genétio ======================

	void gerarPopulacao(int tamanho_da_populacao);                 // Gera uma população de vetores de listas de tamanho definido pelo usuario
	void reproduzir();                                             // Crossing Over baseado na troca das posições do vetor de timeslots
	void mutarCromossomo();                                        // Intercala listas do vetor verticalmente
	Cromossomo aleatorio_melhores();                               // Retorna um cromossomo aleatoriamente da lista dos melhores cromossomos
	vector<Cromossomo> ordenar_por_fitness();                      // Ordena a população de acordo com os fitness
	bool wayToSort(Cromossomo cromossomo1, Cromossomo cromossomo2);// Como deve ser feito a ordenação
	Cromossomo retorna_melhor();                                   // Retorna o melhor indivíduo a população
	vector<Elemento>* criaIndividuo();                             // Gera um indivíduo válido (vetor de listas)

	//=================== Getters and Setters ==============================


	int getNum_individuos() const;

	void setNum_individuos(int num_individuos);

	int getGeracao() const;

	void setGeracao(int geracao);

	double getMutacao() const;

	void setMutacao(double mutacao);

	double getRecombinacao() const;

	void setRecombinacao(double recombinacao);

	const vector<Docente> &getDocentes() const;

	void setDocentes(const vector<Docente> &docentes);

	const vector<Estudante> &getEstudantes() const;

	void setEstudantes(const vector<Estudante> &estudantes);

	const vector<Sala> &getSalas() const;

	void setSalas(const vector<Sala> &salas);

	const vector<Disciplina> &getDisciplinas() const;

	void setDisciplinas(const vector<Disciplina> &disciplinas);

	string **getLista_timeslot() const;

	void setLista_timeslot(string **lista_timeslot);

	const vector<Cromossomo> &getPopulacao() const;

	void setPopulacao(const vector<Cromossomo> &populacao);

	template <class tipo>
	vector<int> get_random_id_vector(vector<tipo> vetor);

	template <class tipo>
	vector<tipo> * clone_vector(vector<tipo> vetor);

	vector<int> get_timeslots_possiveis();

	template <class tipo>
	tipo *get_pointer_by_id(int id, vector<tipo> &vetor);

	template <class tipo>
	vector<int> *get_multiple_random_id_vector(vector<tipo> vetor);

	int get_random_int_and_remove(vector<int> &vetor);

	template <class tipo>
	vector<tipo> get_random_vector(vector<tipo> vetor);

	int get_random_int(vector<int> &vetor);

	vector<sala_timeslot>
	get_salas_e_timeslots(vector<int> timeslots_docente, vector<int> *salas_disponiveis, vector<int> &timeslots_disponiveis,
						  int cht, int tipo_t, int chp, int tipo_p);
};


#endif //ALGORITMOGENETICO_AG_H
