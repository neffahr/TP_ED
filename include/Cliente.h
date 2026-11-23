#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

struct Cliente {
    int id;
    std::string nome;
    int poder;

    Cliente() : id(-1), nome(""), poder(0) {};
    Cliente(int id, const std::string& nome, int poder);

    bool operator<(const Cliente& outro) const;
};

#endif