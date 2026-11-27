#ifndef FUNCOES_H
#define FUNCOES_H

/* Entrada de dados */
int  lerInteiro(char mensagem[], int minimo, int maximo);
void lerNome(char mensagem[], char nome[]);

/* Cadastro, classificacao e senha */
int  classificar(int genero, int idade, int gestante, int lactante,
                 int especial, int obeso);
void gerarSenha(int categoria, char nome[]);
void cadastrarPaciente(void);

/* Filas e atendimento */
int  proximaCategoria(void);
void consultarProxima(void);
void chamarPaciente(void);
void mostrarAtual(void);
void finalizarAtendimento(void);

/* Arquivo de historico */
void salvarAtendimento(void);
void mostrarHistorico(void);

/* Telas */
void mostrarPainel(void);
void mostrarMenu(void);

#endif