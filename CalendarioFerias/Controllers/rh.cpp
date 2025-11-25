#include "rh.h"
#include "../Models/colaborador.h"
#include "../Views/calendario.h"

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <cstdlib> // para system
#include <map>
#include <iomanip> // Para std::setw e std::left


// Adiciona um novo colaborador à lista
void adicionarColaborador(std::vector<Colaborador>& lista){
    
    std::string nomeNovo;
    std::string deptNovo;
    
    // Calcula o novo ID automaticamente para ser único
    int idNovo = 0;
    if (!lista.empty()) {
        int maxId = -1;
        for (const auto& colab : lista) {
            if (colab.id > maxId) {
                maxId = colab.id;
            }
        }
        idNovo = maxId + 1;
    }
    //idNovo++; // Incrementa para obter o próximo ID

    std::cin.ignore(1000, '\n'); // limpar buffer
    // Solicita o nome
    std::cout << "Introduza o nome do colaborador a adicionar: ";
    std::getline(std::cin, nomeNovo);

    // Verifica se já existe um colaborador com este nome (opcional, mas boa prática)
    Colaborador* colaborador = encontrarColaborador(lista, nomeNovo);

    if (colaborador == nullptr){
        // Solicita o departamento
        std::cout << "Introduza o departamento: ";
        std::getline(std::cin, deptNovo);

        // Cria o novo objeto Colaborador e preenche os dados
        Colaborador novoColaborador;
        novoColaborador.id = idNovo;
        novoColaborador.nome = nomeNovo;
        novoColaborador.departamento = deptNovo;

        // Adiciona à lista principal
        lista.push_back(novoColaborador);

        std::cout << "\033[32m" << "Colaborador adicionado com sucesso!\n" << "\033[0m";
        
    } else {
        std::cout << "\033[31m" << "Ja existe um colaborador com esse nome!\n" << "\033[0m";
    }

}


// Lista todos os colaboradores registados
void listarColaboradores(const std::vector<Colaborador>& lista){
    std::cout << "\n------------" << "\033[34m" << " Lista de Colaboradores " << "\033[0m" << "------------\n" << std::endl;

    if (lista.empty()){
        std::cout << "\033[31m" << "De momento nenhum colaborador encontra-se resgistado.\n" << "\033[0m";
        return;
    }

    // Encontra o comprimento máximo do nome e do departamento para alinhar as colunas
    size_t max_nome_len = 0;
    for (const auto& colab : lista) {
        if (colab.nome.length() > max_nome_len) {
            max_nome_len = colab.nome.length();
        }
    }

    // Percorre a lista e imprime os dados básicos
    for (const auto& colab : lista) {
        std::cout << "ID: " << std::setw(3) << colab.id << " | "
                  << "Nome: " << std::left << std::setw(max_nome_len + 2) << colab.nome << " | " //std:left e std::setw para espaçamento na consola
                  << "Dept: " << colab.departamento 
                  << std::right << std::endl; // Restaura o alinhamento padrão para a próxima linha
    }

    std::cout << "-------------------------------------------------\n" << std::endl;
}

// Encontra um colaborador pelo nome (case-insensitive)
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

// Encontra um colaborador pelo ID
Colaborador* encontrarColaboradorPorId(std::vector<Colaborador>& lista, int id) {
    for (auto& colab : lista) {
        if (colab.id == id) {
            return &colab;
        }
    }
    return nullptr;
}

// Função principal para marcar férias ou faltas
void marcarAusencia(std::vector<Colaborador>& lista){  
    std::string nomeColaborador;
    
    std::cout << "Introduza o nome do colaborador: ";
    std::cin.ignore(1000, '\n'); 
    std::getline(std::cin, nomeColaborador);

    Colaborador* colaborador = encontrarColaborador(lista, nomeColaborador);

    if (colaborador != nullptr){
        int diaA, mesA, anoA;
        char tipo;

        // Loop para garantir uma data válida
        while (true){
            std::cout << "Introduza o dia, mes e ano\n"; 
            std::cout << "Dia: "; std::cin >> diaA;
            std::cout << "Mes: "; std::cin >> mesA;
            std::cout << "Ano: "; std::cin >> anoA;

            int maxDias = diasNoMes(mesA, anoA);
            bool dataValida = true;

            if (diaA <= 0 || diaA > maxDias) dataValida = false;
            if (mesA <= 0 || mesA > 12) dataValida = false;
            if (anoA < 0 || anoA > 9999) dataValida = false;

            if (dataValida) break;
            else std::cout << "Data invalida, tente de novo\n";
        }

        // Verifica se a data é um fim de semana
        int diaDaSemana = diaSemana(diaA, mesA, anoA);
        if (diaDaSemana == 0 || diaDaSemana == 6) { // 0=Domingo, 6=Sábado
            std::cout << "\033[31m" << "Nao e possivel marcar ausencias ao fim de semana (Sabado/Domingo).\n" << "\033[0m";
            return; // Interrompe a função
        }

        // Loop para garantir um tipo de marcação válido
        do{
            std::cout << "Tipo de marcacao ('F'- Ferias, 'X' - Falta, 'L' - Limpar): ";
            std::cin >> tipo;
            tipo = std::toupper(tipo); 
            
            if (tipo == 'L'){
                // Remover marcação existente
                bool encontrada = false;
                for (int i = 0; i < colaborador->falta.size(); ++i) {
                    Faltas& f = colaborador->falta[i];
                    if (f.dia == diaA && f.mes == mesA && f.ano == anoA) {
                        // O método erase() remove o elemento apontado pelo iterador.
                        // colaborador->falta.begin() retorna um iterador para o início do vetor.
                        // Ao somar 'i', obtemos o iterador para o elemento na posição exata
                        // da marcação que queremos remover.
                        colaborador->falta.erase(colaborador->falta.begin() + i); 
                        encontrada = true;
                        std::cout << "Marcacao removida.\n";
                        break; // Interrompe o loop, pois a marcação já foi encontrada e removida.
                    }
                }
                if (!encontrada) std::cout << "Nenhuma marcacao encontrada.\n";

            } else if (tipo == 'F' || tipo == 'X'){ 
                // Verificar conflito de férias (apenas se for marcar Férias)
                if (tipo == 'F') {
                     for(const auto& c : lista) {
                         // Verifica outros colaboradores do mesmo departamento (excluindo o próprio)
                         if (c.departamento == colaborador->departamento && c.id != colaborador->id) {
                             for(const auto& f : c.falta) {
                                 if (f.dia == diaA && f.mes == mesA && f.ano == anoA && std::toupper(f.tipoDeFalta) == 'F') {
                                     std::cout << "\033[33m[AVISO] Conflito de ferias! Outro colaborador do mesmo departamento tem ferias neste dia.\033[0m\n";
                                 }
                             }
                         }
                     }
                }

                // Adicionar nova falta/férias
                Faltas novaFalta;
                novaFalta.ano = anoA;
                novaFalta.mes = mesA;
                novaFalta.dia = diaA;
                novaFalta.tipoDeFalta = tipo;
                colaborador->falta.push_back(novaFalta);
                std::cout << "Marcacao '" << tipo << "' adicionada.\n";
            } else {
                std::cout << "Tipo de marcacao invalido, tente de novo!\n";
            }
        } while (tipo != 'L' && tipo != 'X' && tipo != 'F');       

    } else {
        std::cout << "Nenhum colaborador encontrado com esse nome!\n";
    }
}

// Busca um colaborador por ID ou Nome e mostra detalhes
void buscarColaborador(std::vector<Colaborador>& lista) {
    std::cout << "Buscar por (1) ID ou (2) Nome? ";
    int op;
    std::cin >> op;
    std::cin.ignore(1000, '\n');

    Colaborador* colab = nullptr;
    if (op == 1) {
        int id;
        std::cout << "ID: ";
        std::cin >> id;
        colab = encontrarColaboradorPorId(lista, id);
    } else {
        std::string nome;
        std::cout << "Nome: ";
        std::getline(std::cin, nome);
        colab = encontrarColaborador(lista, nome);
    }

    if (colab) {
        std::cout << "ID: " << colab->id << " | Nome: " << colab->nome << " | Dept: " << colab->departamento << "\n";
        int mes, ano;
        std::cout << "Para ver o calendario, introduza mes e ano (ex: 11 2025): ";
        std::cin >> mes >> ano;
        imprimirCalendario(*colab, mes, ano);
    } else {
        std::cout << "Colaborador nao encontrado.\n";
    }
}

// Calcula e mostra estatísticas de ausências por departamento
void estatisticasDepartamento(const std::vector<Colaborador>& lista) {
    // Utiliza um std::map para agregar as estatísticas
    // A chave é o nome do departamento e o valor é um par de inteiros: {férias, faltas}.
    std::map<std::string, std::pair<int, int>> deptStats;

    // Garante que todos os departamentos são inicializados no mapa com valores a zero.
    for (const auto& colab : lista) {
        deptStats.try_emplace(colab.departamento, 0, 0);
    }

    // Itera sobre cada colaborador e as suas respetivas faltas
    for (const auto& colab : lista) {
        for (const auto& f : colab.falta) {
            // O operador[] do map cria o departamento se não existir
            // e permite aceder diretamente aos seus contadores.
            if (toupper(f.tipoDeFalta) == 'F') {
                deptStats[colab.departamento].first++; // Incrementa contador de férias
            } else if (toupper(f.tipoDeFalta) == 'X') {
                deptStats[colab.departamento].second++; // Incrementa contador de faltas
            }
        }
    }

    std::cout << "Estatisticas por Departamento:\n";
    std::string deptMaisAusencias;
    int maxAusencias = -1;

    for (const auto& par : deptStats) {
        std::cout << "Dept: " << par.first << " | Ferias: " << par.second.first << " | Faltas: " << par.second.second << "\n";
        if (par.second.second > maxAusencias) {
            maxAusencias = par.second.second;
            deptMaisAusencias = par.first;
        }
    }
    std::cout << "Departamento com mais faltas: " << deptMaisAusencias << " (" << maxAusencias << ")\n";
}

// Mostra um resumo de férias e faltas para todos os colaboradores
void dashboardResumido(const std::vector<Colaborador>& lista) {
    std::cout << "Nome\t\tFerias\tFaltas\tDias Restantes (Total 22)\n";
    for (const auto& colab : lista) {
        int ferias = 0;
        int faltas = 0;
        for (const auto& f : colab.falta) {
            if (toupper(f.tipoDeFalta) == 'F') ferias++;
            if (toupper(f.tipoDeFalta) == 'X') faltas++;
        }
        std::cout << colab.nome << "\t\t" << ferias << "\t" << faltas << "\t" << (22 - ferias) << "\n";
    }
}

// Gestão de Formações 
void gerirFormacoes(std::vector<Colaborador>& lista) {
    std::string nome;
    std::cout << "\nNome do colaborador: ";
    std::cin.ignore(1000, '\n');
    std::getline(std::cin, nome);
    Colaborador* colab = encontrarColaborador(lista, nome);

    if (!colab) { std::cout << "Nao encontrado.\n"; return; }

    int op;
    do {
        std::cout << "\n1. Listar formacoes\n2. Adicionar formacao\n3. Remover formacao\n4. Editar formacao\n0. Voltar\nOpcao: ";
        std::cin >> op;
        std::cin.ignore(1000, '\n');
        std::cout << std::endl;

        if (op == 1) {
            for (int i = 0; i < colab->formacoes.size(); ++i) {
                std::cout << i+1 << ". " << colab->formacoes[i].nome_curso << " (" << colab->formacoes[i].data_conclusao << ")\n";
            }
        } else if (op == 2) {
            Formacao f;
            std::cout << "Curso: "; 
            std::getline(std::cin, f.nome_curso);

            std::cout << "Data: "; 
            std::getline(std::cin, f.data_conclusao);
            colab->formacoes.push_back(f);
        } else if (op == 3) {
            int idx;
            std::cout << "\n" << "Numero da formacao a remover: ";
            std::cin >> idx;
            if (idx > 0 && idx <= colab->formacoes.size()) {
                colab->formacoes.erase(colab->formacoes.begin() + idx - 1);
            }
        } else if (op == 4){
            int idx;
            std::cout << "\n" << "Numero da formacao a editar: ";
            std::cin >> idx;
            std::cin.ignore(1000, '\n'); // Limpa o buffer de entrada
            if (idx > 0 && idx <= colab->formacoes.size()) {
                std::string novo_nome, nova_data;
                std::cout << "Novo nome do curso (atual: " << colab->formacoes[idx - 1].nome_curso << "): "; 
                std::getline(std::cin, novo_nome);

                std::cout << "Nova data de conclusao (atual: " << colab->formacoes[idx - 1].data_conclusao << "): "; 
                std::getline(std::cin, nova_data);

                colab->formacoes[idx - 1].nome_curso = novo_nome;
                colab->formacoes[idx - 1].data_conclusao = nova_data;
                std::cout << "\033[32m" << "Formacao editada com sucesso!\n" << "\033[0m";
            }
        }
    } while (op != 0);
}

// Gestão de Notas Internas
void gerirNotas(std::vector<Colaborador>& lista) {
    std::string nome;
    std::cout << "\nNome do colaborador: ";
    std::cin.ignore(1000, '\n');
    std::getline(std::cin, nome);
    Colaborador* colab = encontrarColaborador(lista, nome);

    if (!colab) {
        std::cout << "Nao encontrado.\n";
        return;
    }

    int op;
    do {
        std::cout << "\n1. Listar notas\n2. Adicionar nota\n3. Remover nota\n4. Editar nota\n0. Voltar\nOpcao: ";
        std::cin >> op;
        std::cin.ignore(1000, '\n');
        std::cout << std::endl;

        if (op == 1) {
            for (int i = 0; i < colab->notas.size(); ++i) {
                std::cout << i+1 << ". " << colab->notas[i].texto << " (" << colab->notas[i].data << ")\n";
            }
        } else if (op == 2) {
            Nota n;
            std::cout << "Texto: "; std::getline(std::cin, n.texto);
            std::cout << "Data: "; std::getline(std::cin, n.data);
            colab->notas.push_back(n);
        } else if (op == 3) {
            int idx;
            std::cout << "\n" << "Numero da nota a remover: ";
            std::cin >> idx;
            if (idx > 0 && idx <= colab->notas.size()) {
                colab->notas.erase(colab->notas.begin() + idx - 1);
            }
        }else if (op == 4){
            int idx;
            std::cout << "\n" << "Numero da nota a editar: ";
            std::cin >> idx;
            std::cin.ignore(1000, '\n'); // Limpa o buffer de entrada
            if (idx > 0 && idx <= colab->notas.size()) {
                std::string novo_texto, nova_data;
                std::cout << "Novo texto da nota (atual: " << colab->notas[idx - 1].texto << "): "; 
                std::getline(std::cin, novo_texto);

                std::cout << "Nova data (atual: " << colab->notas[idx - 1].data << "): "; 
                std::getline(std::cin, nova_data);

                colab->notas[idx - 1].texto = novo_texto;
                colab->notas[idx - 1].data = nova_data;
                std::cout << "\033[32m" << "Nota editada com sucesso!\n" << "\033[0m";
            }
        }
    } while (op != 0);
}

// Exporta relatório para ficheiro de texto
void exportarRelatorio(const std::vector<Colaborador>& lista) {
    std::ofstream file("relatorio_exportado.txt");
    for (const auto& colab : lista) {
        file << "Colaborador: " << colab.nome << " (" << colab.departamento << ")\n";
        file << "Faltas/Ferias:\n";
        for (const auto& f : colab.falta) {
            file << "  " << f.dia << "/" << f.mes << "/" << f.ano << " - " << f.tipoDeFalta << "\n";
        }
        file << "----------------\n";
    }
    file.close();
    std::cout << "Relatorio exportado para relatorio_exportado.txt\n";
}


void limparEcra() {
#ifdef _WIN32 // Esta macro é definida pelo compilador se estiver no Windows
    std::system("cls");
#else
    // Assume que é um sistema POSIX (Linux, macOS)
    std::system("clear");
#endif
}