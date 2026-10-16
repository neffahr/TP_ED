#ifndef ITEM_H
#define ITEM_H

#include <string>

struct Item {
    int id;
    std::string nome;

    Item();
    Item(int id, const std::string& nome);
};

#endif