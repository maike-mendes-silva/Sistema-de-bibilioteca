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
	
	int bookCopies;
	int idBook;
	bookFile = fopen("books.txt", "r+");
	if(bookFile == NULL){
		printf("Erro na abertura do arquivo.\n");
		return;
	}
	int pos;
	int notFound = 1;
	while(fscanf(bookFile, "%d '%*[^']' '%*[^']' %*d '%*[^']' %d %*d\n", &idBook, &bookCopies) != EOF){
		if(idBook == id){
			notFound = 0;
			break;
		}
	}
	if(notFound){
		printf("Livro nao encontrado.\n");
		return;
	}
	fseek(bookFile, -4, SEEK_CUR);
	fprintf(bookFile, "%d", bookCopies + copies);
	fclose(bookFile);
	printf("Quantidade atualizada com sucesso.\n");	
	
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

#endif
