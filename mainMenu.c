#include"leituraArquivos.h"


int lerInt() {
    int valor;
    scanf("%d", &valor);
    getchar();
    //getchar() Lê um caractere de entrada do usuário. 
    //fazendo isso, limpa-se o buffer de entrada, subistituindo o \n do usuario por \0

    return valor;
}

int main() {
    TLLDE lista;
    inicializarLLDE(&lista);
    
    int resposta;
    int hasBeenRead = 0;
    do {
        printf("\n");
        printf("**************************************\n");
        printf("**   BOAS VINDAS À LISTA DO CORPO DOCENTE   **\n");
        printf("**************************************\n");
        printf("Digite o número da opção desejada:\n\n");

        printf("-------------//* Carregamento de Dados *//-------------\n");
        printf("1   - Carregar dados do arquivo\n"); 
        printf("2   - Carregar dados de modo ordenado CRESCENTE\n"); 
        printf("3   - Carregar dados de modo ordenado DECRESCENTE\n\n"); 
        
        printf("-------------//* Exibição Completa *//-------------\n");
        printf("4   - Listar os dados da lista\n"); 
        printf("5   - Listar os dados da lista de trás para frente\n\n"); 
        
        printf("-------------//*Exibição Única*//-------------\n");
        printf("6   - Acessar o início da lista\n"); 
        printf("7   - Acessar o fim da lista\n");  
        printf("8   - Acessar uma posição da lista\n\n");
        
        printf("-------------//* Inserção de Dados *//-------------\n");
        printf("9   - Inserir no início da lista\n"); 
        printf("10  - Inserir no fim da lista\n");  
        printf("11  - Inserir em uma posição lista\n"); 
        printf("12  - Inserir ordenado (crescente)\n"); 
        printf("13  - Inserir ordenado (decrescente)\n\n");


        printf("-------------//* Remoção de Dados *//-------------\n");
        printf("14  - Retirar do início da lista\n"); 
        printf("15  - Retirar do fim da lista\n"); 
        printf("16  - Retirar de uma posição da lista\n\n"); 

        printf("---------------------//*&*//---------------------\n");

        printf("17  - Sair\n");
        scanf("%d", &resposta);
        
        while((resposta < 1) || (resposta > 17)) {
            printf("Digite uma opção válida!\n");
            scanf("%d", &resposta);
        }
        getchar();

        switch(resposta) {
            case 1:
                system("cls");
                //envia o comando "cls" para o sistema operacional
                //tal comando serve para limpar a tela
                //retorna um int em caso de sucesso e -1 em caso de falha.
                

                //Has been read é um auxiliar implementado pelo Matheus. Em caso de leitura de arquivo,
                //É atribuído 1 para a variavel. Isso evita múltiplas leituras.
                if(hasBeenRead){
                    printf("\n\nOs dados do arquivo já foram lidos!\n\n");
                    break;
                }
                
                //Essa notação usa operador ternário, que é uma forma simplificada de if e else
                //Notação: (condição) ? expressão_se_verdadeiro : expressão_se_falso;
                (carregarDadosNaLista(&lista, "data.txt", 1)) ? printf("\nDados carregados com sucesso!\n\n") : printf("\nTente novamente\n\n");
                hasBeenRead = 1;
                break;

            case 2:
                system("cls");
                if(hasBeenRead){
                    printf("\n\nOs dados do arquivo já foram lidos!\n\n");
                    break;
                }
                (carregarDadosNaLista(&lista, "data.txt", 2)) ? printf("\nDados carregados com sucesso!\n\n") : printf("\nTente novamente\n\n");
                hasBeenRead = 1;
                break;
            case 3: 
                system("cls");
                if(hasBeenRead){
                    printf("\n\nOs dados do arquivo já foram lidos!\n\n");
                    break;
                }

                (carregarDadosNaLista(&lista, "data.txt", 3)) ? printf("\nDados carregados com sucesso!\n\n") : printf("\nTente novamente\n\n");
                hasBeenRead = 1;
                break;
                
            case 4:{
                system("cls");
                char *listaEmString = mostrarLLDEIncioFim(&lista);
                printf("%s", listaEmString);
                free(listaEmString);
                //free() libera de volta para o sistema a memória alocada pela string em mostrarLLDEIncioFim()
                //parametro: ponteiro para um bloco de memória previamente alocado
                //retorno: não há retorno, é uma função do tipo void.
                break;
            }
            case 5:{
                system("cls");
                char *listaEmString = mostrarLLDEFimIncio(&lista);
                printf("%s", listaEmString);
                free(listaEmString);
                break;
            }

            case 6:{
                system("cls");
                exibirDocente(acessarInicioLLDE(&lista));
                break;
            }
            
            case 7:{
                system("cls");
                exibirDocente(acessarFimLLDE(&lista));
                break;
            }
            
            case 8:{
                system("cls");
                printf("Informe o INDEX do docente: ");
                exibirDocente(acessarNaPosicaoLLDE(&lista, lerInt())) ? printf("\n") : printf("Não foi possível acessar o docente, a lista está vazia ou o INDEX fornecido é invalido.\n\n");                
                break;
                //exibirDocente() é uma função int
            }

            case 9:{
                system("cls");
                (inserirInicioLLDE(lerDocente(), &lista)) ? printf("Docente inserido ao INICIO com sucesso!\n\n") : printf("Não foi possível inserir o docente, tente novamente.\n\n");                
                //inserirInicioLLDE() é uma função int
                break;
            }
            
            case 10:{
                system("cls");
                (inserirFimLLDE(lerDocente(), &lista)) ? printf("\n\nDocente inserido ao FIM com sucesso!\n\n") : printf("\n\nNão foi possível inserir o docente, tente novamente.\n\n");                
                break;
                //inserirFimLLDE é uma função int
                //lerDocente() retorna docente.

            }
            
            case 11:{
                system("cls");
                printf("Informe o INDEX em que o docente será inserido: ");
                int index = lerInt();
                (inserirNaPosicaoLLDE(lerDocente(), &lista, index)) ? printf("Docente inserido com sucesso!\n\n") : printf("Não foi possível inserir o docente, verifique o INDEX informado e tente novamente.\n\n");                
                break;
                
            }
            case 12:{
                system("cls");
                (inserirOrdenadoLLDE(lerDocente(), &lista)) ? printf("\n\nDocente inserido de modo ordenado com sucesso!\n\n") : printf("\n\nNão foi possível inserir o docente, tente novamente.\n\n");
                break;
            }

            case 13:{
                system("cls");
                (inserirOrdenadoDecrescenteLLDE(lerDocente(), &lista)) ? printf("\n\nDocente inserido de modo ordenado decrescente com sucesso!\n\n") : printf("\n\nNão foi possível inserir o docente, tente novamente.\n\n");
                break;
            }

            case 14:{
                system("cls");
                (retirarInicioLLDE(&lista)) ? printf("Docente removido com sucesso!\n\n") : printf("Não foi possível remover o docente.\n\n");                
                break;
            }
            
            case 15:{
                system("cls");
                (retirarFimLLDE(&lista)) ? printf("Docente removido com sucesso!\n\n") : printf("Não foi possível remover o docente.\n\n");                
                break;
            }

            case 16:{
                system("cls");
                printf("Informe o index do elemento a ser removido: ");
                (retirarNaPosicaoLLDE(&lista, lerInt())) ? printf("\n\nElemento removido com sucesso!\n\n") : printf("\n\nErro ao remover o elemento, verifique o INDEX fornecido.\n\n");
                break;
            }
            
            case 17:
                system("cls");
                printf("Saindo...\n");
                break;
                

            default:
                printf("Opção inválida.\n");
                break;
        }

        printf("\n\nAperte ENTER para continuar\n");
        getchar();
        system("cls");

    } while(resposta != 17);
    
    liberarLLDE(&lista);
    return 0;
    
}