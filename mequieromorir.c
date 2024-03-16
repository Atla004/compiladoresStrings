
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

// Tu código aquí


int isValidExpression(char* input);

void saltarespacios(char* input, int* count);

void genfile(char* input);


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

int isValidExpression(char* input) {
    char* operatorscharacter[] = {"<", ">", "==", "!="};
    char* variablecharacter= "abcdefghijklmnopqrstuvwxyz_";
    char* numbercharacter= "0123456789";
    char* variable;
    char* number1;
    char* number2;
    char* character;
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


    //check variable

    for (count = 8; count < strlen(input); count++){  
        for (int j = 0; j < strlen(variablecharacter); j++){
            if (input[count] == variablecharacter[j]){
                valid=1;
                break;
            }
            valid=0;
        }
        //encontro caracter valido si salio por break
        
        // si no es valido y el caracter no es espacio o igual retorna el error
        if (valid==0 && input[count] != ' ' && input[count] != '='){
            printf("Invalid variable character: %c \n",input[count]);
            return 0;
        }
        //si es espacio o igual, es valido y se sale del ciclo
        if (input[count] == ' ' || input[count] == '='){
            valid=1;
            break;
        }
    }

    saltarespacios(input, &count);

    //chekc if the next character is an equal sign

    if (input[count] == '='){
        count++;
    }else{
        printf("Invalid character: %c \n",input[count]);
        return 0;
    }

    saltarespacios(input, &count);
    //check first number


    for (count ; count < strlen(input); count++){  
        for (int j = 0; j < strlen(numbercharacter); j++){
            if (input[count] == numbercharacter[j]){
                
                valid=1;
                break;
            }
            valid=0;
        }
        //encontro caracter valido si salio por break
        if (valid==0 ){
            saltarespacios(input, &count);

int a;
a= (strncmp(input + count, operatorscharacter[2], 2));
printf("a: %d\n",a);
  
            if (strncmp(input + count, operatorscharacter[0], 1) == 0) {
                //es ese operador y es valido >
                printf("entro\n");
                count++;
                valid=1;
                break;

            }else if (strncmp(input + count, operatorscharacter[1], 1) == 0) {
                //es ese operador y es valido <
                count++;
                valid=1;
                break;
            }else if (strncmp(input + count, operatorscharacter[2], 2) == 0) {
                //es ese operador y es valido ==
                count+=2;

                valid=1;
                break;
            }else if (strncmp(input + count, operatorscharacter[3], 2) == 0) {
                //es ese operador y es valido !=
                count+=2;
                valid=1;
                break;
            }else{
                printf("Invalid number character: %c \n",input[count]);
                return 0;
            }
        }

    }
    saltarespacios(input, &count);

    //checks second number
    for (count ; count < strlen(input); count++){  
        for (int j = 0; j < strlen(numbercharacter); j++){
            if (input[count] == numbercharacter[j]){
                
                valid=1;
                break;
            }
            valid=0;
        }
        //encontro caracter valido si salio por break
        if (valid==0 ){
            saltarespacios(input, &count);
            if (strncmp(input + count,  "<CERRAR>", 8) == 0 ) {
                //es ese operador y es valido >
                return 1;
            }else{
                printf("Invalid number character: %c \n",input[count]);
                return 0;
            }
        }

    } 
    return 1;  
};

void saltarespacios(char* input, int* count) {
    while (input[*count] == ' ') {
        (*count)++;
    }
}

void genfile(char* input) {
    FILE *file = fopen("C:/Users/andre/Documents/Visual Studio/Uru/C/output/output.txt", "w");
    if (file != NULL) {
        fputs(input, file);
        fclose(file);
    } else {
        printf("Error opening file!\n");
    }
}
