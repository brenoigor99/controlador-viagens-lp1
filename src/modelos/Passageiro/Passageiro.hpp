#pragma once

#include <string>
#include "../Cidade/Cidade.hpp"

class Passageiro {
private:
    std::string nome;
    Cidade* localAtual;
    bool emTransito;
public:
    Passageiro(std::string nome, Cidade* localAtual);
    std::string getNome();
    Cidade* getLocalAtual();
    void setLocalAtual(Cidade* local);
    bool isEmTransito();
    void setEmTransito(bool estado);
};