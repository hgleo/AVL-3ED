/*
  Implemente um prorama que apresente na tela o seguinte menu de op��es: 
  1 - Ler uma arvore de um araquivo fornecido pelo usuario        ok
  2 - Imprimir a arvore (pre-ordem,em-ordem,pos-ordem,largura)    ok
  3 - Verificar se um elemento x existe na arvore                 ok
  4 - Imprimir o nivel de um no x                                 ok
  5 - Imprimir folhas menor que x                                ok
  6 - Inserir um no x na arvore                                   ok
  7 - Remover um no x na arvore                                   ok
  8 - Sair
  
  Feito por Hugo Melo e Felipe Alves                                                        ok
*/

#include "stdio.h"
#include "stdlib.h"


typedef struct arvore{

    int info;
    struct arvore *esq;
    struct arvore *dir;
}arvore;

arvore *lerArvore(FILE *arq) {

    arvore *a = NULL;
    char c;
    int num;

    fscanf(arq,"%c",&c);
    fscanf(arq,"%d",&num);
    
    if (num==-1) {
        fscanf(arq,"%c",&c);
        return NULL;
    }
    else {
        a = (arvore*)malloc(sizeof(arvore));
        a->info = num;
        a->esq = lerArvore(arq);
        a->dir = lerArvore(arq);
        fscanf(arq,"%c",&c);
        return a;
    }
}

void imprimirPreOrdem(arvore *a){

    if(a != NULL){
      printf("%d ", a->info);
      imprimirPreOrdem(a->esq);
      imprimirPreOrdem(a->dir);  
    }
}

void imprimirPosOrdem(arvore *a){

    if(a != NULL){
      imprimirPosOrdem(a->esq);
      imprimirPosOrdem(a->dir);
      printf("%d ", a->info);
    }
}

void imprimirEmOrdem(arvore *a){

    if(a != NULL){
      imprimirEmOrdem(a->esq);
      printf("%d ", a->info);
      imprimirEmOrdem(a->dir);
    }
}

int altura(arvore *a){

  if (a == NULL) return 0;
  else{
    int he = altura(a->esq);
    int hd = altura(a->dir);
    if(he > hd) return he + 1;
    else return hd + 1;
  }
}

void imprimirNivel(arvore *a, int cont, int n){

  if(a != NULL){
    if(cont == n) 
      printf("%d ", a->info);
    else{
      imprimirNivel(a->esq, cont + 1, n);
      imprimirNivel(a->dir, cont + 1, n);
    }
  }
}

void imprimirEmLargura(arvore *a){

  int h = altura(a);
  for(int i = 1; i <= h; i++){
    imprimirNivel(a, 1, i);
  }
}

int existir(arvore *a, int x){

  if(a == NULL)
    return 0;

  else if(x == a->info)
    return 1;
  
  else if(x < a->info)
    return existir(a->esq, x);

  else 
    return existir(a->dir, x);

}

void imprimirFolhasMenores(arvore *a, int x){

  if(a != NULL){
    if(a->dir == NULL && a->esq == NULL && a->info < x)
      printf("%d ", a->info);
  
  imprimirFolhasMenores(a->esq, x);
  imprimirFolhasMenores(a->dir, x);
}
}

int procurarElemento(arvore *a, int x){
    if(a == NULL) return 0;
    else if(a->info == x) return 1;
    else if(x < a->info) return procurarElemento(a->esq, x);
    else return procurarElemento(a->dir, x);
}

int nivelDoNo(arvore *a, int x, int nivel){

  if(a == NULL) return -1; //menos 1, porque nesse caso o nivel pode ser 0
  else if(a->info == x) return nivel;
  else if(x < a->info) return nivelDoNo(a->esq, x, nivel+1); //procura na esquerda caso seja menor que x, somando um ao nivel
  else return nivelDoNo(a->dir, x, nivel+1); //procura na direita caso nao esteja na esquerda, somando um ao nivel
} 

arvore *rotacaoEsq(arvore *a){

  if
}

arvore *inserir(arvore *a, int x){

  if(a == NULL){
    a = (arvore *)malloc(sizeof(arvore));
    a->info = x;
    a->esq = NULL;
    a->dir = NULL;
    return a;
  }

  else if(x <= a->info)
    a->esq = inserir(a->esq, x);

  else
   a->dir = inserir(a->dir, x);
  
  return a;
}

arvore *remover(arvore *a, int x){

if(a == NULL)
return NULL;

if(x < a->info)
a->esq = remover(a->esq, x);

else if(x > a->info)
a->dir = remover(a->dir, x);

else{
if(a->esq == NULL && a->dir == NULL){ //caso 1: folha
free(a);
a = NULL;
}
else if(a->esq == NULL){ //caso 2: so tem filho a direita
arvore *temp = a;
a = a->dir;
free(temp);
}
else if(a->dir == NULL){ //caso 2: so tem filho a esquerda
arvore *temp = a;
a = a->esq;
free(temp);
}
else{ //caso 3: tem ambos os filhos
arvore *temp = a->esq;
while(temp->dir != NULL){ //busca o maximo da subarvore esquerda
temp = temp->dir;
}
a->info = temp->info; //copia o valor maximo da esquerda para o no que queremos remover
temp->info = x; //troca o valor que queremos remover pelo valor maximo da esquerda
a->esq = remover(a->esq, x); //remove o valor trocado (que agora esta na esquerda)
}
}
return a;
}

void freeArvore(arvore *a) {

    if (a != NULL) {
        freeArvore(a->esq);
        freeArvore(a->dir);
        free(a);
    }
}

int main(){
  
  int opcao, elemento, nivel, opcao2;
  char nomeArq[50]; 
  arvore *a = NULL;
  FILE *arq = NULL;

  do{
    printf("===============================MENU===============================\n\n");
    printf("[1] Ler uma arvore de um arquivo fornecido pelo usuario\n");
    printf("[2] Imprimir a arvore (pre-ordem, em-ordem, pos-ordem, largura)\n");
    printf("[3] Verificar se um elemento x existe na arvore\n");
    printf("[4] Imprimir o nivel de um no x\n");
    printf("[5] Imprimir folhas menores que x\n");
    printf("[6] Inserir um no x na arvore\n");
    printf("[7] Remover um no x na arvore\n");
    printf("[8] Sair\n");
    printf("\nDigite a opcao: ");
    scanf("%d",&opcao);

    switch(opcao){

      case 1:
       
        printf("Digite o nome do arquivo que deseja ler: ");
        scanf("%s", nomeArq);
        arq = fopen(nomeArq, "r");
        if(arq == NULL) {
          printf("Erro ao abrir arquivo!\n\n");
          break;
        }
        a = lerArvore(arq);
        printf("Arvore lida com sucesso!\n");
        fclose(arq);
        break;

      case 2:
        printf("\n[1] Imprimir Pre-Ordem\n[2] Imprimir Em Ordem\n[3] Imprimir Pos Ordem\n[4] Imprimir em Largura\n");
        scanf("%d", &opcao2);
        switch(opcao2){
          case 1:
            imprimirPreOrdem(a);
            printf("\n");
            break;
          case 2:
            imprimirEmOrdem(a);
            printf("\n");
            break;
          case 3:
            imprimirPosOrdem(a);
            printf("\n");
            break;
          case 4:
            imprimirEmLargura(a);
            printf("\n");
            break;
          default:
            printf("Opção Invalida!\n");
            break;
        }
        break;

      case 3:
        printf("\nDigite o elemento a ser procurado: ");
        scanf("%d",&elemento);
        if(existir(a,elemento))
          printf("O elemento %d esta na arvore.\n",elemento);
        else  
          printf("O elemento %d nao esta na arvore.\n",elemento);
        break;

      case 4:
        printf("\nDigite o elemento para saber o nivel: ");
        scanf("%d",&elemento);
        nivel = nivelDoNo(a, elemento, 0);
        if(nivel == -1)
          printf("O elemento %d no esta na arvore.\n",elemento);
        else
          printf("O nivel do elemento %d e %d.\n",elemento,nivel);
        break;

      case 5:
        printf("\nDigite o valor de referencia para imprimir menores: ");
        scanf("%d",&elemento);
        printf("Os valores menores que %d sao: ",elemento);
        imprimirFolhasMenores(a,elemento);
        printf("\n");
        break;

      case 6:
        printf("\nDigite o elemento a ser inserido: ");
        scanf("%d",&elemento);
        a = inserir(a,elemento);
        printf("O elemento %d foi inserido na arvore.\n",elemento);
        break;

      case 7:
        printf("\nDigite o elemento a ser removido: ");
        scanf("%d",&elemento);
        a = remover(a,elemento);
        printf("O elemento %d foi removido da arvore.\n",elemento);
        break;

      case 8:
        printf("\nSaindo...\n");
        break;
      default:
        printf("\nOpcao invalida!\n");
    }
  }while(opcao != 8);

  freeArvore(a);

  return 0;
}