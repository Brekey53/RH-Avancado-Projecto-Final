#include "cifra.h"

// Função simples de encriptação (Cifra de César)
std::string encriptar(const std::string &texto, int chave) {
    std::string resultado = texto;
 
    for (size_t i = 0; i < texto.size(); ++i) {
        char c = texto[i];
 
        if (std::isalpha(c)) { // apenas letras
            char base = std::isupper(c) ? 'A' : 'a';
            resultado[i] = char((c - base + chave) % 26 + base);
        } else {
            resultado[i] = c; // mantém espaços e pontuação
        }
    }
    return resultado;
}
 
// Função de desencriptação (reverte o processo)
std::string desencriptar(const std::string &texto, int chave) {
    return encriptar(texto, 26 - (chave % 26)); // desloca no sentido inverso
}
