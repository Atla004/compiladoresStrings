int isValidExpression(char* input) {
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

    // Split the expression into parts
    char *part = strtok(input + 8, " ");
    while (part != NULL) {
        if (strcmp(part, "=") == 0 || strcmp(part, "==") == 0) {
            // Skip the operator
            part = strtok(NULL, " ");
            continue;
        }

        if (!isNumber(part)) {
            printf("The number part is invalid.\n");
            return 0;
        }

        part = strtok(NULL, " ");
    }

    return 1;
}