#include <stddef.h>
#include <stdint.h>
#include "reg.h"
#include "threads.h"
#include "str.h"

#define MAX_INPUT 50

/* USART TXE Flag
 * This flag is cleared when data is written to USARTx_DR and
 * set when that data is transferred to the TDR
 */
#define USART_FLAG_TXE	((uint16_t) 0x0080)

/* when RXNE is set, data can be read */
#define USART_FLAG_RXNE ((uint16_t) 0x0020)

int fibonacci(int number1);

void usart_init(void)
{
	*(RCC_APB2ENR) |= (uint32_t) (0x00000001 | 0x00000004);
	*(RCC_APB1ENR) |= (uint32_t) (0x00020000);

	/* USART2 Configuration, Rx->PA3, Tx->PA2 */
	*(GPIOA_CRL) = 0x00004B00; 
	*(GPIOA_CRH) = 0x44444444;
	*(GPIOA_ODR) = 0x00000000;
	*(GPIOA_BSRR) = 0x00000000;
	*(GPIOA_BRR) = 0x00000000;

	*(USART2_CR1) = 0x0000000C; // Tx Enable, Rx Enable
	*(USART2_CR2) = 0x00000000;
	*(USART2_CR3) = 0x00000000;
	*(USART2_CR1) |= 0x2000;    // USART Enable
}

void print_str(const char *str)
{
	while (*str) {
		while (!(*(USART2_SR) & USART_FLAG_TXE));
		*(USART2_DR) = (*str & 0xFF);
		str++;
	}
}

void print_char(const char *str) 
{
	if (*str) {
		while (!(*(USART2_SR) & USART_FLAG_TXE));
		*(USART2_DR) = (*str & 0xFF);
	}
}

char recv_char(void)
{
	while (1) {
		if ((*USART2_SR) & (USART_FLAG_RXNE)) {
			return (*USART2_DR) & 0xff;
		}
	}
}

void clear_buffer(char *buffer, size_t index)
{
	int i;
	for(i = index; i >= 0; i--)
		buffer[i] = '\0';
}

void command_detect (char *str, size_t index)
{
	char cmd[index];
	strncpy(str, cmd, index);	
	char *tok = strtok(cmd, " ");
	print_str("token : ");
	print_str(tok);
	print_char("\n");

	if (strcmp("help", tok))
		print_str("This is a help command\n");
	else if (strncmp("fibonacci", str, index)) {
		print_str("Calculating fibonacci sequence ...\n");
		if (thread_create_int(fibonacci, 15) == -1)
			print_str("Failed to create fib thread...QQ\n");
		else
			print_str("Create fibonacci sequence successfully!!\n");
	}
}

void shell(void *user)
{
	char buffer[MAX_INPUT];
	size_t index;
	while (1) {
		print_str("tonyyanxuan:~$ ");
		index = 0;
		while (1) {
			buffer[index] = recv_char();

			/* detect "enter" hit or a new line character */
			if (buffer[index] == 13 || buffer[index] == '\n') {
				print_char("\n");
				buffer[index] = '\0';
				command_detect(&buffer[0], index);
				break;
			} 
			/* detect backspace or delete */
			else if (buffer[index] == 8 || buffer[index] == 127) {
				if (index != 0) {
					print_char("\b");
					print_char(" ");
					print_char("\b");
					buffer[index--] = '\0';
				}
			} else  {
				print_char(&buffer[index++]);
			}

			/* prevent index overflow */
			if (index == MAX_INPUT)
				index--;
		}
		 /* ---- debug ----
		  * print_str("your input is : ");
		  * print_str(&buffer[0]);
		  * print_str("\n"); */
		clear_buffer(buffer, index);
	}
}


/*static void delay(volatile int count)
{
	count *= 50000;
	while (count--);
}*/

/*static void busy_loop(void *str)
{
	while (1) {
		print_str(str);
		print_str(": Running...\n");
		delay(1000);
	}
}*/

/* 72MHz */
#define CPU_CLOCK_HZ 72000000

/* 100 ms per tick. */
#define TICK_RATE_HZ 10

int main(void)
{
	const char *str1 = "Task_SHELL";

	usart_init();

	if (thread_create(shell, (void *) str1) == -1)
		print_str("SHELL creation failed\r\n");


	/* SysTick configuration */
	*SYSTICK_LOAD = (CPU_CLOCK_HZ / TICK_RATE_HZ) - 1UL;
	*SYSTICK_VAL = 0;
	*SYSTICK_CTRL = 0x07;

	thread_start();

	return 0;
}

int fibonacci(int number) 
{
	if (number == 0) return 0;
	if (number == 1) return 1;
	return fibonacci(number - 1) + fibonacci(number - 2);
}
