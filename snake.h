/*
 * snake.h
 *
 *  Created on: 2014��7��16��
 *      Author: Marvin ����Ե
 */
#ifndef SNAKE_H_
#define SNAKE_H_

unsigned char currentDir();
void initializeGame();
void endGame();
unsigned char move(unsigned char dir);
unsigned char* displayArray();
#endif 
