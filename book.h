#ifndef BOOK_H
#define BOOK_H
#define MAX 51
#define ISBN_MAX 15

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getLastIdBook(FILE *bookFile){
	
	int id = 0;
	rewind(bookFile);
	while(fscanf(bookFile, "%d '%*[^']' '%*[^']' %*d '%*[^']' %*d %*d\n", &id) != EOF);
	return (id + 1);
	
}

int isRegisteredBook(FILE *bookFile, char isbn[]){
	
	char isbnBook[ISBN_MAX];
	while(fscanf(bookFile, "%*d '%*[^']' '%*[^']' %*d '%[^']' %*d %*d\n", isbnBook) != EOF){
		if(!strcmp(isbn, isbnBook))
			return 1;
	}
	return 0;
	
}

void insertBook(FILE **bookFile, char nameBook[], char nameAuthor[], int year, char isbn[], int copies){
	
	printf("\n");
	*bookFile = fopen("books.txt", "a+");
	if(*bookFile == NULL){
		printf("Erro na abertura do arquivo.\n");
		return;
	}
	if(isRegisteredBook(*bookFile, isbn)){
		printf("Livro ja registrado.\n");
		return;
	}
	int id;
	id = getLastIdBook(*bookFile);
	fprintf(*bookFile, "%d '%s' '%s' %d '%s' %d %d\n", id, nameBook, nameAuthor, year, isbn, copies, copies);
	fclose(*bookFile);
	printf("Livro adicionado com sucesso.\n");
	
}

void addCopies(FILE *bookFile, int id, int copies){


	printf("\n");
	FILE *bookFileTemp = fopen("booksTemp.txt", "w");
	bookFile = fopen("books.txt", "r+");
	if(bookFileTemp == NULL || bookFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}

	int idBook;
	char nameBook[MAX];
	char nameAuthor[MAX];
	int year;
	char isbn[ISBN_MAX];
	int bookCopies;
	int availableCopies;
	int notFound = 1;
	while(fscanf(bookFile, "%d '%50[^']' '%50[^']' %d '%15[^']' %d %d\n", &idBook, nameBook, nameAuthor, &year, isbn, &bookCopies, &availableCopies) != EOF){
		if(idBook != id)
			fprintf(bookFileTemp, "%d '%s' '%s' %d '%s' %d %d\n", idBook, nameBook, nameAuthor, year, isbn, bookCopies, availableCopies);
		else{
			notFound = 0;
			fprintf(bookFileTemp, "%d '%s' '%s' %d '%s' %d %d\n", idBook, nameBook, nameAuthor, year, isbn, bookCopies + copies, availableCopies + copies);
		}	
	}
	
	if(notFound){
		printf("Livro nao encontrado.\n");
		return;
	}
	
	fclose(bookFile);
	fclose(bookFileTemp);
	
	if(remove("books.txt") != 0){
		printf("Erro na remocao do arquivo.\n");
		return;
	}
	
	if(rename("booksTemp.txt", "books.txt") != 0){
		printf("Erro na renomeacao do arquivo.\n");
		return;
	}
	
	printf("Quantidade atualizada com sucesso.\n");	
	
}

void alterAvailableCopies(FILE **bookFile, int id, int copies){

	printf("\n");
	FILE *bookFileTemp = fopen("booksTemp.txt", "w");
	if(bookFileTemp == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	rewind(*bookFile);

	int idBook;
	char nameBook[MAX];
	char nameAuthor[MAX];
	int year;
	char isbn[ISBN_MAX];
	int bookCopies;
	int availableCopies;
	int notFound = 1;
	while(fscanf(*bookFile, "%d '%50[^']' '%50[^']' %d '%15[^']' %d %d\n", &idBook, nameBook, nameAuthor, &year, isbn, &bookCopies, &availableCopies) != EOF){
		if(idBook != id)
			fprintf(bookFileTemp, "%d '%s' '%s' %d '%s' %d %d\n", idBook, nameBook, nameAuthor, year, isbn, bookCopies, availableCopies);
		else{
			notFound = 0;
			fprintf(bookFileTemp, "%d '%s' '%s' %d '%s' %d %d\n", idBook, nameBook, nameAuthor, year, isbn, bookCopies, availableCopies - copies);
		}	
	}
	
	if(notFound){
		printf("Livro nao encontrado.\n");
		return;
	}
	
	fclose(*bookFile);
	fclose(bookFileTemp);
	
	if(remove("books.txt") != 0){
		printf("Erro na remocao do arquivo.\n");
		return;
	}
	
	if(rename("booksTemp.txt", "books.txt") != 0){
		printf("Erro na renomeacao do arquivo.\n");
		return;
	}
	
}

void removeBook(FILE **bookFile, int id){
	
	printf("\n");
	*bookFile = fopen("books.txt", "r+");
	if(*bookFile == NULL){
		printf("Erro na abertura do arquivo.\n");
		return;
	}
	FILE *bookFileTemp = fopen("booksTemp.txt", "w");
	if(bookFileTemp == NULL){
		printf("Erro na criacao arquivo temporario.\n");
		return;
	}
	if(feof(*bookFile)){
		printf("Nenhum livro cadastrado.\n");
		return;	
	} 
	int idBook;
	char nameBook[MAX];
	char nameAuthor[MAX];
	int year;
	char isbn[ISBN_MAX];
	int copies;
	int availableCopies;

	int notFound = 1;
	while(fscanf(*bookFile, "%d '%50[^']' '%50[^']' %d '%15[^']' %d %d\n", &idBook, nameBook, nameAuthor, &year, isbn, &copies, &availableCopies) != EOF){
		if(idBook != id)
			fprintf(bookFileTemp, "%d '%s' '%s' %d '%s' %d %d\n", idBook, nameBook, nameAuthor, year, isbn, copies, availableCopies);
		else
			notFound = 0;
	}
	if(notFound){
		printf("Livro nao encontrado.\n");
		return;	
	}
	fclose(*bookFile);
	fclose(bookFileTemp);
	
	if(remove("books.txt") != 0){
		printf("Erro na remocao do arquivo.\n");
		return;
	}
	
	if(rename("booksTemp.txt", "books.txt") != 0){
		printf("Erro na renomeacao do arquivo.\n");
		return;
	}
	
	printf("Livro removido com sucesso.\n");
}

void loanBook(FILE *bookFile, FILE *userFile, FILE *loanBookFile, int idUser, int idBook){
	
	bookFile = fopen("books.txt", "r");
	if(bookFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	int idBookFile;
	char nameBook[MAX];
	int availableCopies;
	int notFound = 1;
	while(fscanf(bookFile, "%d '%50[^']' '%*50[^']' %*d '%*15[^']' %*d %d\n", &idBookFile, nameBook, &availableCopies) != EOF){
		if(idBook == idBookFile){
			notFound = 0;
			break;
		}
	}
	if(notFound){
		printf("Livro nao encontrado.\n");
		return;
	}
	if(availableCopies == 0){
		printf("Livro indisponivel para emprestimo.\n");
		return;
	}
	alterAvailableCopies(&bookFile, idBook, 1);
	
	userFile = fopen("users.txt", "r");
	if(userFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	int idUserFile;
	char nameUser[MAX];
	notFound = 1;
	while(fscanf(userFile, "%d '%[^']' '%*[^']'\n", &idUserFile, nameUser) != EOF){
		if(idUser == idUserFile){
			notFound = 0;
			break;
		}
	}
	if(notFound){
		printf("Usuario nao encontrado.\n");
		return;
	}
	
	loanBookFile = fopen("loanbooks.txt", "a+");
	if(loanBookFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	fprintf(loanBookFile, "%d '%s' %d '%s'\n", idBook, nameBook, idUser, nameUser);
	printf("Emprestimo realizado com sucesso.\n");
	
	fclose(userFile);
	fclose(bookFile);
	fclose(loanBookFile);
	
}

void returnBook(FILE *loanBookFile, FILE *bookFile, int idUser, int id){
	
	bookFile = fopen("books.txt", "r+");
	if(bookFile == NULL){
		printf("Erro na abertura do arquivo.\n");
		return;
	}
	loanBookFile = fopen("loanbooks.txt", "r+");
	if(loanBookFile == NULL){
		printf("Erro na abertura do arquivo.\n");
		return;
	}
	FILE *loanBookFileTemp = fopen("loanbooksTemp.txt", "w");
	if(loanBookFileTemp == NULL){
		printf("Erro na criacao arquivo temporario.\n");
		return;
	}
	if(feof(loanBookFile)){
		printf("Nenhum livro cadastrado.\n");
		return;	
	} 
	int idBook;
	char nameBook[MAX];
	int idUserFile;
	char nameUser[MAX];
	
	int notFound = 1;
	while(fscanf(loanBookFile, "%d '%50[^']' %d '%50[^']'\n", &idBook, nameBook, &idUserFile, nameUser) != EOF){
		if(idBook != id && idUser != idUserFile)
			fprintf(loanBookFileTemp, "%d '%50[^']' %d '%50[^']'\n", idBook, nameBook, &idUserFile, nameUser);
		else
			notFound = 0;
	}
	if(notFound){
		printf("Registro nao encontrado.\n");
		return;	
	}
	alterAvailableCopies(&bookFile, idBook, -1);
	
	fclose(loanBookFileTemp);
	fclose(loanBookFile);
	
	if(remove("loanbooks.txt") != 0){
		printf("Erro na remocao do arquivo.\n");
		return;
	}
	
	if(rename("loanbooksTemp.txt", "loanbooks.txt") != 0){
		printf("Erro na renomeacao do arquivo.\n");
		return;
	}
	
	printf("Livro devolvido com sucesso.\n");
	
}

void searchBook(FILE *bookFile, char name[]){
	
	printf("\n");
	bookFile = fopen("books.txt", "r");
	if(bookFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	int idBook;
	char nameBook[MAX];
	char nameAuthor[MAX];
	int year;
	char isbn[ISBN_MAX];
	int copies;
	int availableCopies;
	int notFound = 1;
	while(fscanf(bookFile, "%d '%50[^']' '%50[^']' %d '%15[^']' %d %d\n", &idBook, nameBook, nameAuthor, &year, isbn, &copies, &availableCopies) != EOF){
		if(strstr(nameBook, name) != NULL){
			printf("%d -> %s\n", idBook, nameBook);
			printf("Autor: %s\n", nameAuthor);
			printf("Ano de Lancamento: %d\n", year);
			printf("ISBN: %s\n", isbn);
			printf("Copias totais: %d\n", copies);
			printf("Copias disponiveis: %d\n\n", availableCopies);	
			notFound = 0;
		}
	}
	if(notFound)
		printf("Livro nao encontrado.\n");
	fclose(bookFile);
}

void showBookFile(FILE *bookFile){
	
	printf("\n");
	bookFile = fopen("books.txt", "r");
	if(bookFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	int id;
	char nameBook[MAX];
	char nameAuthor[MAX];
	int year;
	char isbn[ISBN_MAX];
	int copies;
	int availableCopies;
	printf("LIVROS CADASTRADOS:\n");
	while(fscanf(bookFile, "%d '%50[^']' '%50[^']' %d '%15[^']' %d %d\n", &id, nameBook, nameAuthor, &year, isbn, &copies, &availableCopies) != EOF){
		printf("\n%d -> %s\n", id, nameBook);
		printf("Autor: %s\n", nameAuthor);
		printf("Ano de Lancamento: %d\n", year);
		printf("ISBN: %s\n", isbn);
		printf("Copias totais: %d\n", copies);
		printf("Copias disponiveis: %d\n\n", availableCopies);	
	}
	fclose(bookFile);
	
}

void showLoanBookFile(FILE *loanBookFile){
	
	printf("\n");
	loanBookFile = fopen("loanbooks.txt", "r");
	if(loanBookFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	int idBook;
	char nameBook[MAX];
	int idUser;
	char nameUser[MAX];
	printf("LIVROS EMPRESTADOS:\n");
	while(fscanf(loanBookFile, "%d '%50[^']' %d '%50[^']'\n", &idBook, nameBook, &idUser, nameUser) != EOF){
		printf("Usuario: %d -> %s\n", idUser, nameUser);
		printf("Livro: %d -> %s\n", idBook, nameBook);
		printf("\n");
	}
	fclose(loanBookFile);
	
}

#endif
