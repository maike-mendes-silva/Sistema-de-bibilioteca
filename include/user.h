#ifndef USER_H
#define USER_H
#define MAX 51
#define CPF_MAX 15

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int idUserFile;
char nameUserFile[MAX];
char cpfUserFile[MAX];

int getLastIdUser(FILE *userFile){
	
	idUserFile = 0;
	rewind(userFile);
	while(fscanf(userFile, "%d '%*[^']' '%*[^']'\n", &idUserFile) != EOF);
	return (idUserFile + 1);
	
}

int isRegisteredUser(FILE *userFile, char cpfUser[]){
	
	while(fscanf(userFile, "%*d '%*[^']' '%[^']'\n", cpfUserFile) != EOF){
		if(!strcmp(cpfUserFile, cpfUser))
			return 1;
	}
	return 0;
	
}

void insertUser(FILE *userFile, char nameUser[], char cpfUser[]){
	
	printf("\n");
	userFile = fopen("users.txt", "a+");
	if(userFile == NULL){
		printf("Erro na abertura do arquivo.\n");
		return;
	}
	if(isRegisteredUser(userFile, cpfUser)){
		printf("Usuario ja registrado.\n");
		fclose(userFile);
		return;
	}
	idUserFile = getLastIdUser(userFile);
	fprintf(userFile, "%d '%s' '%s'\n", idUserFile, nameUser, cpfUser);
	fclose(userFile);
	printf("Usuario adicionado com sucesso.\n");
	
}

void removeUser(FILE *userFile, int idUser){
	
	printf("\n");
	userFile = fopen("users.txt", "r+");
	if(userFile == NULL){
		printf("Erro na abertura do arquivo.\n");
		return;
	}
	if(fgetc(userFile) == EOF){
		printf("Nenhum usuario cadastrado.\n");
		fclose(userFile);
		return;	
	} 
	rewind(userFile);
	FILE *userFileTemp = fopen("usersTemp.txt", "w");
	if(userFileTemp == NULL){
		printf("Erro na criacao arquivo temporario.\n");
		fclose(userFile);
		return;
	}
	int notFound = 1;
	while(fscanf(userFile, "%d '%50[^']' '%50[^']'\n", &idUserFile, nameUserFile, cpfUserFile) != EOF){
		if(idUserFile != idUser)
			fprintf(userFileTemp, "%d '%s' '%s'\n", idUserFile, nameUserFile, cpfUserFile);
		else
			notFound = 0;
	}
	fclose(userFile);
	fclose(userFileTemp);
	if(notFound){
		printf("Usuario nao encontrado.\n");
		if(remove("usersTemp.txt") != 0)
			printf("Erro na remocao do arquivo.\n");
		return;	
	}
	if(remove("users.txt") != 0){
		printf("Erro na remocao do arquivo.\n");
		return;
	}
	if(rename("usersTemp.txt", "users.txt") != 0){
		printf("Erro na renomeacao do arquivo.\n");
		return;
	}
	printf("Usuario removido com sucesso.\n");
}

void searchUser(FILE *userFile, char nameUser[]){
	
	printf("\n");
	userFile = fopen("users.txt", "r");
	if(userFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	int notFound = 1;
	while(fscanf(userFile, "%d '%[^']' '%[^']'\n", &idUserFile, nameUserFile, cpfUserFile) != EOF){
		if(strstr(nameUserFile, nameUser) != NULL){
			printf("%d -> %s / %s\n", idUserFile, nameUserFile, cpfUserFile);
			notFound = 0;
		}
	}
	fclose(userFile);
	if(notFound)
		printf("Usuario nao encontrado.\n");
}

void showUserFile(FILE *userFile){
	
	printf("\n");
	userFile = fopen("users.txt", "a+");
	if(userFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	fseek(userFile, 0, SEEK_END);
	long fileSize = ftell(userFile);
	if(fileSize == 0){
		printf("Nenhum usuario cadastrado.\n");
		return;
	}
	fseek(userFile, 0, SEEK_SET);
	printf("USUARIOS CADASTRADOS:\n");
	while(fscanf(userFile, "%d '%[^']' '%[^']'\n", &idUserFile, nameUserFile, cpfUserFile) != EOF){
		printf("%d -> %s / %s\n", idUserFile, nameUserFile, cpfUserFile);
	}
	fclose(userFile);
	
}

#endif
