#pragma once

#include "../Cidade/Cidade.hpp"

class Trajeto {
private:
    Cidade* origem;
    Cidade* destino;
    char tipo; // 'A' para Aquatico, 'T' para Terestre
    int distancia;
public:
    Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia);
    Cidade* getOrigem();
    Cidade* getDestino();
    char getTipo();
    int getDistancia();
};