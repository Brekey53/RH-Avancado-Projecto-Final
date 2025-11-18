#include <fstream>
#include <sstream>
#include <iostream>

#include "io.h"
#include "cifra.h"

const int chave = 10;

// Guarda a lista de colaboradores num ficheiro de texto
void guardarDados(const std::vector<Colaborador>& lista, const std::string& filename){
    std::ofstream file(filename);

    if (file.is_open()){
        for (const auto& colab : lista){
            // Encripta o nome antes de guardar
            std::string nomeColaboradorEncriptado = encriptar(colab.nome, chave);
            
            // Formato: NomeEncriptado|ID|Departamento
            file << nomeColaboradorEncriptado << "|" << colab.id << "|" << colab.departamento;

            // Guarda as faltas/férias com prefixo ABS:
            for (const auto& falta : colab.falta){
                file << "|ABS:" << falta.ano << "," << falta.mes << "," << falta.dia << "," << falta.tipoDeFalta;
            }

            // Guarda as formações com prefixo FORM:
            for (const auto& form : colab.formacoes) {
                file << "|FORM:" << form.nome_curso << "," << form.data_conclusao;
            }

            // Guarda as notas com prefixo NOTE:
            for (const auto& nota : colab.notas) {
                file << "|NOTE:" << nota.texto << "," << nota.data;
            }

            file << "\n"; // Nova linha para o próximo colaborador
        }
        file.close();
    } else {
        std::cout << "Erro ao abrir o ficheiro para escrita.\n";
    }
}

// Carrega a lista de colaboradores a partir do ficheiro
std::vector<Colaborador> carregarDados(const std::string& filename) {
    std::vector<Colaborador> lista;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string linha;
        while (std::getline(file, linha)) {
            std::stringstream ss(linha);
            std::string segmento;
            
            Colaborador novoColab;
            
            // Lê o Nome Encriptado e converte para o original
            if(std::getline(ss, segmento, '|')) {
                novoColab.nome = desencriptar(segmento, chave);
            }

            // Lê o ID (se existir, senão assume 0)
            if(std::getline(ss, segmento, '|')) {
                // Verifica se é um campo de dados ou metadados (ABS/FORM/NOTE com std::string::npos)
                // Assume que o segundo campo é ID se não tiver prefixo
                if (segmento.find("ABS:") == std::string::npos && 
                    segmento.find("FORM:") == std::string::npos && 
                    segmento.find("NOTE:") == std::string::npos) {
                    try { 
                        novoColab.id = std::stoi(segmento); 
                    } catch(...) { // catch(...) serve para apanhar todos os erros possiveis
                        novoColab.id = 0; 
                    }
                } else {
                    // Se não houver ID, volta atrás (assume formato novo)
                }
            }

            // Lê o Departamento
            if(std::getline(ss, segmento, '|')) {
                 if (segmento.find("ABS:") == std::string::npos && 
                    segmento.find("FORM:") == std::string::npos && 
                    segmento.find("NOTE:") == std::string::npos) {
                    novoColab.departamento = segmento;
                }
            }

            // Lê o restante da linha (Faltas, Formações, Notas)            
            while(std::getline(ss, segmento, '|')) {
                if (segmento.find("ABS:") == 0) {
                    // Parse Ausência: ABS:Ano,Mes,Dia,Tipo
                    std::string dados = segmento.substr(4);
                    std::stringstream ss2(dados);
                    std::string val;
                    Faltas f;
                    std::getline(ss2, val, ','); f.ano = std::stoi(val);
                    std::getline(ss2, val, ','); f.mes = std::stoi(val);
                    std::getline(ss2, val, ','); f.dia = std::stoi(val);
                    std::getline(ss2, val, ','); f.tipoDeFalta = val[0];
                    novoColab.falta.push_back(f);
                } else if (segmento.find("FORM:") == 0) {
                    // Parse Formação: FORM:Nome,Data
                    std::string dados = segmento.substr(5);
                    size_t commaPos = dados.find_last_of(','); // Assume data no fim
                    if (commaPos != std::string::npos) {
                        Formacao form;
                        form.nome_curso = dados.substr(0, commaPos);
                        form.data_conclusao = dados.substr(commaPos + 1);
                        novoColab.formacoes.push_back(form);
                    }
                } else if (segmento.find("NOTE:") == 0) {
                    // Parse Nota: NOTE:Texto,Data
                    std::string dados = segmento.substr(5);
                    size_t commaPos = dados.find_last_of(',');
                    if (commaPos != std::string::npos) {
                        Nota n;
                        n.texto = dados.substr(0, commaPos);
                        n.data = dados.substr(commaPos + 1);
                        novoColab.notas.push_back(n);
                    }
                }
            }
            
            lista.push_back(novoColab);
        }
        file.close();
    } else {
        std::cout << "Ficheiro nao encontrado. Sera criado um novo ao guardar.\n";
    }
    return lista;
}

