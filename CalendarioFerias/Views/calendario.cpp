#include "../Models/colaborador.h"
#include "../Controllers/rh.h"
#include "calendario.h"
#include <iostream>

// Função que troca o numero do mes para o nome do mes
std::string nomeMes(int mes){
    const std::string meses[] = {"Janeiro","Fevereiro","Março","Abril","Maio","Junho",
                                 "Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"};
    return meses[mes-1];
}

// Função que devolve o dia do mes
int diasNoMes(int mes, int ano) {
    switch(mes){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return ((ano%4==0 && ano%100!=0) || (ano%400==0)) ? 29 : 28;
        default: return 30;
    }
}

// Função devolve o dia da semana
int diaSemana(int dia, int mes, int ano) {
    if(mes < 3) { mes += 12; ano--; }
    int k = ano % 100;
    int j = ano / 100;
    int h = (dia + 13*(mes+1)/5 + k + k/4 + j/4 + 5*j) % 7;
    int d = (h + 6) % 7; // 0 = Domingo, 6 = Sábado
    return d;
}

void imprimirCalendario(const Colaborador& colab, int mes, int ano) {
    
    std::cout << "\n Calendario de " << nomeMes(mes) << " de " << ano << std::endl;
    std::cout << "---------------------------------" << std::endl;
    std::cout << " Dom Seg Ter Qua Qui Sex Sab" << std::endl;

    // Calcula o dia da semana do primeiro dia do mês
    int primeiroDia = diaSemana(1, mes, ano); // 0=Dom, 6=Sab

    // Imprime espaços em branco para o alinhamento inicial
    for (int i = 0; i < primeiroDia; ++i) {
        std::cout << "    ";
    }

    int totalDias = diasNoMes(mes, ano);

    // Loop principal para imprimir os dias
    for (int dia = 1; dia <= totalDias; ++dia) {
        char tipoMarcacao = ' '; // ' ' -> dia normal, 'F' -> Férias, 'X' -> Falta
        bool marcado = false;

        // Procura se existe uma marcação para este dia no vetor de faltas do colaborador
        for (const Faltas& f : colab.falta) {
            if (f.dia == dia && f.mes == mes && f.ano == ano) {
                tipoMarcacao = f.tipoDeFalta;
                marcado = true;
                break; // Encontrou a marcação, pode parar de procurar
            }
        }

        int diaDaSemanaAtual = diaSemana(dia, mes, ano);

        if (marcado) {
            // Imprime a marcação (F ou X)
            if (tipoMarcacao == 'F'){
                std::cout << "  " << "\033[32m" << tipoMarcacao << "\033[0m" << " ";
            } else{
                std::cout << "  " << "\033[31m" << tipoMarcacao << "\033[0m" << " ";
            }
            
        } else if (diaDaSemanaAtual == 0 || diaDaSemanaAtual == 6) {
            // É um fim de semana sem marcação
            std::cout << "\033[33m" << " ## " << "\033[0m";
        } else {
            // É um dia de semana normal
            if (dia < 10) {
                std::cout << "  " << dia << " "; // Adiciona um espaço extra para alinhar
            } else {
                std::cout << " " << dia << " ";
            }
        }

        // Quebra de linha no Sábado ou no último dia do mês
        if (diaDaSemanaAtual == 6 || dia == totalDias) {
            std::cout << std::endl;
        }
    }
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Legenda: " << "\033[32m" << "F" << "\033[0m" << " - Ferias," << "\033[31m" << " X" << "\033[0m" << " - Falta, " << "\033[33m" << "##" << "\033[0m" << " - Fim de Semana\n" << std::endl;
}