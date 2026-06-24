#include "Passageiro.hpp"

using namespace std;

Passageiro::Passageiro(string nome, Cidade* localAtual) {
    this->nome = nome;
    this->localAtual = localAtual;
    this->emTransito = false;
}

string Passageiro::getNome() { return this->nome; }
Cidade* Passageiro::getLocalAtual() { return this->localAtual; }
void Passageiro::setLocalAtual(Cidade* local) { this->localAtual = local; }
bool Passageiro::isEmTransito() { return this->emTransito; }
void Passageiro::setEmTransito(bool estado) { this->emTransito = estado; }