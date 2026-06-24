#ifndef VIAGEM_HPP
#define VIAGEM_HPP

#include "../Transporte/Transporte.hpp"
#include "../Passageiro/Passageiro.hpp"
#include "../Trajeto/Trajeto.hpp"
#include <vector>

class Viagem {
private:
    Transporte* transporte;
    Trajeto* trajeto;
    std::vector<Passageiro*> passageiros;
    Cidade* origem;
    Cidade* destino;
    Viagem* proxima;
    int horasEmTransito;
    bool emAndamento;
    int tempoTotalNecessario;

public:
    Viagem(Transporte* transporte, Trajeto* trajeto, std::vector<Passageiro*> passageiros);
    ~Viagem();

    void iniciarViagem();
    void avancarHoras(int horas);
    
    bool isConcluida() const;
    Transporte* getTransporte() const;
    std::vector<Passageiro*> getPassageiros() const;
    Trajeto* getTrajeto() const;
    Cidade* getOrigem() const;
    Cidade* getDestino() const;
    
    void setProxima(Viagem* prox);
    Viagem* getProxima() const;
};

#endif