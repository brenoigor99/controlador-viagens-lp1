#include "MenuPrincipal.hpp"
#include "../repositories/Repositorio.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void MenuPrincipal::exibir(ControladorDeTransito& controlador) {
    int opcao = -1;
    
    while (opcao != 0) {
        cout << "\n===============================\n";
        cout << "    SISTEMA DE TRANSPORTES    \n";
        cout << "===============================\n";
        cout << "1. Cadastrar Cidade\n";
        cout << "2. Cadastrar Trajeto\n";
        cout << "3. Cadastrar Transporte\n";
        cout << "4. Cadastrar Passageiro\n";
        cout << "5. Iniciar Viagem\n";
        cout << "6. Avancar Horas no Sistema\n";
        cout << "7. Exibir Relatorio Geral (onde estao)\n";
        cout << "8. Exibir Viagens em Andamento\n";
        cout << "9. Exibir Cidades Mais Visitadas\n";
        cout << "0. Sair e Salvar\n";
        cout << "Escolha uma opcao: ";
        
        if (!(cin >> opcao)) {
            cin.clear(); string d; cin >> d; continue;
        }
        cin.ignore();

        switch (opcao) {
            case 1: {
                string nome;
                cout << "Nome da Cidade: "; getline(cin, nome);
                controlador.cadastrarCidade(nome);
                cout << "Cidade cadastrada com sucesso!\n";
                break;
            }
            case 2: {
                string orig, dest; char tipo; int dist;
                cout << "Cidade de Origem: "; getline(cin, orig);
                cout << "Cidade de Destino: "; getline(cin, dest);
                cout << "Tipo de Trajeto (T - Terrestre / A - Aquatico): "; cin >> tipo;
                cout << "Distancia em Km: "; cin >> dist;
                controlador.cadastrarTrajeto(orig, dest, toupper(tipo), dist);
                cout << "Trajeto cadastrado com sucesso!\n";
                break;
            }
            case 3: {
                string nome, localAtual;
                char tipo;
                int capacidade, velocidade, dist_descanso, tempo_descanso;

                cout << "Digite o nome do transporte: ";
                cin >> nome;
                cout << "Digite o tipo (A para Aquatico, T para Terrestre): ";
                cin >> tipo;
                cout << "Digite a capacidade de passageiros: ";
                cin >> capacidade;
                cout << "Digite a velocidade (Km/h): ";
                cin >> velocidade;
    
                cout << "Digite a distancia entre descansos (Km): ";
                cin >> dist_descanso;
                cout << "Digite o tempo de descanso (Horas): ";
                cin >> tempo_descanso;
    
                cout << "Digite a cidade onde o transporte esta localizados: ";
                cin >> localAtual;

                controlador.cadastrarTransporte(nome, tipo, capacidade, velocidade, dist_descanso, tempo_descanso, localAtual);
                cout << "Transporte cadastrado com sucesso!\n";
                break;
            }
            case 4: {
                string nome, cidade;
                cout << "Nome do Passageiro: "; getline(cin, nome);
                cout << "Cidade Inicial: "; getline(cin, cidade);
                controlador.cadastrarPassageiro(nome, cidade);
                cout << "Passageiro cadastrado com sucesso!\n";
                break;
            }
            case 5: {
                string transporte, origem, destino;
                int qtdPassageiros;
                vector<string> nomesPassageiros;

                cout << "Digite o nome do transporte: ";
                cin >> transporte;
                cout << "Digite a cidade de origem: ";
                cin >> origem;
                cout << "Digite a cidade de destino: ";
                cin >> destino;
                cout << "Quantidade de passageiros: ";
                cin >> qtdPassageiros;

                for (int i = 0; i < qtdPassageiros; i++) {
                    string nomeP;
                    cout << "Digite o nome do passageiro " << (i + 1) << ": ";
                    cin >> nomeP;
                    nomesPassageiros.push_back(nomeP);
                }

                controlador.iniciarViagem(transporte, origem, destino, nomesPassageiros);
                break;
            }
            case 6: {
                int horas;
                cout << "Quantas horas deseja avancar no tempo? "; cin >> horas;
                controlador.avancarHoras(horas);
                break;
            }
            case 7: controlador.relatarEstado(); break;
            case 8: controlador.relatarViagensEmAndamento(); break;
            case 9: controlador.relatarCidadesMaisVisitadas(); break;
            case 0:
                Repositorio::salvarDados(controlador);
                cout << "Dados salvos com sucesso. Ate logo!\n";
                break;
            default: cout << "Opcao invalida.\n"; break;
        }
    }
}