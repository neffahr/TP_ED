#include "Cliente.h"

Cliente::Cliente(int id, const std::string& nome, int poder) : id(id), nome(nome), poder(poder) {}

bool Cliente::operator<(const Cliente& outro) const {
    if (this->poder != outro.poder) {
        return this->poder < outro.poder;
    }
    return this->id < outro.id;
}