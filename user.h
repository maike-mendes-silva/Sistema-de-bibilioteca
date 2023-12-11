#ifndef USER_H
#define USER_H
#define MAX 51
#define CPF_MAX 15

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getLastIdUser(FILE *userFile){
	
	int id = 0;
	rewind(userFile);
	while(fscanf(userFile, "%d '%*[^']' '%*[^']'\n", &id) != EOF);
	return (id + 1);
	
}

int isRegisteredUser(FILE *userFile, char cpf[]){
	
	char cpfUser[MAX];
	while(fscanf(userFile, "%*d '%*[^']' '%[^']'\n", cpfUser) != EOF){
		if(!strcmp(cpfUser, cpf))
			return 1;
	}
	return 0;
	
}

void insertUser(FILE **userFile, char name[], char cpf[]){
	
	printf("\n");
	*userFile = fopen("users.txt", "a+");
	if(*userFile == NULL){
		printf("Erro na abertura do arquivo.\n");
		return;
	}
	int id;
	if(isRegisteredUser(*userFile, cpf)){
		printf("Usuario ja registrado.\n");
		return;
	}
	id = getLastIdUser(*userFile);
	fprintf(*userFile, "%d '%s' '%s'\n", id, name, cpf);
	fclose(*userFile);
	printf("Usuario adicionado com sucesso.\n");
	
}

void removeUser(FILE **userFile, int id){
	
	printf("\n");
	*userFile = fopen("users.txt", "r+");
	if(*userFile == NULL){
		printf("Erro na abertura do arquivo.\n");
		return;
	}
	FILE *userFileTemp = fopen("usersTemp.txt", "w");
	if(userFileTemp == NULL){
		printf("Erro na criacao arquivo temporario.\n");
		return;
	}
	int idUser;
	char name[MAX];
	char cpf[CPF_MAX];
	if(feof(*userFile)){
		printf("Nenhum usuario cadastrado.\n");
		return;	
	} 
	int notFound = 1;
	while(fscanf(*userFile, "%d '%[^']' '%[^']'\n", &idUser, name, cpf) != EOF){
		if(idUser != id)
			fprintf(userFileTemp, "%d '%s' '%s'\n", idUser, name, cpf);
		else
			notFound = 0;
	}
	if(notFound){
		printf("Usuario nao encontrado.\n");
		return;	
	}
	fclose(*userFile);
	fclose(userFileTemp);
	
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

void searchUser(FILE *userFile, char name[]){
	
	printf("\n");
	userFile = fopen("users.txt", "r");
	if(userFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	int id;
	char nameUser[MAX];
	char cpf[CPF_MAX];
	int notFound = 1;
	while(fscanf(userFile, "%d '%[^']' '%[^']'\n", &id, nameUser, cpf) != EOF){
		if(strstr(nameUser, name) != NULL){
			printf("%d -> %s / %s\n", id, nameUser, cpf);
			notFound = 0;
		}
	}
	if(notFound)
		printf("Usuario nao encontrado.\n");
	fclose(userFile);
}

void showUserFile(FILE *userFile){
	
	printf("\n");
	userFile = fopen("users.txt", "r");
	if(userFile == NULL){
		printf("Falha no acesso ao arquivo.\n");
		return;
	}
	int id;
	char name[MAX];
	char cpf[CPF_MAX];
	printf("USUARIOS CADASTRADOS:\n");
	while(fscanf(userFile, "%d '%[^']' '%[^']'\n", &id, name, cpf) != EOF){
		printf("%d -> %s / %s\n", id, name, cpf);
	}
	fclose(userFile);
	
}

#endif
