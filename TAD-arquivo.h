/// PARTE 2 -  TAD ARQUIVO = cria , adiciona , procura , apaga CRUD

typedef struct noarquivo{
    char nome[40];
    unsigned long tam;
    NoSetor* setores;
    struct noarquivo* prox;
    struct noarquivo* ant;
}NoArquivo;
//funcoes   :
//cria adiciona e procura arquivo, alem de apagar
NoArquivo* NoArquivo_cria();
void NoArquivo_adiciona (NoArquivo* Arquivo, char* Nome, unsigned long tam);
NoArquivo* NoArquivo_procura(NoArquivo* Arquivo, char* Nome);
void NoArquivo_apaga(NoArquivo* Arquivo);


 ///implementacoes

 NoArquivo* NoArquivo_cria()
 {
     NoArquivo * a = (NoArquivo*) malloc(sizeof(NoArquivo)); //sent
     a->prox = a;
     a->ant = a;
     return a;

 }

  void NoArquivo_adiciona (NoArquivo* Arquivo, char* Nome, unsigned long tam)
  {
        NoArquivo *novo = (NoArquivo*)malloc(sizeof(NoArquivo));

  strcpy(novo->nome, Nome);

  novo->tam = tam;

  novo->setores = criar_NoSetor(); // cria uma sentinela já

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
         printf("Procurando essa porra de arquivo\n");
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

    while( !(Aux == Arquivo) )
        {
         printf(" [ %s ],", Aux->nome);
         Aux = Aux->prox;

  }



}

