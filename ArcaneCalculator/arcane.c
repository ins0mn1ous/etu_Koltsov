#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <locale.h>

 // Цвета в консоли
void setTextColorAndBackground() {

    system("color c4");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_GREEN);

}

// Корректность даты
int validDate(int day, int month, int year) {
    // Проверяем диапазоны
    if (year < 1 || year > 9999) return 0;
    if (month < 1 || month > 12) return 0;
    if (day < 1) return 0;

    // Количество дней в каждом месяце
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Проверка високосного года
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    }

    if (day > daysInMonth[month - 1]) return 0;

    return 1;

}

// Сумма цифр числа
int sumDigits(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

// Вычисление арканы
int calculateArcana(int day, int month, int year) {
    int total = sumDigits(day) + sumDigits(month) + sumDigits(year);

    while (total > 22) {
        total -= 22;
    }

    return total;
}

int main() {

    setTextColorAndBackground();

    int day, month, year;

    printf("Введите дату рождения (дд мм гггг): ");
    if (scanf("%d %d %d", &day, &month, &year) != 3) {
        printf("Ошибка ввода! Убедитесь, что вы ввели три числа.\n");
        return 1;
    }

    if (!validDate(day, month, year)) {
        printf("Неверная дата! Попробуйте снова.\n");
        return 1;
    }

    char* list[22] = { "Маг", "Жрица", "Императрица", "Император", "Иерофант", "Влюбленные", "Колесница", "Сила", "Отшельник", "Колесо фортуны", "Справедливость", "Повешенный", "Смерть", "Умеренность", "Дьявол", "Башня", "Звезда", "Луна", "Солнце", "Суд", "Мир", "Шут"};
    int arcana = calculateArcana(day, month, year);

    printf("Ваш старший аркан: %d - %s\n", arcana, list[arcana - 1]);

    return 0;
}

