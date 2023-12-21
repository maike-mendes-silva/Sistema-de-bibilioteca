#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "user.h"
#include "book.h"

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

void printHeader(){
	system(CLEAR_SCREEN);
	printf("====== LIBRASYS - SISTEMA DE GERENCIAMENTO ======\n");
	printf("Desenvolvido por: Maike Mendes Silva\n\n");
}

void clearBuffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
	
	FILE *userFile;
	FILE *bookFile;
	FILE *loanBookFile;
	
	int op;
	char exiting;
	
	do{	
		printHeader();
		printf("---- MENU PRINCIPAL ----\n\n");
		printf("1. Gerenciar Usuarios\n");
		printf("2. Gerenciar Livros\n");
		printf("3. Encerrar Programa\n\n");
		printf("Digite o numero correspondente a opcao desejada: ");
		scanf(" %d", &op);
		clearBuffer();
		if(op == 1){
			do{
				printHeader();
				printf("---- MENU USUARIO ----\n\n");
				printf("Cadastrar Usuario ==> C 'Nome' 'CPF'\n");
				printf("Remover Usuario ==> R ID\n");
				printf("Pesquisar Usuario(s) ==> P 'Nome'\n");
				printf("Mostrar Usuario(s) ==> M\n");
				printf("Sair do Menu ==> S\n\n");
				printf("Digite o comando: ");
				
				int id;
				char name[MAX];
				char cpf[CPF_MAX];
				scanf(" %c", &exiting);
				switch(exiting){
					case 'C':
						scanf(" '%50[^']' '%14[^']'", name, cpf);
						insertUser(userFile, name, cpf);
						clearBuffer();
						break;
					case 'R':
						scanf(" %d", &id);
						removeUser(userFile, id);
						clearBuffer();
						break;
					case 'P':
						scanf(" '%50[^']'", name);
						searchUser(userFile, name);
						clearBuffer();
						break;
					case 'M':
						showUserFile(userFile);
						clearBuffer();
						break;
					case 'S':
						clearBuffer();
						break;
					default:
						clearBuffer();
						printf("\nComando inexistente.\n");
						break;
				}
				printf("\nPressione qualquer letra para continuar...");
				char c = getch();
			} while(exiting != 'S');
		} else if (op == 2){
			do{
				printHeader();
				printf("---- MENU LIVRO ----\n\n");
				printf("Cadastrar Livro ==> C 'Nome Livro' 'Nome Autor' Ano 'ISBN' Copias\n");
				printf("Aumentar/Diminuir copias ==> A ID Copias\n");
				printf("Remover Livro ==> R ID\n");
				printf("Emprestar Livro ==> E UsuarioID LivroID\n");
				printf("Devolver Livro ==> D UsuarioID LivroID\n");
				printf("Pesquisar Livro(s) ==> P 'Nome'\n");
				printf("Mostrar Livro(s) no Acervo ==> M\n");
				printf("Listar Livro(s) Emprestados ==> L\n");
				printf("Sair do Menu ==> S\n\n");
				printf("Digite o comando: ");
				
				int id;
				int idUser;
				char nameBook[MAX];
				char nameAuthor[MAX];
				int year;
				char isbn[ISBN_MAX];
				int copies;
				scanf(" %c", &exiting);
				switch(exiting){
					case 'C':
						scanf(" '%50[^']' '%50[^']' %d '%15[^']' %d", nameBook, nameAuthor, &year, isbn, &copies);
						insertBook(bookFile, nameBook, nameAuthor, year, isbn, copies);
						clearBuffer();
						break;
					case 'A':
						scanf(" %d %d", &id, &copies);
						addCopies(bookFile, id, copies);
						clearBuffer();
						break;
					case 'R':
						scanf(" %d", &id);
						removeBook(bookFile, id);
						clearBuffer();
						break;
					case 'E':
						scanf(" %d %d", &idUser, &id);
						loanBook(bookFile, userFile, loanBookFile, idUser, id);
						clearBuffer();
						break;
					case 'D':
						scanf(" %d %d", &idUser, &id);
						returnBook(loanBookFile, bookFile, idUser, id);
						clearBuffer();
						break;
					case 'P':
						scanf(" '%50[^']'", nameBook);
						searchBook(bookFile, nameBook);
						clearBuffer();
						break;
					case 'M':
						showBookFile(bookFile);
						clearBuffer();
						break;
					case 'L':
						showLoanBookFile(loanBookFile);
						clearBuffer();
						break;
					case 'S':
						clearBuffer();
						break;
					default:
						printf("\nComando inexistente.\n");
						clearBuffer();
						break;
				}
				printf("\nPressione qualquer letra para continuar...");
				char c = getch();
			} while(exiting != 'S');
		} else if(op != 3){
			printf("\nComando inexistente.\n");
			printf("\nPressione qualquer letra para continuar...");
			clearBuffer();
			//char c = getch();	
		}			
	} while(op != 3);
	
	printf("\nPrograma finalizado.");
	return 0;
}
