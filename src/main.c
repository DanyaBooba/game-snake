#include <stdio.h>

#define SIZE 20

#define POINT_EMPTY 0
#define POINT_SNAKE 1
#define POINT_APPLE 2

#define PRINT_EMPTY "."
#define PRINT_SNAKE "x"
#define PRINT_APPLE "&"

#define DEFAULT_SNAKE_SIZE 3
#define DIR_UP_RIGHT_BOTTOM_LEFT 1

struct {
    int x;
    int y;
} typedef pointPosition;

pointPosition head;
pointPosition end;

int Field[SIZE][SIZE];

void FieldInit();
void FieldPrint();
void ClearTerminal();
void SpawnSnakeDefault();
void FieldUpdate();

int main(int argc, char * argv[]) {
    if(argc > 1) {
        printf("ARC");
    }

    FieldInit();
    SpawnSnakeDefault();

    while(1) {
        FieldPrint();
        FieldUpdate();

        getchar();
    }

    return 0;
}

//
// Инициализация поля
//

void FieldInit() {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            Field[i][j] = POINT_EMPTY;
        }
    }
}

//
// Печать поля
//

void FieldPrint() {
    ClearTerminal();
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if(Field[i][j] == POINT_EMPTY) {
                printf("%2s", PRINT_EMPTY);
            }
            else if(Field[i][j] == POINT_SNAKE) {
                printf("%2s", PRINT_SNAKE);
            }
            else if(Field[i][j] == POINT_APPLE) {
                printf("%2s", PRINT_APPLE);
            }
        }
        printf("\n");
    }
}

//
// Очистить терминал
//

void ClearTerminal() {
    printf("\e[1;1H\e[2J");
}

//
// Спавн змеи по умолчанию
//

void SpawnSnakeDefault() {
    Field[2][2] = POINT_SNAKE;
    Field[2][3] = POINT_SNAKE;
    Field[2][4] = POINT_SNAKE;

    end = (pointPosition) { 2, 2 };
    head = (pointPosition) { 2, 4 };
}

//
// Обновление поля
//

void FieldUpdate() {
    // ...
}
