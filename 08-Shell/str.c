#include "str.h"

/* return 1 if they are the same. 
 * otherwise, return 0, it should detect faster. */
int strncmp(const char *str1, const char *str2, size_t n)
{
	int i;
	for (i = 0; i < n; i++) {
		if (str1[i] != str2[i])
			return 0;
	}
	return 1;
}

/* return 1 if they are the same. 
 * otherwise, return 0 */
int strcmp(const char *str1, const char *str2)
{
	while (1) {
		if (*str1 == '\0' || *str2 == '\0') {
			if (*str1 == *str2) return 1;
			return 0;
		}
		else if (*str1++ != *str2++ ) break;
	}
	return 0;
}

/* if we don't detect '\0' , it will be dangerous */
int strlen(const char *str)
{
	int i = 0;
	while (*str++) 
		i++;
	return i;
}

int strncpy(char *src, char *dst, size_t n) 
{
	int i;
	for (i = 0; i < n; i++) {
		dst[i] = src[i]; 
	}
	if (dst[i-1] == '\0') return 1;
	return 0;
}

char *str_ptr;

char *strtok(char *str,const char *delimiters) 
{
	int i;
	int len = strlen(delimiters);
	
	/* check delimiters */
	if (len == 0) return NULL;

	/* check str not empty */
	if (!str && !str_ptr) return NULL;
	
	/* first call of strtok */
	if (str && !str_ptr) str_ptr = str;
	
	/* get start position */
	char *start;
	start = str_ptr;
	
	/* we don't want delimiters, skip it */
	while (1) {
		for (i = 0; i < len; i++) {
			if (*start == delimiters[i]) {
				start++;
				break;
			}
		}
		/* check we find the start position */
		if (i == len) {
			str_ptr = start;
			break;
		}
	}

	/* reach the end of the string */
	if (*str_ptr == '\0') return NULL;

	/* find the end of the substring */
	while (1) {
		for (i = 0; i < len; i++) {
			if (*str_ptr == delimiters[i]) {
				/* replace delim with null */
				*str_ptr = '\0';
				break;
			}
		}
		if(i < len) break;
		str_ptr++;
	}
	return start;
}
