#include "LLDE.h"

/**
 *  Essa função busca no arquivo .csv os trechos separados por ";", que correspondem aos campos
 *  matrícula, nome, área, tutulação e vínculo. Ao encontrar cada, ele atribui a string ao
 *  seu campo corrspondente, linha por linha.
 *  
 *  Tendo feito isso linha por linha, a função insere na lista
 *  
 *  Este programa possui diferentes modos de inserção, sendo a inserção padrão e ordenada
 *  A ordenada possui 2 formas, sendo elas crescente e decrescente.abort
 * 
 * 
 * @param lista TLLDE
 * @param arquivo arquivo.csv
 * @param modo int
 * 
 * O modo será um parâmetro que determinará a forma de inserção. 
 * 1 - inserção padrão
 * 2 - inserção ordenada crescente
 * 3 - inserção ordenada decrescente
 */
int carregarDadosNaLista(TLLDE * const lista, const char* nomeDoArquivo, int modo) {
    FILE *file = fopen(nomeDoArquivo, "r");
    //fopen() = abre um arquivo 
    //primeiro parametro: nome do arquivo
    //segundo parametro: modo de leitura (r = read, w = write e a = add)
    //retorna ponteiro para o arquivo e NULL em caso de erro ou não encontro do arquivo.

    if (file == NULL) {
        printf("\n\n\nErro ao abrir o arquivo. %s\n\n\n", nomeDoArquivo);
        return 0;
    }
    
    char linha[512];
    while (fgets(linha, sizeof(linha), file)) {
        //fgets: lê uma linha de texto (arquivo ou entrada do usuario) e armazena em uma string
        //primeiro parametro: ponteiro para uma string onde será armazenado (destino)
        //segundo parametro: numero maximo de caracteres a serem lidos
        //ponteiro para o fluxo de entrada (file = arquivo, stdin = entrada do usuario)
        //retorna NULL em caso de erro ou fim do arquivo
        //o NULL em C é interpretado como FALSE (ou 0), por isso funciona no while().

        TDocente *docente = (TDocente *)malloc(sizeof(TDocente)); 

        char *token = strtok(linha, ";");
        // No primiro parametro, é passado "linha" para indicar que linha será a string a ser analisada
        // já nas demais chamadas é passado NULL, pois é para continuar a tokenizacao da linha, não ler uma string nova

        if (token) docente->matricula = atoi(token);
        
        //strtok() = divide a string em tokens. Um token surge quando é econtrado o delimitador (;)
        //primeiro parametro: ponteiro para a string que será dividida
        //segundo parametro: o caractere delimitador.
        //retorna ponteiro para o proximo token encontrado, ou NULL, caso não haja proximo.

        token = strtok(NULL, ";");
        if (token) strcpy(docente->nome, token);
        //strcpy: copia a string da origem e a salva no destino
        //primeiro parametro: ponteiro para o buffer de destino
        //segundo parametro: ponteiro para a string que será copiada
        //retorna ponteiro para o destino

        token = strtok(NULL, ";");
        if (token) strcpy(docente->area, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(docente->titulacao, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(docente->vinculo, token);
        
        if (modo == 1){
            inserirFimLLDE(docente, lista); 
        }
        else if (modo == 2){
            inserirOrdenadoLLDE(docente, lista);
        }
        else if(modo == 3){
            inserirOrdenadoDecrescenteLLDE(docente, lista);
        }
    }
    
    fclose(file);

    return 1;
}