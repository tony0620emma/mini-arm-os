#ifndef __STR_H
#define __STR_H

#include <stddef.h>
#include <stdint.h>

int strncmp(const char * , const char * , size_t);
int strcmp(const char *, const char *);
int strlen(const char *);
int strncpy(char *, char *, size_t);
char *strtok(char *,const char *);
void strtok_flush(void);

#endif
