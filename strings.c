#include <stdio.h>
#include <stdlib.h>
#include "strings.h"

int slen(char *str) {
  int count = 0;

  while (str[count] != '\0') {
    count++;
  }
  return count;
} 

int s_tok(char *str, char delim, char *ptr[]) {
  char *suf = str;
  ptr[0] = str;
  int i, j = 1;

  while ((i = schr(suf, delim)) >= 0) {
    suf[i] = '\0';
    suf = suf + i + 1;
    ptr[j] = suf;
    j++;
  }
  return j;
}

int schr(char *str, char ch) {
  int i, index = -1;

  for (i = 0; (str[i] != '\0') && (str[i] != ch); i++) ;
  if (str[i] == ch)
    index = i;

  return index;
}

void suntok(char str[], char delim, char *ptr[], int cnt) {
  int i;
  for (i = 1; i < cnt; i++) {
    *(ptr[i] - 1) = delim;
  }
}

void ToLower(char *str) {
  while (*str != '\0') {
    if (*str >= 128 && *str <= 160) {
      *str = *str + 32;
    }
    str++;
  }
}