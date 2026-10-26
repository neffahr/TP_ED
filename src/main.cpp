#include "Forja.h"
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

int main() {
    string comando;
    char modo_inicial;
    cin >> comando >> modo_inicial;
    Forja forja(modo_inicial);

    // Acumuladores de tempo em milissegundos para cada operação
    double t_E = 0, t_A = 0, t_I = 0, t_M = 0;
    double t_H = 0, t_F = 0, t_Z = 0, t_D = 0;
    double t_LI = 0, t_LA = 0, t_LH = 0, t_Q = 0;

    // Contadores de execuções
    int c_E = 0, c_A = 0, c_I = 0, c_M = 0;
    int c_H = 0, c_F = 0, c_Z = 0, c_D = 0;
    int c_LI = 0, c_LA = 0, c_LH = 0, c_Q = 0;

    while (cin >> comando) {
        if (comando == "E") {
            char modo;
            cin >> modo; // Leitura ANTES de iniciar o cronômetro
            
            auto start = high_resolution_clock::now();
            forja.alterarModo(modo);
            auto end = high_resolution_clock::now();
            
            t_E += duration<double, std::milli>(end - start).count();
            c_E++;
        } 
        else if (comando == "A") {
            string nome;
            cin >> nome;
            
            auto start = high_resolution_clock::now();
            forja.cadastrarAtributo(nome);
            auto end = high_resolution_clock::now();
            
            t_A += duration<double, std::milli>(end - start).count();
            c_A++;
        } 
        else if (comando == "I") {
            string nome;
            cin >> nome;
            
            auto start = high_resolution_clock::now();
            forja.cadastrarItem(nome);
            auto end = high_resolution_clock::now();
            
            t_I += duration<double, std::milli>(end - start).count();
            c_I++;
        } 
        else if (comando == "M") {
            int id_item, id_atributo, valor;
            cin >> id_item >> id_atributo >> valor;
            
            auto start = high_resolution_clock::now();
            forja.definirModificador(id_item, id_atributo, valor);
            auto end = high_resolution_clock::now();
            
            t_M += duration<double, std::milli>(end - start).count();
            c_M++;
        } 
        else if (comando == "H") {
            string nome;
            cin >> nome;
            
            auto start = high_resolution_clock::now();
            forja.cadastrarAventureiro(nome);
            auto end = high_resolution_clock::now();
            
            t_H += duration<double, std::milli>(end - start).count();
            c_H++;
        } 
        else if (comando == "F") {
            int id_aventureiro, id_item;
            cin >> id_aventureiro >> id_item;
            
            auto start = high_resolution_clock::now();
            forja.adicionarEncomenda(id_aventureiro, id_item);
            auto end = high_resolution_clock::now();
            
            t_F += duration<double, std::milli>(end - start).count();
            c_F++;
        } 
        else if (comando == "Z") {
            int k;
            cin >> k;
            
            auto start = high_resolution_clock::now();
            forja.trabalharTurnos(k);
            auto end = high_resolution_clock::now();
            
            t_Z += duration<double, std::milli>(end - start).count();
            c_Z++;
        } 
        else if (comando == "D") {
            int id_aventureiro;
            cin >> id_aventureiro;
            
            auto start = high_resolution_clock::now();
            forja.desequiparPecaAventureiro(id_aventureiro);
            auto end = high_resolution_clock::now();
            
            t_D += duration<double, std::milli>(end - start).count();
            c_D++;
        } 
        else if (comando == "LI") {
            int id_item;
            cin >> id_item;
            
            auto start = high_resolution_clock::now();
            forja.consultarItem(id_item);
            auto end = high_resolution_clock::now();
            
            t_LI += duration<double, std::milli>(end - start).count();
            c_LI++;
        } 
        else if (comando == "LA") {
            int id_atributo;
            cin >> id_atributo;
            
            auto start = high_resolution_clock::now();
            forja.consultarAtributo(id_atributo);
            auto end = high_resolution_clock::now();
            
            t_LA += duration<double, std::milli>(end - start).count();
            c_LA++;
        } 
        else if (comando == "LH") {
            int id_aventureiro;
            cin >> id_aventureiro;
            
            auto start = high_resolution_clock::now();
            forja.consultarBuild(id_aventureiro);
            auto end = high_resolution_clock::now();
            
            t_LH += duration<double, std::milli>(end - start).count();
            c_LH++;
        } 
        else if (comando == "Q") {
            int id_aventureiro, n, m;
            cin >> id_aventureiro >> n >> m;

            string* nomes_metricas = new string[m];
            double* pesos_metricas = new double[m];

            for (int i = 0; i < m; i++) {
                cin >> nomes_metricas[i] >> pesos_metricas[i];
            }

            auto start = high_resolution_clock::now();
            forja.consultarRecomendacao(id_aventureiro, n, m, nomes_metricas, pesos_metricas);
            auto end = high_resolution_clock::now();
            
            t_Q += duration<double, std::milli>(end - start).count();
            c_Q++;

            delete[] nomes_metricas;
            delete[] pesos_metricas;
        } 
    }

    // =========================================================================
    // IMPRESSÃO DOS RESULTADOS NA SAÍDA DE ERRO (cerr)
    // =========================================================================
    cerr << "\n=== RELATÓRIO DE TEMPOS DE EXECUÇÃO (em milissegundos) ===\n";
    cerr << fixed << setprecision(4);
    cerr << "Op | Chamadas | Tempo Total (ms) | Tempo Médio/Op (ms)\n";
    cerr << "--------------------------------------------------------\n";
    if (c_E > 0)  cerr << "E  | Count:" << setw(8) << c_E  << " | Time Per op" << (t_E / c_E) << "\n";
    if (c_A > 0)  cerr << "A  | Count:" << setw(8) << c_A  << " | Time Per op" << (t_A / c_A) << "\n";
    if (c_I > 0)  cerr << "I  | Count:" << setw(8) << c_I  << " | Time Per op" << (t_I / c_I) << "\n";
    if (c_M > 0)  cerr << "M  | Count:" << setw(8) << c_M  << " | Time Per op" << (t_M / c_M) << "\n";
    if (c_H > 0)  cerr << "H  | Count:" << setw(8) << c_H  << " | Time Per op" << (t_H / c_H) << "\n";
    if (c_F > 0)  cerr << "F  | Count:" << setw(8) << c_F  << " | Time Per op" << (t_F / c_F) << "\n";
    if (c_Z > 0)  cerr << "Z  | Count:" << setw(8) << c_Z  << " | Time Per op" << (t_Z / c_Z) << "\n";
    if (c_D > 0)  cerr << "D  | Count:" << setw(8) << c_D  << " | Time Per op" << (t_D / c_D) << "\n";
    if (c_LI > 0) cerr << "LI | Count:" << setw(8) << c_LI << " | Time Per op" << (t_LI / c_LI) << "\n";
    if (c_LA > 0) cerr << "LA | Count:" << setw(8) << c_LA << " | Time Per op" << (t_LA / c_LA) << "\n";
    if (c_LH > 0) cerr << "LH | Count:" << setw(8) << c_LH << " | Time Per op" << (t_LH / c_LH) << "\n";
    if (c_Q > 0)  cerr << "Q  | Count:" << setw(8) << c_Q  << " | Time Per op" << (t_Q / c_Q) << "\n";
    cerr << "Total time: "
         << (t_E + t_A + t_I + t_M + t_H + t_F + t_Z + t_D +
             t_LI + t_LA + t_LH + t_Q)
         << " ms\n";

    return 0;
}