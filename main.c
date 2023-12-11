#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "user.h"
#include "book.h"

void printHeader(){
	system("cls");
	printf("====== SISTEMA DE GERENCIAMENTO DE BIBLIOTECA ======\n");
	printf("Feito por: Maike Mendes Silva\n\n");
	printf("---- COMANDOS ----\n\n");
}

int main() {
	
	FILE *userFile;
	FILE *bookFile;
	char op;
	
	do{	
		printHeader();
		printf("Menu Usuario ==> U\n");
		printf("Menu Livro ==> L\n");
		printf("Encerrar Programa ==> E\n\n");
		printf("Digite o comando: ");
		scanf(" %c", &op);
		if(op == 'U'){
			do{
				printHeader();
				printf("MENU USUARIO:\n");
				printf("Cadastrar Usuario ==> C 'Nome' 'CPF'\n");
				printf("Remover Usuario ==> R ID\n");
				printf("Pesquisar Usuario(s) ==> P 'Nome'\n");
				printf("Mostrar Usuario(s) ==> M\n");
				printf("Sair do Menu ==> S\n\n");
				printf("Digite o comando: ");
				
				int id;
				char name[MAX];
				char cpf[CPF_MAX];
				scanf(" %c", &op);
				switch(op){
					case 'C':
						scanf(" '%50[^']' '%14[^']'", name, cpf);
						insertUser(&userFile, name, cpf);
						break;
					case 'R':
						scanf(" %d", &id);
						removeUser(&userFile, id);
						break;
					case 'P':
						scanf(" '%50[^']'", name);
						searchUser(userFile, name);
						break;
					case 'M':
						showUserFile(userFile);
						break;
				}
				printf("\nPressione qualquer letra para continuar...");
				char c = getch();
			} while(op != 'S');
		} else if (op == 'L'){
			do{
				printHeader();
				printf("MENU LIVRO:\n");
				printf("Cadastrar Livro ==> C 'Nome Livro' 'Nome Autor' Ano 'ISBN' Copias\n");
				printf("Aumentar/Diminuir copias ==> A ID Copias\n");
				printf("Remover Livro ==> R ID\n");
				printf("Emprestar Livro ==> E Usuario_ID Livro_ID\n");
				printf("Devolver Livro ==> D Usuario_ID Livro_ID\n");
				printf("Pesquisar Livro(s) ==> P 'Nome'\n");
				printf("Mostrar Livro(s) no Acervo ==> M\n");
				printf("Listar Livro(s) Emprestados ==> L\n");
				printf("Sair do Menu ==> S\n\n");
				printf("Digite o comando: ");
				
				int id;
				char nameBook[MAX];
				char nameAuthor[MAX];
				int year;
				char isbn[ISBN_MAX];
				int copies;
				scanf(" %c", &op);
				switch(op){
					case 'C':
						scanf(" '%50[^']' '%50[^']' %d '%15[^']' %d", nameBook, nameAuthor, &year, isbn, &copies);
						insertBook(&bookFile, nameBook, nameAuthor, year, isbn, copies);
						break;
					case 'A':
						scanf(" %d %d", &id, &copies);
						addCopies(bookFile, id, copies);
						break;
					case 'R':
						scanf(" %d", &id);
						removeBook(&bookFile, id);
						break;
					case 'P':
						scanf(" '%50[^']'", nameBook);
						searchBook(bookFile, nameBook);
						break;
					case 'M':
						showBookFile(bookFile);
						break;
				}
				printf("\nPressione qualquer letra para continuar...");
				char c = getch();
			} while(op != 'S');
		}
			
	} while(op != 'E');
	
	printf("\nPrograma finalizado.");
	return 0;
}
