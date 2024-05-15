#include "Stack.h" //включает stdio, stdint, malloc

uint8_t CharToNum(char c);
uint8_t CharIsNum(char c);
uint8_t PrintStack(Stack *S, const char *fmt);
uint8_t MultOfStack(Stack *S, uint16_t *mult);
uint8_t SumOfStack(Stack *S, uint16_t *sum);
/*
Написать и отладить программу, реализующую работу с динамической
структурой данных «Стек» на основе динамических массивов.

Ввести некоторое число и записать его цифры в стек. Цифры из
записи числа считывать поочередно (например, с помощью
getch()). Вычислить сумму и произведение его цифр.
*/
int main(void)
{
	Stack // Стек чисел
		NumStack = InitStack();

	char // Символ, в который записывается число
		c;

	uint16_t // Число, в которое будет записано произведение, либо сумма
		MultOrSum;

	/* Цикл ввода чисел, пока не нажат Enter */
	while ('\n' != (c = getchar()))
		if (CharIsNum(c)) // Если символ является числом, он записывается в стек
			if (PushInStack(&NumStack, CharToNum(c)))
				return ERR_MALLOC; // Возврат кода ошибки, если malloc не выделил память

	// Если в стек не были записаны элементы, будет выведено сообщение
	if (!IsStackEmpty(&NumStack))
	{
		puts("Стек пустой!");
		// Завершение работы
		return ERR_NO;
	}

	//Цикл продолжится, пока не будет нажата нужная клавиша
	while (1)
	{
		puts("Введите p чтобы вывести элементы");
		puts("Введите s чтобы вывести сумму элементов");
		puts("Введите m чтобы вывести произведение элементов");

		switch (getchar())
		{
		case 'p':
		case 'P':
			// Вывод стека, вместе с его уничтожением, проверка malloc
			if (PrintStack(&NumStack, "%hhu "))
				return ERR_MALLOC;
			return ERR_NO;

		case 's':
		case 'S':
			//Подсчёт суммы членов стека, его уничтожение, проверка malloc
			if (SumOfStack(&NumStack, &MultOrSum))
				return ERR_MALLOC;
			printf("Сумма чисел стека: %hu\n", MultOrSum);
			return ERR_NO;

		case 'm':
		case 'M':
			//Подсчёт произведения членов стека, его уничтожение, проверка malloc
			if (MultOfStack(&NumStack, &MultOrSum))
				return ERR_MALLOC;
			printf("Произведение чисел стека: %hu\n", MultOrSum);
			return ERR_NO;

		default:
			break;
		}
	}
}

// Посчитать произведение членов стека S в mult, очистив его
uint8_t MultOfStack(Stack *S, uint16_t *mult)
{
	*mult = 1;
	uint8_t el; // элемент, в который будет записыватся число

	// Цикл перебора, пока в стеке есть число
	while (IsStackEmpty(S))
	{ // Осуществляется исключающее чтение
		if (PullFromStack(S, &el))
			return ERR_MALLOC;

		*mult *= el;
	}
	return ERR_NO;
}

// Посчитать сумму стека S в sum, очистив его
uint8_t SumOfStack(Stack *S, uint16_t *sum)
{
	*sum = 0;
	uint8_t el; // элемент, в который будет записыватся число

	// Цикл перебора, пока в стеке есть число
	while (IsStackEmpty(S))
	{ // Осуществляется исключающее чтение
		if (PullFromStack(S, &el))
			return ERR_MALLOC;

		*sum += el;
	}
	return ERR_NO;
}

// Конвертирует символ, являющийся цифрой, в эту цифру
uint8_t CharToNum(char c)
{
	return c - '0';
}

// Проверяет, принадлежит ли данный символ к цифрам
uint8_t CharIsNum(char c)
{
	return (c >= '0' && c <= '9');
}

// Уничтожающий вывод стека S форматом fmt
uint8_t PrintStack(Stack *S, const char *fmt)
{
	uint8_t el; // элемент, в который будет записыватся число

	// Цикл перебора, пока в стеке есть число
	while (IsStackEmpty(S))
	{ // Осуществляется исключающее чтение
		if (PullFromStack(S, &el))
			return ERR_MALLOC;

		// Вывод каждого элемента в соответствии с форматом
		printf(fmt, el);
	}
	// Перенос строки в конце
	putchar('\n');
	return ERR_NO;
}
