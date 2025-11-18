/* 
Objetivo
Implementar um mini-sistema RH em C++ que permita gerir colaboradores e marcar férias e faltas, visualizar o calendário mensal com marcações e aplicar uma encriptação pedagógica ao gravar nomes em ficheiro.

Requisitos mínimos
Estrutura de dados:

struct Colaborador { std::string nome;  ...  } ou equivalente;
Funcionalidades (interface de consola):

Adicionar colaborador;
Marcar/Desmarcar férias e faltas (por dia, mês e ano);
Listar colaboradores;
Visualizar calendário mensal de um colaborador com indicação de férias (F), faltas (X) e fins-de-semana;
Guardar e carregar dados para/desde ficheiro (txt ou csv) ao sair/iniciar.
Validações:

Verificar dias válidos para o mês/ano (bisexto);
Evitar duplicados (nomes iguais) ou pedir confirmação. ------
Persistência e privacidade:

Ao gravar ficheiros, aplicar uma encriptação (Cifra) nos nomes dos colaboradores; ao ler, desencriptar;
Código:

Separar código em módulos/files (ex.: colaborador.h/.cpp, io.h/.cpp, main.cpp);
Utilizar boas práticas: funções pequenas, tratamento de erros básicos, comentários claros.
Extras opcionais (valorizados na avaliação):

Interface de consola com cores/alinhamento;
Entregáveis
Código fonte (ficheiros .cpp, .h) organizados num diretório com README contendo instruções de compilação e uso.
Ficheiro de dados de exemplo (gerado pelo programa).
Breve documentação (1 página): explicação da estrutura do programa, utilização da Cifra.

Critérios de avaliação
Funcionamento das funcionalidades obrigatórias (60%);
Qualidade do código e modularização (15%);
Persistência (gravação/leitura correta) e aplicação da encriptação pedagógica (10%);
Validações e tratamento de erros (10%);
Documentação e apresentação (5%).
Tempo sugerido na aula
120 minutos.
Entrega
Envio de link do repository github do projecto

joaopedrotvilares@gmail.com


. Função para calcular o dia da semana
Usa a congruência de Zeller para determinar o dia da semana de qualquer data.
 
int diaSemana(int dia, int mes, int ano) {
    if(mes < 3) { mes += 12; ano--; }
    int k = ano % 100;
    int j = ano / 100;
    int h = (dia + 13*(mes+1)/5 + k + k/4 + j/4 + 5*j) % 7;
    int d = (h + 6) % 7; // 0 = Domingo, 6 = Sábado
    return d;
}
2. Função para calcular o número de dias num mês
Esta função deve tratar corretamente anos bissextos.
 
int diasNoMes(int mes, int ano) {
    switch(mes){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return ((ano%4==0 && ano%100!=0) || (ano%400==0)) ? 29 : 28;
        default: return 30;
    }
}
3. Função auxiliar para o nome do mês
std::string nomeMes(int mes){
    const std::string meses[] = {"Janeiro","Fevereiro","Março","Abril","Maio","Junho",
                                 "Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"};
    return meses[mes-1];
}


*/

#include "Models/colaborador.h"
#include "Controllers/rh.h"
#include "Views/calendario.h"
#include "Models/io.h"
#include "Models/cifra.h"

#include <iostream>
#include <vector>

void pausaLer();
void calendarioColaborador(std::vector<Colaborador>& lista);
const std::string filename = "DBrh.csv";

int main(){

    std::vector<Colaborador> colaboradores = carregarDados(filename);
    int op = 0;
 

    do
    {
        limparEcra();
        std::cout << "\n=============" << "\033[34m" << " MENU " << "\033[0m" << "=============" << std::endl;
        std::cout << "1. Adicionar Colaborador\n2. Listar Colaboradores\n3. Marcar/Desmarcar Ausencia\n4. Ver Calendario Mensal\n5. Guardar e sair" << std::endl;
        std::cout << "================================\n" << std::endl;
        std::cout << "Escolha uma opcao: ";
        
        if (!(std::cin >> op)){
            std::cout << "\n[ERRO] Entrada invalida! Por favor, introduza um NUMERO.\n";
            std::cin.clear();

            std::cin.ignore(1000, '\n');
            op = 0;
        }

        
        switch (op)
        {
        case 1:
            adicionarColaborador(colaboradores);
            std::cout << "\nPressione Enter para continuar...";
            std::cin.get();
            break;
        

        case 2:
            listarColaboradores(colaboradores);
            pausaLer();
            break;


        case 3:
            marcarAusencia(colaboradores);
            pausaLer();
            break;

            
        case 4:
            calendarioColaborador(colaboradores);          
            pausaLer();
            break;

            
        case 5:
            guardarDados(colaboradores, filename);
            std::cout << "Dados guardados. A sair...\n";
            break;

        case 0: // Nào faz nada, apenas permite a redefinição do op = 0
            break;


        default:
            std::cout << "Opcao invalida! Introduza um valor de 1 a 5.";
            break;
        }
        
    } while (op != 5);
    

    return 0;

}


void pausaLer(){  
            std::cout << "\nPressione Enter para continuar...";
            std::cin.ignore(1000, '\n'); // 1. Limpa o 'Enter' pendente
            std::cin.get();             // 2. Espera que o utilizador pressione Enter
}

void calendarioColaborador(std::vector<Colaborador>& lista){
    std::string nomeColab;
    std::cout << "Introduza o nome do colaborador para ver o calendario: ";
    std::cin.ignore(1000, '\n');
    std::getline(std::cin, nomeColab);

    Colaborador* colab = encontrarColaborador(lista, nomeColab);

    if (colab != nullptr) {
        int mes, ano;
        std::cout << "Introduza o mes (1-12): ";
        std::cin >> mes;
        std::cout << "Introduza o ano: ";
        std::cin >> ano;

        // Validação básica
        if (mes >= 1 && mes <= 12 && ano > 1900 && ano < 9999) {
            imprimirCalendario(*colab, mes, ano);
        } else {
            std::cout << "Data invalida!\n";
        }
    } else {
        std::cout << "Colaborador nao encontrado.\n";
    }
}