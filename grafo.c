#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------------------------------PROTOTIPOS E STRUCTS------------------------------------------------------

//------------------------------------------------------------------------------
// STRUCTS
//------------------------------------------------------------------------------
// declara nó da lista
typedef struct noh *noh;
// nó da lista com conteudo, proximo e anterior
struct noh {
	void *cont;
	noh prox, ant;
};

// declara lista
typedef struct lista *lista;
// lista com inicio, fim e tamanho
struct lista {
	noh ini, fim;
	unsigned int tam;
};

// (apontador para) estrutura de dados para representar um vértice
// 
// o vértice tem um nome, que é uma "string", uma lista de vizinhos que guarda com quem eles estão conctados
// um int removido e um int estado

typedef struct _vertice *vertice;

struct _vertice {
	char* nome;
	lista vizinhos;
};

// (apontador para) estrutura de dados para representar um grafo
// 
// o grafo tem um nome, que é uma "string", uma lista de vértices que correspondem aos vértices do grafo
// e um long que guarda a quantidade de vértices do grafo

typedef struct _grafo *grafo;

struct _grafo {
  const char* nome;
  lista vert;
};

// (apontador para) estrutura de dados para representar os já impressos
// 
typedef struct impressos *impressos;
struct impressos {
	char *v1,*v2;
};

// (apontador para) estrutura de dados para representar os impares
// 
typedef struct impar *impar;
struct impar {
	char *nome;
};

//------------------------------------------------------------------------------
// LISTA
//------------------------------------------------------------------------------

// inicia lista alocando memória e iniciando parâmetros
lista iniciaLista(void);

// libera lista da memória, um nó de cada vez, então a lista
void liberaLista(lista l);
void liberaNohLista(lista l);

// cria noh para inserir na lista
noh criaNoh(void *cont);

// insere nó com conteúdo passado no final da lista
noh insereLista(lista l, void *cont);

// insere nó com conteúdo passado no inicio da lista
noh insereListaIni(lista l, void *cont);

// procura noh em uma lista, se existir devolve o nó, senão NULL
noh procuraNoh(lista l, char *p);

noh procuraNohCiclo(lista l, char *p);

// funde duas listas
void fundeListas(lista f, noh n);

// remove nó do final da lista
void removeLista(lista l);

// remove nó do inicio da lista
void removeListaIni(lista l);

// remove nó específico de uma lista
void removeListaEspec(lista l, noh aux);

// imprime uma lista
// usado para testes
void imprimeLista(lista l);

//------------------------------------------------------------------------------
// GRAFO
//------------------------------------------------------------------------------

// cria um novo grafo alocando memória e definindo suas variáveis
grafo criaGrafo(const char *nome);

// insere os vertices 
vertice insereVert(grafo gr, char *nome, int f);

// insere os vizinhos
void insereViz(vertice v1, vertice v2);

// devolve o número de vértices de g
unsigned int n_vertices(grafo g);

// devolve o número de arestas de g
unsigned int n_arestas(grafo g);

// devolve o vértice de nome 'nome' em g
//         ou
//         NULL, caso não exista tal vertice
vertice vertice_nome(grafo g, char *nome);

// devolve o número mínimo k de trilhas necessárias para cobrir o grafo g
unsigned int cobertura_por_trilhas(grafo g, vertice **cobertura[]);

// coloca uma trilha em uma matriz
void segmenta_trilha_euleriana(lista, vertice **cobertura[]);

// faz uma busca ate achar o elemento inicial novamente, isto é, o ciclo
void encontra_trilha_euleriana_fechada(grafo , lista );

// coloca a lista de ciclo na trilha euleriana 
void insere_ciclo_na_trilha(lista ciclo, lista trilha_euleriana);

// remove as arestas do ciclo no grafo
void remove_arestas_do_ciclo_no_grafo(grafo g, lista ciclo);

// procura vertice de menor nome em lista
vertice procura_menor_vert(lista l);

// procura vértice de nome específico em uma lista
vertice procuraVert(lista l, char *p);

// descobre a quantidade de linhas da matriz cobertura a partir de uma trilha
unsigned int quantidade_linhas(lista trilha_euleriana);

// a partir de uma trilha euleriana é montada uma matriz no qual a quantidade de linhas são a quantidade de trilhas
// e as colunas correspondem a cada vértice da trilha
void adiciona_matriz(lista trilha_euleriana,unsigned int i,unsigned int colunas, vertice *cob[]);

// desaloca toda a memória usada em *g
// devolve 1 em caso de sucesso,
//         ou 
//         0, caso contrário
int destroi_grafo(grafo g);

// imprime o grafo com seus parâmetros e informações relevantes
// usado para testes
void imprimeGrafo(grafo g);

// lê um grafo de input.
// um grafo é um arquivo onde cada linha tem zero, uma ou duas
// strings (sequência de caracteres sem "whitespace").
// 
// devolve o grafo lido. Caso o arquivo esteja mal formado o
// comportamento da função é indefinido
grafo le_grafo(FILE *input); 

// escreve o grafo g em output, no mesmo formato que o usado por le_grafo()
//
// devolve o grafo escrito,
//         ou 
//         NULL, em caso de erro 
grafo escreve_grafo(FILE *output, grafo g);

// cria um novo vertice alocando memória e definindo suas variáveis
vertice criaVert(char *nome);

// remove vertice de uma lista
void remove_vert(lista l, vertice v);

// imprime os vertices com seus parâmetros e informações relevantes
// usado para testes
noh imprimeVert(noh aux, int vert);

// devolve o nome de v
char *nome(vertice v);

// exclui a lista de vizinhos do vértice e o vértice 
void liberaVertice(vertice v);

// clona um grafo
grafo clona_grafo(grafo g);

//------------------------------------------------------------------------------
// IMPRESSOS
//------------------------------------------------------------------------------

// procura na lista de impressos se v1 e v2 estão juntos na lista, isto é, já
// foram impressos, levando em consideração que se v1 e v2 são vizinhos.
impressos procuraImp(lista listaImp, vertice v1, vertice v2);

//------------------------------------------------------------------------------
// IMPARES
//------------------------------------------------------------------------------

// função que insere um novo vértice e conecta com os impares, se existir no grafo
void insere_novo_impares(grafo g, lista l);

// função que preenche uma lista com os vertices de grau ímpar
lista lista_vertices_impares(grafo g);

// verifica se o vétice tem grau par
int eh_par(vertice v);

//-------------------------------------IMPLEMENTAÇÃO DAS FUNÇÕES--------------------------------------------------


//------------------------------------------------------------------------------
// MÉTODOS DE IMPRESSÃO - TESTE
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// imprime o grafo com seus parâmetros e informações relevantes
// usado para testes

void imprimeGrafo(grafo g) { imprimeVert(g->vert->ini, 1); }

//------------------------------------------------------------------------------
// imprime os vertices com seus parâmetros e informações relevantes
// usado para testes

noh imprimeVert(noh aux, int vert) {
  if (!aux)
    return aux;
  vertice v = (vertice)aux->cont;
  if (vert) {
    printf("%s -> ", v->nome);
    imprimeVert(v->vizinhos->ini, 0);
    printf("\n");
  } else {
    printf("%s,", v->nome);
    return imprimeVert(aux->prox, 0);
  }
  return imprimeVert(aux->prox, 1);
}

//------------------------------------------------------------------------------
// imprime a lista de impares com seus parâmetros e informações relevantes
// usado para testes

void imprimeLista(lista l) {
  noh aux = l->ini;
  while (aux) {
    char *nome = (char *)aux->cont;
    printf(" %s ", nome);
    aux = aux->prox;
  }
  printf("\n");
}

//------------------------------------------------------------------------------
// MÉTODOS DE CRIAÇÃO
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// cria um novo grafo alocando memória e definindo suas variáveis

grafo criaGrafo(const char *nome) {
  grafo gr = malloc(sizeof(struct _grafo));
  gr->nome = nome;
  gr->vert = iniciaLista();
  return gr;
}

//------------------------------------------------------------------------------
// cria um novo vertice alocando memória e definindo suas variáveis

vertice criaVert(char *nome) {
  vertice vert = malloc(sizeof(struct _vertice));
  vert->nome = nome;
  vert->vizinhos = iniciaLista();
  return vert;
}

//------------------------------------------------------------------------------
// MÉTODOS DE INSERÇÃO
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// insere os vertices ao grafo

vertice insereVert(grafo gr, char *nome, int f) {
  vertice vert = criaVert(nome);
  if (f)
    insereLista(gr->vert, vert);
  else
    insereListaIni(gr->vert, vert);
  return vert;
}

//---------------------------------------------------------------------------------
void insereViz(vertice v1, vertice v2) { insereLista(v1->vizinhos, v2); }

//------------------------------------------------------------------------------
// MÉTODOS DE BUSCA
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// procura lista pelo conteudo e retorna o vertice ou NULL se nao encontrar

vertice procuraVert(lista l, char *p) {
  noh aux = l->ini;
  while (aux) {
    vertice v = (vertice)aux->cont;
    if (strcmp(v->nome, p) == 0)
      return v;
    aux = aux->prox;
  }
  return NULL;
}

//------------------------------------------------------------------------------

noh procuraNoh(lista l, char *p) {
  noh aux = l->ini;
  while (aux) {
    vertice v = (vertice)aux->cont;
    if (strcmp(v->nome, p) == 0)
      return aux;
    aux = aux->prox;
  }
  return NULL;
}

//------------------------------------------------------------------------------

noh procuraNohCiclo(lista l, char *p) {
  noh aux = l->ini;
  while (aux) {
    char *v = (char *)aux->cont;
    if (strcmp(v, p) == 0)
      return aux;
    aux = aux->prox;
  }
  return NULL;
}

//------------------------------------------------------------------------------
// procura lista pelo menor vertice na lista, retorna o vértice menor ou NULL

vertice procura_menor_vert(lista l) {
  vertice menor = (vertice)l->ini->cont;
  for (noh aux = l->ini->prox; aux; aux = aux->prox) {
    vertice atual = (vertice)aux->cont;
    if ((atual->vizinhos->tam > 0 && strcmp(atual->nome, menor->nome) < 0) ||
        menor->vizinhos->tam == 0) {
      menor = atual;
    }
  }
  return menor;
}

//------------------------------------------------------------------------------
// MÉTODOS DE LEITURA
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// le o grafo e adiciona no grafo os vertices

grafo le_grafo(FILE *fp) {
  char linha[2049];
  char *palavra1, *palavra2;

  if (fp == NULL) {
    printf("%s\n", "Erro na abertura do arquivo!");
    exit(1);
  }

  grafo gr = criaGrafo("grafo");

  while (!feof(fp)) {

    // lê do arquivo uma linha
    fgets(linha, 2048, fp);

    // se a linha estiver vazia, ignora
    if (linha[0] == '\n' || linha[0] == '\0' || linha[0] == '#')
      continue;
    // separa o primeiro vértice
    palavra1 = (char *)malloc(sizeof(char) * 1024);
    strcpy(palavra1, strtok(linha, " \n"));

    vertice v1 = procuraVert(gr->vert, palavra1);
    if (!v1) {
      // adiciona no grafo o vértice 1
      v1 = insereVert(gr, palavra1, 1);
    }

    // separa o segundo vértice
    palavra2 = (char *)malloc(sizeof(char) * 1024);
    char *str = strtok(NULL, " \n");
    if (str)
      strcpy(palavra2, str);

    // ignora se o vértice 2 for NUUL, isto é há um vértice 1 que não tem
    // vizinhos adiciona no grafo o vértice 2
    if (str) {
      if (palavra2 != NULL) {
        vertice v2 = procuraVert(gr->vert, palavra2);
        if (!v2) {
          v2 = insereVert(gr, palavra2, 1);
        }
        if (!procuraVert(v1->vizinhos, v2->nome)) {
          insereViz(v1, v2);
        }
        if (!procuraVert(v2->vizinhos, v1->nome)) {
          insereViz(v2, v1);
        }
      }
    }

    // limpa a variável linha para evitar lixo
    strcpy(linha, "\0");
  }
  fclose(fp);
  return gr;
}

//------------------------------------------------------------------------------
// MÉTODOS DE ESCRITA
//------------------------------------------------------------------------------

// escreve o grafo em um arquivo de saida, de nome e formarto escolhido pelo usuário, na saída padrão 

grafo escreve_grafo(FILE *output, grafo g) {
  lista listaImp = iniciaLista();
  noh aux1 = g->vert->ini;
  while (aux1) {
    vertice v1 = (vertice)aux1->cont;
    noh aux2 = v1->vizinhos->ini;
    if (aux2 == NULL) {
      if (!procuraImp(listaImp, v1, NULL)) {
        fprintf(output, "%s \n\n", v1->nome);
        impressos imp = malloc(sizeof(struct impressos));
        imp->v1 = v1->nome;
        imp->v2 = NULL;
        insereLista(listaImp, imp);
      }
    }
    while (aux2) {
      vertice v2 = (vertice)aux2->cont;
      if (!procuraImp(listaImp, v1, v2)) {
        fprintf(output, "%s %s\n\n", v1->nome, v2->nome);
        impressos imp = malloc(sizeof(struct impressos));
        imp->v1 = v1->nome;
        imp->v2 = v2->nome;
        insereLista(listaImp, imp);
      }
      aux2 = aux2->prox;
    }
    aux1 = aux1->prox;
  }
  fclose(output);
  return g;
}

//---------------------------------------------------------------------------------
// procura na lista de impressos se v1 e v2 estão juntos na lista, isto é, já
// foram impressos, levando em consideração que se v1 e v2 são vizinhos.

impressos procuraImp(lista listaImp, vertice v1, vertice v2) {
  noh aux = listaImp->ini;
  if (v2 != NULL) {
    while (aux) {
      impressos imp = (impressos)aux->cont;
      if ((imp->v1 == v1->nome || imp->v2 == v1->nome) &&
          (imp->v1 == v2->nome || imp->v2 == v2->nome)) {
        return imp;
      }
      aux = aux->prox;
    }
  } else {
    while (aux) {
      impressos imp = (impressos)aux->cont;
      if (imp->v1 == v1->nome || imp->v2 == v1->nome) {
        return imp;
      }
      aux = aux->prox;
    }
  }

  return NULL;
}

//------------------------------------------------------------------------------
// função que clona um grafo

grafo clona_grafo(grafo g){
  grafo gr = criaGrafo("clone");
  noh aux1V = g->vert->ini;
  vertice auxV = aux1V->cont;
  noh listaViz = auxV->vizinhos->ini;
  vertice listaV = listaViz->cont;
  while(aux1V){
    vertice c = criaVert(auxV->nome);
    insereLista(gr->vert,c);
    listaViz = auxV->vizinhos->ini;
    listaV = listaViz->cont;
    while(listaViz){
      vertice v = criaVert(listaV->nome);
      insereLista(c->vizinhos,v);
      listaViz = listaViz->prox;
      if (listaViz)
        listaV = listaViz->cont;
    }
    aux1V = aux1V->prox;
    if(aux1V)
      auxV = aux1V->cont;
  }
  return gr;
}

//------------------------------------------------------------------------------
// MÉTODOS DE DESTRUIÇÃO
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
//
// devolve 1 em caso de sucesso,
//         ou
//         0, caso contrário

int destroi_grafo(grafo g) {
  // libera grafo
  liberaLista(g->vert);
  free(g);

  return 1;
}

//------------------------------------------------------------------------------
// exclui a lista de vizinhos do vértice e o vértice

void liberaVertice(vertice v) {
  liberaLista(v->vizinhos);
  free(v);
}

//---------------------------------------------------------------------------------
// LISTA
//---------------------------------------------------------------------------------

// inicia lista alocando memória e iniciando parâmetros

lista iniciaLista(void) {
  lista l = malloc(sizeof(struct lista));

  l->tam = 0;
  l->ini = NULL;
  l->fim = NULL;

  return l;
}

//---------------------------------------------------------------------------------
// libera lista da memória, um nó de cada vez, então a lista

void liberaNohLista(lista l) {
  noh aux;
  while ((aux = l->fim)) {
    l->fim = aux->ant;
    free(aux);
  }
}
void liberaLista(lista l) {
  liberaNohLista(l);
  free(l);
}

//---------------------------------------------------------------------------------
// cria noh para inserir na lista

noh criaNoh(void *cont) {
  noh aux = malloc(sizeof(struct noh));
  aux->cont = cont;
  aux->ant = NULL;
  aux->prox = NULL;

  return aux;
}

//---------------------------------------------------------------------------------
// insere nó com conteúdo passado no inicio da lista

noh insereListaIni(lista l, void *cont) {
  noh n = criaNoh(cont);

  if (l->tam == 0) {
    l->ini = n;
    l->fim = n;
  } else {
    l->ini->ant = n;
    n->prox = l->ini;
    l->ini = n;
  }
  l->tam++;

  return n;
}

//---------------------------------------------------------------------------------
// insere nó com conteúdo passado no final da lista

noh insereLista(lista l, void *cont) {
  noh n = criaNoh(cont);

  if (l->tam == 0) {
    l->ini = n;
    l->fim = n;
  } else {
    l->fim->prox = n;
    n->ant = l->fim;
    l->fim = n;
  }
  l->tam++;

  return n;
}

//---------------------------------------------------------------------------------
// função que funde listas a partir de um noh

void fundeListas(lista f, noh n) {
  n->prox->ant = f->fim;
  f->fim->prox = n->prox;
  n->prox = f->ini;
  f->ini->ant = n;
}

//---------------------------------------------------------------------------------
// remove nó do final da lista

void removeLista(lista l) {
  noh aux = l->fim;
  if (!aux)
    return;

  noh ant = aux->ant;
  if (ant) {
    l->fim = ant;
    ant->prox = NULL;
  } else {
    l->ini = NULL;
    l->fim = NULL;
  }

  l->tam--;
  free(aux);
}

//---------------------------------------------------------------------------------
// remove nó do inicio da lista

void removeListaIni(lista l) {
  noh aux = l->ini;
  if (!aux)
    return;

  noh prox = aux->prox;
  if (prox) {
    l->ini = prox;
    prox->ant = NULL;
  } else {
    l->ini = NULL;
    l->fim = NULL;
  }

  l->tam--;
  free(aux);
}

//---------------------------------------------------------------------------------
// remove nó específico da lista

void removeListaEspec(lista l, noh aux) {
  if (!aux)
    return;

  if (aux == l->ini && aux == l->fim) {
    l->ini = NULL;
    l->fim = NULL;
  } else if (aux == l->ini) {
    aux->prox->ant = NULL;
    l->ini = aux->prox;
  } else if (aux == l->fim) {
    aux->ant->prox = NULL;
    l->fim = aux->ant;
  } else {
    aux->prox->ant = aux->ant;
    aux->ant->prox = aux->prox;
  }

  l->tam--;
  free(aux);
}

//---------------------------------------------------------------------------------
// NUMERO ARESTAS E VÉRTICES
//---------------------------------------------------------------------------------

// Devolve o numero de vértices do grafo

unsigned int n_vertices(grafo g) { return g->vert->tam; }

//---------------------------------------------------------------------------------
// Devolve o numero de arestas do grafo

unsigned int n_arestas(grafo g) {
  noh aux = g->vert->ini;
  unsigned int arestas = 0;
  while (aux != NULL) {
    vertice v = aux->cont;
    arestas = arestas + v->vizinhos->tam;
    aux = aux->prox;
  }
  return arestas / 2;
}

//---------------------------------------------------------------------------------
// NOMES
//---------------------------------------------------------------------------------

// devolve o vértice de nome 'nome' em g
//         ou
//         NULL, caso não exista tal vertice

vertice vertice_nome(grafo g, char *nome) {
  noh aux = g->vert->ini;
  while (aux) {
    vertice v = aux->cont;
    if (strcmp(v->nome, nome) == 0)
      return v;
    aux = aux->prox;
  }
  return NULL;
}

//------------------------------------------------------------------------------
// devolve o nome de v

char *nome(vertice v) { return v->nome; }

//---------------------------------------------------------------------------------
// TRILHA(S)
//---------------------------------------------------------------------------------

// função que retorna se o grau do vértice é par

int eh_par(vertice v) {
  if ((v->vizinhos->tam % 2) == 0)
    return 1;
  return 0;
}

//---------------------------------------------------------------------------------
// função que preenche uma lista com os vertices de grau ímpar

lista lista_vertices_impares(grafo g) {
  lista impares = iniciaLista();
  noh aux1 = g->vert->ini;
  while (aux1) {
    vertice v = (vertice)aux1->cont;
    if (!eh_par(v)) {
      impar i = malloc(sizeof(struct impar));
      i->nome = v->nome;
      insereLista(impares, i);
    }
    aux1 = aux1->prox;
  }
  return impares;
}

//---------------------------------------------------------------------------------
// função que insere um novo vértice e conecta com os impares

void insere_novo_impares(grafo g, lista l) {
  vertice novo = insereVert(g, (char *)"", 0);
  noh aux = l->ini;

  while (aux) {
    impar i = (impar)aux->cont;
    vertice v = procuraVert(g->vert, i->nome);
    if (v) {
      if (!procuraVert(v->vizinhos, novo->nome))
        insereViz(v, novo);

      if (!procuraVert(novo->vizinhos, v->nome))
        insereViz(novo, v);
    }
    aux = aux->prox;
  }
}

//---------------------------------------------------------------------------------
// remove um vertice especifico da lista

void remove_vert(lista l, vertice v) {
  removeListaEspec(l, procuraNoh(l, v->nome));
}

//---------------------------------------------------------------------------------
// insere o ciclo encontrado na trilha, se o vertice inicial do ciclo já existir na trilha, funde
//  na trilha a partir do vertice inicial do ciclo, senão, insere o ciclo no final da trilha

void insere_ciclo_na_trilha(lista ciclo, lista trilha_euleriana) {
  noh aux = ciclo->ini;
  noh encontrado = procuraNohCiclo(trilha_euleriana, (char *)aux->cont);
  if (!encontrado) {
    // insere o ciclo para o fim da lista
    while (aux) {
      insereLista(trilha_euleriana, aux->cont);
      aux = aux->prox;
    }
  } else {
    // insere o ciclo a partir do vertice encontrado, ignorando o aux inicial
    removeListaIni(ciclo);
    fundeListas(ciclo, encontrado);
  }
}

//---------------------------------------------------------------------------------
// encontra trilha euleriana fechada em g
void encontra_trilha_euleriana_fechada(grafo g, lista trilha_euleriana) {
  lista ciclo = iniciaLista();
  vertice menorPrimeiro = procura_menor_vert(g->vert);
  insereLista(ciclo, menorPrimeiro->nome);
  vertice menor = menorPrimeiro;
  do {
    vertice menorViz = procura_menor_vert(menor->vizinhos);
    insereLista(ciclo, menorViz->nome);
    remove_vert(menor->vizinhos, menorViz);
    remove_vert(menorViz->vizinhos, menor);
    menor = menorViz;
  } while (menor != menorPrimeiro);

  insere_ciclo_na_trilha(ciclo, trilha_euleriana);
}

//---------------------------------------------------------------------------------
// descobre a quantidade de linhas da matriz cobertura a partir de uma trilha
// se o grafo é euleriano ele possui apenas uma trilha, senão, possui mais e as
// trilhas serão os valores entre dois  vertices novos

unsigned int quantidade_linhas(lista trilha_euleriana) {
  noh aux = trilha_euleriana->ini;
  unsigned int linhas = 0;
  while (aux) {
    if (strcmp(aux->cont, "") == 0) {
      aux = aux->prox;
      if (aux == NULL)
        return linhas;
      linhas = linhas + 1;
      while (strcmp(aux->cont, "") != 0 && (aux != NULL)) {
        aux = aux->prox;
      }
    } else
      return 1;

    if (aux == NULL)
      return linhas;
  }
  return linhas;
}

//---------------------------------------------------------------------------------
// a partir de uma trilha euleriana é montada uma matriz no qual a quantidade de linhas são a quantidade de trilhas
// e as colunas correspondem a cada vértice da trilha

void adiciona_matriz(lista trilha_euleriana, unsigned int i,
                     unsigned int colunas, vertice *cob[]) {
  noh aux = trilha_euleriana->ini;

  for (unsigned int j = 0; j < colunas; j++) {
    if (strcmp(aux->cont, "") == 0 && aux != NULL) {
      removeListaIni(trilha_euleriana);
      aux = trilha_euleriana->ini;
    }
    if (strcmp(aux->cont, "") != 0) {
      cob[i][j] = criaVert(aux->cont);
      strcpy(cob[i][j]->nome, aux->cont);
    }
    removeListaIni(trilha_euleriana);
    aux = trilha_euleriana->ini;
  }

}

//---------------------------------------------------------------------------------

void segmenta_trilha_euleriana(lista trilha_euleriana, vertice **cobertura[]) {
  vertice **cob;
  unsigned int i = 0;
  unsigned int linhas = quantidade_linhas(trilha_euleriana);
  unsigned int colunas = 0;
  cob = (vertice **)calloc(linhas, sizeof(vertice *));

  if (cob == NULL) {
    printf("** Erro: Memoria Insuficiente **");
    return;
  }
  noh aux = trilha_euleriana->ini;
  while (aux) {
    if (strcmp(aux->cont, "") == 0 && aux != NULL) {
      aux = aux->prox;
      if (aux == NULL)
        break;
      colunas = 0;
      while (strcmp(aux->cont, "") != 0 && (aux != NULL)) {
        colunas = colunas + 1;
        aux = aux->prox;
      }
      cob[i] = (vertice *)malloc((1 + colunas) * sizeof(vertice *));

      if (cob[i] == NULL) {
        printf("** Erro: Memoria Insuficiente **");
        return;
      }
      adiciona_matriz(trilha_euleriana, i, colunas, cob);
      colunas = 0;
      i = i + 1;
    } else {
      colunas = 0;
      if (aux == NULL)
        break;
      while (aux) {

        colunas = colunas + 1;
        aux = aux->prox;
      }

      cob[i] = (vertice *)malloc((1 + colunas) * sizeof(vertice *));

      if (cob[i] == NULL) {
        printf("** Erro: Memoria Insuficiente **");
        return;
      }

      adiciona_matriz(trilha_euleriana, i, colunas, cob);
      i = i + 1;
    }
  }
  *cobertura = cob;
}

//---------------------------------------------------------------------------------
// devolve o número mínimo k de trilhas necessárias para cobrir o grafo g
//
// observe que
//
//   k = 1, se g é euleriano, ou
//   k = (número de vértices de grau ímpar em g)/2, caso contrário
//
// aloca e preenche o vetor cobertura de maneira que cobertura[i] contém uma
// trilha em G para cada 0 <= i < k.
//
// cada trilha é um sequência de vertices terminada por NULL, isto é, para cada
// 0 <= i < k a sequência
// 
//     (cobertura[i][0], cobertura[i][1], ..., cobertura[i][l-1],
//     cobertura[i][l])
//
// é tal que
//
//     1. cobertura[i][j] é um vertice, para cada 0 <= j < l,
//     2. cobertura[i][l] == NULL, e
//     3. cobertura[i][j-1] é vizinho de cobertura[i][j] em g, para cada 0 < j <
//     l

unsigned int cobertura_por_trilhas(grafo g, vertice **cobertura[]) {
  unsigned int k = 0;
  lista l = lista_vertices_impares(g);
  k = (unsigned int)l->tam;
  lista trilha_euleriana = iniciaLista();
  if (k != 0) {
    // grafo nao euleriano, possui mais de uma trilha de cobertura
    insere_novo_impares(g, l);
  }

  while (n_arestas(g)) {
    encontra_trilha_euleriana_fechada(g, trilha_euleriana);
  }
  segmenta_trilha_euleriana(trilha_euleriana, cobertura);

  return k == 0 ? 1 : k / 2;
}

//---------------------------------------------------------------------------------

int main(void) {
  grafo g = le_grafo(stdin);
  grafo gr = clona_grafo(g);

  if (!g)
    return 1;

  vertice **cobertura;
  unsigned int k = cobertura_por_trilhas(g, &cobertura);
  // imprime as trilhas da matriz cobertura

/*
  for (unsigned int i = 0; i < k; i++) {
    printf("Trilha %d: ", i + 1);
    unsigned int j = 0;
    while (cobertura[i][j] != NULL) {
      printf("%s ", nome(cobertura[i][j]));
      j++;
    }

    free(cobertura[i]);
    printf("\n");
  }

  printf("\n");
*/
  escreve_grafo(stdout,gr);

  destroi_grafo(g);
  
  return !destroi_grafo(gr);
}
