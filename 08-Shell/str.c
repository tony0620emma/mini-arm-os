
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
