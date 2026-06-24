#include "ControladorDeTransito.hpp"
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

ControladorDeTransito::~ControladorDeTransito() {
    for (auto c : cidades) delete c;
    for (auto p : passageiros) delete p;
    for (auto t : transportes) delete t;
    for (auto tj : trajetos) delete tj;
    for (auto v : viagens) delete v;
}

void ControladorDeTransito::cadastrarCidade(string nome) {
    for (auto c : cidades) if (c->getNome() == nome) return;
    cidades.push_back(new Cidade(nome));
}

void ControladorDeTransito::cadastrarPassageiro(string nome, string nome_cidade) {
    Cidade* cid = nullptr;
    for (auto c : cidades) if (c->getNome() == nome_cidade) cid = c;
    passageiros.push_back(new Passageiro(nome, cid));
}

void ControladorDeTransito::cadastrarTransporte(string nome, char tipo, int capacidade, int velocidade, int dist_descanso, int tempo_descanso, string nome_cidade) {
    Cidade* cid = nullptr;
    for (auto c : cidades) if (c->getNome() == nome_cidade) cid = c;
    
    string nomeFinal = nome;
    if (nomeFinal.empty()) {
        int cont = 1;
        for (auto t : transportes) if (t->getTipo() == tipo) cont++;
        nomeFinal = (tipo == 'T' ? "Terrestre_" : "Aquatico_") + to_string(cont);
    }
    transportes.push_back(new Transporte(nomeFinal, tipo, capacidade, velocidade, dist_descanso, tempo_descanso, cid));
}

void ControladorDeTransito::cadastrarTrajeto(string origem, string destino, char tipo, int distancia) {
    Cidade* cidOrigem = nullptr;
    Cidade* cidDestino = nullptr;
    for (auto c : cidades) {
        if (c->getNome() == origem) cidOrigem = c;
        if (c->getNome() == destino) cidDestino = c;
    }
    if (cidOrigem && cidDestino) {
        trajetos.push_back(new Trajeto(cidOrigem, cidDestino, tipo, distancia));
    }
}

bool ControladorDeTransito::iniciarViagem(string nome_transporte, string nome_origem, string nome_destino, vector<string> nomes_passageiros) {
    Transporte* trans = nullptr;
    for (auto t : transportes) if (t->getNome() == nome_transporte) trans = t;

    if (!trans || !trans->getLocalAtual() || trans->getLocalAtual()->getNome() != nome_origem) {
        cout << "\nErro: Transporte nao encontrado ou nao esta na cidade de origem!\n";
        return false;
    }

    queue<Cidade*> fila;
    map<Cidade*, Trajeto*> pai;
    Cidade* cOrigem = trans->getLocalAtual();
    Cidade* cDestino = nullptr;
    for (auto c : cidades) if (c->getNome() == nome_destino) cDestino = c;

    if (!cDestino) {
        cout << "Erro: Cidade destino nao cadastrada!\n";
        return false;
    }

    fila.push(cOrigem);
    bool achou = false;

    while (!fila.empty() && !achou) {
        Cidade* atual = fila.front();
        fila.pop();

        if (atual == cDestino) {
            achou = true;
            break;
        }

        for (auto tj : trajetos) {
            if (tj->getOrigem() == atual && tj->getTipo() == trans->getTipo()) {
                Cidade* proxCidade = tj->getDestino();
                if (pai.find(proxCidade) == pai.end() && proxCidade != cOrigem) {
                    pai[proxCidade] = tj;
                    fila.push(proxCidade);
                }
            }
        }
    }

    if (!achou) {
        cout << "\nErro: Nao existe nenhuma rota conectada compativel com o tipo do transporte!\n";
        return false;
    }

    vector<Trajeto*> rotaCaminho;
    Cidade* passo = cDestino;
    while (passo != cOrigem) {
        Trajeto* tj = pai[passo];
        rotaCaminho.push_back(tj);
        passo = tj->getOrigem();
    }
    reverse(rotaCaminho.begin(), rotaCaminho.end());

    // Coletar e validar os passageiros informados limpando resíduos de arquivo (\r ou \n)
    vector<Passageiro*> passageirosViagem;
    for (string nomeP : nomes_passageiros) {
        // Remove espaços ou quebras de linha do nome digitado
        nomeP.erase(remove_if(nomeP.begin(), nomeP.end(), ::isspace), nomeP.end());
        
        for (auto p : passageiros) {
            if (p != nullptr) {
                string nomeCadastrado = p->getNome();
                // Remove quebras de linha residuais que vieram do arquivo .txt
                nomeCadastrado.erase(remove_if(nomeCadastrado.begin(), nomeCadastrado.end(), ::isspace), nomeCadastrado.end());

                if (nomeCadastrado == nomeP) {
                    if (p->getLocalAtual() != nullptr && p->getLocalAtual()->getNome() == nome_origem) {
                        if ((int)passageirosViagem.size() < trans->getCapacidade()) {
                            passageirosViagem.push_back(p);
                        }
                    } else {
                        cout << "Aviso: O passageiro " << nomeP << " nao esta fisicamente em " << nome_origem << "!\n";
                    }
                }
            }
        }
    }

    if (passageirosViagem.empty()) {
        cout << "\nErro: Nenhum dos passageiros digitados foi encontrado ou esta disponivel na origem.\n";
        return false;
    }

    trans->setLocalAtual(nullptr);
    for (auto p : passageirosViagem) p->setLocalAtual(nullptr);

    Viagem* primeiraViagem = new Viagem(trans, rotaCaminho[0], passageirosViagem);
    Viagem* atualV = primeiraViagem;
    
    for (size_t i = 1; i < rotaCaminho.size(); i++) {
        Viagem* proxV = new Viagem(trans, rotaCaminho[i], passageirosViagem);
        atualV->setProxima(proxV);
        atualV = proxV;
    }

    viagens.push_back(primeiraViagem);
    cout << "\nViagem iniciada com sucesso! Conexões geradas: " << rotaCaminho.size() << "\n";
    return true;
}

void ControladorDeTransito::avancarHoras(int horas) {
    for (int h = 0; h < horas; h++) {
        for (auto it = viagens.begin(); it != viagens.end(); ) {
            Viagem* v = *it;
            v->avancarHoras(1);

            if (v->isConcluida()) {
                Transporte* t = v->getTransporte();
                Viagem* proximaPerna = v->getProxima();

                if (proximaPerna != nullptr) {
                    v->setProxima(nullptr);
                    delete v;
                    *it = proximaPerna; 
                    proximaPerna->iniciarViagem();
                    cout << "\n>>> CONEXAO CONCLUIDA: Transporte " << t->getNome() << " iniciando proxima etapa rumo a " << proximaPerna->getTrajeto()->getDestino()->getNome() << "!\n";
                } else {
                    Cidade* destinoFinal = v->getTrajeto()->getDestino();
                    t->setLocalAtual(destinoFinal);
                    for (auto p : v->getPassageiros()) {
                        p->setLocalAtual(destinoFinal);
                    }
                    visitasCidades[destinoFinal->getNome()]++;
                    cout << "\n>>> CHEGADA REGISTRADA: O transporte " << t->getNome() << " chegou ao destino final em " << destinoFinal->getNome() << "!\n";
                    delete v;
                    it = viagens.erase(it);
                    continue;
                }
            }
            ++it;
        }
    }
}

void ControladorDeTransito::relatarEstado() {
    cout << "\n======= RELATORIO DE LOCALIZACAO =======" << endl;
    
    cout << "\n--- Cidades Cadastradas ---" << endl;
    for (auto c : cidades) if (c) cout << "Cidade: " << c->getNome() << endl;

    cout << "\n--- Pessoas ---" << endl;
    for (auto p : passageiros) {
        if (p) {
            cout << "Passageiro: " << p->getNome();
            if (p->getLocalAtual()) {
                cout << " | Na cidade: " << p->getLocalAtual()->getNome() << endl;
            } else {
                string infoViagem = "Em conexao";
                for (auto v : viagens) {
                    if (v) {
                        for (auto pass : v->getPassageiros()) {
                            if (pass == p) {
                                infoViagem = "Origem: " + v->getOrigem()->getNome() +
                                             " -> Proxima Parada: " + v->getTrajeto()->getDestino()->getNome() +
                                             " | Transporte: " + v->getTransporte()->getNome();
                                break;
                            }
                        }
                    }
                }
                cout << " | Status: EM TRANSITO (" << infoViagem << ")" << endl;
            }
        }
    }

    cout << "\n--- Transportes ---" << endl;
    for (auto t : transportes) {
        if (t) {
            cout << "Transporte: " << t->getNome() << " [" << (t->getTipo() == 'T' ? "Terrestre" : "Aquatico") << "]";
            if (t->getLocalAtual()) {
                cout << " | Na cidade: " << t->getLocalAtual()->getNome() << endl;
            } else {
                string rotaInfo = "Definindo rota";
                for (auto v : viagens) {
                    if (v && v->getTransporte() == t) {
                        rotaInfo = v->getOrigem()->getNome() + " -> " + v->getTrajeto()->getDestino()->getNome();
                        break;
                    }
                }
                cout << " | Status: EM TRANSITO (" << rotaInfo << ")" << endl;
            }
        }
    }
    cout << "\n========================================" << endl;
}

void ControladorDeTransito::relatarViagensEmAndamento() {
    cout << "\n======= VIAGENS EM ANDAMENTO =======" << endl;
    if (viagens.empty()) { 
        cout << "\nNenhuma viagem ocorrendo no momento.\n"; 
        return; 
    }
    for (auto v : viagens) {
        if (v) {
            cout << "Transporte: " << v->getTransporte()->getNome() 
                 << " | Etapa Atual: " << v->getTrajeto()->getOrigem()->getNome() 
                 << " -> " << v->getTrajeto()->getDestino()->getNome() 
                 << " | Passageiros: " << v->getPassageiros().size() << endl;
        }
    }
}

void ControladorDeTransito::relatarCidadesMaisVisitadas() {
    cout << "\n======= CIDADES MAIS VISITADAS =======" << endl;
    if (visitasCidades.empty()) { 
        cout << "\nNenhuma viagem concluida ainda.\n"; 
        return; 
    }
    for (auto const& [cidade, qtd] : visitasCidades) {
        cout << "Cidade: " << cidade << " | Visitas: " << qtd << " vezes\n";
    }
}