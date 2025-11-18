#ifndef IO_H
#define IO_H

#include "colaborador.h"
#include <vector>

void guardarDados(const std::vector<Colaborador>& lista, const std::string& filename);
std::vector<Colaborador> carregarDados(const std::string& filename);

#endif