
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* filenNAME = "C:/Users/ATS/Documents/Visual studio/BASICO/C/Compiladores/s.txt";

// <ABRIR> variable = 5 < 3 <CERRAR>
// <ABRIR> var{iable = 5 > 3 <CERRAR>

void print_error_marker(int position) {
    for (int i = 0; i < position + 22; i++) {
        printf(" ");
    }
    printf("^\n");
}

int isValidExpression(char* input, char *operators, char **variable, char **number1, char **number2) {
    char* operatorscharacter[] = {"<", ">", "==", "!="};
    char* variablecharacter= "abcdefghijklmnopqrstuvwxyz_";
    char* numbercharacter= "0123456789";

    int startvariable, startnumber1, startnumber2, valid;
    int count=0;
    *variable = malloc(20 * sizeof(char));
    *number1 = malloc(20 * sizeof(char));
    *number2 = malloc(20 * sizeof(char));

    // Check if the input starts with "ABRIR "
    if (strncmp(input, "<ABRIR> ", 8) != 0) {
        //no es valido
        print_error_marker(count);
        printf("el input no empieza con <ABRIR> \n");
        return 0;
    }

    // Check if the input ends with " CERRAR"
    if (strncmp(input + strlen(input) - 9, " <CERRAR>", 9) != 0) {
        //no es valido
        print_error_marker(strlen(input) - 8);
        printf("el input no termina con <CERRAR> \n");
        return 0;
    }
    count=8;
    saltarespacios(input, &count);
    startvariable=count;

    //check variable
    for (count; count < strlen(input); count++){  
        for (int j = 0; j < strlen(variablecharacter); j++){
            if (input[count] == variablecharacter[j]){
                valid=1;
                break;
            }
            valid=0;
        }
        // si no es valido y el caracter no es espacio o igual retorna el error
        if (valid==0 && input[count] != ' ' && input[count] != '='){
            print_error_marker(count);
            printf("Invalid variable character: %c \n",input[count]);
            return 0;
        }
        //si es espacio o igual, es valido y se sale del ciclo
        if (input[count] == ' ' || input[count] == '='){
            valid=1;
            break;
        }
    }
    
    strncpy((*variable), &input[startvariable], count-startvariable);
    (*variable)[count-startvariable] = '\0';

    saltarespacios(input, &count);


    //chekc if the next character is an equal sign
    if (input[count] == '='){
        count++;
    }else{
        print_error_marker(count);
        printf("Invalid character: %c \n",input[count]);
        return 0;
    }

    saltarespacios(input, &count);


    //check first number
    startnumber1=count;
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
            // guardando el numero
            strncpy((*number1), &input[startnumber1], count-startnumber1);
            (*number1)[count-startnumber1] = '\0';
            saltarespacios(input, &count);

            if (strncmp(input + count, operatorscharacter[0], 1) == 0) {
                //es ese operador y es valido <
                operators[0]='<';
                operators[1]='\0';
                count++;
                valid=1;
                break;

            }else if (strncmp(input + count, operatorscharacter[1], 1) == 0) {
                //es ese operador y es valido >
                operators[0]='>';
                operators[1]='\0';
                count++;
                valid=1;
                break;
            }else if (strncmp(input + count, operatorscharacter[2], 2) == 0) {
                //es ese operador y es valido ==
                strcpy(operators, "==");
                operators[2]='\0';
                count+=2;

                valid=1;
                break;
            }else if (strncmp(input + count, operatorscharacter[3], 2) == 0) {
                //es ese operador y es valido !=
                strcpy(operators, "!=");
                operators[2]='\0';
                count+=2;
                valid=1;
                break;
            }else{
                print_error_marker(count);
                printf("Invalid number character: %c \n",input[count]);
                return 0;
            }
        }

    }
    

    saltarespacios(input, &count);

    //checks second number
    startnumber2=count;
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
            strncpy((*number2), &input[startnumber2], count-startnumber2);
            (*number2)[count-startnumber2] = '\0';
            saltarespacios(input, &count);
            if (strncmp(input + count,  "<CERRAR>", 8) == 0 ) {
                //es ese operador y es valido >
                return 1;
            }else{
                print_error_marker(count);
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

void genfile(char* input, char *operators, char **variable, char **number1, char **number2) {
    FILE *file = fopen(filenNAME, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return ;
    }
    fprintf(file,"input: %s\n", input);
    fprintf(file, "variable: %s\n", *variable);
    fprintf(file, "number1: %s\n", *number1);
    fprintf(file, "number2: %s\n", *number2);
    fprintf(file, "operator: %s\n", operators);

    fclose(file);
}

void performOperation(char *operator, char *number1, char *number2) {
    int num1 = atoi(number1);
    int num2 = atoi(number2);
    int result;

    if (strcmp(operator, "<") == 0) {
        result = num1 < num2;
    } else if (strcmp(operator, ">") == 0) {
        result = num1 > num2;
    } else if (strcmp(operator, "==") == 0) {
        result = num1 == num2;
    } else if (strcmp(operator, "!=") == 0) {
        result = num1 != num2;
    }

    if (result) {
        printf("Result: true\n");
    } else {
        printf("Result: false\n");
    }
}

int main() {
    char input[100];
    char operators[3];
    char* variable,* number1,* number2;
    printf("Enter the expression: ");
    fgets(input, sizeof(input), stdin);

    // Remove the newline character from the input
    input[strcspn(input, "\n")] = '\0';

    if (isValidExpression(input,operators,&variable, &number1, &number2)) {
        printf("Valid\n");
        genfile(input,operators,&variable, &number1, &number2);
        performOperation(operators, number1, number2);
    } else {
        printf("Invalid\n");
    }


    return 0;
}
