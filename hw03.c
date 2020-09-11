#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Split (char* string, const char* del, char** tokens);

void Split (char* string, const char* del, char** tokens) {
  //const char* del = *delimiters;
  int i = 0;
  tokens[0] = strtok (string, del);
  //printf("%s\n", tokens[0]);
  while (tokens [i] != NULL) {
      //i++;
      //tokens[i] = strtok(NULL, del);
      //printf("%s\n", tokens[i]);
      i++;
      tokens[i] = strtok(NULL, del);
  }
}
int main () {
    char str[] = "jop,d d-a hg- hghf=jnbv";
    const char del[5] = " ,-=";
    char** token = (char**)malloc(10 * sizeof(char*));
    for(int j = 0; j < 10; j++)
	token[j] = (char*) malloc(10 * sizeof(char));
    Split (str, del, token);
    for(int j = 0; j < 7; j++)
        printf("%s\n", token[j]);
    return 0;
}
