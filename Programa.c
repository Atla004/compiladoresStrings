
//<ABRIR> juan = 3 == 3 <CERRAR> valid
//<ABRIR> juan=3==3 <CERRAR> valid
//<ABRIR>juan=3==3<CERRAR> invalid
//<ABRIR>juan = 3 == 3<CERRAR> invalid
//<ABRIR> juan = 3 < 3 <CERRAR> valid
//<ABRIR> juan =3>3 <CERRAR> valid

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isValidExpression(char* input) {
    char* validStart = "<ABRIR> ";
    char* validEnd = " <CERRAR>";
    char* operators[] = {"<", ">", "==", "!="};
    char* variable
    int i, j;
    int len =strlen(input);

    // Check if the input starts with "ABRIR "
    if (strncmp(input, "<ABRIR> ", 8) != 0) {
        //no es valido
        return 0;
    }

    // Check if the input ends with " CERRAR"
    if (strncmp(input + len - 9, " <CERRAR>", 9) != 0) {
        //no es valido
        return 0;
    }


    // Check relational operators
    for (i = 0; i < 4; i++) {
        char* opLocation = strstr(input, operators[i]);
        if (opLocation != NULL) {
            for (j = 0; j < 4; j++) {
                if (i != j && strstr(input, operators[j]) != NULL) {
                    return 0;
                }
            }
            // Check if there is exactly one '=' before the operator
            char* equalLocation = strchr(input + strlen(validStart), '=');
            if (equalLocation == NULL || equalLocation >= opLocation) {
                return 0;
            }
            // Check if there are numbers before and after the operator
            char* numberStart = equalLocation + 1;
            char* numberEnd = opLocation - 1;
            while (numberStart <= numberEnd) {
                if (*numberStart < '0' || *numberStart > '9') {
                    return 0;
                }
                numberStart++;
            }
            numberStart = opLocation + strlen(operators[i]);
            numberEnd = input + strlen(input) - strlen(validEnd) - 1;
            while (numberStart <= numberEnd) {
                if (*numberStart < '0' || *numberStart > '9') {
                    return 0;
                }
                numberStart++;
            }
            return 1;
        }
    }

    return 0;
}

void genfile(char* input) {
    FILE *file = fopen("C:\\Users\\YourUsername\\Desktop\\output.txt", "w");
    if (file != NULL) {
        fputs(input, file);
        fclose(file);
    } else {
        printf("Error opening file!\n");
    }
}

int main() {
    char input[100];
    printf("Enter the expression: ");
    fgets(input, sizeof(input), stdin);

    // Remove the newline character from the input
    input[strcspn(input, "\n")] = '\0';

    if (isValidExpression(input)) {
        printf("Valid\n");
        genfile(input);
    } else {
        printf("Invalid\n");
    }

    return 0;
}