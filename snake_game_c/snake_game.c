#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>

#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20

bool gameOver;
int score;
int snakeX, snakeY;
int fruitX, fruitY;
int tailX[100], tailY[100];
int tailLength;

enum eDirection {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum eDirection dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    snakeX = BOARD_WIDTH / 2;
    snakeY = BOARD_HEIGHT / 2;
    fruitX = rand() % BOARD_WIDTH;
    fruitY = rand() % BOARD_HEIGHT;
    score = 0;
}

void Draw() {
    clear();
    for (int i = 0; i < BOARD_WIDTH + 2; i++)
        printw("#");
    printw("\n");

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (j == 0)
                printw("#");
            if (i == snakeY && j == snakeX)
                printw("O");
            else if (i == fruitY && j == fruitX)
                printw("F");
            else {
                bool printTail = false;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printw("o");
                        printTail = true;
                    }
                }
                if (!printTail)
                    printw(" ");
            }
            if (j == BOARD_WIDTH - 1)
                printw("#");
        }
        printw("\n");
    }

    for (int i = 0; i < BOARD_WIDTH + 2; i++)
        printw("#");
    printw("\n");
    printw("Score: %d\n", score);
    refresh();
}

void Input() {
    int ch = getch();
    switch (ch) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = snakeX;
    tailY[0] = snakeY;
    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
        case LEFT:
            snakeX--;
            break;
        case RIGHT:
            snakeX++;
            break;
        case UP:
            snakeY--;
            break;
        case DOWN:
            snakeY++;
            break;
        default:
            break;
    }
    if (snakeX >= BOARD_WIDTH) snakeX = 0;
    else if (snakeX < 0) snakeX = BOARD_WIDTH - 1;
    if (snakeY >= BOARD_HEIGHT) snakeY = 0;
    else if (snakeY < 0) snakeY = BOARD_HEIGHT - 1;

    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == snakeX && tailY[i] == snakeY) {
            gameOver = true;
        }
    }

    if (snakeX == fruitX && snakeY == fruitY) {
        score += 10;
        fruitX = rand() % BOARD_WIDTH;
        fruitY = rand() % BOARD_HEIGHT;
        tailLength++;
    }
}

int main() {
    srand(time(NULL));
    initscr();
    clear();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        // Change speed of the game by adding delay
        for (int i = 0; i < 10000000; i++);
    }
    printw("\nGame Over! Your final score is: %d\n", score);
    getch();
    endwin();
    return 0;
}
