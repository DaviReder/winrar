## 📦 Huffman File Compressor
Este repositório contém uma implementação inicial do algoritmo de Codificação de Huffman desenvolvida em linguagem C. O projeto faz parte dos meus estudos práticos sobre Algoritmos e Estruturas de Dados, com foco em manipulação de arquivos binários e compressão de dados.

O objetivo principal deste projeto é consolidar conhecimentos fundamentais de programação de baixo nível, explorando como a frequência de caracteres pode ser utilizada para reduzir o tamanho físico de arquivos de texto.

---

## 🛠️ Funcionalidades Atuais
No estágio atual de desenvolvimento, o programa opera de forma simplificada para validação da lógica de compressão:
Leitura de Arquivo: O programa busca por um arquivo de entrada obrigatório nomeado como log.txt.
Mapeamento de Frequências: Realiza a contagem de ocorrências de cada caractere para a construção da árvore.
Geração de Binário: Codifica o conteúdo e gera um arquivo de saída chamado compactado.dc.
Nota: Atualmente, a descompressão requer que a árvore de Huffman permaneça na memória da sessão de execução, servindo como uma Prova de Conceito (PoC).

---

## 🚀 Como Rodar o Projeto

Para compilar e executar este projeto, você precisará de um ambiente com o compilador `gcc` instalado.
Abra o terminal e execute:

```bash
git clone [https://github.com/DaviReder/winrar.git](https://github.com/DaviReder/winrar.git)
cd winrar
gcc main.c -o huffman
./huffman
```

## 📈 Próximos Passos (Roadmap)

Este projeto está em desenvolvimento. As próximas melhorias planejadas são:
*   **Implementação de Cabeçalho (Header):** Adicionar a serialização da árvore de Huffman dentro do arquivo compactado para permitir a descompressão independente.
*   **Entrada Dinâmica:** Permitir que o usuário escolha o nome do arquivo de entrada via argumentos de linha de comando.
*   **Otimização de Bits:** Refinar o buffer de escrita para garantir que o preenchimento (padding) do último byte seja tratado de forma eficiente.

---

**Sobre o autor:** Estudante da **PUCMG**.
*O intuito deste projeto é puramente didático, servindo como base para fortificar o aprendizado em estruturas de dados complexas e otimização de software.*
*Sinta-se à vontade para explorar e sugerir melhorias!*
