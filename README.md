# Compilador MicroPascal (Parte 1)

[![GIT](https://img.shields.io/badge/GIT-F05032?style=for-the-badge&logo=git&logoColor=white)](#)
[![GITHUB](https://img.shields.io/badge/GITHUB-181717?style=for-the-badge&logo=github&logoColor=white)](#)
[![STATUS](https://img.shields.io/badge/STATUS-EM%20DESENVOLVIMENTO-yellow?style=for-the-badge)](#)
[![LICENSE](https://img.shields.io/badge/LICENSE-MIT-green?style=for-the-badge)](#)

Status do Projeto: :warning: (em desenvolvimento) 


---

## Contexto
Projeto desenvolvido para a disciplina de **Construção de Compiladores** na Universidade Católica de Pernambuco (UNICAP), sob orientação do Professor Robson Lins. A proposta desta primeira etapa consiste no desenvolvimento dos módulos iniciais de um compilador para uma versão simplificada da linguagem Pascal, denominada **micro-Pascal**.

## Problema
O processamento de linguagens de programação exige a transformação de código-fonte em estruturas inteligíveis pelo computador. Sem as etapas de análise léxica e sintática adequadas, a validação estrutural de um programa escrito em micro-Pascal não é viável, impedindo a geração e execução posterior do código.


## Objetivo
Implementar as duas primeiras etapas do compilador da linguagem micro-Pascal:
1. **Analisador Léxico (Lexer):** Responsável por tokenizar o código-fonte e identificar erros léxicos.
2. **Analisador Sintático (Parser):** Responsável por verificar a estrutura gramatical conforme a gramática abstrata definida e validar precedências e associatividades.

---

## Funcionalidades e Requisitos

### 1. Analisador Léxico (Lexer)
- [ ] **Reconhecimento de Tokens:**
  - Identificadores (sensível a maiúsculas/minúsculas).
  - Operadores relacionais (`<`, `>`, `<=`, `>=`, `=`, `<>`).
  - Operadores lógico-aritméticos (`+`, `-`, `*`, `/`, `div`, `and`, `or`, `not`).
  - Símbolos especiais (`:`, `;`, `,`, `.`, `(`, `)`).
  - Palavras reservadas (`program`, `if`, `then`, `else`, `while`, `do`, `repeat`, `until`, `integer`, `real`, `char`, `begin`, `end`, `write`, `var`).
  - Literais: inteiros, reais e caracteres (`'a'`, `'\n'`, `'\t'`).
- [ ] **Tratamento de Erros Léxicos:** Emite a mensagem `Erro léxico no caracter [x]`.
- [ ] **Descarte de Caracteres Irrelevantes:** Ignora espaços, quebras de linha (`\n`), tabulações (`\t`) e retorno de cursor (`\r`).

### 2. Analisador Sintático (Parser)
- [ ] **Validação Gramatical:** Análise sintática baseada na Notação BNF para programas, declaração de variáveis, comandos (`if`, `while`, `repeat`, `write`, atribuições) e expressões.
- [ ] **Precedência e Associatividade (à esquerda):**
  1. `*`, `/`, `div`
  2. `+`, `-`
  3. `=`, `<>`, `<`, `>`, `<=`, `>=`
  4. `or`, `and`
- [ ] **Tratamento de Erros Sintáticos:** Emite a mensagem `Erro de sintaxe no token [lexema]`.

---

## Como Executar

### Pré-requisitos
- Ferramenta de compilação/execução da linguagem escolhida.

### Passos
1. Clone o repositório:
   ```bash
   git clone [https://github.com/seu-usuario/seu-repositorio.git](https://github.com/seu-usuario/seu-repositorio.git)
