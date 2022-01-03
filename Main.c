#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 64

int calculator(char command[], char result[], int size);

int main(int argc, char *argv[])
{
	char expr[MAX_LEN] = {0};
	int count = 0;

	while (1)
	{
		// Program prompt
		printf("Calc >>> ");
		// Necessary for prompt
		
		char command[MAX_LEN];
		char result[MAX_LEN];
		int i, j, len;
		
		fgets(command, sizeof(command), stdin);
		
		if(strcmp(command, "exit\n") == 0) {
			printf("Exiting\n");
			break;
		}
		
		else if(strcmp(command, "hist\n") == 0) {
			if(count == 0) {
				printf("\n");
			}
			else {
				printf("%s", expr);
			}
		}
		
		else {
			len = sizeof(command);
			j = calculator(command, result, len);
			
			if(j == 1) {
				count += 1;
				strncat(expr, command, sizeof(command));
				strncat(expr, "\n", 1);
				if(count > 10) {
					char* p = expr;
					p += strcspn(expr, "\n") + 1;
					strcpy(expr, p);
				}
			}
		}
		
		fflush(stdout);
	}
	
	return 0;
}

int calculator(char command[], char result[], int size) {
	
	int i;
	int op_count = 0;
	int cal = 0;
	int res = 0;
	char operator = 'o';
	
	for(i = 0 ; i < size ; i++) {
		
		if(strstr(command, "++") || strstr(command, "+-") || strstr(command, "-+") || strstr(command, "--") != 0) {
			printf("ERROR: Invalid Syntax! Try Again.\n");
			break;
		}
		
		if(command[0] == '+' || command[0] == '-' || command[0] == '\n'){
			printf("ERROR: Invalid Syntax! Try Again.\n");
			break;
		}
		
		if(op_count >= 10) {
			printf("ERROR: Invalid Syntax! Try Again.\n");
			break;
		}
			
		if(command[i] >= '0' && command[i] <= '9') {
			if(operator == '-') {
				cal = - 10 * cal + (command[i] - '0');
				if(cal >= 0) {
					cal = -cal;
				}
			}
			else{
				cal = 10 * cal + (command[i] - '0');
			}	
		}
			
		else if(command[i] == '+') {
			operator = '+';
			op_count += 1;
			res += cal;
			cal = 0;	
		}
			
		else if(command[i] == '-') {
			operator = '-';
			op_count += 1;
			res += cal;
			cal = 0;	
		}
			
		else if(command[i] == '\n') {
			if (command[i - 1] == '+' || command[i - 1] == '-') {
				printf("ERROR: Invalid Syntax! Try Again.\n");
				break;
			}
			if (operator == 'o') {
				res = cal;
			}
			else {
				res = res + cal;
			}	
			command[i] = '=';
			printf("=%d\n", res);
			sprintf(result, "%d", res);
			strncat(command, result, sizeof(result));
			return 1;
			}
			
		else {
			printf("ERROR: Invalid Syntax! Try Again.\n");
			break;
		}
	}
}