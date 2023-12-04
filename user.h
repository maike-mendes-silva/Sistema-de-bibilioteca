#ifndef USER_H
#define USER_H
#define MAX 51

#include <string.h>
#include <stdlib.h>

typedef struct user{
	int id;
	char name[MAX];
	char cpf[15];
	struct user *next;
} User;

int getLastIdUser(User *list){
	
	for(; list->next != NULL; list = list->next);
	return (list->id + 1);
	
}

void insertUser(User **list, char name[], char cpf[]){
	
	printf("\n");
	User *newUser = (User *) malloc(sizeof(User));
	if(newUser == NULL){
		printf("Erro ao cadastrar usuario.\n");
		printf("Falha na alocacao de memoria.\n");
		return;
	}
	if(*list == NULL)
		newUser->id = 1;
	else{
		int id = getLastIdUser(*list);
		newUser->id = id;
	}
	strcpy(newUser->name, name);
	strcpy(newUser->cpf, cpf);
	newUser->next = *list;
	*list = newUser;
	printf("Usuario adicionado com sucesso.\n");
	
}

void removeUser(User **list, int id){
	
	printf("\n");
	if(*list == NULL){
		printf("Nenhum usuario cadastrado.\n");
		return;
	} else{
		User *p = NULL;
		User *q = *list;
		while(q != NULL && q->id != id){
			p = q;
			q = q->next;	
		}
		if(p == NULL){
			*list = q->next;
			free(q);
		} else{
			if(q != NULL){
				p->next = q->next;
				free(q);
			} else{
				printf("Usuario nao encontrado.\n");
			}
		}
	}
	
	printf("Usuario removido com sucesso!\n");
	
}

User *searchUser(User *list, char name[]){
	User *user = list;
	while(user != NULL){
		if(strstr(user->name, name) != NULL){
			printf("Usuario encontrado.\n");
			return user;
		}
		user = user->next;
	}
	printf("Usuario nao encontrado.\n");
	return NULL;
}

void showUserList(User *list){
	
	printf("\n");
	if(list == NULL){
		printf("Lista vazia.\n");
		return;
	} else{
		printf("USUARIOS CADASTRADOS:\n");
		for(; list != NULL; list = list->next)
			printf("%d %s %s\n", list->id, list->name, list->cpf);
	}
}

#endif
