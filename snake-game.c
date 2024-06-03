#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 20
#define HEIGHT 10

int snakeX[100], snakeY[100], snakeLength;
int foodX, foodY;
int direction; // 1 for left, 2 for right, 3 for up, 4 for down
int gameover;

void setup() {
    snakeLength = 1;
    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;
    direction = 2; // Start moving right
    gameover = 0;
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
}

void draw() {
    system("clear");
    int i, j;
    for (i = 0; i < HEIGHT + 2; i++) {
        for (j = 0; j < WIDTH + 2; j++) {
            if (i == 0 || i == HEIGHT + 1 || j == 0 || j == WIDTH + 1) {
                printf("#"); // Draw walls
            } else if (i == foodY && j == foodX) {
                printf("F"); // Draw food
            } else {
                int isSnakePart = 0;
                for (int k = 0; k < snakeLength; k++) {
                    if (snakeX[k] == j && snakeY[k] == i) {
                        printf("O"); // Draw snake
                        isSnakePart = 1;
                        break;
                    }
                }
                if (!isSnakePart) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Use WASD or arrow keys to move the snake. Press q to quit.\n");
}

void input() {
    char key;
    scanf("%c", &key);

    switch (key) {
        case 'w':
        case 'W':
        case 72: // Up arrow key
            if (direction != 4)
                direction = 3;
            break;
        case 's':
        case 'S':
        case 80: // Down arrow key
            if (direction != 3)
                direction = 4;
            break;
        case 'a':
        case 'A':
        case 75: // Left arrow key
            if (direction != 2)
                direction = 1;
            break;
        case 'd':
        case 'D':
        case 77: // Right arrow key
            if (direction != 1)
                direction = 2;
            break;
        case 'q':
        case 'Q':
            gameover = 1;
            break;
    }
}

void logic() {
    // Move snake
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }
    switch (direction) {
        case 1: // Left
            snakeX[0]--;
            break;
        case 2: // Right
            snakeX[0]++;
            break;
        case 3: // Up
            snakeY[0]--;
            break;
        case 4: // Down
            snakeY[0]++;
            break;
    }

    // Check if snake eats food
    if (snakeX[0] == foodX && snakeY[0] == foodY) {
        snakeLength++;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
    }

    // Check if snake hits walls or itself
    if (snakeX[0] == 0 || snakeX[0] == WIDTH + 1 || snakeY[0] == 0 || snakeY[0] == HEIGHT + 1) {
        gameover = 1;
    }
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            gameover = 1;
        }
    }
}

int main() {
    setup();
    while (!gameover) {
        draw();
        input();
        logic();
        usleep(100000); // Slow down the game
    }
    printf("Game over!\n");
    return 0;
}
