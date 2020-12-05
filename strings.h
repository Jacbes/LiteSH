#ifndef STRINGS_H
#define STRINGS_H

#include <stdio.h>
#include <stdlib.h>

int slen(char *str);
int s_tok(char *str, char delim, char *ptr[]);
int schr(char *str, char ch);
void suntok(char str[], char delim, char *ptr[], int cnt);
void ToLower(char *str);
#endif 
