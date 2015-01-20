/*
 * snake.h
 *
 *  Created on: 2014年7月16日
 *      Author: Marvin 蒋子缘
 */
#ifndef SNAKE_H_
#define SNAKE_H_

unsigned char currentDir();
void initializeGame();
void endGame();
unsigned char move(unsigned char dir);
unsigned char* displayArray();
#endif 
