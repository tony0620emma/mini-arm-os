#include "type.h"

void itoa(int n, char *str)
{
	int i, sign;
	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		str[i++] = n % 10 + '0';
	} while((n /= 10) > 0);
	if (sign < 0)
		str[i++] = '-';
	str[i] = '\0';
	reverse(str);
}

void reverse(char *str)
{
	int i, length;
	char c;
	
	length = 0;
	while (*str++) 
		length++;
	for (i = 0; i < length; i++, length--) {
		c = str[i];
		str[i] = str[length];
		str[length] = c;
	}
}
