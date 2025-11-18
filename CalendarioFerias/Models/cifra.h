#ifndef CIFRA_H
#define CIFRA_H

#include <string>

std::string encriptar(const std::string &texto, int chave);
std::string desencriptar(const std::string &texto, int chave);

#endif