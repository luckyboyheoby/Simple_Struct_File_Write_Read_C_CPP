#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
	char name[50];
	int age;
};

User list[100];

void inputUser(User list[], int &n);
void printUser(User list[], int n);
int writeFileList(char *fileName, User list[], int n);
int readFileList(char *fileName, User list[], int &n);
void removeNewLine(char str[]);


int main() {
	int choice = 0;
	int n = 0; //array length
	char fileName[] = "data.bin"; //write read->binary
	
	do {
		printf("\n1. Input user");
		printf("\n2. Print user");
		printf("\n3. Write list user to file");
		printf("\n4. Read list user from file");
		printf("\nChoice: ");
		
		scanf("%d", &choice);
		
		switch(choice) {
			case 1:
				inputUser(list, n);
				break;
			case 2:
				printUser(list, n);
				break;
			case 3:
				if(writeFileList(fileName, list, n)) {
					printf("\n\tFile write successfully!");
				} else {
					printf("\n\tFailed to write file!");
				}
				break;
			case 4:
				if(readFileList(fileName, list, n)) {
					printf("\n\tFile read successfully!");
				} else {
					printf("\n\tFailed to read file!");
				}
				break;
			}
				
	} while(choice);
	
	return 0;
}

void inputUser(User list[], int &n) {
	printf("Name: ");
	fflush(stdin);
	fgets(list[n].name, sizeof(list->name), stdin);
	removeNewLine(list[n].name);
	
	printf("age: ");
	scanf("%d", &list[n].age);
	
	n++;
}
int writeFileList(char *fileName, User list[], int n) {
	FILE *f = fopen(fileName, "wb");
	
	if(!f) {
		printf("\n\tFailed to read file!");
		return 0; // failed
	}
	for(int i = 0; i < n; i++) {
		fwrite(&list[i], sizeof(User), 1, f);
	}
	
	fclose(f);
	
	return 1; //success
}

int readFileList(char *fileName, User list[], int &n) {
	n = 0;
	FILE *f = fopen(fileName, "rb");
	if(!f) {
		printf("\n\tFailed to read file!");
		return 0; //failed
	}
	
	while(!feof(f)) {
		fread(&list[n], sizeof(User), 1, f);
		n++;
	}
	
	n--;
	fclose(f);
	return 1;
}

void printUser(User list[], int n) {
	for(int i = 0; i < n; i++) {
		printf("Name: %s\n", list[i].name);
		printf("age: %d\n", list[i].age);
	}
}
void removeNewLine(char str[]) {
	size_t len = strlen(str);

	if(str[len-1]=='\n') {
		str[len-1]='\0';
	}
}

