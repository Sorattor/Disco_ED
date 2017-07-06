///Parte 3 - TAD disco = cria , grava , remove , recupera

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



//funcoes:crud
Disco* disco_criar(char* nome, unsigned long tamanho);
TipoRetorno disco_gravar(Disco* d, char* nomeArquivo); ///nome arquivo deve conter o caminho absoluto ou relativo do arquivo
TipoRetorno disco_remover(Disco* d, char* nome); ///somente o nome do arquivo sem o caminho
TipoRetorno disco_recuperar(Disco* d, char* nome, FILE* arquivoFisico);
unsigned long Tamanho_arquivo(char *nomeArquivo);


 ///implementacoes


