#include "TDocente.h"

// Struct que representa o No da LLDE
typedef struct No{
	TDocente *docente;
	struct No *anterior;
	struct No *proximo;
}TNo;

// Struct que representa a LLDE
typedef struct{
   struct No *inicio;
	struct No *fim;
	int tamanho;
}TLLDE;

/**********************************************************
 * Funções Base da LLDE
 **********************************************************/

 // Função que cria e inicializa um no para a LLDE
TNo *criarNoLLDE(TDocente * docente){
	TNo *no = (TNo*)malloc(sizeof(TNo));
	//malloc: aloca memória dinamicamente. Reserva um bloco de memória
	//retorna void * (ponteiro generico) para o início da memória alocada
	//retorna NULL em caso de falha 

	if(no == NULL) return NULL;
	no->docente = docente;
	no->proximo = NULL;
	no->anterior = NULL;
	return no;
} 

//  Função que inicializa a LLDE 
void inicializarLLDE(TLLDE * const lista){
	lista->inicio = NULL;
	lista->fim = NULL;
	lista->tamanho = 0;
}

// Função que verifica se a LLDE esta vazia 
int estaVazia(TLLDE const * const lista){
	return  (lista->inicio == NULL);
}

// Função que libera o espaco de memória usado pela LLDE
void liberarLLDE(TLLDE *const lista){
	if(estaVazia(lista)) return;
    while(lista->inicio != NULL){
        TNo *pAux = lista->inicio;
        lista->inicio = pAux->proximo;
        //printf("Liberando o no com dado %d\n", pAux->dado);
        free(pAux->docente);
        free(pAux);
        lista->tamanho--;
    }
}


/**********************************************************
 * Funções de Exibição da LLDE
 **********************************************************/

// Função para retornar uma string com a lista do inicio ao fim
char* mostrarLLDEIncioFim(TLLDE const * const lista){ 
	// tamanho do nó + tamanho do docente + tamanho em bytes do texto que vai decorar o docente e tudo * a quantidade de elementos da lista :)
	// lista->tamanho + 1 pq se n tiver elemento nenhum eu ainda vou precisar do espaço pra string de qnd ela tá vazia
	char *str = (char*) malloc(1024 * (lista->tamanho + 1024)); 
	if (estaVazia(lista)){
		sprintf(str, "LLDE = { VAZIA }");
		//escreve dados formatados na string.
		// primeiro parametro: ponteiro para array onde será escrito
		// segundo parametro: a string a ser escrita em str.

		return str;
	}
	strcpy(str, "LLDE = {\n");
    //strcpy: copia uma string de uma origem para um destino
	// primeiro parametro: ponteiro para array de destino
	// segundo parametro: string que será copiada.

	char strAux[512];
	for(TNo *pAux = lista->inicio; pAux != NULL; pAux = pAux->proximo){
		snprintf(strAux, sizeof(strAux),
				"Matrícula: %d,"
				"Nome: %s,"
				"Área: %s,"
				"Titulação: %s,"
				"Vínculo: %s",
				pAux->docente->matricula,
				pAux->docente->nome,
				pAux->docente->area,
				pAux->docente->titulacao,
				pAux->docente->vinculo);

        //snprintf: serve para escrever dados formatados em uma string, mas com limite de tamanho.
        //primeiro parametro: destino, no caso, onde será escrito.
		//segundo parametro: tamanho maximo, já incluso \0
		// string a ser escrita

		strcat(str, strAux);
		//strcat(): junta (concatena) strings, juntando uma à outra
		// primeiro parametro: string que receberá a string adicional
		// segundo parametro: string adicional. Concatena-se elas.
	}
	strcat(str," }\n");
	return str;
}

// Função para mostrar a LLDE do fim para o inicio

char* mostrarLLDEFimIncio(TLLDE const * const lista){ 
    // tamanho do nó + tamanho do docente + tamanho em bytes do texto que vai decorar o docente e tudo * a quantidade de elementos da lista :)
	// lista->tamanho + 1 pq se n tiver elemento nenhum eu ainda vou precisar do espaço pra string de qnd ela tá vazia
	char *str = (char*) malloc(( sizeof(TNo) + sizeof(TDocente) + 180) * (lista->tamanho + 1)); 
	if (estaVazia(lista)){
		sprintf(str, "LLDE = { VAZIA }");
		return str;
	}
	strcpy(str, "LLDE = {\n");
	char strAux[512];
	for(TNo *pAux = lista->fim; pAux != NULL; pAux = pAux->anterior){
		snprintf(strAux, sizeof(strAux),
				"Matrícula: %d,"
				" Nome: %s,"
				" Área: %s,"
				" Titulação: %s,"
				" Vínculo: %s",
				pAux->docente->matricula,
				pAux->docente->nome,
				pAux->docente->area,
				pAux->docente->titulacao,
				pAux->docente->vinculo);

		strcat(str, strAux);
	}
	strcat(str," }\n");
	return str;
}

//********************************************************
// Funções para manipulação da LLDE
//*******************************************************

/**
 * Função para incluir um elemento no inicio da LLDE
 * 
 * @param docente ponteiro para struct docente
 * @param lista TLLDE
 * 
 * @throw 0 caso ERROR
 * @return 1 caso SUCCESS
 */
int inserirInicioLLDE(TDocente *docente, TLLDE *const lista){
	TNo *no = criarNoLLDE(docente);
	if(no == NULL) return 0;
	if(estaVazia(lista)){
		lista->inicio = no;
		lista->fim = no;
		lista->tamanho++;
		return 1;
	}
	lista->inicio->anterior = no;
	no->proximo = lista->inicio;
	lista->inicio = no;
	lista->tamanho++;
	return 1;
}

/**
 * Função para acessar um elemento do inicio LLDE
 * 
 * @param lista TLLDE
 * 
 * @throw 0 caso vazia
 * @return ponteiro para docente caso sucesso.
 */
TDocente* acessarInicioLLDE(TLLDE const * const lista){
	if (estaVazia(lista)){
		printf("\nNão foi possivel acessar. A lista esta vazia.\n");
		return 0;
	}
	return lista->inicio->docente;
}

/**
 * Função para retirar um elemento do inicio LLDE
 * 
 * @param lista TLLDE
 * 
 * @throw 0 caso esteja vazia.
 * @return 1 caso retire com sucesso.
 */
int retirarInicioLLDE(TLLDE *const lista){
	if (estaVazia(lista)) return 0;

	if(lista->tamanho == 1){
        free(lista->inicio->docente);
		free(lista->inicio);
		lista->inicio = NULL;
		lista->fim = NULL;
		lista->tamanho = 0;
		return 1;
	}

	TNo *no = lista->inicio;
	lista->inicio = no->proximo;
	lista->inicio->anterior = NULL;
	lista->tamanho--;
	free(no);
	return 1;
}

/**
 * Função para incluir um elemento no fim da LLDE
 * 
 * @param lista TLLDE
 * 
 * @return 0 caso FAIL
 * @return 1 caso SUCESS.
 */
int inserirFimLLDE(TDocente *docente, TLLDE *const lista){
	TNo *no = criarNoLLDE(docente);
	if(no == NULL) return 0;
	if(estaVazia(lista)){
		lista->inicio = no;
		lista->fim = no;
		lista->tamanho++;
		return 1;
	}
	lista->fim->proximo = no;
	no->anterior = lista->fim;
	lista->fim = no;
	lista->tamanho++;
	return 1;
}

/**
 * Função para acessar um elemento no fim da  LLDE
 * 
 * @param lista TLLDE
 * 
 * @return 0 caso a lista esteja vazia, 
 * @return valor do fim caso não esteja vazia
 */
TDocente* acessarFimLLDE(TLLDE const * const lista){
	if(estaVazia(lista)){
		printf("\n\nNão foi possivel acessar. A lista esta vazia.\n\n");
		return 0;
	}
	return (lista->fim->docente);
}

// 
/**
 * Função para retirar um elemento do fim LLDE
 * 
 * @param lista TLLDE
 * 
 * @return 0 caso esteja vazia, 
 * @return 1 caso retire com sucesso.
 */
int retirarFimLLDE(TLLDE *const lista){
	if(estaVazia(lista)) return 0;
	if(lista->tamanho == 1){
		retirarInicioLLDE(lista);
		return 1;
	}

	TNo *no = lista->fim;
	lista->fim = no->anterior;
	lista->fim->proximo = NULL;
	lista->tamanho--;
    free(no->docente);
	free(no);
	return 1;
}

// Insere um elemento no index informado
int inserirNaPosicaoLLDE(TDocente *docente, TLLDE *const lista, int pos){
	if(docente == NULL) return 0;
	if(pos < 0 || pos > lista->tamanho) return 0;

	if(pos == 0){
		inserirInicioLLDE(docente, lista);
		return 1;
	} 
	if(pos == lista->tamanho){
		inserirFimLLDE(docente, lista);
		return 1;
	} 

	TNo *pAux = lista->inicio->proximo;
	for(int i = 1; i < pos; i++){
		pAux = pAux->proximo;
	}

	TNo *no = criarNoLLDE(docente);
	pAux->anterior->proximo = no; 
	no->anterior = pAux->anterior;
	no->proximo = pAux;
	pAux->anterior = no;
	lista->tamanho++;

	return 1;
}

/**
 * Função para inserção de modo ordenado por matrícula
 * 
 * @param docente TDocente
 * @param lista TLLDE
 * 
 * @return 0 caso falhe, 
 * @return 1 caso insira com sucesso.
 */
int inserirOrdenadoLLDE(TDocente *docente, TLLDE *const lista){
	if(docente == NULL || lista == NULL) return 0;
	
    //caso a lista esteja vazia
    if(estaVazia(lista)){
		inserirInicioLLDE(docente, lista);
		return 1;
	}
	
	// verifico se é viavel inserir nas pontas pra faciltar minha vida
	if(docente->matricula <= lista->inicio->docente->matricula){
		inserirInicioLLDE(docente, lista);
		return 1;
	}
	if(docente->matricula >= lista->fim->docente->matricula){
		inserirFimLLDE(docente, lista);
		return 1;
	}    
	
    TNo * pAux = lista->inicio;
	int index = 0;
    //percorre até encontrar a posição correta
    while(pAux->docente->matricula < docente->matricula){
        pAux = pAux->proximo;
		index++;
    }
	inserirNaPosicaoLLDE(docente, lista, index);
    return 1;
}


/**
 * Função para inserção de modo ordenado decrescente por matrícula
 * 
 * @param docente TDocente
 * @param lista TLLDE
 * 
 * @return 0 caso esteja vazia, 
 * @return 1 caso retire com sucesso.
 */
int inserirOrdenadoDecrescenteLLDE(TDocente *docente, TLLDE *const lista){
    if(docente == NULL || lista == NULL) return 0;
	
    //caso a lista esteja vazia
    if(estaVazia(lista)){
		inserirInicioLLDE(docente, lista);
		return 1;
	}
	
	// verifico se é viavel inserir nas pontas pra faciltar minha vida
	if(docente->matricula >= lista->inicio->docente->matricula){
		inserirInicioLLDE(docente, lista);
		return 1;
	}
	if(docente->matricula <= lista->fim->docente->matricula){
		inserirFimLLDE(docente, lista);
		return 1;
	}
	
    TNo * pAux = lista->inicio;
	int index = 0;
    //percorre até encontrar a posição correta
    while(pAux->docente->matricula > docente->matricula){
        pAux = pAux->proximo;
		index++;
    }
	inserirNaPosicaoLLDE(docente, lista, index);
    return 1;
}







/**
 *  Retorna o elemento no index passado como parametro.
 * 
 * @param lista TLLDE
 * @param pos index do elemento
 * 
 * @return -1 caso esteja vazia ou a possição seja invalida, 
 * @return valor do elemento caso não esteja vazia e a posição seja valida.
 */
TDocente * acessarNaPosicaoLLDE(TLLDE const * const lista, int pos){
	if(estaVazia(lista)) return NULL;
	if(pos >= lista->tamanho || pos < 0) return NULL;

	if(pos == 0) return acessarInicioLLDE(lista);
	if(pos == lista->tamanho - 1) return acessarFimLLDE(lista);

	TNo *pAux = lista->inicio;
	for(int i = 0; i < pos; i++){
		pAux = pAux->proximo;
	}
	return (pAux->docente);
}

/**
 *  Retira o elemento no index passado como parametro
 * 
 * @param lista TLLDE
 * @param pos index do elemento
 * 
 * @return 0 caso esteja vazia ou a possição seja invalida, 
 * @return 1 caso não esteja vazia e a posição seja valida.
 */
int retirarNaPosicaoLLDE(TLLDE *const lista, int pos){
	if(estaVazia(lista)) return 0;
	if(pos >= lista->tamanho || pos < 0) return 0;
	
	TNo *pAux;
	if(pos == 0){
		retirarInicioLLDE(lista);
		return 1;
	}
	if(pos == lista->tamanho - 1){
		retirarFimLLDE(lista);
		return 1;
	}

	pAux = lista->inicio;
	for(int index = 0; index < pos; index++){
		pAux = pAux->proximo;
	}
	pAux->anterior->proximo = pAux->proximo;
	pAux->proximo->anterior = pAux->anterior;
	lista->tamanho--;
    free(pAux->docente);
	free(pAux);
	return 1;	
}

/**
 *  Retira o elemento passado como parametro da lista caso haja na lista um nó com o mesmo valor.
 * 
 * @param lista TLLDE
 * @param elemento valor do elemento
 * 
 * @return -1 caso esteja vazia ou a possição seja invalida, 
 * @return 1 caso tenha um elemento com esse valor e ele tenha sido removido.
 */
int retirarElementoLLDE(TLLDE *const lista, int matricula){
	if(estaVazia(lista)) return -1;

	if(acessarInicioLLDE(lista)->matricula == matricula){ 
		retirarInicioLLDE(lista);
		return 1;
	}
	if(acessarFimLLDE(lista)->matricula == matricula){ 
		retirarFimLLDE(lista);
		return 1;
	}

	TNo *pAux;
	pAux = lista->inicio->proximo;
	for(int index = 1; index < lista->tamanho - 1; index++){
		if(pAux->docente->matricula == matricula){
			pAux->anterior->proximo = pAux->proximo;
			pAux->proximo->anterior = pAux->anterior;
            free(pAux->docente);
			free(pAux);
			lista->tamanho--;
			return 1;
		}
		pAux = pAux->proximo;
	}
	return -1;
}

// -1 caso n exista, index do elemento caso exista
int buscarElementoNaLLDE(int matricula, TLLDE *const lista){
	if(estaVazia(lista)) return 0;

	if(acessarInicioLLDE(lista)->matricula == matricula) return 0;	
	if(acessarFimLLDE(lista)->matricula == matricula) return lista->tamanho - 1;

	TNo *pAux;
	pAux = lista->inicio->proximo;
	for(int index = 1; index < lista->tamanho - 1; index++){
		if(pAux->docente->matricula == matricula){
			return index;
		}
		pAux = pAux->proximo;
	}
	return -1;
}
// TODO:
/*
	Menu com todas essas funções (menos as tecnicas da lista)
	Metodo de carregar os dados de um arquivo na ordem do arquivo ou ordenado em crescente ou decrescente
*/
