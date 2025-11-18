#include "rh.h"
#include "../Models/colaborador.h"

#include <cstdlib> // Para system()
#include <iostream>
#include <string>
#include <vector>



void adicionarColaborador(std::vector<Colaborador>& lista){
    
    std::string nomeNovo;
    
    std::cout << "Introduza o nome do colaborador a adicionar: ";
    std::cin.ignore(1000, '\n'); // limpar buffer
    // Lê a linha inteira, incluindo espaços
    std::getline(std::cin, nomeNovo);

    Colaborador* colaborador = encontrarColaborador(lista, nomeNovo);

    if (colaborador == nullptr){
        Colaborador novoColaborador;

        novoColaborador.nome = nomeNovo;

        lista.push_back(novoColaborador);

        std::cout << "\033[32m" << "Colaborador adicionado com sucesso!\n" << "\033[0m";
        
    } else {

        std::cout << "\033[31m" << "Ja existe um colaborador com esse nome!\n" << "\033[0m";
    }

}

void listarColaboradores(const std::vector<Colaborador>& lista){
    

    std::cout << "\n------------" << "\033[34m" << " Lista de Colaboradores " << "\033[0m" << "------------\n" << std::endl;

    if (lista.empty()){
        std::cout << "\033[31m" << "De momento nenhum colaborador encontra-se resgistado.\n" << "\033[0m";
        return;
    }

    for (int i = 0; i < lista.size(); i++){

        std::cout << lista[i].nome << std::endl;
    }

    std::cout << "-------------------------------------------------\n" << std::endl;
}

Colaborador* encontrarColaborador(std::vector<Colaborador>& lista, const std::string& nome){
    
    for (int i = 0; i < lista.size(); i++){
        std::string nomeLower, nomeListaLower;
        int teste = 0;
        for(int j=0 ; j<nome.size(); j++){
            nomeLower += tolower(nome[j]);
        }

        for(int j=0 ; j<lista[i].nome.size(); j++){
            nomeListaLower += tolower(lista[i].nome[j]);
        }

        if (nomeLower == nomeListaLower){
            return &lista[i];
        }
        
    }

    return nullptr;
}

void marcarAusencia(std::vector<Colaborador>& lista){  

    std::string nomeColaborador;
    
    std::cout << "Introduza o nome do colaborador: ";
    std::cin.ignore(1000, '\n'); // limpar buffer
    // Lê a linha inteira, incluindo espaços
    std::getline(std::cin, nomeColaborador);

    Colaborador* colaborador = encontrarColaborador(lista, nomeColaborador);

    if (colaborador != nullptr){

        int diaA, mesA, anoA;
        char tipo;

        while (true){
            std::cout << "Introduza o dia, mes e ano\n"; 

            std::cout << "Dia: ";
            std::cin >> diaA;

            std::cout << "Mes: ";
            std::cin >> mesA;

            std::cout << "Ano: ";
            std::cin >> anoA;

            int maxDias = diasNoMes(mesA, anoA);
            bool dataValida = true;

            if (diaA <= 0 || diaA >= maxDias){
                std::cout << "Dia invalido! Tem de ser entre 1 e " << maxDias << std::endl;
                dataValida = false;
            }
            if (mesA <= 0 || mesA > 12){
                std::cout << "Mes invalido! Tem de ser entre 1 e 12\n";
                dataValida = false;
            }
            if (anoA < 0 || anoA > 9999){
                std::cout << "Ano invalido!\n";
                dataValida = false;
            }

            if (dataValida){
                break;
            } else {
                std::cout << "Data invalida, tente de novo";
            }
        }

        do{
            std::cout << "Tipo de marcacao ('F'- Ferias, 'X' - Falta, 'L' - Limpar): ";
            std::cin >> tipo;

            tipo = std::toupper(tipo); // converter para maiuscula
            
            if (tipo == 'L'){

                bool encontrada = false;

                // Loop para encontrar a falta a apagar
                for (int i = 0; i < colaborador->falta.size(); ++i) {
                    
                    Faltas& f = colaborador->falta[i];
                    
                    if (f.dia == diaA && f.mes == mesA && f.ano == anoA) {
                        // Encontrámos! Apagar usando um "iterador"
                        colaborador->falta.erase(colaborador->falta.begin() + i);
                        encontrada = true;
                        std::cout << "Marcacao removida.\n";
                        break; // Sair do loop 'for'
                    }
                }
                
                if (!encontrada) {
                    std::cout << "Nenhuma marcacao encontrada para o dia " << diaA << "/" << mesA << "/" << anoA << ".\n";
                }

            } else if (tipo == 'F' || tipo == 'X'){ // criar falta / colocar férias

                
                Faltas novaFalta;

                novaFalta.ano = anoA;
                novaFalta.mes = mesA;
                novaFalta.dia = diaA;
                novaFalta.tipoDeFalta = tipo;
                
                // Adicionar ao vector do colaborador
                colaborador->falta.push_back(novaFalta);
                
                std::cout << "Marcacao '" << tipo << "' adicionada.\n";

            } else {

                std::cout << "Tipo de marcacao invalido, tente de novo!";

            }

        } while (tipo != 'L' && tipo != 'X' && tipo != 'F');       


    } else {
        std::cout << "Nenhum colaborador encontrado com esse nome!";
    }

}

void limparEcra() {
#ifdef _WIN32 // Esta macro é definida pelo compilador se estiver no Windows
    std::system("cls");
#else
    // Assume que é um sistema POSIX (Linux, macOS)
    std::system("clear");
#endif
}