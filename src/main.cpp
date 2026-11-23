#include "Consultoria.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    string comando;
    char modo_inicial;
    cin >> comando >> modo_inicial;
    Consultoria consultoria(modo_inicial);
    cout << comando << " " << modo_inicial << "\n";

    while (cin >> comando) {

        if (comando == "E") {
            char modo;
            cin >> modo;
            consultoria.alterarModo(modo);
        } 
        
        else if (comando == "A") {
            string nome;
            cin >> nome;
            consultoria.cadastrarAtributo(nome);
        } 

        else if (comando == "C") {
            string nome;
            int k;
            cin >> nome >> k;

            int* ids_atributos = new int[k];
            int* valores = new int[k];
            for (int i = 0; i < k; i++) {
                cin >> ids_atributos[i] >> valores[i];
            }

            consultoria.cadastrarCliente(nome, k, ids_atributos, valores);
            delete[] ids_atributos;
            delete[] valores;
        } 

        else if (comando == "D") {
            int id_cliente;
            cin >> id_cliente;
            consultoria.encerrarCliente(id_cliente);
        } 
        
        else if (comando == "BP") {
            int poder;
            cin >> poder;
            consultoria.buscarPorPoder(poder);
        } 
        
        else if (comando == "BF") {
            int min, max;
            cin >> min >> max;
            consultoria.buscarPorFaixa(min, max);
        } 
        
        else if (comando == "R") {
            string nome;
            cin >> nome;
            consultoria.cadastrarRegiao(nome);
        } 
        
        else if (comando == "T") {
            int id_regiao_1, id_regiao_2, custo;
            cin >> id_regiao_1 >> id_regiao_2 >> custo;
            consultoria.cadastrarRota(id_regiao_1, id_regiao_2, custo);
        } 
        
        else if (comando == "CC") {
            int id_regiao_1, id_regiao_2;
            cin >> id_regiao_1 >> id_regiao_2;
            consultoria.consultarCaminho(id_regiao_1, id_regiao_2);
        } 
        
        else if (comando == "F") {
            int id_cliente, prioridade;
            cin >> id_cliente >> prioridade;
            consultoria.inserirFila(id_cliente, prioridade);
        } 
        
        else if (comando == "Z") {
            int k;
            cin >> k;
            consultoria.atenderClientes(k);
        }
    }

    return 0;
}