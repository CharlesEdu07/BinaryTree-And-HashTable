# Projeto de Análise de Algoritmos de Ordenação

Este projeto consiste em uma atividade avaliativa da disciplina de Estrutura de Dados.

O objetivo principal deste trabalho é realizar uma análise das estruturas de dados árvore binária e tabela-hash, com foco especial nos tempos de execução da busca em cada estrutura. Além disso, busca-se comparar os diferentes cenários de cada tarefa de busca.

Os códigos desenvolvidos para este projeto foram implementados em linguagem de programação C.

## Requisitos

Antes de executar os códigos deste projeto, certifique-se de ter um compilador C instalado na sua máquina. Recomenda-se o uso do GCC (GNU Compiler Collection).

Também é necessário ter o Gnuplot instalado para gerar os gráficos correspondentes.

## Estrutura do diretório

O diretório do projeto contém a seguinte estrutura:

<pre>
projeto-analise-algoritmos/
├── fontes/
│ ├── nome_algoritmo/
│ │ └── algoritmo.c
├── graficos/
│ └── nome_algoritmo/
│ │ └── nome_caso/
└── README.md
</pre>


## Executando os códigos

Para executar os códigos deste projeto, siga as instruções abaixo:

1. Navegue até o diretório do arquivo C correspondente ao algoritmo desejado.
2. Execute o seguinte comando no terminal:

<pre>
gcc -Wall arquivo.c -o arquivo
</pre>

Certifique-se de substituir "arquivo" pelo nome real do arquivo C.

3. Após a compilação bem-sucedida, execute o programa com o seguinte comando:

<pre>
./arquivo tamanho_vetor
</pre>

Substitua "arquivo" pelo nome do executável gerado e "tamanho_vetor" pelo tamanho desejado para o vetor de entrada.

## Gerando os gráficos

Para gerar os gráficos correspondentes aos resultados obtidos, siga as instruções abaixo:

1. Navegue até o diretório do algoritmo específico em `graficos/nome_algoritmo/nome_caso` ou `graficos/nome_algoritmo`.
2. Abra o terminal nesse diretório.
3. Digite o comando `gnuplot` para abrir o Gnuplot.
4. Use o seguinte comando para plotar o gráfico a partir do arquivo de dados:

<pre>
plot "arquivo.txt" with linespoint
</pre>

Substitua "arquivo.txt" pelo nome do arquivo de dados correspondente.

## Contribuição

Este projeto é resultado de uma atividade acadêmica e não está aberto para contribuições externas no momento.

## Licença

Este projeto é licenciado sob a [MIT License](https://opensource.org/licenses/MIT). Consulte o arquivo LICENSE para obter mais informações.
