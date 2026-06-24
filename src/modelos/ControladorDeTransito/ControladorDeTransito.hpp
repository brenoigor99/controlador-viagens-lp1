#pragma once

#include <vector>
#include <string>
#include <map>
#include "../Cidade/Cidade.hpp"
#include "../Passageiro/Passageiro.hpp"
#include "../Transporte/Transporte.hpp"
#include "../Trajeto/Trajeto.hpp"
#include "../Viagem/Viagem.hpp"

class ControladorDeTransito {
private:
    std::vector<Cidade*> cidades;
    std::vector<Passageiro*> passageiros;
    std::vector<Transporte*> transportes;
    std::vector<Trajeto*> trajetos;
    std::vector<Viagem*> viagens;
    std::map<std::string, int> visitasCidades; // Guarda quantas vezes cada cidade foi visitada

public:
    ~ControladorDeTransito();
    
    void cadastrarCidade(std::string nome);
    void cadastrarPassageiro(std::string nome, std::string nome_cidade);
    void cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade, int dist_descanso, int tempo_descanso, std::string nome_cidade);
    void cadastrarTrajeto(std::string origem, std::string destino, char tipo, int distancia);
    
    bool iniciarViagem(std::string nome_transporte, std::string nome_origem, std::string nome_destino, std::vector<std::string> nomes_passageiros);
    void avancarHoras(int horas);
    
    void relatarEstado();
    void relatarViagensEmAndamento();
    void relatarCidadesMaisVisitadas();

    // Getters para o repositório
    std::vector<Cidade*> getCidades() { return cidades; }
    std::vector<Passageiro*> getPassageiros() { return passageiros; }
    std::vector<Transporte*> getTransportes() { return transportes; }
    std::vector<Trajeto*> getTrajetos() { return trajetos; }
};