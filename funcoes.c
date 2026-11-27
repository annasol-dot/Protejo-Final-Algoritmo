#include <stdio.h>
#include <string.h>
#include "funcoes.h"

#define MAX 100

char letras[3] = {'N', 'P', 'U'};
char nomes[3][15] = {"Normal", "Preferencial", "Urgente"};

int fila[3][MAX];
char pacientes[3][MAX][50];
int quantidade[3];   
int contador[3];     

int emAtendimento = 0;  
int categoriaAtual;
int numeroAtual;
char nomeAtual[50];

int lerInteiro(char mensagem[], int minimo, int maximo)
{
    int valor, c;

    while (1) {
        printf("%s", mensagem);

        if (scanf("%d", &valor) != 1) {
            printf("Entrada invalida! Digite apenas numeros.\n");
            while ((c = getchar()) != '\n' && c != EOF);   /* limpa o teclado */
        } else if (valor < minimo || valor > maximo) {
            printf("Valor fora do intervalo (%d a %d).\n", minimo, maximo);
        } else {
            return valor;
        }
    }
}

void lerNome(char mensagem[], char nome[])
{
    int c;

    printf("%s", mensagem);
    scanf(" %49[^\n]", nome);                      
    while ((c = getchar()) != '\n' && c != EOF);   
}

/*  Cadastro, classificacao e senha  */

int classificar(int genero, int idade, int gestante, int lactante,
                int especial, int obeso)
{
    if (idade > 80) {
        return 2;
    }

    if (gestante == 1 || lactante == 1 || especial == 1 || obeso == 1) {
        return 1;
    }
    if (genero == 1 && idade >= 60) {  
        return 1;
    }
    if (genero == 2 && idade >= 65) {  
        return 1;
    }

    return 0;
}

void gerarSenha(int categoria, char nome[])
{
    if (quantidade[categoria] >= MAX || contador[categoria] >= 999) {
        printf("\nFila cheia! Nao foi possivel gerar a senha.\n");
        return;
    }

    contador[categoria]++;
    fila[categoria][quantidade[categoria]] = contador[categoria];
    strcpy(pacientes[categoria][quantidade[categoria]], nome);
    quantidade[categoria]++;

    printf("\nSenha gerada: %c%03d (%s) - %s\n",
           letras[categoria], contador[categoria], nomes[categoria], nome);
}

void cadastrarPaciente(void)
{
    int genero, idade, gestante = 0, lactante = 0, especial, obeso, categoria;
    char nome[50];

    printf("\n--- Cadastro de paciente ---\n");
    lerNome("Nome do paciente: ", nome);
    genero = lerInteiro("Genero (1 - Feminino, 2 - Masculino): ", 1, 2);
    idade  = lerInteiro("Idade: ", 0, 130);

    if (genero == 1) {  
        gestante = lerInteiro("Gestante? (1 - Sim, 0 - Nao): ", 0, 1);
        lactante = lerInteiro("Lactante? (1 - Sim, 0 - Nao): ", 0, 1);
    }

    especial = lerInteiro("Necessidade especial? (1 - Sim, 0 - Nao): ", 0, 1);
    obeso    = lerInteiro("Obesidade? (1 - Sim, 0 - Nao): ", 0, 1);

    categoria = classificar(genero, idade, gestante, lactante, especial, obeso);
    gerarSenha(categoria, nome);
}

/*  Filas e atendimento */

int proximaCategoria(void)
{
    int c;

    for (c = 2; c >= 0; c--) {
        if (quantidade[c] > 0) {
            return c;
        }
    }
    return -1;
}

void consultarProxima(void)
{
    int c = proximaCategoria();

    if (c == -1) {
        printf("\nNao ha senhas aguardando.\n");
    } else {
        printf("\nProxima senha: %c%03d (%s) - %s\n",
               letras[c], fila[c][0], nomes[c], pacientes[c][0]);
    }
}

void chamarPaciente(void)
{
    int c, i;

    if (emAtendimento == 1) {
        printf("\nJa existe um atendimento em andamento. Finalize antes.\n");
        return;
    }

    c = proximaCategoria();
    if (c == -1) {
        printf("\nNao ha senhas aguardando.\n");
        return;
    }

    categoriaAtual = c;
    numeroAtual = fila[c][0];
    strcpy(nomeAtual, pacientes[c][0]);
    emAtendimento = 1;

    for (i = 0; i < quantidade[c] - 1; i++) {
        fila[c][i] = fila[c][i + 1];
        strcpy(pacientes[c][i], pacientes[c][i + 1]);
    }
    quantidade[c]--;

    printf("\nChamando a senha %c%03d (%s) - %s!\n",
           letras[c], numeroAtual, nomes[c], nomeAtual);
}

void mostrarAtual(void)
{
    if (emAtendimento == 0) {
        printf("\nNinguem esta sendo atendido agora.\n");
    } else {
        printf("\nEm atendimento: %c%03d (%s) - %s\n",
               letras[categoriaAtual], numeroAtual, nomes[categoriaAtual], nomeAtual);
    }
}

void finalizarAtendimento(void)
{
    if (emAtendimento == 0) {
        printf("\nNao ha atendimento para finalizar.\n");
        return;
    }

    printf("\nAtendimento da senha %c%03d finalizado.\n",
           letras[categoriaAtual], numeroAtual);
    salvarAtendimento();  
    emAtendimento = 0;

    consultarProxima();  
}

/* Historico em arquivo  */

void salvarAtendimento(void)
{
    FILE *arquivo;

    arquivo = fopen("atendidos.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de historico.\n");
        return;
    }

    fprintf(arquivo, "%c%03d - %s - %s\n",
            letras[categoriaAtual], numeroAtual, nomes[categoriaAtual], nomeAtual);

    fclose(arquivo);
}

void mostrarHistorico(void)
{
    FILE *arquivo;
    char linha[100];

    arquivo = fopen("atendidos.txt", "r");

    if (arquivo == NULL) {
        printf("\nAinda nao ha historico de atendimentos.\n");
        return;
    }

    printf("\n--- Historico de atendidos ---\n");
    while (fgets(linha, 100, arquivo) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivo);
}

/*  Telas */

void mostrarPainel(void)
{
    int c, i, mostradas = 0;

    printf("\n========== PAINEL DE CHAMADA ==========\n");

    if (emAtendimento == 1) {
        printf("Senha chamada: %c%03d\n", letras[categoriaAtual], numeroAtual);
        printf("Paciente     : %s\n", nomeAtual);
        printf("Categoria    : %s\n", nomes[categoriaAtual]);
    } else {
        printf("Senha chamada: --\n");
        printf("Paciente     : --\n");
        printf("Categoria    : --\n");
    }

    printf("Proximas     : ");
    for (c = 2; c >= 0; c--) {
        for (i = 0; i < quantidade[c] && mostradas < 5; i++) {
            printf("%c%03d ", letras[c], fila[c][i]);
            mostradas++;
        }
    }
    if (mostradas == 0) {
        printf("(nenhuma)");
    }

    printf("\n---------------------------------------\n");
    printf("Esperando - Urgente     : %d\n", quantidade[2]);
    printf("Esperando - Preferencial: %d\n", quantidade[1]);
    printf("Esperando - Normal      : %d\n", quantidade[0]);
    printf("=======================================\n");
}

void mostrarMenu(void)
{
    printf("\n===== SISTEMA DE SENHAS DA CLINICA =====\n");
    printf("1 - Cadastrar paciente (gerar senha)\n");
    printf("2 - Consultar proxima senha\n");
    printf("3 - Chamar paciente\n");
    printf("4 - Ver senha em atendimento\n");
    printf("5 - Finalizar atendimento\n");
    printf("6 - Painel de chamada\n");
    printf("7 - Ver historico de atendidos\n");
    printf("0 - Sair\n");
}