#ifndef RH_H
#define RH_H

#include <string>
#include <vector>
#include "../Models/colaborador.h"

// Função para adicionar um novo colaborador
void adicionarColaborador(std::vector<Colaborador>& lista);

// Função para listar todos os colaboradores
void listarColaboradores(const std::vector<Colaborador>& lista);

// Função para marcar uma ausência
void marcarAusencia(std::vector<Colaborador>& lista);

// Busca colaborador e mostra detalhes
void buscarColaborador(std::vector<Colaborador>& lista);

// Mostra estatísticas por departamento
void estatisticasDepartamento(const std::vector<Colaborador>& lista);

// Mostra dashboard resumido
void dashboardResumido(const std::vector<Colaborador>& lista);

// Gere formações de um colaborador
void gerirFormacoes(std::vector<Colaborador>& lista);

// Gere notas internas de um colaborador
void gerirNotas(std::vector<Colaborador>& lista);

// Exporta relatório para ficheiro
void exportarRelatorio(const std::vector<Colaborador>& lista);


// --- Funções de Busca ---
// Encontra um colaborador pelo nome
Colaborador* encontrarColaborador(std::vector<Colaborador>& lista, const std::string& nome);
// Encontra um colaborador pelo ID
Colaborador* encontrarColaboradorPorId(std::vector<Colaborador>& lista, int id);



// Função que troca o numero do mes para o nome do mes
std::string nomeMes(int mes);

// Função que devolve o dia do mes
int diasNoMes(int mes, int ano);

// Função devolve o dia da semana
int diaSemana(int dia, int mes, int ano);



// Função simples de encriptação (Cifra de César)
std::string encriptar(const std::string &texto, int chave);
 
// Função de desencriptação (reverte o processo)
std::string desencriptar(const std::string &texto, int chave);

// Função para limpar ecra
void limparEcra();

#endif