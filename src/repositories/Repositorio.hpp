#pragma once

#include <string>
#include "../modelos/ControladorDeTransito/ControladorDeTransito.hpp"

class Repositorio {
public:
    static void carregarDados(ControladorDeTransito& controlador);
    static void salvarDados(ControladorDeTransito& controlador);
};