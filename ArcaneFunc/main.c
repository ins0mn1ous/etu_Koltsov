#include "arcana.h"

int main() {
    int selected = 0; // Выбранный пункт
    int running = 1;  // Флаг для выполнения программы

    while (running) {
        system("cls");
        displayMenu(selected);

        int key = _getch();
        switch (key) {
        case '1': selected = 0; break;
        case '2': selected = 1; break;
        case '3': selected = 2; break;
        case 72:
            selected = (selected - 1 + NUM_ITEMS) % NUM_ITEMS;
            break;
        case 80:
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
                running = 0;
            }
            break;
        case ESC:
            running = 0;
            break;
        }
    }

    return 0;
}