#include "Repositorio.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void Repositorio::carregarDados(ControladorDeTransito& controlador) {
    // 1. Carrega Cidades
    ifstream fileCidades("cidades.txt");
    if (fileCidades.is_open()) {
        string nomeCidade;
        while (getline(fileCidades, nomeCidade)) {
            if (!nomeCidade.empty()) {
                controlador.cadastrarCidade(nomeCidade);
            }
        }
        fileCidades.close();
    }

    // 2. Carrega Trajetos
    ifstream fileTrajetos("trajetos.txt");
    if (fileTrajetos.is_open()) {
        string orig, dest, tipoStr, distStr;
        while (getline(fileTrajetos, orig, ',') && 
               getline(fileTrajetos, dest, ',') && 
               getline(fileTrajetos, tipoStr, ',') && 
               getline(fileTrajetos, distStr)) {
            if (!orig.empty()) {
                if (!distStr.empty() && distStr.back() == '\n') distStr.pop_back();
                if (!distStr.empty() && distStr.back() == '\r') distStr.pop_back();
                controlador.cadastrarTrajeto(orig, dest, tipoStr[0], stoi(distStr));
            }
        }
        fileTrajetos.close();
    }

    // 3. Carrega Passageiros
    ifstream filePassageiros("passageiros.txt");
    if (filePassageiros.is_open()) {
        string nome, localAtual;
        while (getline(filePassageiros, nome, ',') && getline(filePassageiros, localAtual)) {
            if (!nome.empty() && !localAtual.empty()) {
                if (!localAtual.empty() && localAtual.back() == '\n') localAtual.pop_back();
                if (!localAtual.empty() && localAtual.back() == '\r') localAtual.pop_back();
                controlador.cadastrarPassageiro(nome, localAtual);
            }
        }
        filePassageiros.close();
    }

    // 4. Carrega Transportes
    ifstream fileTransportes("transportes.txt");
    if (fileTransportes.is_open()) {
        string nome, tipoStr, localAtual, capStr, velStr;
        while (getline(fileTransportes, nome, ',') && 
               getline(fileTransportes, tipoStr, ',') && 
               getline(fileTransportes, localAtual, ',') &&
               getline(fileTransportes, capStr, ',') &&
               getline(fileTransportes, velStr)) {
            if (!nome.empty()) {
                if (!velStr.empty() && velStr.back() == '\n') velStr.pop_back();
                if (!velStr.empty() && velStr.back() == '\r') velStr.pop_back();
                char tipo = tipoStr.empty() ? 'T' : tipoStr[0];
                int cap = stoi(capStr);
                int vel = stoi(velStr);
                controlador.cadastrarTransporte(nome, tipo, cap, vel, 150, 1, localAtual);
            }
        }
        fileTransportes.close();
    }
}

void Repositorio::salvarDados(ControladorDeTransito& controlador) {
    // 1. Salva Cidades
    ofstream fileCidades("cidades.txt");
    if (fileCidades.is_open()) {
        auto asCidades = controlador.getCidades();
        for (unsigned int i = 0; i < asCidades.size(); i++) {
            if (asCidades[i] != nullptr) fileCidades << asCidades[i]->getNome() << "\n";
        }
        fileCidades.close();
    }

    // 2. Salva Trajetos
    ofstream fileTrajetos("trajetos.txt");
    if (fileTrajetos.is_open()) {
        auto osTrajetos = controlador.getTrajetos();
        for (unsigned int i = 0; i < osTrajetos.size(); i++) {
            if (osTrajetos[i] != nullptr) {
                fileTrajetos << osTrajetos[i]->getOrigem()->getNome() << ","
                             << osTrajetos[i]->getDestino()->getNome() << ","
                             << osTrajetos[i]->getTipo() << ","
                             << osTrajetos[i]->getDistancia() << "\n";
            }
        }
        fileTrajetos.close();
    }

    // 3. Salva Passageiros
    ofstream filePassageiros("passageiros.txt");
    if (filePassageiros.is_open()) {
        auto osPassageiros = controlador.getPassageiros();
        for (unsigned int i = 0; i < osPassageiros.size(); i++) {
            if (osPassageiros[i] != nullptr) {
                filePassageiros << osPassageiros[i]->getNome() << "," 
                                << (osPassageiros[i]->getLocalAtual() != nullptr ? osPassageiros[i]->getLocalAtual()->getNome() : "Em_Transito") << "\n";
            }
        }
        filePassageiros.close();
    }

    // 4. Salva Transportes
    ofstream fileTransportes("transportes.txt");
    if (fileTransportes.is_open()) {
        auto osTransportes = controlador.getTransportes();
        for (unsigned int i = 0; i < osTransportes.size(); i++) {
            if (osTransportes[i] != nullptr) {
                fileTransportes << osTransportes[i]->getNome() << ","
                                << osTransportes[i]->getTipo() << ","
                                << (osTransportes[i]->getLocalAtual() != nullptr ? osTransportes[i]->getLocalAtual()->getNome() : "Em_Transito") << ","
                                << osTransportes[i]->getCapacidade() << ","
                                << osTransportes[i]->getVelocidade() << "\n";
            }
        }
        fileTransportes.close();
    }
}