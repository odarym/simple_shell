#ifndef STRING_H
#define STRING_H

#include "Shell.h"


char *StringCopy(char *dest, char *src);
char *StringCat(char *dest, char *src);
int StringCompare(char *s1, char *s2);
char *String_N_Copy(char *dest, char *src, int n);
int StringLength(char *s);

int String_N_Compare(const char *s1, const char *s2, size_t n);
char *StringDuplicate(char *str);
char *MemSet(char *s, char b, unsigned int n);
int IsDigit(char c);
int Atoi(char *s);
char *MemCopy(char *dest, char *src, unsigned int n);
char *Itoa(unsigned int n);
char *GetLine();


#endif

