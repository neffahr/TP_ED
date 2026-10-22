#ifndef ITEM_H
#define ITEM_H

#include <string>

struct Item {
    int id;
    std::string nome;

    Item() : id(-1), nome("") {}
    Item(int id, const std::string& nome);
};

#endif