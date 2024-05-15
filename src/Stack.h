#ifndef STACK_H_
#define STACK_H_
#include <stdint.h>
#include <stdio.h>
#include <malloc.h>

enum Errors
{
	ERR_NO,//Отсутствие ошибок
	ERR_MALLOC//Ошибка malloc
};

//Стек чисел
typedef struct
{
	uint8_t num;	//Число элементов стека 
	uint8_t *stack;	//Непосредственно память стека
}
Stack;

/*Вталкивание элемента num в стек S. 
Возврат 0 при успехе, либо ERR_MALLOC*/
uint8_t PushInStack(Stack *S, uint8_t num);

//Тихое уничтожение стека S
void SilentFreeStack(Stack *S);

//Возврат 0, если стек пустой
uint8_t IsStackEmpty(Stack *S);

//Извлечение вершины стека S в num
uint8_t PullFromStack(Stack *S, uint8_t *num);

//Создание пустого стека
Stack InitStack(void);

//Неисключающее чтение вершины стека S
uint8_t ReadTopFromStack(Stack *S);

#endif 
