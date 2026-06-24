#include "Cidade.hpp"

using namespace std;

Cidade::Cidade(string nome) {
    this->nome = nome;
}

string Cidade::getNome() {
    return this->nome;
}