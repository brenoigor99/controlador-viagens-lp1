#pragma once

#include <string>
#include "../Cidade/Cidade.hpp"

class Transporte {
private:
    std::string nome;
    char tipo; // 'A' ou 'T'
    int capacidade;
    int velocidade;
    int distancia_entre_descansos;
    int tempo_de_descanso;
    int tempo_de_descanso_atual;
    Cidade* localAtual;
    bool emTransito;
public:
    Transporte(std::string nome, char tipo, int capacidade, int velocidade, 
               int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual);
    
    std::string getNome();
    char getTipo();
    int getCapacidade();
    int getVelocidade();
    int getDistanciaEntreDescansos();
    int getTempoDescanso();
    int getTempoDescansoAtual();
    Cidade* getLocalAtual();
    void setLocalAtual(Cidade* local);
    bool isEmTransito();
    void setEmTransito(bool estado);
    void setTempoDescansoAtual(int tempo);
};