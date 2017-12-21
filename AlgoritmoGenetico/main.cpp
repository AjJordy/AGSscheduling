#include <sstream>
#include "Ag.h"
#include "file_to_object.h"

using namespace std;


int main() {
	int contador = 0;
	int geracoes;                                   //numero de gerações
	double mutacao;                                 //taxa de mutação
	double recombinacao;                            //taxa de recombinação
    int tamanho_da_populacao;                       //tamanho da população inicial

    // ========== Recebimento dos dados =======
	File_to_object fto("../ag-informacoes.csv");
	fto.file_to_object();

/**    Teste dos dados*/
//    stringstream temp;
//    while (!fto.getSalas().empty()) {
//        temp << fto.getSalas().back().getId();
//    }


    // ========== Entradas do usuário =========
//    cout << "Ensira o número de gerações:" << endl;
//    cin >> geracoes;
//    cout << "Ensira a taxa de mutação:" << endl;
//    cin >> mutacao;
//    cout << "Ensira a taxa de recombinação:" << endl;
//    cin >> recombinacao;
//    cout << "Ensira o tamanho da população inicial:" << endl;
//    cin >> tamanho_da_populacao;
	geracoes = 10;
	mutacao = 0.1;
	recombinacao = 0.6;
	tamanho_da_populacao = 15;

    // ========== Execução da AG ==============

	Ag ag = Ag(tamanho_da_populacao, geracoes, mutacao, recombinacao,
			   fto.getDocentes(), fto.getEstudandes(), fto.getSalas(),
			   fto.getDisciplinas(), fto.getTimeslots());

    cout << "Ag instanciada" << endl;

	ag.gerarPopulacao(tamanho_da_populacao);
    while (contador < geracoes){

        cout << "População gerou " << ag.getNum_individuos() << endl;
        ag.reproduzir();
        cout << "População reproduziu "  << endl;
        ag.mutarCromossomo();
        cout << "População mutou" << endl;
        Cromossomo melhor = ag.retorna_melhor();
        cout << "Melhor indivíduo tem fitness de " << melhor.gerarFitness() << endl;

        contador++;
    }

    // ========== Saída =====================
    Cromossomo melhor = ag.retorna_melhor();
    cout << melhor.toString();
    //TODO Corrigir saída, está saindo um arquivo vazio
    ofstream output ("saida.csv");
    if (output.is_open())
    {
        output << melhor.toString();
        output.close();
    }
    else cout << "Unable to open file";

	return 0;
}

