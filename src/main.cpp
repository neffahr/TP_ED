#include "Forja.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    Forja forja;
    string comando;

    while (cin >> comando) {
        if (comando == "E") {
            char modo;
            cin >> modo;
            forja.alterarModo(modo);
        } 
        else if (comando == "A") {
            string nome;
            cin >> nome;
            forja.cadastrarAtributo(nome);
        } 
        else if (comando == "I") {
            string nome;
            cin >> nome;
            forja.cadastrarItem(nome);
        } 
        else if (comando == "M") {
            int id_item, id_atributo, valor;
            cin >> id_item >> id_atributo >> valor;
            forja.definirModificador(id_item, id_atributo, valor);
        } 
        else if (comando == "H") {
            string nome;
            cin >> nome;
            forja.cadastrarAventureiro(nome);
        } 
        else if (comando == "F") {
            int id_aventureiro, id_item;
            cin >> id_aventureiro >> id_item;
            forja.adicionarEncomenda(id_aventureiro, id_item);
        } 
        else if (comando == "Z") {
            int k;
            cin >> k;
            forja.trabalharTurnos(k);
        } 
        else if (comando == "D") {
            int id_aventureiro;
            cin >> id_aventureiro;
            forja.desequiparPecaAventureiro(id_aventureiro);
        } 
        else if (comando == "LI") {
            int id_item;
            cin >> id_item;
            forja.consultarItem(id_item);
        } 
        else if (comando == "LA") {
            int id_atributo;
            cin >> id_atributo;
            forja.consultarAtributo(id_atributo);
        } 
        else if (comando == "LH") {
            int id_aventureiro;
            cin >> id_aventureiro;
            forja.consultarBuild(id_aventureiro);
        } 
        else if (comando == "Q") {
            int id_aventureiro, n, m;
            cin >> id_aventureiro >> n >> m;

            string* nomes_metricas = new string[m];
            double* pesos_metricas = new double[m];

            for (int i = 0; i < m; i++) {
                cin >> nomes_metricas[i] >> pesos_metricas[i];
            }

            forja.consultarRecomendacao(id_aventureiro, n, m, nomes_metricas, pesos_metricas);

            delete[] nomes_metricas;
            delete[] pesos_metricas;
        } 
    }

    return 0;
}