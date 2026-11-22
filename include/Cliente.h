#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

struct Cliente {
    int id;
    std::string nome;
    int poder;
    int qtd_atributos;
    int* build;

    Cliente();
    Cliente(int id, const std::string& nome, const int* build_entrada, int num_atributos);
    ~Cliente();

    Cliente(const Cliente& copiado);
    Cliente& operator=(const Cliente& copiado);
};

#endif