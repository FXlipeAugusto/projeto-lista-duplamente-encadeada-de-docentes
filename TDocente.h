#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int matricula;  
    char nome[64];
    char area[16];
    char titulacao[32];         
    char vinculo[32];
}TDocente;

TDocente* lerDocente() {
    TDocente* docente = (TDocente*)malloc(sizeof(TDocente));
    if (docente == NULL) {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }
    
    do{
        //Aqui alterei para que ao inserir a matrícula, o código verifique se ela é pelo menos
        //um valor não negativo e maior que 0.
        
        printf("Matricula: ");
        scanf("%d", &docente->matricula);
        getchar(); //limpar o \n do buffer
        //getchar() Lê um caractere de entrada do usuário. Retorna um int
        //O int que o getchar() retorna, é o código numerico do caractere lido.


        if(docente->matricula < 1) printf("Insira uma matrícula válida.\n");
    }while(docente->matricula < 1);
    //while(): laço de repetição que executa enquanto a condição for verdadeira.

    printf("Nome: ");
    //printf() exibe mensagem formatada. Retorna um int que representa o número de caracteres exibidos.
    //(ou seja, não inclui caractere nulo!)
    //em caso de erro, ela retorna -1.
    
    fgets(docente->nome, sizeof(docente->nome), stdin);
    //fgets(): ele lê linha de texto de uma entrada
    //         primeiro paramentro: ponteiro para onde a string será armazenada
    //         segundo parametro: numero maximo de caracteres a ser lido, já incluso \0
    //         terceiro paramentro: origem da entrada. Em caso de stdin, entrada do usuário
    docente->nome[strcspn(docente->nome, "\n")] = '\0';
    //strcspn(): busca a primeira ocorrencia do caractere especificado no segundo parametro. Retorna o
    //número de caracteres antes da ocorrência.
    //primeiro parametro: onde a busca será feita
    //segundo paramentro: string com os caracteres proibidos
    //retorno: o int retornado é índice da primeira ocorrencia do caractere proibido
    //Caso não haja o caractere proibido, retornara o tamanho da string toda. 

    printf("Area: ");
    fgets(docente->area, sizeof(docente->area), stdin);
    docente->area[strcspn(docente->area, "\n")] = '\0';

    printf("Titulacao: ");
    fgets(docente->titulacao, sizeof(docente->titulacao), stdin);
    docente->titulacao[strcspn(docente->titulacao, "\n")] = '\0';

    printf("Vinculo: ");
    fgets(docente->vinculo, sizeof(docente->vinculo), stdin);
    docente->vinculo[strcspn(docente->vinculo, "\n")] = '\0';

    return docente;
}

int exibirDocente(const TDocente *docente) {
    //Ponteiro para uma constante. Os valores não podem ser alterados
    //mas para onde aponta, sim.

    if (docente == NULL) return 0;
    //NULL = usado para vazio (que é diferente de 0).

    printf("Matrícula: %d, Nome: %s, Área: %s, Titulação : %s, Vínculo: %s", docente->matricula, docente->nome, docente->area, docente->titulacao, docente->vinculo);
    
    
   
    return 1;
}
