#include <stdio.h>

#define DEBUG 1

#define SIZE 20

#define POINT_EMPTY 0
#define POINT_SNAKE 1
#define POINT_APPLE 2

#define PRINT_EMPTY "."
#define PRINT_SNAKE "x"
#define PRINT_APPLE "&"

#define DEFAULT_SNAKE_SIZE 3

struct {
    int x;
    int y;
} typedef pointPosition;

pointPosition head;
pointPosition end;

int needBreakEnd = 1;
int step = 1;

int Field[SIZE][SIZE];
int GameContinue = 1;
int DIR_UP_RIGHT_BOTTOM_LEFT = 1;

void FieldInit();
void FieldPrint();
void ClearTerminal();
void SpawnSnakeDefault();
void FieldUpdate();
pointPosition GetNewPoint(pointPosition point);
int Point(pointPosition pos);
void SetPoint(pointPosition pos, int value);

int main(int argc, char * argv[]) {
    if(argc > 1) {
        printf("ARC");
    }

    FieldInit();
    SpawnSnakeDefault();

    while(GameContinue) {
        FieldPrint();
        FieldUpdate();

        if(step == 3) DIR_UP_RIGHT_BOTTOM_LEFT = 2;

        step += 1;

        getchar();
    }

    printf("Игра окончена.\n");

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

    if(DEBUG) {
        printf("Шаг: %d\n", step);
        printf("Удаляем хвост: %s\n", (needBreakEnd ? "да" : "нет"));
        printf("Коор головы: (%d;%d)\n", head.x, head.y);
        printf("Коор хвоста: (%d;%d)\n", end.x, end.y);
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
    pointPosition newHead = GetNewPoint(head);
    if(newHead.x < 0 || newHead.x >= SIZE || newHead.y < 0 || newHead.y >= SIZE) {
        GameContinue = 0;
        return;
    }

    if(Point(newHead) == POINT_APPLE) {
        needBreakEnd = 0;
    }

    if(Point(newHead) == POINT_SNAKE) {
        GameContinue = 0;
        return;
    }

    head = newHead;
    SetPoint(head, POINT_SNAKE);

    if(needBreakEnd) {
        pointPosition newEnd = GetNewPoint(end);
        SetPoint(end, POINT_EMPTY);
        end = newEnd;
    }
    needBreakEnd = 1;
}

//
// Получить координаты "новой" головы
//

pointPosition GetNewPoint(pointPosition point) {
    pointPosition newHead = point;
    int dir = DIR_UP_RIGHT_BOTTOM_LEFT;

    if(dir == 0) {
        newHead.x += 1;
    }
    else if(dir == 1) {
        newHead.y += 1;
    }
    else if(dir == 2) {
        newHead.x += 1;
    }
    else if(dir == 3) {
        newHead.y -= 1;
    }
    else {
        printf("Ошибка направления для координат\n");
    }

    return newHead;
}

//
// Получить точку по координатам
//

int Point(pointPosition pos) {
    return Field[pos.x][pos.y];
}

//
// Задать точку
//

void SetPoint(pointPosition pos, int value) {
    Field[pos.x][pos.y] = value;
}
