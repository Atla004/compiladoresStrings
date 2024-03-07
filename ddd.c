#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{


char cadena[] = " hola,como= estas ";
char *hola, *como, *estas;

hola = strtok(cadena,",");
como = strtok(NULL,"=");
estas = strtok(NULL," ");

if(hola != NULL) printf("hola: %s\n", hola);
if(como != NULL) printf("como: %s\n", como);
if(estas != NULL) printf("estas: %s\n", estas);

    return 0;
}
