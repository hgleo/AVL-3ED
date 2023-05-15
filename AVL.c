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
  
  Feito por Hugo Melo e Felipe Alves                                                     ok
*/

#include "stdio.h"
#include "stdlib.h"


typedef struct arvore{

    int info;
    int FB;
    struct arvore *esq;
    struct arvore *dir;
}arvore;

int altura(arvore *a){
  if (a == NULL)
    return 0;
  else{
    int he = altura(a->esq);
    int hd = altura(a->dir);
    int FB = hd - he;

    if (FB > 0)
      return hd + 1;
    else
      return he + 1;
  }
}

/*
int altura(arvore *a){

  if (a == NULL) return 0;
  else{
    int he = altura(a->esq);
    int hd = altura(a->dir);
    if(he > hd) return he + 1;
    else return hd + 1;
  }
}
*/

void ajustarFB(arvore *a){
  
  if(a!=NULL){
    int he = altura(a->esq);
    int hd = altura(a->dir);
    a->FB = he - hd;

    ajustarFB(a->esq);
    ajustarFB(a->dir);
  }
}

arvore *lerArvore(FILE *arq) {

    arvore *a = NULL;
    char c;
    int num;

    fscanf(arq,"%c",&c);
    fscanf(arq,"%d",&num);
    
    ajustarFB(a);
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
  if (a != NULL){
    if (a->info < x){
      if (a->esq == NULL && a->dir == NULL){
        printf("%d ", a->info);
      } else {
        imprimirFolhasMenores(a->esq, x);
        imprimirFolhasMenores(a->dir, x);
      }
    } else if (a->info >= x){
      imprimirFolhasMenores(a->esq, x);
    }
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

arvore *rotacaoEsqSimples(arvore *a){
  
  arvore *x = a;
  arvore *y = a->dir;

  a->dir = y->esq;
  y->esq =a;

  if(y->FB == 1){
    x->FB =0;
    y->FB =0;
  }
  else{
    x->FB= 1;
    y->FB=-1;
  }
  a = y;

  return a;
}

arvore *rotacaoEsqDupla(arvore *a){

  arvore *x = a;
  arvore *y = x->dir;
  arvore *z = y->esq; // Esse nó será a nova raiz

  z->esq = y->dir;
  x->dir = y->esq;
  y->esq = x;
  y->dir = z;

  // Com FB da nova raiz

  switch(y->FB){
    
    case -1:
      x->FB = 0;
      z->FB =1;
    break;

    case 0:
      x->FB =0;
      z->FB =0;
    break;

    case +1:
      x->FB =-1;
      z->FB =0;
    break;
  }
  y->FB = 0;

  a = y;

  return a;

}

arvore *rotacaoEsq(arvore *a){

  if(a->dir->FB == -1)
    a = rotacaoEsqDupla(a);
  else
    a = rotacaoEsqSimples(a);
  
  return a;
}



arvore *rotacaoDirSimples(arvore *a){
  
  arvore *x = a->esq;
  arvore *y = a;

  y->esq = x->dir;
  x->dir = y;

  if(x->FB == -1){
    
    x->FB =0;
    y->FB =0;
  }
  else{

    x->FB = 1;
    y->FB = -1;
  }
  
  a=x;

  return a;
}

arvore *rotacaoDirDupla(arvore *a){
  // Os nós x,y,z serão aqueles com FB´s modificados

  arvore *z = a;
  arvore *x = z->esq;
  arvore *y = x->dir;

  z->esq = y->dir;
  x->dir = y->esq;
  y->esq = x;
  y->dir = z;

  // Setando o svalores dos FB´s de acordo com a nova raiz;

  switch(y->FB){
    
    case -1:
      x->FB = 0;
      z->FB = 1;
    break;

    case 0:
     x->FB =0;
     z->FB = 0;
    break;

    case +1:
      x->FB=-1;
      z->FB=0;
    break; 

  }

  y->FB =0;
  a = y;
  return a;
}

arvore *rotacaoDir(arvore *a){
  if(a->esq->FB ==1)
    a = rotacaoDirDupla(a);
  else
    a = rotacaoDirSimples(a);
  
  return a;
}

arvore *inserir(arvore *a, int x, int *hMudou){
  
  if(a == NULL){

    a = (arvore *)malloc(sizeof(arvore));
    a->info = x;
    a->esq = NULL;
    a->dir = NULL;
    a->FB = 0;
    *hMudou = 1;
  }
  else{
    
    if(x<=a->info){

      a->esq = inserir(a->esq,x,hMudou);
      
      if(*hMudou == 1){

        switch(a->FB){

          case -1:
            a = rotacaoDir(a);
            *hMudou = 0;
          break;

          case 0:
            a->FB = -1;
            *hMudou = 1;
          break;

          case 1:
            a->FB = 0;
            *hMudou= 0;
          break;
        }

      }
    }
    else{

      a->dir = inserir(a->dir,x,hMudou);
      if(*hMudou==1){

        switch(a->FB){

          case -1:
            a->FB = 0;
            *hMudou =0;
          break;

          case 0:
            a->FB = +1;
            *hMudou =1;
          break;

          case 1:
            a = rotacaoEsq(a);
            *hMudou = 0;
          break;
        }
      }
    }
  }

  return a;
}

arvore *remover(arvore *a, int x, int *hMudou){

  if(a != NULL){
    
    if(a->info == x){
      
      // Verificar se é folha
      if(a->esq == NULL && a->dir == NULL){
        free(a);
        *hMudou = 1;
        return NULL;
      }
      // Verificar se um dos filhos é nulo
      else if(a->esq == NULL || a->dir == NULL){

        arvore *aux;
        if(a->esq == NULL)
          aux = a->dir;
        else
          aux = a->esq;
        
        free(a);
        *hMudou = 1;
        return aux;
      }
      // Nenhum filho nulo
      else{
        
        arvore *maiorEsq = a->esq;

        while(maiorEsq->dir != NULL)
          maiorEsq = maiorEsq->dir;
        
        a->info = maiorEsq->info;
        a->esq = remover(a->esq,a->info,hMudou);

        if(*hMudou == 1){

          switch(a->FB){

            case -1:
              a->FB = 0;
              *hMudou = 1;
            break;

            case 0:
              a->FB = 1;
              *hMudou = 0;
            break;

            case +1:{
              int aux = a->dir->FB;
              a = rotacaoEsq(a);

              if(aux == 0)
                *hMudou = 0;
              else
                *hMudou = 1;
            break;
            }   
          }
        }
      }
    }
    else if(x < a->info){

      a->esq = remover(a->esq,x,hMudou);

      if(*hMudou == 1){
        switch(a->FB){
          
          case -1:
            a->FB = 0;
            *hMudou = 1;
          break;

          case 0:
            a->FB =1;
            *hMudou = 0;
          break;

          case +1:{
            int aux = a->dir->FB;
            a = rotacaoEsq(a);

            if(aux ==0)
              *hMudou = 0;
            else
              *hMudou = 1;
          break;
          }
        }
      }
    }
    else{
      a->dir = remover(a->dir,x,hMudou);

      if(*hMudou == 1){
        switch(a->FB){

        case -1:
          a->FB = 0;
          *hMudou = 1;
        break;

        case 0:
          a->FB = 1;
          *hMudou = 0;
        break;

        case +1:{
          int aux = a->esq->FB;
          a = rotacaoDir(a);

          if(aux ==0)
            *hMudou = 0;
          else 
            *hMudou = 1;
          break;
        }
        }
      }
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
  
  int hMudou = 0;
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
        a = inserir(a,elemento,&hMudou);
        printf("O elemento %d foi inserido na arvore.\n",elemento);
        break;

      case 7:
        printf("\nDigite o elemento a ser removido: ");
        scanf("%d",&elemento);
        a = remover(a,elemento,&hMudou);
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