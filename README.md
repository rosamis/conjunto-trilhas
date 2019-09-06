# Conjunto de Trilhas de Tamanho Mínimo
Trabalho para fins da disciplina de Grafos, UFPR. 

# Explicação do código 
O trabalho 2 de grafos foi desenvolvido por Roberta Samistraro Tomigian, GRR20171631. 
Para compilar ele deve-se digitar o comando: make ou escrever no terminal:
gcc -o grafo grafo.c

Para executar ele deve-se digitar no terminal:
./grafo < input.txt > output.txt

No qual ele lê um arquivo de formato e nome de escolha do usuário, que deve possuir conteúdo no seguinte formato:

a b 

b c

c d

d a

Em que cada linha pode conter zero, uma ou duas strings. E cada string representa um vértice. Quando há duas strings 
significa que os dois vértices são vizinhos entre si. 

O arquivo de saída sera uma representação do grafo de entrada utilizando o mesmo formado que da leitura.
Isto é, o conteudo do arquivo output.txt será, por exemplo:

a b

a d

b c

c d

Se a função que imprime as trilhas estiver descomentada o arquivo de saída será: 

Trilha 1: a b c d a 

a b

a d

b c

c d

A estrutura utilizada no trabalho 2 é a mesma do trabalho 1, tendo como representação do grafo uma lista de adjacência.
No qual temos a struct grafo que guarda um nome e uma lista de vértices.

typedef struct _grafo *grafo;
struct _grafo {
  const char* nome;
  lista vert;
};

E a struct vértice, no qual guardamos o nome do vértice e uma lista para os vizinhos dele.

typedef struct _vertice *vertice;
struct _vertice {
	char* nome;
	lista vizinhos;
};

São usadas as estruturas auxilires:

typedef struct noh *noh;
struct noh {
	void *cont;
	noh prox, ant;
};

typedef struct lista *lista;
struct lista {
	noh ini, fim;
	unsigned int tam;
};

Elas representam uma estrutura genérica que é utilizada durante a implementação. Por exemplo, um grafo tem um 
ponteiro para uma lista vizinhos, no qual cada vizinho representa um noh, e cada nó tem um ponteiro void para um cont,
neste exemplo o cont conterá um vértice.

O grafo após a leitura do arquivo será armazenado no seguinte formato:

a -> b, d
b -> a, c
c -> b, d
d -> c, a

No qual os valores antes da seta correspondem aos vértices do grafo e os de depois da seta se referem aos vértices
vizinhos dele, isto é, a quem eles se conectam.

Esse trabalho tem como objetivo criar uma função que encontra um conjunto minimal de trilhas que percorrem um grafo passado 
como entrada e retorna o numero mínimo k de trilhas. Chamada de cobertura_por_trilhas() tem como parâmetros a 
estrutura grafo já preenchida com a função le_grafo(), e a matriz de ponteiros **cobertura[], que conterá o 
conjunto das trilhas. No qual, cada linha representa uma trilha e as colunas serão os vértices da trilha.

O algoritmo para encontrar o conjunto foi o sugerido em pseudo código na especificação:

Um conjunto de trilhas que cobre um grafo conexo G pode ser obtido da seguinte maneira.

    1. Seja I o conjunto de vértices de grau ímpar de G.
    2. Se I não é vazio, acrescente um novo vértice v a G e acrescente arestas de forma que v seja vizinho de todos os 
vértices de I. Observe que agora o grafo G é euleriano.
    3. Encontre uma trilha euleriana fechada T em G.
    4. Devolva o conjunto dos segmentos maximais de T que não contém o vértice v.

Uma trilha euleriana fechada em um grafo euleriano conexo G pode ser encontrada da seguinte maneira.

    1. Seja v um vértice de G e seja T a trilha T=(v).
    2. Enquanto existir em V(T) um vértice u de grau positivo em G,
        2.1 encontre um ciclo C em G contendo o vértice u,
        2.2 incorpore o ciclo C na trilha T, e
        2.3 remova de G as arestas de C.
    3. Devolva T

Incorporar o circuito C=(v_0=u, v_1, ..., v_n=u) na trilha T=(w_0, ..., w_k=u, ..., w_n) significa modificar T 
de forma a obter como resultado a trilha T=(w_0, ..., w_k=u) . C . (u=w_k, ..., w_n)

De acordo com os testes realizados não foram encontrados bugs.
