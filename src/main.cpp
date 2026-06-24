#include <iostream>
#include "modelos/ControladorDeTransito/ControladorDeTransito.hpp"
#include "repositories/Repositorio.hpp"
#include "usecases/MenuPrincipal.hpp"

using namespace std;

int main() {
    ControladorDeTransito controlador;

    cout << "Inicializando Sistema..." << endl;
    
    // Tenta carregar dados persistidos previamente
    Repositorio::carregarDados(controlador);

    // Passa o controle para o menu interativo
    MenuPrincipal::exibir(controlador);

    return 0;
}