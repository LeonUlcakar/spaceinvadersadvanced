#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

const unsigned int WIDTH = 40;
const unsigned int HEIGHT = 20;
const unsigned int PLAYER_START_X = WIDTH / 2;
const unsigned int PLAYER_START_Y = HEIGHT - 2;
const unsigned int ENEMY_START_X = 1;
const unsigned int ENEMY_START_Y = 1;
const unsigned int ENEMY_SPACING = 6;
const unsigned int numOfEnemies = 5;
bool gameOver = false;
int unsigned score = 0;

struct player {
    int unsigned playerX = WIDTH / 2;
    int unsigned playerY = HEIGHT - 1;
    int unsigned bulletX = playerX;
    int unsigned bulletY = playerY - 1;
    bool isFiring = false;
};

struct enemy {
    int unsigned enemyX = 0;
    int unsigned enemyY = 0;
    bool enemyIsFiring = false;
    int unsigned enemyBulletX = 0;
    int unsigned enemyBulletY = 0;
    bool isAlive = true;
};

void drawBoard(player p1, enemy enemies[]) {
    system("cls");
    for (int i = 0; i < WIDTH + 2; i++) {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) {
                cout << "|";
            }
            if (i == p1.playerY && j == p1.playerX) {
                cout << "A";
            }
            else if (i == p1.bulletY && j == p1.bulletX) {
                cout << "*";
            }
            else {
                bool enemyAlive = false;
                for (int k = 0; k < numOfEnemies; k++) {
                    if (i == enemies[k].enemyY && j == enemies[k].enemyX) {
                        cout << "M";
                        enemyAlive = true;
                        break;
                    }
                    else if (i == enemies[k].enemyBulletY && j == enemies[k].enemyBulletX) {
                        cout << "*";
                        enemyAlive = true;
                        break;
                    }
                }
                if (!enemyAlive) {
                    cout << " ";
                }
            }
            if ((j == WIDTH - 1)) {
                cout << "|";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < WIDTH + 2; i++) {
        cout << "-";
    }
    cout << endl;
    cout << "Score: " << score << endl;
}

void playerInit(player& p1) {
    p1.playerX = WIDTH / 2;
    p1.playerY = HEIGHT - 1;
    p1.isFiring = false;
}

void enemyInit(enemy enemies[]) {
    for (int i = 0; i < numOfEnemies; i++) {
        if (i == 0) {
            enemies[i].enemyX = ENEMY_START_X;
            enemies[i].enemyY = ENEMY_START_Y;
        }
        else {
            enemies[i].enemyX = enemies[i - 1].enemyX + ENEMY_SPACING;
            enemies[i].enemyY = enemies[i - 1].enemyY;
        }
        enemies[i].enemyIsFiring = false;
    }
}

void movePlayer(char input, player& p1) {
    switch (input) {
    case 'a':
        if (p1.playerX > 0) {
            p1.playerX--;
        }
        break;
    case 'd':
        if (p1.playerX < WIDTH - 1) {
            p1.playerX++;
        }
        break;
    case ' ':
        if (!p1.isFiring) {
            p1.bulletX = p1.playerX;
            p1.bulletY = p1.playerY + 1;
            p1.isFiring = true;
        }
        break;
    case 'q':
        exit(0);
        break;
    }
}

/*
void moveEnemies(enemy enemies[], player& p1) {
    static int enemyDirection = 1;
    static bool enemyReachedEdge = false;
    for (int i = 0; i < numOfEnemies; i++) {
        if (enemies[i].isAlive) {
            if (enemies[i].enemyX == 0 && enemies[i].isAlive == true) {
                enemyDirection = 1;
                enemyReachedEdge = true;
            }
            else if (enemies[i].enemyX == WIDTH - 1) {
                enemyDirection = -1;
                enemyReachedEdge = true;
            }
            else {
                enemyReachedEdge = false;
            }
            if (enemies[i].enemyIsFiring == false) {
                srand(time(NULL));
                int chance = rand() % 20;
                if (chance == 0) {
                    enemies[i].enemyIsFiring = true;
                    enemies[i].enemyBulletX = enemies[i].enemyX;
                    enemies[i].enemyBulletY = enemies[i].enemyY + 1;
                }
            }
            if (enemies[i].enemyIsFiring == true) {
                enemies[i].enemyBulletY++;
                if (enemies[i].enemyBulletY == p1.playerY && enemies[i].enemyBulletX == p1.playerX) {
                    gameOver = true;
                    return;
                }
            }
            enemies[i].enemyX += enemyDirection;
        }
    }
    // Move enemies down if they have reached the edge
    if (enemyReachedEdge) {
        for (int i = 0; i < numOfEnemies; i++) {
            if (enemies[i].isAlive) {
                enemies[i].enemyY++;
            }
        }
    }
}
*/

void moveEnemies(enemy enemies[], player &p1) {
    static int enemyDirection = 1;
    static bool enemyReachedEdge = false;
    for (int i = 0; i < numOfEnemies; i++) {
        if (enemies[i].isAlive) {

            if (enemies[i].enemyX == 0) {
                enemyDirection = 1;
                enemyReachedEdge = true;
            }
            else if (enemies[i].enemyX == WIDTH - 1) {
                enemyDirection = -1;
                enemyReachedEdge = true;
            }
            else {
                enemyReachedEdge = false;
            }
            if (enemies[i].enemyIsFiring == false) {
                srand(time(NULL));
                int chance = rand() % 20;
                if (chance == 0) {
                    enemies[i].enemyIsFiring = true;
                    enemies[i].enemyBulletX = enemies[i].enemyX;
                    enemies[i].enemyBulletY = enemies[i].enemyY + 1;
                }
            }
            if (enemies[i].enemyIsFiring == true) {
                enemies[i].enemyBulletY++;
                if (enemies[i].enemyBulletY == p1.playerY && enemies[i].enemyBulletX == p1.playerX) {
                    gameOver = true;
                }
                else if (enemies[i].enemyBulletY == HEIGHT - 1) {
                    enemies[i].enemyIsFiring = false;
                }
            }
            if (enemies[i].enemyY == p1.playerY) {
                gameOver = true;
            }
        }
    }
    if (enemyReachedEdge) {
        for (int i = 0; i < numOfEnemies; i++) {
            enemies[i].enemyY++;
            enemies[i].enemyX += enemyDirection;
        }
    }
    else {
        for (int i = 0; i < numOfEnemies; i++) {
            enemies[i].enemyX += enemyDirection;
        }
    }
}

void moveBullets(player& p1, enemy enemies[]) {
    if (p1.isFiring) {
        p1.bulletY--;
        if (p1.bulletY <= 0) {
            p1.isFiring = false;
            p1.bulletX = ' ';
        }
        for (int i = 0; i <= numOfEnemies; i++) {
            if (p1.bulletY == enemies[i].enemyY && p1.bulletX == enemies[i].enemyX) {
                p1.isFiring = false;
                enemies[i].enemyX = ' ';
                enemies[i].enemyY = ' ';
                p1.bulletX = ' ';
                p1.bulletY = ' ';
                score += 10;
                enemies[i].isAlive = false;
            }
        }
    }
    for (int i = 0; i <= numOfEnemies; i++) {
        if (enemies[i].enemyIsFiring) {
            enemies[i].enemyBulletY++;
            if (enemies[i].enemyBulletY > HEIGHT) {
                enemies[i].enemyIsFiring = false;
            }
            if (enemies[i].enemyBulletY == p1.playerY && enemies[i].enemyBulletX == p1.playerX) {
                gameOver = true;
                break;
            }
        }
    }
}

int main() {
    srand(time(NULL));
    struct player player1;
    struct enemy enemies[numOfEnemies]{};
    playerInit(player1);
    enemyInit(enemies);
    char input;

    while (!gameOver) {
        moveEnemies(enemies, player1);
        moveBullets(player1, enemies);
        drawBoard(player1, enemies);
        if (_kbhit()) {
            input = _getch();
            movePlayer(input, player1);
        }

        Sleep(100);
    }
    cout << "GAME OVER";
    return 0;
}

/*
void drawBoard(player p1, enemy enemies[]) {
    system("cls");
    for (int i = 0; i < WIDTH + 2; i++) {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) {
                cout << "|";
            }
            if (i == p1.playerY && j == p1.playerX) {
                cout << "A";
            }
            else if (i == p1.bulletY && j == p1.bulletX) {
                cout << "*";
            }
            else {
                bool enemyAlive = false;
                for (int k = 0; k < numOfEnemies; k++) {
                    if (i == enemies[k].enemyY && j == enemies[k].enemyX) {
                        cout << "M";
                        enemyAlive = true;
                        break;
                    }
                    else if (i == enemies[k].enemyBulletY && j == enemies[k].enemyBulletX) {
                        cout << "*";
                        enemyAlive = true;
                        break;
                    }
                }
                if (!enemyAlive) {
                    cout << " ";
                }
            }
            if ((j == WIDTH - 1)) {
                cout << "|";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < WIDTH + 2; i++) {
        cout << "-";
    }
    cout << endl;
    cout << "Score: " << score << endl;
}
*/