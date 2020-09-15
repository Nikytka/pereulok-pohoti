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
  
    // fixit: нужна константа с понятным именем для числа 10 
    char** token = (char**)malloc(10 * sizeof(char*));
  
    // посмотрите, как работает strtok и память под что именно необходимо выделять
    for(int j = 0; j < 10; j++)
        token[j] = (char*) malloc(10 * sizeof(char));
    Split (str, del, token);
  
    // fixit: ф-я split должна возвращать число найденных слов. вариант с числом 7 - не является общим решением.
    for(int j = 0; j < 7; j++)
        printf("%s\n", token[j]);
  
    // fixit: выделенную память надо освободить
    return 0;
}
