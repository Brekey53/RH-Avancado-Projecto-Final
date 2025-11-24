# 📅 Sistema de Gestão de RH e Férias

Bem-vindo ao **Sistema de Gestão de RH**, uma aplicação em C++ desenvolvida para facilitar a administração de colaboradores, marcação de férias/faltas e visualização de calendários. Este projeto foi desenvolvido no âmbito da UC00607.

## 🚀 Funcionalidades Principais

- **👥 Gestão de Colaboradores**: Adicionar, listar e buscar colaboradores por ID ou Nome.
- **📅 Controlo de Ausências**: Marcar e desmarcar férias ('F') e faltas ('X'), com validação de dias úteis e deteção de conflitos de férias no mesmo departamento.
- **👁️ Visualização Gráfica**: Calendários mensais detalhados e relatórios visuais diretamente na consola.
- **📊 Estatísticas e Relatórios**: Análise de ausências por departamento, dashboard resumido e exportação de relatórios para `.txt`.
- **🔒 Segurança e Persistência**: Os dados são guardados automaticamente em ficheiro (`DBrh.csv`) com **encriptação pedagógica** (Cifra de César) aplicada aos nomes dos colaboradores.
- **🎓 Extras**: Gestão de formações e notas internas dos colaboradores.

## 📂 Estrutura do Projeto

O código está organizado seguindo o padrão **MVC (Model-View-Controller)** para garantir modularidade e facilidade de manutenção.

```plaintext
CalendarioFerias/
├── 📂 Controllers/       # Lógica de negócio e gestão de dados
│   ├── rh.cpp            # Implementação das funções de RH
│   └── rh.h              # Declarações das funções de RH
│
├── 📂 Models/            # Estruturas de dados e persistência
│   ├── colaborador.h     # Definição da struct Colaborador
│   ├── cifra.cpp         # Algoritmo de encriptação
│   └── io.cpp            # Leitura e escrita de ficheiros
│
├── 📂 Views/             # Interface visual e apresentação
│   ├── calendario.cpp    # Desenho do calendário na consola
│   └── calendario.h      # Cabeçalhos da vista
│
├── 📄 main.cpp           # Ponto de entrada e Menu Principal
├── 📄 DBrh.csv           # Base de dados (gerada automaticamente)
└── 📄 README.md          # Documentação do projeto
```

## 🛠️ Como Compilar e Executar

Para executar este projeto, necessita de um compilador C++ instalado (como o G++).

### 1. Compilação

Abra o terminal na pasta raiz do projeto (`CalendarioFerias`) e execute o seguinte comando para compilar todos os ficheiros necessários:

```bash
g++ main.cpp Controllers/rh.cpp Models/io.cpp Models/cifra.cpp Views/calendario.cpp -o rh_app.exe
```

### 2. Execução

Após a compilação bem-sucedida, execute o programa gerado:

**Windows (CMD/PowerShell):**

```cmd
.\rh_app.exe
```

**Linux/macOS:**

```bash
./rh_app.exe
```

## 📝 Notas Adicionais

- **Base de Dados**: O ficheiro `DBrh.csv` será criado automaticamente na primeira execução se não existir.
- **Encriptação**: Os nomes no ficheiro CSV estão cifrados. O programa desencripta-os automaticamente ao carregar os dados.

## 👤 Autor

**André Correia**
<br>
[![GitHub](https://img.shields.io/badge/GitHub-Brekey53-181717?style=for-the-badge&logo=github)](https://github.com/Brekey53)

---

_Projeto desenvolvido para a disciplina de RH Avançado._
