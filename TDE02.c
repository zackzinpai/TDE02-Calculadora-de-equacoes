#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>   // para ajudar a ler as strings completas
#include <math.h>     // usei para o  sqrt

// --- FUNÇÕES DE CALCULO E AUXILIARES ---

// Função para remover espaços e quebras de linha da string
void limparString(char *str) {
    int i, j;
    char temp[256];
    strcpy(temp, str);
    
    for (i = 0, j = 0; temp[i] != '\0'; i++) {
        if (temp[i] != ' ' && temp[i] != '\n' && temp[i] != '\r') {
            str[j++] = temp[i];
        }
    }
    str[j] = '\0';
}

// Função para extrair o valor numérico de uma substring, para poder usar frações
double extrairValorNumerico(const char *sub_str, int len) {
    char num_part[50];
    strncpy(num_part, sub_str, len);
    num_part[len] = '\0';

    char *divisor_ptr = strchr(num_part, '/');
    if (divisor_ptr) {
        *divisor_ptr = '\0';
        double numerador = atof(num_part);
        double denominador = atof(divisor_ptr + 1);

        if (denominador == 0) {
            fprintf(stderr, "Erro: Divisao por zero encontrada em uma fracao. Retornando 0.\n");
            return 0.0;
        }
        return numerador / denominador;
    } else {
        return atof(num_part);
    }
}

// --- FUNÇÃO PRINCIPAL DE PARSING (parseEquacao) ---
// Analisa a string da equação e preenche os coeficientes a, b, e c. Esta função é importante demais nesse algoritimo.
void parseEquacao(const char *equacao, double *a, double *b, double *c) {
    char eq_processed[256]; 
    strcpy(eq_processed, equacao);
    limparString(eq_processed); 

    *a = 0.0;
    *b = 0.0;
    *c = 0.0;

    char *ptr = eq_processed;
    char *end_of_eq_marker = strstr(eq_processed, "=0");
    if (end_of_eq_marker) {
        *end_of_eq_marker = '\0'; // Trunca a string antes de "=0"
    }
    
    char current_sign = '+';
    int term_start_index = 0; // Marca o início do termo atual dentro de eq_processed

    for (int i = 0; eq_processed[i] != '\0'; i++) {
        // Quando encontra um sinal de '+' ou '-' (que não seja o primeiro caractere se for um '-' no começo)
        if ((eq_processed[i] == '+' || eq_processed[i] == '-') && i > 0) {
            // Processa o termo  lido (do term_start_index até i)
            char temp_term_str[100];
            strncpy(temp_term_str, eq_processed + term_start_index, i - term_start_index);
            temp_term_str[i - term_start_index] = '\0';
            
            double term_value;
            char *x2_pos = strstr(temp_term_str, "x^2");
            char *x_pos = strchr(temp_term_str, 'x');

            if (x2_pos) { // Termo x^2
                int num_len = x2_pos - temp_term_str;
                if (num_len == 0) term_value = 1.0;
                else if (num_len == 1 && temp_term_str[0] == '-') term_value = -1.0;
                else term_value = extrairValorNumerico(temp_term_str, num_len);
                
                if (current_sign == '-') *a -= term_value; else *a += term_value;
            } else if (x_pos) { // Termo x
                int num_len = x_pos - temp_term_str;
                if (num_len == 0) term_value = 1.0;
                else if (num_len == 1 && temp_term_str[0] == '-') term_value = -1.0;
                else term_value = extrairValorNumerico(temp_term_str, num_len);

                if (current_sign == '-') *b -= term_value; else *b += term_value;
            } else { // Termo que é constante
                term_value = extrairValorNumerico(temp_term_str, strlen(temp_term_str));
                if (current_sign == '-') *c -= term_value; else *c += term_value;
            }

            // Atualiza o sinal para o próximo termo e o índice de início do próximo termo
            current_sign = eq_processed[i];
            term_start_index = i + 1;
        }
    }

    // Processa o último termo da string (após o loop, pois ele não é seguido por um sinal)
    if (strlen(eq_processed) > term_start_index) {
        char temp_term_str[100];
        strncpy(temp_term_str, eq_processed + term_start_index, strlen(eq_processed) - term_start_index);
        temp_term_str[strlen(eq_processed) - term_start_index] = '\0';
        
        double term_value;
        char *x2_pos = strstr(temp_term_str, "x^2");
        char *x_pos = strchr(temp_term_str, 'x');

        if (x2_pos) {
            int num_len = x2_pos - temp_term_str;
            if (num_len == 0) term_value = 1.0;
            else if (num_len == 1 && temp_term_str[0] == '-') term_value = -1.0;
            else term_value = extrairValorNumerico(temp_term_str, num_len);
            
            if (current_sign == '-') *a -= term_value; else *a += term_value;
        } else if (x_pos) {
            int num_len = x_pos - temp_term_str;
            if (num_len == 0) term_value = 1.0;
            else if (num_len == 1 && temp_term_str[0] == '-') term_value = -1.0;
            else term_value = extrairValorNumerico(temp_term_str, num_len);

            if (current_sign == '-') *b -= term_value; else *b += term_value;
        } else {
            term_value = extrairValorNumerico(temp_term_str, strlen(temp_term_str));
            if (current_sign == '-') *c -= term_value; else *c += term_value;
        }
    }
}

int main() {
    char equacao_str[256];
    double a, b, c;
    double delta;
    double x1, x2;

    // INSTRUÇÕES DE USO, DESCULPE O NOME DO TRABALHO, NÃO RESISTI, NÃO TIRE PONTOS POR FAVOR.
    printf("--- SUPER HIPER MEGA RESOLVEDOR DE EQUACOES ---]\n");
    printf("------------------------------------------------------------\n");
    printf("---INSTRUCOES DE USO---\n");
    printf("Digite a equacao no formato : ax^2+bx+c=0.\n");
    printf("Exemplos: x^2+2x+1=0 ou 6x+10=0\n");
    printf("Pode ser usado numeros decimais e fracoes\n");
    printf("As solucoes reais vao ser mostradas\n");
    printf("------------------------------------------------------------\n");
    
    printf("Digite a equacao: "); 
    fgets(equacao_str, sizeof(equacao_str), stdin);

    equacao_str[strcspn(equacao_str, "\n")] = 0;

    parseEquacao(equacao_str, &a, &b, &c);

    printf("\n--- Analise da Equacao ---\n");
    printf("Equacao digitada: %s\n", equacao_str);
    printf("Coeficientes extraidos: a=%.4f, b=%.4f, c=%.4f\n", a, b, c);

    if (a == 0) { // Equação de 1º grau (bx + c = 0)
        printf("Grau: 1o grau | ");
        if (b == 0) {
            if (c == 0) {
                printf("Possui Solucao Real: Sim (Infinitas) | Solucao: Qualquer X\n");
            } else {
                printf("Possui Solucao Real: Nao | Solucao: X=N.A. (Equacao Impossivel: 0 = c, onde c != 0)\n");
            }
        } else {
            x1 = -c / b;
            printf("Possui Solucao Real: Sim | Solucao: x=%.4f\n", x1);
        }
    } else { // Equação de 2º grau (ax^2 + bx + c = 0)
        printf("Grau: 2o grau | ");
        delta = b * b - 4 * a * c;

        if (delta >= 0) {
            printf("Possui Solucao Real: Sim | ");
            if (delta == 0) {
                x1 = -b / (2 * a);
                printf("Solucao: x=%.4f\n", x1);
            } else {
                x1 = (-b + sqrt(delta)) / (2 * a);
                x2 = (-b - sqrt(delta)) / (2 * a);
                printf("Solucao: x1=%.4f, x2=%.4f\n", x1, x2);
            }
        } else {
            printf("Possui Solucao Real: Nao | Solucao: x=N.A.\n");
        }
    }

    system("pause");
    return 0;
}