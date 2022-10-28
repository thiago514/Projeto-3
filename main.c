#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _no{
	void *e;
	struct _no *prox;
}No;

typedef struct _lista{
	No *primeiro;
	No *ultimo;
	int tamanho;
}Lista;

typedef struct _personagem{
    int id;
    char nome[20];
    char descricao[30];
}Personagem;

typedef struct _livro{
    int id;
    char titulo[25];
    int anoDePublicacao;
    char ISBN[20];
    Lista *personagem;
    int numPersonagens;
}Livro;

typedef struct _autor{
    int id;
    char nome[20];
    int anoDeNacimento;
    char paisDeNacimento[15];
    Lista *livro;
    int numLivros;
}Autor;

Lista* criarLista(){
	Lista *novaLista = (Lista*) malloc(sizeof(Lista));
	novaLista->primeiro = NULL;
	novaLista->ultimo = NULL;
	novaLista->tamanho = 0;
	return novaLista;
}

void inserir(Lista *lista, void *novoElemento){
	No *novoNo = (No*) malloc(sizeof(No));
	novoNo->e = novoElemento;
	novoNo->prox = NULL;

	if(lista->tamanho == 0){
		lista->primeiro = novoNo;
		lista->ultimo = novoNo;
		lista->tamanho++;
	}else{
		lista->ultimo->prox = novoNo;
		lista->ultimo = novoNo;
		lista->tamanho++;
	}
}

void InfoLista(Lista *lista){
	printf("end lista: %p\nend primeiro: %p\nend ultimo: %p\ntamanho: %d\n",
		lista, lista->primeiro, lista->ultimo, lista->tamanho);
	printf("\n");
}

int remover(Lista *lista, int pos){
	if(pos < 0 || pos>= lista->tamanho)
		return -1;
	No *removido;
	if(lista->tamanho == 1 && pos == 0){
		removido = lista->primeiro;
		free(removido);
		lista->primeiro = NULL;
		lista->ultimo = NULL;
		lista->tamanho--;
		return 0;
	}
	if(pos == 0){
		removido = lista->primeiro;
		lista->primeiro = lista->primeiro->prox;
		free(removido);
		lista->tamanho--;
		return 0;
	}
	No *aux = lista->primeiro;
	int i;
	for(i=0; i<pos-1; i++){
		aux = aux->prox;
	}
	removido = aux->prox;
	aux->prox = aux->prox->prox;
	free(removido);
	if(lista->tamanho-1 == pos){
		lista->ultimo = aux;
	}
	lista->tamanho--;
	return 0;
}
Autor* buscarAutor(Lista *lista, int pos){
	int i;
	if(pos < 0 || pos>= lista->tamanho)
		return NULL;
	No *aux = lista->primeiro;
	for(i=0; i<pos; i++)
		aux = aux->prox;
	return aux->e;
}
Livro* buscarLivro(Lista *lista, int pos){
	int i;
	if(pos < 0 || pos>= lista->tamanho)
		return NULL;
	No *aux = lista->primeiro;
	for(i=0; i<pos; i++)
		aux = aux->prox;
	return aux->e;
}
Personagem* buscarPesonagem(Lista *lista, int pos){
	int i;
	if(pos < 0 || pos>= lista->tamanho)
		return NULL;
	No *aux = lista->primeiro;
	for(i=0; i<pos; i++)
		aux = aux->prox;
	return aux->e;
}

int buscarPosicaoIDLivro(Lista *lista, int id){
    int i=0;
	No *aux = lista->primeiro;
    Livro *l;
    l = (Livro*)aux->e;
	while(l->id!=id){
        aux = aux->prox;
        l = (Livro*)aux->e;
        i++;
    }
		
	return i;
}

int buscarPosicaoIDPersoagem(Lista *lista, int id){
        int i=0;
	No *aux = lista->primeiro;
    Personagem *l;
    l = (Personagem*)aux->e;
	while(l->id!=id){
        aux = aux->prox;
        l = (Personagem*)aux->e;
        i++;
    }
		
	return i;
}
//--------------------------------------
void telaInicial(){
    printf("1 - Exibir autores\n");
    printf("2 - Adicionar autor\n");
    printf("3 - Exibir livros\n");
    printf("4 - adicionar livros\n");
    printf("5 - Exibir personagens\n");
    printf("6 - adicionar personagens\n");
    printf("7 - Adicionar livro para autor\n");//relacionar livro com autor
    printf("8 - Adicionar personagem para livro\n"); //relacionar personagem com livro
    printf("9 - Remover livro de autor\n");
    printf("10 - Remover personagem de livro\n");
    printf("11 - Sair\n");
}

void listarAutores(Lista *lista){
    No *aux = lista->primeiro;
    Autor *a;
    printf("id     nome         nacimento         pais\n");
    while(aux != NULL){
        a = (Autor*) aux->e;
        printf("%d - %s          %d         %s\n",a->id ,a->nome, a->anoDeNacimento, a->paisDeNacimento);
        aux = aux->prox;
    }
    printf("\n\n");
}

void listarLivros(Lista *lista){
    No *aux = lista->primeiro;
    Livro *l;
    printf("id     titulo         ano de publicacao         ISBN\n");
    while(aux != NULL){
        l = (Livro*) aux->e;
        printf("%d  -   %s          %d         %s\n", l->id, l->titulo, l->anoDePublicacao, l->ISBN);
        aux = aux->prox;
    }
    printf("\n\n");
}

void listarPersonagens(Lista *lista){
    No *aux = lista->primeiro;
    Personagem *p;
    printf("id     nome         descricao\n");
    while(aux != NULL){
        p = (Personagem*) aux->e;
        printf("%d  -   %s          %s \n", p->id, p->nome, p->descricao);
        aux = aux->prox;
    }
    printf("\n\n");
}

Autor* addAutor(int numAutor){
    Autor *autor;
    autor = malloc(sizeof(Autor));
    autor->id = numAutor;
    printf("Digite o nome do autor: ");
    scanf(" %[^\n]s", autor->nome);
    printf("Ano de nacimento: ");
    scanf("%d", &autor->anoDeNacimento);
    printf("pais de Nacimento: ");
    scanf(" %[^\n]s", autor->paisDeNacimento);
    printf("\nAutor adicionado com sucesso\n");
    autor->numLivros = 0;
    autor->livro = criarLista();
    return autor;
}

Livro* addLivro(int numLivro){
    Livro *livro;
    livro = malloc(sizeof(Livro));
    livro->id = numLivro;
    printf("Digite o titulo do livro: ");
    scanf(" %[^\n]s", livro->titulo);
    printf("Digite o ano de publicação: ");
    scanf("%d", &livro->anoDePublicacao);
    printf("digite o ISBN do livro: ");
    scanf(" %[^\n]s", livro->ISBN);
    printf("\nLivro adicionado com sucesso\n");
    livro->personagem = criarLista();
    livro->numPersonagens = 0;
    return livro;
}

Personagem* addPersonagem(int numPesonagem){
    Personagem* personagem;
    personagem = malloc(sizeof(Personagem));
    personagem->id = numPesonagem;
    printf("Digite o nome do personagem: ");
    scanf(" %[^\n]s", personagem->nome);
    printf("Digite a descricao do personagem: ");
    scanf(" %[^\n]s", personagem->descricao);
    printf("\n personagem adicionado com sucesso\n");
    return personagem;
}

int main(){
    int c = 0, op = 0, op2, numAutores = 0, numLivros = 0, numPersonagens = 0, listIdAutor, listIdLivro;
    int autorOP, livroOP, personagemOP;
    Lista *autor = criarLista();
    Lista *livro = criarLista();
    Lista *personagem = criarLista();

    while(c!=11){
        telaInicial();
        scanf("%d", &op);
        switch(op){
        case 1://Exibir autores   FUNCIONANDO
           if (numAutores <= 0){
            printf("Nenhum autor foi adicionado\n");
           }
           else{
            listarAutores(autor);
           }
        break;
        
        case 2://Adicionar autores   FUNCIONANDO
            inserir(autor, ((void*)addAutor(numAutores)));
            numAutores++;
        break;

        case 3://Exibir livros   
            printf("1 - exibir todos os livros\n");
            printf("2 - exibir livros de um autor especifico\n");
            scanf("%d", &op2);
            switch(op2){
            case 1://exibir todos os livros
                if (numLivros <= 0){
                printf("Nenhum livro foi adicionado\n");
                }
                else{
                listarLivros(livro);
                }
            break;
            case 2: // exibir livros de um autor especifico
                if (numAutores <= 0){
                   printf("Nenhum autor foi adicionado\n");
                   break;
                }
                else{
                   listarAutores(autor);
                }
                printf("\n\n");
                printf("Digite o id do autor:");
                scanf("%d", &listIdAutor);
                
                if (buscarAutor(autor,listIdAutor)->numLivros <= 0){
                printf("O Autor não possui nenhum livro adicionado\n");
                }
                else{
                    listarLivros(buscarAutor(autor,listIdAutor)->livro);
                }
            break;
            }
        break;

        case 4://adicionar Livros 
            inserir(livro, ((void*)addLivro(numLivros))); 
            numLivros++;

        break;

        case 5://Exibir personagens 
            printf("1 - exibir todos os personagens\n");
            printf("2 - exibir personagens de um livro especifico\n");
            scanf("%d", &op2);
            switch(op2){
                case 1: // exibir todos os personagens
                    if (numPersonagens <= 0){
                        printf("Nenhum personagem foi adicionado\n");
                    }
                    else{
                        listarPersonagens(personagem);
                    }
                break;

                case 2:// exibir personagens de um livro especifico
                    if (numLivros <= 0){
                        printf("Nenhum livro foi adicionado\n");
                        break;
                    }
                    else{
                       listarLivros(livro);
                    }
                    printf("\n\n");
                    printf("Digite o id do livro\n");
                    scanf("%d", &listIdLivro);
                    if (buscarLivro(livro, listIdLivro)->numPersonagens <= 0){
                        printf("O livro não possui nenhum personagem adicionado\n");
                    }
                    else{
                        listarPersonagens((buscarLivro(livro, listIdLivro)->personagem));
                    }

                break;
            }
            
        break;

        case 6://Adicionar Personagens 
           inserir(personagem, ((void*)addPersonagem(numPersonagens)));
           numPersonagens++;
        break;

        case 7://relacionar livro com autor
            listarAutores(autor);
            printf("\ndigite o id do autor que voce deseja relacionar um livro\n");
            scanf("%d", &autorOP);
            listarLivros(livro);
            printf("\nDigite o id do livro do autor: ");
            scanf("%d", &livroOP);
            inserir(buscarAutor(autor, autorOP)->livro, buscarLivro(livro, livroOP));
            buscarAutor(autor, autorOP)->numLivros++;
            printf("livro relacionado com sucesso\n");
        break;

        case 8://relacionar personagem com livro
            listarLivros(livro);
            printf("\nDigite o id do livro que voce deseja relacionar um personagem: ");
            scanf("%d", &livroOP);
            listarPersonagens(personagem);
            printf("digite o id do personagem do livro: ");
            scanf("%d", &personagemOP);
            inserir(buscarLivro(livro, livroOP)->personagem, buscarPesonagem(personagem, personagemOP));
            buscarLivro(livro,livroOP)->numPersonagens++;
            printf("personagem relacionado com sucesso\n");
        break;
        case 9://remover livro de autor
            listarAutores(autor);
            printf("Digite o id do autor desejado: ");
            scanf("%d", &autorOP);
            listarLivros(buscarAutor(autor,autorOP)->livro);
            printf("Digite o ID do livro que deseja remover: ");
            scanf("%d", &livroOP);
            if(livroOP<0 || livroOP>numLivros){
                printf("opcao de livro invalida\n");
            }
            else{
                Autor *a = buscarAutor(autor,autorOP);
                int posL = buscarPosicaoIDLivro(a->livro,livroOP);
                remover(a->livro, posL);
                a->numLivros--;
                printf("removido com sucesso\n");
            }
            break;
        case 10:// remover personagem de livro
            listarLivros(livro);
            printf("\nDigite o id do livro que voce deseja relacionar um personagem: ");
            scanf("%d", &livroOP);
            listarPersonagens(buscarLivro(livro,livroOP)->personagem);
            printf("digite o id do personagem do livro: ");
            scanf("%d", &personagemOP);
            if(personagemOP<0 || personagemOP>numPersonagens){
                printf("opcao de personagem invalida");
            }
            else{
                Livro *l = buscarLivro(livro, livroOP);
                int posP = buscarPosicaoIDPersoagem(l->personagem, personagemOP);
                remover(l->personagem, posP);
                l->numPersonagens--;
                printf("removido com sucesso\n");
            }
        break;

        case 11:
        c = 11;
        break;

        default:
        printf("Opção invalida\n");
            
        };
    }
return 0;
}