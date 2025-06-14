README - Projeto "Calculadora de Equações em C"

Este projeto consiste no desenvolvimento de um algoritmo de linha de comando em linguagem C, capaz de resolver equações de 1º e 2º grau. O objetivo principal do sistema é aplicar conhecimentos práticos adquiridos no curso de Análise e Desenvolvimento de Sistemas , envolvendo lógica de programação, manipulação avançada de strings e a aplicação de estruturas de dados para resolver um problema matemático real.


Descrição do Projeto
A calculadora funciona inteiramente via terminal, sem uma interface gráfica. O sistema é projetado para receber uma equação completa no formato de string (ex: "ax^2 + bx + c = 0"). A partir dessa entrada, o algoritmo executa uma série de passos:

Limpeza: Remove todos os espaços da string para facilitar a análise.
Parsing: "Lê" a string caractere por caractere para identificar os termos e extrair os coeficientes (a, b, c). Essa é a etapa mais complexa, capaz de interpretar números decimais, fracionários (ex: "1/2x^2") e coeficientes implícitos (ex: "x" é lido como "1x").



Cálculo: Com base nos coeficientes extraídos, o sistema identifica se a equação é de 1º ou 2º grau  e aplica a fórmula correta (solução linear ou Bhaskara) para encontrar as raízes reais. Casos especiais, como equações sem solução real (delta negativo) ou com infinitas soluções, também são tratados.




Estrutura de Arquivos
A estrutura de arquivos do projeto é minimalista e focada em um único código-fonte:

📦 calculadora-equacoes-c/
└── main.c  # Código-fonte principal com a lógica de parsing, cálculo e funções auxiliares.
Tecnologias Utilizadas
Linguagem C: Utilizada para o desenvolvimento completo do algoritmo, desde a manipulação de baixo nível das strings até a execução dos cálculos matemáticos.
Compilador GCC: Ferramenta utilizada para compilar o código-fonte C em um programa executável para o ambiente de linha de comando.
Bibliotecas Padrão:
<string.h>: Fornece o conjunto de funções essenciais para o parsing e manipulação da string da equação.
<math.h>: Utilizada para funções matemáticas, especificamente sqrt() para o cálculo da raiz quadrada no delta de Bhaskara.
Recursos e Funcionalidades
Análise de equações de 1º e 2º grau a partir de uma única string de entrada.
Extração robusta de coeficientes inteiros, decimais e fracionários.
Interpretação de coeficientes implícitos (ex: x^2 se torna 1x^2).
Cálculo preciso de raízes reais com a fórmula de Bhaskara.
Identificação e tratamento de casos especiais (sem solução real, raízes duplas, infinitas soluções).


Funções modulares para limpeza de string, extração de valores e resolução de equações.

Observações
O sistema não possui interface gráfica (GUI) e toda a interação ocorre via linha de comando.
O projeto foi desenvolvido com foco na robustez do parsing da equação, sendo este o seu principal diferencial.

O código foi escrito em C padrão (ANSI C) para garantir a portabilidade e a compilação com o GCC.
Objetivo Acadêmico
Este projeto foi desenvolvido como trabalho discente efetivo para a disciplina de Construção de Algoritmos. Seu propósito é reforçar e validar os conhecimentos em conceitos fundamentais da programação em C, como a gestão de memória com ponteiros, o uso de estruturas de dados (arrays de caracteres), a manipulação de strings, o controle de fluxo e a modularização do código em funções, aplicando-os a um problema prático e desafiador de cálculo algébrico.
