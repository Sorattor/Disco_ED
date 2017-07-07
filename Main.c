#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"TAD_DiscoCompleto.h"
void adiciona_arq(Disco* Disk){

  char escolha[50];
  printf("\n\nQual arquivo quer Adicionar em Disco: \n");
  scanf("%s", &escolha);
  printf("\n Retorno ARQ[%s]: %d \n ",escolha, disco_grava(Disk, escolha) );

}

void recupera_arq(Disco* Disk){

  char escolha[50];
  char escolha_save[50];
    printf("\n\nQual Arquivo Recuperar: \n");
    scanf("%s", &escolha);

    printf("\n\nNome de Saida?: \n");
    scanf("%s", &escolha_save);

    FILE* Arquivo= fopen(escolha_save, "w+b");
    printf("\n Retorno ARQ = %d \n", disco_recupera(Disk,escolha,Arquivo)); // Recuperar o Arquivo e Escrever no FILE

    //fclose(Arquivo);

}

void listar_arq(Disco* Disk){
  printf("\nArquivos em Disco:");
  ver_NoArquivo(Disk->arquivos);
  printf("\n");
}

void detalhe_arq(Disco* Disk){
    char escolha[10];
    printf("\n\nQual Arquivo visualizar em detalhe: \n");
    scanf("%s", &escolha);
    NoArquivo* auxArq = procura_NoArquivo(Disk->arquivos, escolha);
    printf("Nome [%s] \n", auxArq->nome);
    printf("Tamanho [%d] \n", auxArq->tam);

}

void ver_setorLivre(Disco* Disk){


  printf("\nIntervalo Disponivel Livre em Disco: \n");
  ver_NoSetor(Disk->livres);

}

 void ver_arq(Disco* Disk){
  char escolha[10];
  printf("\n\nQual Arquivo Ver os Setores: \n");
  scanf("%s", &escolha);
  system("cls");
  printf("\nNos do Arquivo: [%s] \n",escolha);
 ver_NoSetor(procura_NoArquivo(Disk->arquivos, escolha)->setores);
}

void deleta_arq(Disco* Disk){
  char escolha[10];
  printf("\n\nQual Arquivo Deseja Remover: \n");
  scanf("%s", &escolha);
  disco_remove(Disk, escolha );

}

void disco_info(Disco* Disk){
  printf("\n Nome do Disco [%s]",Disk->nome );
  printf("\n Tamanho: [%d]",Disk->tamDisco );
  printf("\n Espaco Livre: [%d]",Disk->espacoLivre );
  printf("\n Quantidade de Arquivos: [%d] \n",Disk->qtdeArquivos );


}


int main () {

  Disco* Disk = disco_cria("Disco C", 20) ; /// 219086 902094

  int escolha = 0;
  int funcionando = 1;
  while(funcionando){
    printf("\nEscolha uma Opcao:");
    printf("\n 1- Adicionar Arquivos");
    printf("\n 2- Recuperar um Arquivo");
    printf("\n 3- Listar Arquivos");
    printf("\n 4- Detalhe do Arquivo");
    printf("\n 5- Ver Setores Livres");
    printf("\n 6- Ver Setores de um Arquivo");
    printf("\n 7- Deletar um Arquivo");
    printf("\n 8- Estatisticas do Disco\n");
    printf("\n 9- Sair\n");

    scanf("%d",&escolha);
    system("cls");
    switch ( escolha ) {
    case 1:
        adiciona_arq(Disk);
      break;
    case 2:
        recupera_arq(Disk);
      break;
    case 3:
        listar(Disk);
      break;
    case 4:
       detalhe_arq(Disk);
      break;
    case 5:
        ver_SetorLivre(Disk);
      break;
    case 6:
        ver_arq(Disk);
      break;
    case 7:
       deleta_arq(Disk);
      break;
    case 8:
       disco_info(Disk);
      break;
    case 9:
        funcionando = 0;
      break;
    default:
        printf("\n ESCOLHA UMA OPCAO VALIDA! \n");
      break;
    }

  }
}

