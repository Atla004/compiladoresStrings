#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isValidExpression(char* input);
int main() {
    char input[100];
    printf("Enter the expression: ");
    fgets(input, sizeof(input), stdin);

    // Remove the newline character from the input
    input[strcspn(input, "\n")] = '\0';

    if (isValidExpression(input)) {
        printf("Valid\n");

        // Generate the lexemes file
        FILE* file = fopen("C:/Users/andre/Documents/Visual Studio/Uru/C/text.txt", "w");
        if (file != NULL) {
            fprintf(file, "ABRIR\n");
            char* expression = strtok(input + 6, " ");
            while (expression != NULL) {
                fprintf(file, "%s\n", expression);
                expression = strtok(NULL, " ");
            }
            fprintf(file, "CERRAR\n");
            fclose(file);
        } else {
            printf("Failed to generate  file\n");
        }
    } else {
        printf("Invalid\n");
    }

    return 0;
}

int isValidExpression(char* input) {
    int len = strlen(input);
    int i = 0;
    int openCount = 0;
    int closeCount = 0;
    int operatorCount = 0;
    int valid = 1;

    // Check if the input starts with "ABRIR "
    if (strncmp(input, "<ABRIR> ", 8) != 0) {
        //no es valido
        valid = 0;
    }

    // Check if the input ends with " CERRAR"
    if (strncmp(input + len - 9, " <CERRAR>", 9) != 0) {
        //no es valido
        valid = 0;
    }

    char *invalidvariable = "+-*/^(){}[]<>=!&|~.,;: \t\n";

    // Check if the input contains a valid  expression
    char* expression = strtok(input + 8, "=");  
    for (int i=0; i < strlen(expression); i++)
    for(int j=0; j < strlen(invalidvariable); j++) 
    if  (strcpmr(expression+i, invalidvariable +j )==  0){
    valid=0;
    }

    expression = strtok(NULL, "<>")
  

    while (expression != NULL) {
        if (strcmp(expression, "<") == 0 || strcmp(expression, ">") == 0 || strcmp(expression, "==") == 0 || strcmp(expression, "!=") == 0 || strcmp(expression, "+") == 0 || strcmp(expression, "-") == 0) {
            operatorCount++;
        } else {
            if (atoi(expression) == 0 && strcmp(expression, "0") != 0) {
                valid = 0;
            }
        }
        expression = strtok(NULL, "<> ");
    }


    return valid;
}
