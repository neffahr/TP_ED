#include "Hash.h"

Hash::Hash(int tamanho_inicial) {
    M = (tamanho_inicial > 0) ? proximoPrimo(tamanho_inicial) : M_INICIAL;
    tamanho = 0;
    tabela = new NoHash*[M];

    for (int i = 0; i < M; i++) {
        tabela[i] = nullptr;
    }
}

Hash::~Hash() {
    limpa();
    delete[] tabela;
}

void Hash::limpa() {
    for (int i = 0; i < M; i++) {
        NoHash* atual = tabela[i];
        while (atual != nullptr) {
            NoHash* prox = atual->prox;
            delete atual;
            atual = prox;
        }
        tabela[i] = nullptr;
    }
    tamanho = 0;
}

bool Hash::ehPrimo(int n) const {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int Hash::proximoPrimo(int n) const {
    if (n <= 2) return 2;
    int candidato = (n % 2 == 0) ? n + 1 : n;
    while (!ehPrimo(candidato)) {
        candidato += 2;
    }
    return candidato;
}

void Hash::rehash() {
    int M_antigo = M;
    NoHash** tabela_antiga = tabela;

    M = proximoPrimo(M_antigo * 2);
    tabela = new NoHash*[M];
    for (int i = 0; i < M; i++) {
        tabela[i] = nullptr;
    }

    for (int i = 0; i < M_antigo; i++) {
        NoHash* atual = tabela_antiga[i];
        while (atual != nullptr) {
            NoHash* prox = atual->prox;
            int nova_pos = funcaoHash(atual->registro.poder);
            atual->prox = tabela[nova_pos];
            tabela[nova_pos] = atual;
            atual = prox;
        }
    }

    delete[] tabela_antiga;
}


void Hash::insere(int poder, int id_cliente) {
    if (tamanho + 1 > M) { rehash(); }

    int pos = funcaoHash(poder);
    tabela[pos] = new NoHash(poder, id_cliente, tabela[pos]);
    tamanho++;
}

void Hash::remove(int poder, int id_cliente) {
    int pos = funcaoHash(poder);
    NoHash* atual = tabela[pos];
    NoHash* anterior = nullptr;

    while (atual != nullptr) {
        if (atual->registro.poder == poder && atual->registro.id_cliente == id_cliente) {
            if (anterior == nullptr) {
                tabela[pos] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            delete atual;
            tamanho--;
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}


void Hash::buscaPontual(int poder, Lista<int>& resultado) const {
    int pos = funcaoHash(poder);

    for (NoHash* p = tabela[pos]; p != nullptr; p = p->prox) {
        if (p->registro.poder == poder) {
           resultado.insereFinal(p->registro.id_cliente);
        }
    }

    // Ordenação por id_cliente
    resultado.ordenar();
}

void Hash::buscaFaixa(int min, int max, Lista<DadoIndice>& resultado) const {
    if (min > max || tamanho == 0) return;

    for (int i = 0; i < M; i++) {
        for (NoHash* p = tabela[i]; p != nullptr; p = p->prox) {
            if (p->registro.poder >= min && p->registro.poder <= max) {
                resultado.insereFinal(DadoIndice(p->registro.poder, p->registro.id_cliente));
            }
        }
    }

    // Ordena por (poder, desempate por id_cliente)
    resultado.ordenar();
}


void Hash::exportarElementos(Lista<DadoIndice>& registros) const {
    for (int i = 0; i < M; i++) {
        for (NoHash* p = tabela[i]; p != nullptr; p = p->prox) {
            DadoIndice reg = DadoIndice(p->registro.poder, p->registro.id_cliente);
            registros.insereFinal(reg);
        }
    }
}