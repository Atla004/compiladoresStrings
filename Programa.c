
//<ABRIR> juan = 3 == 3 <CERRAR> valid
//<ABRIR> juan=3==3 <CERRAR> valid
//<ABRIR>juan=3==3<CERRAR> invalid
//<ABRIR>juan = 3 == 3<CERRAR> invalid
//<ABRIR> juan = 3 < 3 <CERRAR> valid
//<ABRIR> juan =3>3 <CERRAR> valid

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isValidExpression(char* input) {
    char* validStart = "<ABRIR> ";
    char* validEnd = " <CERRAR>";
    char* operators[] = {"<", ">", "==", "!="};
    char* variable= "abcdefghijklmnopqrstuvwxyz_";
    int valid;
    int count=0;

    // Check if the input starts with "ABRIR "
    if (strncmp(input, "<ABRIR> ", 8) != 0) {
        //no es valido
        return 0;
    }

    // Check if the input ends with " CERRAR"
    if (strncmp(input + strlen(input) - 9, " <CERRAR>", 9) != 0) {
        //no es valido
        return 0;
    }



    //check first number
    if (isdigit(input[count]) == 0)
    {
        printf("Invalid first number: %c \n",input[count-1]);
        return 0;

        for (int i = 8; i < strlen(input); i++)
        {  
            for (int j = 0; j < strlen(variable); j++)
            {
                if (input[i] == variable[j])
                {
                    printf("character: %c \n",variable[j]);
                    valid=1;
                    break;
                }
                valid=0;
            }
            count = input[i];
            if (valid==0 && input[i] != ' ' && input[i] != '=')
            {
                printf("Invalid variable character: %c \n",input[i]);
                return 0;
            }
            if (input[i] == ' ' || input[i] == '='){
                valid=1;
                count = i+1;
                break;
            }
        }
    }
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