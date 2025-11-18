#ifndef CALENDARIO_H
#define CALENDARIO_H

#include <string>
#include "../Models/colaborador.h"

// imprime o calendario
void imprimirCalendario(const Colaborador& colab, int mes, int ano);

// Função que troca o numero do mes para o nome do mes
std::string nomeMes(int mes);

// Função que devolve o dia do mes
int diasNoMes(int mes, int ano);

// Função devolve o dia da semana
int diaSemana(int dia, int mes, int ano);

#endif