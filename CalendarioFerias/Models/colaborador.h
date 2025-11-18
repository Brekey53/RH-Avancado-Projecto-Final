#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <string>
#include <vector>

struct Faltas
{
    int ano;
    int mes;
    int dia;
    char tipoDeFalta; // 'F' para férias e 'X' para falta 
};

struct Colaborador
{
    std::string nome;
    std::vector<Faltas> falta;
};




#endif