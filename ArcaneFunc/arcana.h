#ifndef ARCANA_H
#define ARCANA_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define ESC 27
#define ENTER 13
#define NUM_ITEMS 3
#define MAX_LINE_LENGTH 256

// Прототипы функций
void displayMenu(int selected);
int validDate(int day, int month, int year);
int sumDigits(int num);
int calculate(int day, int month, int year);
int calculateArcana();
void viewLogFile();

#endif 