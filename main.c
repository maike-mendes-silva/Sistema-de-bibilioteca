#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "user.h"

int main(int argc, char *argv[]) {
	
	User *userList = NULL;
	char op;
	
	do{	
		system("cls");
		printf("====== SISTEMA DE GERENCIAMENTO DE BIBLIOTECA ======\n");
		printf("Feito por: Maike Mendes Silva\n\n");
		printf("---- COMANDOS ----\n\n");
		printf("MENU USUARIO:\n");
		printf("Cadastrar Usuario ==> C {'Nome'} {'CPF'}\n");
		printf("Remover Usuario ==> R {'ID'}\n");
		printf("Pesquisar Usuario(s) ==> P {'Nome'}\n");
		printf("Mostrar Usuario(s) ==> M\n\n");
		printf("Digite o comando: ");
		int id;
		char name[MAX];
		char cpf[15];
		scanf(" %c", &op);
		switch(op){
			case 'C':
				scanf(" '%50[^']' '%14[^']'", name, cpf);
				insertUser(&userList, name, cpf);
				break;
			case 'R':
				scanf(" %d", &id);
				removeUser(&userList, id);
				break;
			case 'P':
				scanf(" '%50[^']'", name);
				User *user = searchUser(userList, name);
				if(user != NULL)
					printf("%d %s %s\n", user->id, user->name, user->cpf);
				break;
			case 'M':
				showUserList(userList);
				break;
		}
		printf("\nPressione qualquer letra para continuar...");
		char c = getch();
	} while(op != 'S');
	
}
