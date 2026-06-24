#pragma once

#include <string>

class Cidade {
private:
    std::string nome;
public:
    Cidade(std::string nome);
    std::string getNome();
};