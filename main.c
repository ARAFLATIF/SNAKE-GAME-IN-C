#include <conio.h>  // For _kbhit() and _getch()
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // For Sleep()

#define WIDTH 20
#define HEIGHT 20
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int tailX[100], tailY[100];
int tailLength = 0;
int gameOver, score;
int x, y, fruitX, fruitY, flag;

void setup() {
    gameOver = 0;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    label1:
    fruitX = rand() % 20;
    if (fruitX == 0)
        goto label1;
    label2:
    fruitY = rand() % 20;
    if (fruitY == 0)
        goto label2;
    score = 0;
}

void draw() {
    int i, j, k;
    system("cls");
    for (i = 0; i < WIDTH; i++) {
        for (j = 0; j < HEIGHT; j++) {
            if (i == 0 || i == WIDTH - 1 || j == 0 || j == HEIGHT - 1) {
                printf("#");
            } else {
                if (i == x && j == y)
                    printf("O");
                else if (i == fruitX && j == fruitY)
                    printf("F");
                else {
                    int print = 0;
                    for (k = 0; k < tailLength; k++) {
                        if (i == tailX[k] && j == tailY[k]) {
                            printf("o");
                            print = 1;
                        }
                    }
                    if (!print)
                        printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            flag = 1;
            break;
        case 's':
            flag = 2;
            break;
        case 'd':
            flag = 3;
            break;
        case 'w':
            flag = 4;
            break;
        case 'x':
            gameOver = 1;
            break;
        }
    }
}

void logic() {
    int i;
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (flag) {
    case 1:
        y--;
        break;
    case 2:
        y++;
        break;
    case 3:
        x++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameOver = 1;
    for (i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    }
    if (x == fruitX && y == fruitY) {
    label3:
        fruitX = rand() % 20;
        if (fruitX == 0)
            goto label3;
    label4:
        fruitY = rand() % 20;
        if (fruitY == 0)
            goto label4;
        score += 10;
        tailLength++;
    }
}

int main() {
    int m, n;
    char c;
    srand(time(0));
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(100); // Sleep(10);
    }
    printf("\nPress Y to play again: ");
    scanf("%c", &c);
    if (c == 'y' || c == 'Y') {
        main();
    }
    return 0;
}
