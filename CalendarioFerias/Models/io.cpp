#include <fstream>
#include <sstream>
#include <iostream>

#include "io.h"
#include "cifra.h"

const int chave = 10;

void guardarDados(const std::vector<Colaborador>& lista, const std::string& filename){
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Erro ao abrir o ficheiro para escrita: " << filename << std::endl;
        return;
    }

    for (const auto& colab : lista){
        std::string nomeColaboradorEncriptado = encriptar(colab.nome, chave);

        file << nomeColaboradorEncriptado;

        for (const auto& falta : colab.falta){ // Adicionar faltas ao colaborador
            file << "|" << falta.ano << "," << falta.mes << "," << falta.dia << "," << falta.tipoDeFalta;
        }
        file << "\n";
    }

    file.close();
}


std::vector<Colaborador> carregarDados(const std::string& filename) {

    std::vector<Colaborador> lista;
    std::ifstream file(filename);
    if (!file.is_open()) {
        // Se o ficheiro não existe (primeira execução), retorna lista vazia. Não é um erro fatal.
        return lista;
    }
 
    std::string linha;
 
    while (std::getline(file, linha)) {
        if (linha.empty()) {
            continue; // Ignora linhas vazias
        }

        std::stringstream ss(linha);
        std::string nomeEncriptado;
        
        if (!std::getline(ss, nomeEncriptado, '|')) {
            continue; // Linha mal formada, sem nome
        }

        Colaborador novoColab;
        novoColab.nome = desencriptar(nomeEncriptado, chave);

        // Ler cada bloco de falta (separados por '|')
        std::string blocoFalta;
        while (std::getline(ss, blocoFalta, '|')) {
            std::stringstream ssFalta(blocoFalta);
            std::string campoAno, campoMes, campoDia, campoTipo;

            // separado por virgula pela ordem -> ano, mes, dia, campo tipoDeFalta
            if (std::getline(ssFalta, campoAno, ',') &&
                std::getline(ssFalta, campoMes, ',') &&
                std::getline(ssFalta, campoDia, ',') &&
                std::getline(ssFalta, campoTipo, ','))
            {
                Faltas novaFalta;
                novaFalta.ano = std::stoi(campoAno);
                novaFalta.mes = std::stoi(campoMes);
                novaFalta.dia = std::stoi(campoDia);
                novaFalta.tipoDeFalta = campoTipo[0];
                novoColab.falta.push_back(novaFalta);
            }
        }

        // introduzir na lista
        lista.push_back(novoColab);
    }
 
    file.close();
    return lista;
}
