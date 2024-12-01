#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define ESC 27
#define ENTER 13
#define NUM_ITEMS 3
#define MAX_LINE_LENGTH 256

// Прототипы функций
void viewLogFile();
void displayMenu(int selected);

// Основная программа
int main() {
    int selected = 0; // Выбранный пункт
    int running = 1;  // Флаг для выполнения программы

    while (running) {
        system("cls"); // Очистка экрана
        displayMenu(selected);

        // Обработка клавиш
        int key = _getch();
        switch (key) {
        case '1': selected = 0; break;
        case '2': selected = 1; break;
        case '3': selected = 2; break;
        case 72: // Вверх
            selected = (selected - 1 + NUM_ITEMS) % NUM_ITEMS;
            break;
        case 80: // Вниз
            selected = (selected + 1) % NUM_ITEMS;
            break;
        case ENTER:
            if (selected == 0) {
                system("cls");
                calculateArcana();
            }
            else if (selected == 1) {
                system("cls");
                viewLogFile();
            }
            else if (selected == 2) {
                running = 0; // Завершение программы
            }
            break;
        case ESC:
            running = 0; // Завершение программы
            break;
        }
    }

    return 0;
}

// Функция для отображения меню
void displayMenu(int selected) {
    const char* menuItems[NUM_ITEMS] = {
        "1) Ввод даты для расчета аркана",
        "2) Просмотр log.txt",
        "3) Выход из программы"
    };

    printf("Используйте стрелки или цифры для выбора пункта. Нажмите Enter для перехода.\n\n");

    // Вывод меню с выделением выбранного пункта
    for (int i = 0; i < NUM_ITEMS; i++) {
        if (i == selected) {
            printf("-> %s\n", menuItems[i]); // Указатель на выбранный пункт
        }
        else {
            printf("   %s\n", menuItems[i]);
        }
    }

    printf("\nEsc - выход.\n");
}

// Функция для расчета старшего аркана

int validDate(int day, int month, int year) {

    if (year < 1 || year > 9999) return 0;
    if (month < 1 || month > 12) return 0;
    if (day < 1) return 0;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    }

    if (day > daysInMonth[month - 1]) return 0;

    return 1;

}

int sumDigits(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int calculate(int day, int month, int year) {
    int total = sumDigits(day) + sumDigits(month) + sumDigits(year);

    while (total > 22) {
        total -= 22;
    }

    return total;
}

int calculateArcana() {

    int day, month, year;

    printf("Введите дату рождения (дд мм гггг): ");
    if (scanf("%d %d %d", &day, &month, &year) != 3) {
        printf("Ошибка ввода! Убедитесь, что вы ввели три числа.\n");
        _getch();
        return;
    }

    if (!validDate(day, month, year)) {
        printf("Неверная дата! Попробуйте снова.\n");
        _getch();
        return;

    }

    char* list[22] = { "Маг", "Жрица", "Императрица", "Император", "Иерофант", "Влюбленные", "Колесница", "Сила", "Отшельник", "Колесо фортуны", "Справедливость", "Повешенный", "Смерть", "Умеренность", "Дьявол", "Башня", "Звезда", "Луна", "Солнце", "Суд", "Мир", "Шут" };
    int arcana = calculate(day, month, year);

    printf("Ваш старший аркан: %d - %s\n", arcana, list[arcana - 1]);

    int number = arcana;

    //Вывод текста по найденному аркану
    FILE* file = fopen("arcaneInfo.txt", "r");
    char line[MAX_LINE_LENGTH];
    char target[MAX_LINE_LENGTH];
    snprintf(target, sizeof(target), "%d.", number); // Формируем строку для поиска "X."

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, target, strlen(target)) == 0) {
            printf("%s", line); // Вывод строки, соответствующей числу
            fclose(file);
        }
    }
    fclose(file);

    // Запись в лог-файл
    FILE* logFile = fopen("log.txt", "a");
    if (logFile) {
        fprintf(logFile, "Дата рождения: %02d.%02d.%d, Аркан: %d\n", day, month, year, arcana);
        fclose(logFile);
    }

    printf("Нажмите любую клавишу для возврата в меню.\n");
    _getch();
}


// Функция для просмотра log.txt
void viewLogFile() {
    FILE* logFile = fopen("log.txt", "r");

    printf("Содержимое log.txt:\n");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), logFile)) {
        printf("%s", buffer);
    }
    fclose(logFile);

    printf("\nНажмите любую клавишу для возврата в меню.\n");
    _getch();
}