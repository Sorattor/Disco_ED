#include<stdio.h>
#include<stdlib.h>
#include<string.h>


 typedef struct nosetor {
unsigned long inicio;
unsigned long fim;
struct nosetor * prox;
struct nosetor * ant;
}NoSetor;

typedef struct noarquivo{
        char nome[40];
        unsigned long tam;
        NoSetor* setores;
        struct noarquivo* prox;
        struct noarquivo* ant;
}NoArquivo;


typedef struct{
    char nome[40];
    void* disco;
    NoSetor* livres;
    NoArquivo* arquivos;
    unsigned long tamDisco;
    unsigned long espacoLivre;
    unsigned long espacoOcupado;
    unsigned long qtdeArquivos;
}Disco;
typedef enum{
    SUCESSO = 0,
    ESPACO_INSUFICIENTE,
    ARQUIVO_INEXISTENTE
}TipoRetorno;

NoSetor* cria_NoSetor();
void adiciona_NoSetor(NoSetor* campos, unsigned long inicio, unsigned long fim);
void edita_NoSetor(NoSetor* campos, unsigned long inicio, unsigned long fim);
void apaga_NoSetor(NoSetor* campos);
void visualiza_NoSetor(NoSetor* Setores);
NoSetor* setoreslivres(NoSetor* a, NoSetor* a2);


NoArquivo* cria_NoArquivo();
void adiciona_NoArquivo (NoArquivo* Arquivo, char* Nome, unsigned long tam);
NoArquivo* procura_NoArquivo(NoArquivo* Arquivo, char* Nome);
void apaga_NoArquivo(NoArquivo* Arquivo);
 void ver_NoArquivo(NoArquivo* Arquivo);


//funcoes:crud
Disco* disco_cria(char* nome, unsigned long tamanho);
TipoRetorno disco_grava(Disco* d, char* nomeArquivo); ///nome arquivo deve conter o caminho absoluto ou relativo do arquivo
TipoRetorno disco_remove(Disco* d, char* nome); ///somente o nome do arquivo sem o caminho
TipoRetorno disco_recupera(Disco* d, char* nome, FILE* arquivoFisico);
unsigned long Tamanho_arquivo(char *nomeArquivo);



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

void apaga_NoSetor(NoSetor* Setores)
     {

      NoSetor *aux = Setores->prox;

      Setores->prox->prox->ant = Setores->prox->ant;

      Setores->prox = Setores->prox->prox;

      free(aux);

     }

void visualiza_NoSetor(NoSetor* Setores)
{

  NoSetor *aux = Setores->prox;



  while( !(aux == Setores) )
    {

    printf(" [ %d, %d ],", aux->inicio, aux->fim);

    aux = aux->prox;

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
    {

    aux->fim = aux->prox->fim;

    apagar_NoSetor(aux);
    }

  return auxRetorno;

}





 NoArquivo* cria_NoArquivo()
 {
     NoArquivo * a = (NoArquivo*) malloc(sizeof(NoArquivo)); //sent
     a->prox = a;
     a->ant = a;
     return a;

 }

  void adiciona_NoArquivo (NoArquivo* Arquivo, char* Nome, unsigned long tam)
  {
        NoArquivo *novo = (NoArquivo*)malloc(sizeof(NoArquivo));

  strcpy(novo->nome, Nome);

  novo->tam = tam;

  novo->setores = cria_NoSetor();

  novo->ant = Arquivo->prox->ant;

  novo->prox = Arquivo->prox;

  Arquivo->prox->ant = novo;

  Arquivo->prox = novo;

}

NoArquivo* procura_NoArquivo(NoArquivo* Arquivo, char* Nome)
{
   NoArquivo* aux = Arquivo->prox;
   int compara  = (strcmp (aux->nome,Nome));

    while( compara != 0)
        {
         printf("Procurando esse belo arquivo\n");
          aux = aux->prox;
          if(aux == Arquivo) return NULL;

        }



  return aux;
}



void apaga_NoArquivo(NoArquivo* Arquivo){

  NoArquivo *aux = Arquivo->prox;

  Arquivo->prox->prox->ant = Arquivo->prox->ant;

  Arquivo->prox = Arquivo->prox->prox;

  free(aux);
}

 void ver_NoArquivo(NoArquivo* Arquivo)
 {
   NoArquivo *aux = Arquivo->prox;

    while( !(aux == Arquivo) )
        {
         printf(" [ %s ],", aux->nome);
         aux = aux->prox;

  }



}





Disco* disco_cria(char* nome, unsigned long tamanho)
 {

  Disco * d = (Disco*) malloc(sizeof(Disco));
   strcpy(d->nome, nome);


  d->disco = (void*)malloc(tamanho) ;
  d->livres = cria_NoSetor();
  adiciona_NoSetor(d->livres, 0, tamanho);

  d->arquivos = cria_NoArquivo();
  strcpy(d->arquivos->nome, "Sentinela");

  d->tamDisco = d->espacoLivre = tamanho;

  d->espacoOcupado = d->qtdeArquivos = 0;
   return d ;

}
TipoRetorno disco_grava(Disco* d, char* nomeArquivo)
{

  int t = 1 ;

  unsigned long tamRest = 0;


	unsigned long SizeFile = Tamanho_arquivo(nomeArquivo);

  FILE* Arquivo = fopen(nomeArquivo, "rb") ;


	if( SizeFile > ( d->espacoLivre )) return ESPACO_INSUFICIENTE;

  adiciona_NoArquivo(d->arquivos, nomeArquivo, SizeFile);

  tamRest = SizeFile;

  while(t){
    adiciona_NoSetor(d->arquivos->prox->setores, 0, 0);
    edita_NoSetor(d->arquivos->prox->setores, d->livres->prox->inicio, 0);

    if( ((d->livres->prox->fim) - (d->livres->prox->inicio)) >= tamRest ){
      edita_NoSetor(d->arquivos->prox->setores, d->arquivos->prox->setores->prox->inicio, (d->arquivos->prox->setores->prox->inicio)+tamRest);

      if(d->livres->prox->inicio == d->arquivos->prox->setores->prox->inicio ){

        d->livres->prox->inicio = d->arquivos->prox->setores->prox->fim;

        if(d->livres->prox->inicio == d->livres->prox->fim){



          apaga_NoSetor(d->livres);
        }

      }

      fread(d->disco+(d->arquivos->prox->setores->prox->inicio), (d->arquivos->prox->setores->prox->fim)-(d->arquivos->prox->setores->prox->inicio), 1, Arquivo);
      d->espacoLivre = d->espacoLivre - SizeFile;
      d->qtdeArquivos = d->qtdeArquivos + 1 ;
      t = 0;

    }else{

      d->arquivos->prox->setores->prox->fim = d->livres->prox->fim;
      apaga_NoSetor(d->livres);
      tamRest = tamRest - ( d->arquivos->prox->setores->prox->fim - d->arquivos->prox->setores->prox->inicio );
      fread(d->disco+(d->arquivos->prox->setores->prox->inicio), (d->arquivos->prox->setores->prox->fim)-(d->arquivos->prox->setores->prox->inicio), 1, Arquivo);


    }

  }
  fclose(Arquivo);
  return SUCESSO;
}

TipoRetorno disco_recupera(Disco* d, char* nome, FILE* arquivoFisico){

  NoArquivo* auxArq = procura_NoArquivo(d->arquivos, nome);
  if(auxArq == NULL) return ARQUIVO_INEXISTENTE;

  NoSetor *AuxNo = auxArq->setores->ant;

  while(!(AuxNo == auxArq->setores)){
    fwrite(d->disco+(AuxNo->inicio), (AuxNo->fim)-(AuxNo->inicio), 1, arquivoFisico);
    AuxNo = AuxNo->ant;
  }
  fclose(arquivoFisico);

  return SUCESSO;
}

TipoRetorno disco_remove(Disco* d, char* nome){

  NoArquivo* auxArq = procura_NoArquivo(d->arquivos, nome);
  if(auxArq == NULL) return ARQUIVO_INEXISTENTE;

  NoSetor *AuxNo = auxArq->setores->ant;
  while(!(AuxNo == auxArq->setores)){

    AuxNo = setoreslivres(d->livres, AuxNo);
  }

  d->espacoLivre = d->espacoLivre + (auxArq->tam);
  apaga_NoArquivo(auxArq->ant);
  d->qtdeArquivos = d->qtdeArquivos - 1;

  return SUCESSO;

}

unsigned long Tamanho_arquivo(char* nomeArquivo)
 {
  FILE* Arquivo = fopen(nomeArquivo, "rb") ;
  fseek(Arquivo,0,SEEK_END);
  unsigned long tamArquivo = ftell(Arquivo);
  fseek(Arquivo,0,SEEK_SET); ///nao deixa o ponteiro ficar no final do arquivo
  fclose(Arquivo) ;

  return  tamArquivo; /// recebe nome do arquivo e retorna seu tamanho
}
