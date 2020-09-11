#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void GenerateString (int n, char* string);

void GenerateString (int n, char* string) {
  int i, len = 0, k = 0;
  len = pow(2, n);
  char letter = 'a';
  string[0] = letter;
  for ( i = 1; i < n; i++ ) {
      k = pow(2,i) - 1;
      letter++;
      string[k] = letter;
      strncpy((string + k + 1), string, k);
  }
}

int main() {
  int n;
  scanf("%d", &n);
  int len = pow(2, n) + 1;
  char* string = (char*)calloc(len, sizeof(char));
  GenerateString (n, string);
  printf("%s", string);
  free(string);
  return 0;
}
