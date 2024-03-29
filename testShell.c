#include <stdio.h>
#include <stdlib.h>

char input_line[1000];
char params[100][100];

int valid_value(char* guess)
{
	int i;
	
	char* hex = "0x";
	for (i = 0; i < 2; i++) if (guess[i] != hex[i]) return 0;
	
	for (i = 2; i < strlen(guess); i++) {
		if ((guess[i] >= 'A' && guess[i] <= 'Z') || (guess[i] >= '0' && guess[i] <= '9')) continue;
		else return 0;
	}
	return 1;
}

int valid_address(char* guess)
{
	int num = 0;

	int i = 0;
	for (i = 0; i < strlen(guess); i++) {
		if (guess[i] >= '0' && guess[i] <= '9') {
			num = num * 10 + (guess[i] - '0');
		}
		else {
			return -1;
		}
	}
	return num;
}

void write(int address, char* value)
{
	char command[100];
	sprintf(command, "./ssd W %d %s", address, value);
	system(command);
}

void read(int address)
{
	char command[100];
	sprintf(command, "./ssd R %d", address);
	system(command);
	FILE * fp;

	char result[100];
	fp = fopen("./result.txt", "r");
	fscanf(fp, "%s", &result);
	printf("%s\n", result);
}

int main()
{
	while (1) {
		printf("SSD TEST SHELL>> ");
		gets(input_line);

		int argc = 1;
		int now_i = 0;
		int i = 0;
		for (i = 0; i < 1000; i++) {
			if (input_line[i] == ' ') {
				params[argc - 1][now_i] = '\0';
				argc += 1;
				now_i = 0;
			}
			else {
				params[argc - 1][now_i++] = input_line[i];
			}
			if (input_line[i] == '\0') break;
		}

		int error = 0;
		if (argc == 1) {
			if (strcmp("exit", params[0]) == 0) break;
			else if (strcmp("help", params[0]) == 0) {
				printf("this is help\n");
			}
			else if (strcmp("fullread", params[0]) == 0) {
				int lba;
				for (lba = 1; lba < 100; lba++) {
					printf("%d ", lba);
					read(lba);
				}
			}
			else {
				error = 1;
			}
		}
		else if (argc == 2) {
			if (strcmp("read", params[0]) == 0) {
				int num;
				if (strlen(params[1]) > 2) error = 1;
				else num = valid_address(params[1]);
				if (num == -1) error = 1;

				if (error == 0) read(num);
			}
			else if (strcmp("fullwrite", params[0]) == 0) {
				error = !valid_value(params[1]);

				if (error == 0) {
					int lba;
					for (lba = 1; lba < 100; lba++) {
						write(lba, params[1]);
					}
				}
			}
		}
		else if (argc == 3) {
			if (strcmp("write", params[0]) == 0) {
				int num;
				if (strlen(params[1]) > 2) error = 1;
				else num = valid_address(params[1]);
				if (num == -1) error = 1;

				error = !valid_value(params[2]);

				if (error == 0) write(num, params[2]);
			}
		}

		if (error) printf("INVALID COMMAND\n");
	}



	return 0;
}
