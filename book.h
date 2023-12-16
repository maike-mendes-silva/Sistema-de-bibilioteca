#ifndef BOOK_H
#define BOOK_H
#define MAX 51
#define ISBN_MAX 15

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int idBookFile;
char nameBookFile[MAX];
char nameAuthorBookFile[MAX];
int yearBookFile;
char isbnBookFile[ISBN_MAX];
int copiesBookFile;
int availableCopiesBookFile;
int notFound;
char nameUserFile[MAX];
int idUserFile;

int getLastIdBook(FILE *bookFile){
	
	idBookFile = 0;
	rewind(bookFile);
	while(fscanf(bookFile, "%d '%*[^']' '%*[^']' %*d '%*[^']' %*d %*d\n", &idBookFile) != EOF);
	return (idBookFile + 1);
	
}

int isRegisteredBook(FILE *bookFile, char isbnBook[]){
	
	while(fscanf(bookFile, "%*d '%*[^']' '%*[^']' %*d '%[^']' %*d %*d\n", isbnBookFile) != EOF){
		if(!strcmp(isbnBook, isbnBookFile))
			return 1;
	}
	return 0;
	
}

void insertBook(FILE *bookFile, char nameBook[], char nameAuthorBook[], int yearBook, char isbnBook[], int copiesBook){
	
	printf("\n");
	bookFile = fopen("books.txt", "a+");
	if(bookFile == NULL){
		printf("Erro na abertura do arquivo.\n");
		return;
	}
	if(isRegisteredBook(bookFile, isbnBook)){
		printf("Livro ja registrado.\n");
		fclose(bookFile);
		return;
	}
	idBookFile = getLastIdBook(bookFile);
	fprintf(bookFile, "%d '%s' '%s' %d '%s' %d %d\n", idBookFile, nameBook, nameAuthorBook, yearBook, isbnBook, copiesBook, copiesBook);
	fclose(bookFile);
	printf("Livro adicionado com sucesso.\n");
	
}

void addCopies(FILE *bookFile, int idBook, int copiesBook){

	printf("\n");
	FILE *bookFileTemp = fopen("booksTemp.txt", "w");
	bookFile = fopen("books.txt", "r+");
	if(bookFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	if(bookFileTemp == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	notFound = 1;
	while(fscanf(bookFile, "%d '%50[^']' '%50[^']' %d '%15[^']' %d %d\n", &idBookFile, nameBookFile, nameAuthorBookFile, &yearBookFile, isbnBookFile, &copiesBookFile, &availableCopiesBookFile) != EOF){
		if(idBookFile != idBook)
			fprintf(bookFileTemp, "%d '%s' '%s' %d '%s' %d %d\n", idBookFile, nameBookFile, nameAuthorBookFile, yearBookFile, isbnBookFile, copiesBookFile, availableCopiesBookFile);
		else{
			notFound = 0;
			fprintf(bookFileTemp, "%d '%s' '%s' %d '%s' %d %d\n", idBookFile, nameBookFile, nameAuthorBookFile, yearBookFile, isbnBookFile, copiesBookFile + copiesBook, availableCopiesBookFile + copiesBook);
		}	
	}
	fclose(bookFile);
	fclose(bookFileTemp);
	if(notFound){
		printf("Livro nao encontrado.\n");
		return;
	}
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

int alterAvailableCopies(FILE **bookFile, int idBook, int copiesBook){

	FILE *bookFileTemp = fopen("booksTemp.txt", "w");
	if(bookFileTemp == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return 0;
	}
	rewind(*bookFile);
	notFound = 1;
	while(fscanf(*bookFile, "%d '%50[^']' '%50[^']' %d '%15[^']' %d %d\n", &idBookFile, nameBookFile, nameAuthorBookFile, &yearBookFile, isbnBookFile, &copiesBookFile, &availableCopiesBookFile) != EOF){
		if(idBookFile != idBook)
			fprintf(bookFileTemp, "%d '%s' '%s' %d '%s' %d %d\n", idBookFile, nameBookFile, nameAuthorBookFile, yearBookFile, isbnBookFile, copiesBookFile, availableCopiesBookFile);
		else{
			notFound = 0;
			fprintf(bookFileTemp, "%d '%s' '%s' %d '%s' %d %d\n", idBookFile, nameBookFile, nameAuthorBookFile, yearBookFile, isbnBookFile, copiesBookFile, availableCopiesBookFile - copiesBook);
		}	
	}
	fclose(*bookFile);
	fclose(bookFileTemp);
	if(notFound){
		printf("Livro nao encontrado.\n");
		return 0;
	}
	if(remove("books.txt") != 0){
		printf("Erro na remocao do arquivo.\n");
		return 0;
	}
	
	if(rename("booksTemp.txt", "books.txt") != 0){
		printf("Erro na renomeacao do arquivo.\n");
		return 0;
	}
	
	return 1;
}

void removeBook(FILE *bookFile, int idBook){
	
	printf("\n");
	bookFile = fopen("books.txt", "r+");
	if(bookFile == NULL){
		printf("Erro na abertura do arquivo.\n");
		return;
	}
	FILE *bookFileTemp = fopen("booksTemp.txt", "w");
	if(bookFileTemp == NULL){
		printf("Erro na criacao arquivo temporario.\n");
		return;
	}
	if(fgetc(bookFile) == EOF){
		printf("Nenhum livro cadastrado.\n");
		fclose(bookFile);
		return;	
	} 
	rewind(bookFile);
	notFound = 1;
	while(fscanf(bookFile, "%d '%50[^']' '%50[^']' %d '%15[^']' %d %d\n", &idBookFile, nameBookFile, nameAuthorBookFile, &yearBookFile, isbnBookFile, &copiesBookFile, &availableCopiesBookFile) != EOF){
		if(idBookFile != idBook)
			fprintf(bookFileTemp, "%d '%s' '%s' %d '%s' %d %d\n", idBookFile, nameBookFile, nameAuthorBookFile, yearBookFile, isbnBookFile, copiesBookFile, availableCopiesBookFile);
		else
			notFound = 0;
	}
	fclose(bookFile);
	fclose(bookFileTemp);
	if(notFound){
		printf("Livro nao encontrado.\n");
		if(remove("booksTemp.txt") != 0)
			printf("Erro na remocao do arquivo.\n");
		return;	
	}
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
	
	printf("\n");
	bookFile = fopen("books.txt", "r");
	if(bookFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	notFound = 1;
	while(fscanf(bookFile, "%d '%50[^']' '%*50[^']' %*d '%*15[^']' %*d %d\n", &idBookFile, nameBookFile, &availableCopiesBookFile) != EOF){
		if(idBook == idBookFile){
			notFound = 0;
			break;
		}
	}
	if(notFound){
		printf("Livro nao encontrado.\n");
		fclose(bookFile);
		return;
	}
	if(availableCopiesBookFile == 0){
		printf("Livro indisponivel para emprestimo.\n");
		fclose(bookFile);
		return;
	}
	if(!alterAvailableCopies(&bookFile, idBook, 1))
		return;
	
	userFile = fopen("users.txt", "r");
	if(userFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	notFound = 1;
	while(fscanf(userFile, "%d '%[^']' '%*[^']'\n", &idUserFile, nameUserFile) != EOF){
		if(idUser == idUserFile){
			notFound = 0;
			break;
		}
	}
	fclose(userFile);
	if(notFound){
		printf("Usuario nao encontrado.\n");
		return;
	}
	
	loanBookFile = fopen("loanBooks.txt", "a+");
	if(loanBookFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	fprintf(loanBookFile, "%d '%s' %d '%s'\n", idBook, nameBookFile, idUser, nameUserFile);
	printf("Emprestimo realizado com sucesso.\n");
	fclose(loanBookFile);
	
}

void returnBook(FILE *loanBookFile, FILE *bookFile, int idUser, int idBook){
	
	printf("\n");
	bookFile = fopen("books.txt", "r+");
	loanBookFile = fopen("loanBooks.txt", "r+");
	FILE *loanBookFileTemp = fopen("loanBooksTemp.txt", "w");
	if(bookFile == NULL){
		printf("Erro no acesso ao arquivo.\n");
		return;
	}
	if(loanBookFile == NULL){
		printf("Erro no acesso ao arquivo.\n");
		fclose(bookFile);
		return;
	}
	if(loanBookFileTemp == NULL){
		printf("Erro no acesso ao arquivo.\n");
		fclose(bookFile);
		fclose(loanBookFile);
		return;
	}
	if(fgetc(loanBookFile) == EOF){
		printf("Nenhum livro emprestado.\n");
		fclose(bookFile);
		fclose(loanBookFile);
		fclose(loanBookFileTemp);
		if(remove("loanBooksTemp.txt") != 0)
			printf("Erro na remocao do arquivo.\n");
		return;	
	} 
	rewind(loanBookFile);
	notFound = 1;
	
	while(fscanf(loanBookFile, "%d '%50[^']' %d '%50[^']'\n", &idBookFile, nameBookFile, &idUserFile, nameUserFile) != EOF){
		if(idBookFile != idBook || idUser != idUserFile)
			fprintf(loanBookFileTemp, "%d '%s' %d '%s'\n", idBookFile, nameBookFile, idUserFile, nameUserFile);	
		else 
			notFound = 0;
	}
	if(notFound){
		printf("Registro nao encontrado.\n");
		fclose(loanBookFileTemp);
		fclose(loanBookFile);
		fclose(bookFile);
		if(remove("loanBooksTemp.txt") != 0)
			printf("Erro na remocao do arquivo.\n");
		return;	
	}
	
	if(!alterAvailableCopies(&bookFile, idBook, -1))
		return;
		
	fclose(loanBookFileTemp);
	fclose(loanBookFile);
	if(remove("loanBooks.txt") != 0){
		printf("Erro na remocao do arquivo.\n");
		return;
	}
	
	if(rename("loanBooksTemp.txt", "loanBooks.txt") != 0){
		printf("Erro na renomeacao do arquivo.\n");
		return;
	}
	
	printf("Livro devolvido com sucesso.\n");
	
}

void searchBook(FILE *bookFile, char nameBook[]){
	
	printf("\n");
	bookFile = fopen("books.txt", "r");
	if(bookFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	notFound = 1;
	while(fscanf(bookFile, "%d '%50[^']' '%50[^']' %d '%15[^']' %d %d\n", &idBookFile, nameBookFile, nameAuthorBookFile, &yearBookFile, isbnBookFile, &copiesBookFile, &availableCopiesBookFile) != EOF){
		if(strstr(nameBookFile, nameBook) != NULL){
			printf("%d -> %s\n", idBookFile, nameBookFile);
			printf("Autor: %s\n", nameAuthorBookFile);
			printf("Ano de Lancamento: %d\n", yearBookFile);
			printf("ISBN: %s\n", isbnBookFile);
			printf("Copias totais: %d\n", copiesBookFile);
			printf("Copias disponiveis: %d\n\n", availableCopiesBookFile);	
			notFound = 0;
		}
	}
	fclose(bookFile);
	if(notFound)
		printf("Livro nao encontrado.\n");
}

void showBookFile(FILE *bookFile){
	
	printf("\n");
	bookFile = fopen("books.txt", "r");
	if(bookFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	if(fgetc(bookFile) == EOF){
		printf("Nenhum livro cadastrado.\n");
		fclose(bookFile);
		return;	
	} 
	rewind(bookFile);
	printf("LIVROS CADASTRADOS:\n");
	while(fscanf(bookFile, "%d '%50[^']' '%50[^']' %d '%15[^']' %d %d\n", &idBookFile, nameBookFile, nameAuthorBookFile, &yearBookFile, isbnBookFile, &copiesBookFile, &availableCopiesBookFile) != EOF){
		printf("\n%d -> %s\n", idBookFile, nameBookFile);
		printf("Autor: %s\n", nameAuthorBookFile);
		printf("Ano de Lancamento: %d\n", yearBookFile);
		printf("ISBN: %s\n", isbnBookFile);
		printf("Copias totais: %d\n", copiesBookFile);
		printf("Copias disponiveis: %d\n\n", availableCopiesBookFile);	
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
	if(fgetc(loanBookFile) == EOF){
		printf("Nenhum livro emprestado.\n");
		fclose(loanBookFile);
		return;	
	} 
	rewind(loanBookFile);
	printf("LIVROS EMPRESTADOS:\n");
	while(fscanf(loanBookFile, "%d '%50[^']' %d '%50[^']'\n", &idBookFile, nameBookFile, &idUserFile, nameUserFile) != EOF){
		printf("Usuario: %d -> %s\n", idUserFile, nameUserFile);
		printf("Livro: %d -> %s\n", idBookFile, nameBookFile);
		printf("\n");
	}
	fclose(loanBookFile);
	
}

#endif
