# Protejo-Final-Algoritmo

## Sistema de Gerenciamento de Senhas — Clínica de Especialidades

Programa em **linguagem C**, executado no terminal, que informatiza a triagem e a organização das filas de atendimento de uma clínica. O sistema cadastra pacientes, classifica cada um em uma categoria de prioridade, emite senhas sequenciais e controla a ordem de chamada.

## Funcionalidades

- Cadastro de pacientes (nome, gênero, idade, gestante, lactante, necessidade especial e obesidade)
- Classificação automática em **Normal**, **Preferencial** ou **Urgente**
- Emissão de senhas com numeração independente por categoria (`N001`, `P001`, `U001`...)
- Consulta da próxima senha a ser chamada
- Chamada do paciente, identificação da senha em atendimento e finalização do atendimento
- Painel de chamada com a senha atual, as próximas senhas e a quantidade de pacientes em espera por categoria
- Histórico dos atendimentos finalizados, gravado no arquivo `atendidos.txt`
- Validação das entradas do usuário (letras no lugar de números, valores fora do intervalo, operações inválidas)

## Regras de classificação

| Código | Categoria | Condição |
|---|---|---|
| `U001` | Urgente | Pacientes com idade **superior a 80 anos** |
| `P001` | Preferencial | Gestantes, lactantes, pessoas com necessidades especiais, pessoas obesas, mulheres com 60 anos ou mais e homens com 65 anos ou mais |
| `N001` | Normal | Pacientes sem condições de prioridade cadastradas |

## Ordem de chamada

1. Senhas **urgentes** são chamadas antes das preferenciais e das normais.
2. Senhas **preferenciais** são chamadas antes das normais.
3. Dentro de cada categoria vale a ordem de emissão (**FIFO**: primeiro a entrar, primeiro a ser chamado).
4. Uma senha já atendida não volta para a fila.

## Estrutura do projeto

```
.
├── main.c        # menu principal; chama as funções, sem lógica própria
├── funcoes.h     # declarações (protótipos) das funções
├── funcoes.c     # implementação de todas as funções do sistema
└── README.md
```

## Como executar

### No OnlineGDB

1. Acesse [onlinegdb.com](https://www.onlinegdb.com) e escolha a linguagem **C**.
2. Cole o conteúdo de `main.c` no arquivo principal.
3. Crie os arquivos `funcoes.h` e `funcoes.c` e cole o conteúdo de cada um.
4. Com o `main.c` aberto, clique em **Run**.

### No computador (GCC)

```bash
gcc main.c funcoes.c -o clinica
./clinica
```

## Menu do sistema

```
===== SISTEMA DE SENHAS DA CLINICA =====
1 - Cadastrar paciente (gerar senha)
2 - Consultar proxima senha
3 - Chamar paciente
4 - Ver senha em atendimento
5 - Finalizar atendimento
6 - Painel de chamada
7 - Ver historico de atendidos
0 - Sair
```

## Exemplo de uso

Cadastro de uma paciente de 85 anos:

```
Nome do paciente: Maria Silva
Genero (1 - Feminino, 2 - Masculino): 1
Idade: 85
Gestante? (1 - Sim, 0 - Nao): 0
Lactante? (1 - Sim, 0 - Nao): 0
Necessidade especial? (1 - Sim, 0 - Nao): 0
Obesidade? (1 - Sim, 0 - Nao): 0

Senha gerada: U001 (Urgente) - Maria Silva
```

Painel de chamada com a senha `U001` em atendimento e dois pacientes aguardando:

```
========== PAINEL DE CHAMADA ==========
Senha chamada: U001
Paciente     : Maria Silva
Categoria    : Urgente
Proximas     : P001 N001
---------------------------------------
Esperando - Urgente     : 0
Esperando - Preferencial: 1
Esperando - Normal      : 1
=======================================
```

## Histórico de atendimentos

Cada atendimento finalizado é acrescentado ao arquivo `atendidos.txt`, no formato:

```
U001 - Urgente - Maria Silva
P001 - Preferencial - Ana
N001 - Normal - Joao Pedro de Souza
```

No computador, o arquivo é criado na mesma pasta do programa e acumula os registros entre as execuções. No OnlineGDB ele existe apenas durante a execução.

## Limitações

- Cada fila comporta até 100 pacientes aguardando, e a numeração vai até 999 por categoria.
- Os dados ficam apenas na memória: ao encerrar o programa, as filas são perdidas (somente o histórico é gravado em arquivo).

