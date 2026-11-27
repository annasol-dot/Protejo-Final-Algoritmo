#include <stdio.h>
#include "funcoes.h"

int main(void)
{
    int opcao;

    do {
        mostrarMenu();
        opcao = lerInteiro("Escolha uma opcao: ", 0, 7);

        if (opcao == 1) {
            cadastrarPaciente();
        } else if (opcao == 2) {
            consultarProxima();
        } else if (opcao == 3) {
            chamarPaciente();
        } else if (opcao == 4) {
            mostrarAtual();
        } else if (opcao == 5) {
            finalizarAtendimento();
        } else if (opcao == 6) {
            mostrarPainel();
        } else if (opcao == 7) {
            mostrarHistorico();
        }
    } while (opcao != 0);

    printf("\nSistema encerrado.\n");
    return 0;
}