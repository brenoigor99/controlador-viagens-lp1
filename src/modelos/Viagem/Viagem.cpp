#include "Viagem.hpp"
#include <cmath>
#include <iostream>

Viagem::Viagem(Transporte* transporte, Trajeto* trajeto, std::vector<Passageiro*> passageiros)
    : transporte(transporte), trajeto(trajeto), passageiros(passageiros), origem(trajeto->getOrigem()), destino(trajeto->getDestino()), proxima(nullptr), horasEmTransito(0), emAndamento(true) {
    
    // Tempo de deslocamento puro
    double tempoMovimento = (double)trajeto->getDistancia() / transporte->getVelocidade();
    int horasMovimento = std::ceil(tempoMovimento);

    // Tempo gasto com descansos obrigatórios
    int descansos = 0;
    if (transporte->getDistanciaEntreDescansos() > 0 && trajeto->getDistancia() > transporte->getDistanciaEntreDescansos()) {
        descansos = (trajeto->getDistancia() - 1) / transporte->getDistanciaEntreDescansos();
    }
    int tempoDescansoTotal = descansos * transporte->getTempoDescanso();

    tempoTotalNecessario = horasMovimento + tempoDescansoTotal;
}

Viagem::~Viagem() {
    if (proxima != nullptr) {
        delete proxima;
    }
}

void Viagem::iniciarViagem() {
    emAndamento = true;
}

void Viagem::avancarHoras(int horas) {
    if (!emAndamento) return;
    horasEmTransito += horas;
}

bool Viagem::isConcluida() const {
    return horasEmTransito >= tempoTotalNecessario;
}

Transporte* Viagem::getTransporte() const { return transporte; }
std::vector<Passageiro*> Viagem::getPassageiros() const { return passageiros; }
Trajeto* Viagem::getTrajeto() const { return trajeto; }
Cidade* Viagem::getOrigem() const { return origem; }
Cidade* Viagem::getDestino() const { return destino; }
void Viagem::setProxima(Viagem* prox) { proxima = prox; }
Viagem* Viagem::getProxima() const { return proxima; }