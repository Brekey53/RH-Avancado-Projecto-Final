#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <string>
#include <vector>

// Estrutura para representar uma falta ou dia de férias
struct Faltas
{
    int ano;
    int mes;
    int dia;
    char tipoDeFalta; // 'F' para férias e 'X' para falta 
};

// Estrutura para representar uma formação ou curso
struct Formacao {
    std::string nome_curso;
    std::string data_conclusao;
};

// Estrutura para representar uma nota interna ou observação
struct Nota {
    std::string texto;
    std::string data;
};

// Estrutura principal do Colaborador
struct Colaborador
{
    int id;                         // Identificador único
    std::string nome;               // Nome do colaborador
    std::string departamento;       // Departamento a que pertence
    std::vector<Faltas> falta;      // Lista de ausências (férias/faltas)
    std::vector<Formacao> formacoes;// Lista de formações concluídas
    std::vector<Nota> notas;        // Lista de notas internas
};

#endif