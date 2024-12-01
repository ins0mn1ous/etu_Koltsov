#include "arcana.h"

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

// Проверка корректности даты
int validDate(int day, int month, int year) {
    if (year < 1 || year > 9999) return 0;
    if (month < 1 || month > 12) return 0;
    if (day < 1) return 0;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    }

    return day <= daysInMonth[month - 1];
}

// Суммирование цифр числа
int sumDigits(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

// Расчет числа аркана
int calculate(int day, int month, int year) {
    int total = sumDigits(day) + sumDigits(month) + sumDigits(year);
    while (total > 22) {
        total -= 22;
    }
    return total;
}

// Расчет и вывод информации об аркане
int calculateArcana() {
    int day, month, year;

    printf("Введите дату рождения (дд мм гггг): ");
    if (scanf("%d %d %d", &day, &month, &year) != 3) {
        printf("Ошибка ввода! Убедитесь, что вы ввели три числа.\n");
        _getch();
        return 0;
    }

    if (!validDate(day, month, year)) {
        printf("Неверная дата! Попробуйте снова.\n");
        _getch();
        return 0;
    }

    clock_t start = clock();

    char* list[22] = {
        "Маг", "Жрица", "Императрица", "Император", "Иерофант", "Влюбленные",
        "Колесница", "Сила", "Отшельник", "Колесо фортуны", "Справедливость",
        "Повешенный", "Смерть", "Умеренность", "Дьявол", "Башня", "Звезда",
        "Луна", "Солнце", "Суд", "Мир", "Шут"
    };

    int arcana = calculate(day, month, year);
    printf("Ваш старший аркан: %d - %s\n", arcana, list[arcana - 1]);

    FILE* file = fopen("arcaneInfo.txt", "r");
    if (!file) {
        printf("Ошибка: файл с описанием арканов не найден.\n");
        _getch();
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    char target[MAX_LINE_LENGTH];
    snprintf(target, sizeof(target), "%d.", arcana);

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, target, strlen(target)) == 0) {
            printf("%s", line);
            break;
        }
    }

    fclose(file);

    FILE* logFile = fopen("log.txt", "a");
    if (logFile) {
        fprintf(logFile, "Дата рождения: %02d.%02d.%d, Аркан: %d\n", day, month, year, arcana);
        fclose(logFile);
    }

    clock_t end = clock();
    double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Время выполнения: %.3f секунд.\n", timeTaken);
    printf("Нажмите любую клавишу для возврата в меню.\n");
    _getch();
    return 0;
}

// Просмотр log.txt
void viewLogFile() {
    FILE* logFile = fopen("log.txt", "r");
    if (!logFile) {
        printf("Ошибка: файл log.txt не найден.\n");
        _getch();
        return;
    }

    printf("Содержимое log.txt:\n");
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, sizeof(buffer), logFile)) {
        printf("%s", buffer);
    }
    fclose(logFile);

    printf("\nНажмите любую клавишу для возврата в меню.\n");
    _getch();
}
