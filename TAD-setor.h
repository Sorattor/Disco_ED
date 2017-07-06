#include<stdio.h>
#include<stdlib.h>
#include<string.h>



///PARTE 1- TAD setor = cria , adiciona , edita , apaga , setoreslivres; (CRUD + SETORES LIVRES)

 typedef struct nosetor {
    unsigned long inicio; // O tamanho da memória é sempre positivo, entao usamos o unsigned;
    unsigned long fim;
     struct nosetor* prox;
     struct nosetor* ant;
}NoSetor;
//funcoes   :
NoSetor* cria_NoSetor();//valor que indica o proximo e anterior da seqüência de dados, utulizado sentinela
void adiciona_NoSetor(NoSetor* campos, unsigned long inicio, unsigned long fim);//o campo nessa funçao insere o elemeno no inicio e no fim.
void edita_NoSetor(NoSetor* campos, unsigned long inicio, unsigned long fim);//funçao para editar o começo e o fim.
void apaga_NoSetor(NoSetor* campos); //funçao para excluir, auxiliar é uzada para excluir anterior e o proximo


 ///implementacoes

 NoSetor* cria_NoSetor()
  { NoSetor* sent = (NoSetor*)malloc(sizeof(NoSetor));
    sent->prox = sent;
    sent->ant = sent;

    return sent;

  }

  void adiciona_NoSetor(NoSetor* Setores, unsigned long inicio, unsigned long fim)
  {



  NoSetor *novo1 = (NoSetor*)malloc(sizeof(NoSetor));

  novo1->inicio = inicio ;

  novo1->fim = fim ;





  novo1->ant = Setores->prox->ant;

  novo1->prox = Setores->prox;

  Setores->prox->ant = novo1;

  Setores->prox = novo1;


}

void edita_NoSetor(NoSetor* Setores, unsigned long inicio, unsigned long fim)
{


  Setores->prox->inicio = inicio ;

  Setores->prox->fim = fim ;

}

void apagaa_NoSetor(NoSetor* Setores)
     {

      NoSetor *aux = Setores->prox;

      Setores->prox->prox->ant = Setores->prox->ant;

      Setores->prox = Setores->prox->prox;

      free(aux);

     }

void visualiza_NoSetor(NoSetor* Setores)
{

  NoSetor *aux = Setores->prox;



  while( !(Aux == Setores) ) // enquanto nao voltar no sentinela
    {

    printf(" [ %d, %d ],", Aux->inicio, Aux->fim); //mosta inicio e o fim de todos arquivos

    Aux = Aux->prox;

  }
}



NoSetor* setoreslivres(NoSetor* a, NoSetor* a2)
 {

  NoSetor* aux2 = a2->prox;

  NoSetor* aux = a;

  NoSetor* auxRetorno = aux->ant;



  while( aux2->inicio < aux->inicio )
    {
     aux2 = aux2->prox;
    }



  aux->prox = aux2;

  aux->ant = aux2->ant;

  aux2->ant->prox = aux;

  aux2->ant = aux;



  if(aux->ant->fim == aux->inicio && !(aux->ant == a2) )
    {
    aux->inicio = aux->ant->inicio;
    apagar_NoSetor(aux->ant->ant);
    }



  if(aux->prox->inicio == aux->fim && !(aux->prox == a2))
    { //Verifica se nao esta Olhando o Sentinela

    aux->fim = aux->prox->fim;

    apagar_NoSetor(aux);
    }

  return auxRetorno;

}
