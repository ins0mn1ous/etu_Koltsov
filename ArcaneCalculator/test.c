#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h> 

void setTextColorAndBackground() {

    system("color c4");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_GREEN);
    
}

//void setConsoleBackgroundColor() {
//
//    system("color c4");
//}

int main() {
    setTextColorAndBackground();

    printf("colour\n");

    return 0;
}


//int kek() {
//	main();
//	printf("skg;shs[oifhdg [oi");
//}
//
//int main() {
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_RED );
//	return 0;
//}

