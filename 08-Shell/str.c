
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
int strcmp(const char *str1; const char *str2)
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
int strlen(const char str)
{
	int i = 0;
	while (*str++) 
		i++;
	return i;
}

char *strtok(const char *str, char delim) 
{
	int index = 0;
	char *tok;
	while (*str != delim && *str != '\0') {
		index++;
		str++;
	}	
	tok = (char *) malloc((index + 1 ) * sizeof(char));
	*(tok + index) = '\0';
	for (index = index - 1; index >= 0; index--) {
		*(tok + index) = *str--;
	}
	return tok;
}
