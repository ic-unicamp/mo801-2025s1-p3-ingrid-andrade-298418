# Repositório base para o Projeto 3

**Aluno:** Ingrid Andrade de Aguiar
**RA:** 298418

---

## Breve descrição dos objetivos

O principal objetivo deste projeto foi explorar a plataforma LiteX, criando e rodando um programa baremetal (sem sistema operacional) em um SoC simulado com CPU VexRiscv.

O projeto teve várias etapas, e consegui realizar as seguintes:

* Portei um programa de multiplicação de matrizes (`matmul.c`) para o ambiente LiteX.
* Compilei o código para RISC-V usando a toolchain adequada.
* Rodei o firmware no simulador LiteX/Verilator e medi o desempenho usando o comando `time`.
* Fiz três versões do matmul trocando a ordem dos loops para testar desempenho.
* Testei uma rede neural simples (MLP para resolver XOR) treinada em Python e reimplementada em C para rodar no LiteX.
* Implementei a UART diretamente para imprimir resultados, já que não tinha suporte à biblioteca padrão (`printf`, `puts`).
* Documentei todas as etapas com prints, gráficos, tabelas e explicações no relatório em PDF.

Com isso, consegui cumprir os principais objetivos propostos pelo projeto.

---

## Desafios encontrados

Durante o projeto, enfrentei vários desafios técnicos. Abaixo explico alguns dos principais e como consegui resolver:

1. **Simulador não encerrava sozinho:**

   * Depois que o programa terminava de rodar, o simulador continuava aberto.
   * Tentei usar a instrução especial `ebreak` para parar, mas não funcionou.
   * Solução foi ficar de olho na UART e apertar `Ctrl+C` no terminal assim que o programa terminava.

2. **Não tinha `printf` no baremetal:**

   * O código baremetal não tem acesso à biblioteca padrão do C, então `printf()` dava erro.
   * Resolvi isso acessando diretamente a UART (endereço de memória `0xe0001800`) e escrevendo caractere por caractere.

3. **Portar rede neural (TinyML) sem `math.h`:**

   * Ao implementar a inferência do XOR em C, não podia usar `tanh()` nem `sigmoid()` da biblioteca padrão.
   * Recriei versões aproximadas dessas funções usando polinômios simples, o que é comum em embarcados.

4. **Erros ao simular o SoC com Litescope:**

   * Alguns erros de Python apareciam por conta de nomes de clock ou registradores não especificados.
   * Tive que editar manualmente partes do código do LiteX para declarar `ClockDomain("sys")` e `CSRStorage(name="...")`.

5. **Ambiente Python não reconhecia pacotes:**

   * O pacote `litescope` não era encontrado pelo Python.
   * Consertei isso configurando corretamente a variável `PYTHONPATH` e reinstalando o pacote com `pip install -e .`.

---

## Barreiras alcançadas

Nem todos os desafios foram resolvidos completamente. Algumas barreiras ficaram como limitações do projeto:

1. **Encerramento automático do simulador:**

   * Mesmo com várias tentativas, não consegui fazer o simulador LiteX fechar sozinho quando o programa termina. Precisa sempre de `Ctrl+C`.

2. **Implementar um acelerador em hardware:**

   * Embora tenha estudado sobre isso, não tive tempo suficiente para implementar um bloco LiteX customizado (como um acelerador matmul por hardware).

3. **Matrizes maiores no matmul:**

   * Usei N=16 para não estourar a pilha. Queria testar com matrizes maiores, mas não consegui ajustar a stack no linker para isso.

---

## Comentários gerais e conclusões

Esse projeto foi uma experiência muito rica. Aprendi na prática como funciona a execução baremetal em um SoC simulado, como portar código C para RISC-V, e como lidar com um ambiente embarcado sem bibliotecas padrão.

Além disso:

* Entendi melhor como funcionam os acessos à UART, o uso de `volatile`, e o mapeamento de memória em periféricos.
* Vi que é possível rodar até mesmo redes neurais simples (TinyML) em plataformas assim, com as devidas adaptações.
* Acompanhei todo o ciclo: escrever o código, compilar, gerar o binário, rodar na simulação e interpretar os resultados.

Mesmo com dificuldades (como a simulação não parar sozinha e limitações da biblioteca), consegui atingir os objetivos principais e entregar um projeto completo, com documentação, código, medições e aprendizados bem descritos.

Foi uma ótima oportunidade para juntar conhecimentos de programação, arquitetura de computadores e sistemas embarcados em um projeto prático.

---

> ✅ Código e versões testadas: `matmul.c`, `matmul_ikj.c`, `matmul_kij.c`, `mlp_xor_litex.c`
> ✅ Scripts de compilação e execução incluídos
> ✅ Resultados impressos via UART no simulador
> ✅ Comparações de desempenho feitas com `time`
> ✅ Relatório PDF completo entregue no Classroom
> ✅ Repositório com todos os arquivos:
> [https://github.com/ic-unicamp/mo801-2025s1-p3-ingrid-andrade-298418](https://github.com/ic-unicamp/mo801-2025s1-p3-ingrid-andrade-298418)
