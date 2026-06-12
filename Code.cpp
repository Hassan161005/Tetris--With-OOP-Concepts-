#include "raylib.h"
#include <iostream>
#include <cstdlib>   
#include <ctime> 
using namespace std;
const int Board_Width = 10;
const int Board_Height = 20;
const Color blank = { 26,31,40,255 };
const int ipiece[4][4] = { {0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0} };
void RotateMatrix(int Matrix[4][4]) {
    int  temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = Matrix[3 - j][i];
        }
    }
    memcpy(Matrix, temp, sizeof(int) * 4 * 4);
}
class Piece {
public:
    int x = 0, y = 0;
    int shape[4][4] = {};
    Color color = {};
    virtual void rotate() = 0;
    virtual ~Piece() {

    }
    void Draw() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
            {
                if (shape[i][j]) {
                    DrawRectangle((x + j) * 30 + 1, (y + i) * 30 + 1, 30 - 1, 30 - 1, color);
                }
            }
        }
    }
    void Move(int x, int y) {
        this->x += x;
        this->y += y;
    }
};
class Lpiece : public Piece {
public:
    Lpiece() {
        x = 3;
        y = 0;
        color = { 192, 192, 192, 255 };//Silver
        int temp[4][4] = { {0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0} };
        memcpy(shape, temp, sizeof(shape));
    }
    void rotate() { //override function
        RotateMatrix(shape);
    }
};
class Opiece : public Piece {
public:
    Opiece() {
        x = 3;
        y = 0;
        color = { 255, 215,   0, 255 };  // Gold
        int temp[4][4] = { {0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0} };
        memcpy(shape, temp, sizeof(shape));
    }
    void rotate() {

    }
};
class Tpiece : public Piece {
public:
    Tpiece() {
        x = 3;
        y = 0;
        color = { 205, 127,  50, 255 };  // Bronze
        int temp[4][4] = { {0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0} };
        memcpy(shape, temp, sizeof(shape));
    }
    void rotate() {
        RotateMatrix(shape);
    }
};
class Jpiece : public Piece {
public:
    Jpiece() {
        x = 3;
        y = 0;
        color = { 229, 228, 226, 255 };  // Platinum (light silver)
        int temp[4][4] = { {1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0} };
        memcpy(shape, temp, sizeof(shape));
    }
    void rotate() {
        RotateMatrix(shape);
    }
};
class Spiece : public Piece {
public:
    Spiece() {
        x = 3;
        y = 0;
        color = { 80, 200, 120, 255 };  // Emerald green
        int temp[4][4] = { {0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0} };
        memcpy(shape, temp, sizeof(shape));
    }
    void rotate() {
        RotateMatrix(shape);
    }
};
class Zpiece : public Piece {
public:
    Zpiece() {
        x = 3;
        y = 0;
        color = { 224,  17,  95, 255 };  // Ruby red
        int temp[4][4] = { {1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0} };
        memcpy(shape, temp, sizeof(shape));
    }
    void rotate() {
        RotateMatrix(shape);
    }
};
class Ipiece : public Piece {
public:
    Ipiece() {
        x = 3;
        y = 0;
        color = RED;
        int temp[4][4] = { {0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0} };
        memcpy(shape, temp, sizeof(shape));
    }
    void rotate() {
        RotateMatrix(shape);
    }
};
class Board {
public:
    ~Board() {

    }
    Color grid[Board_Height][Board_Width];
    Board() {
        Init();
    }
    void Init() {
        for (int i = 0; i < Board_Height; i++) {
            for (int j = 0; j < Board_Width; j++) {
                grid[i][j] = blank;

            }
        }
    }
    void Draw() {
        for (int i = 0; i < Board_Height; i++) {
            for (int j = 0; j < Board_Width; j++) {
                DrawRectangle((j * 30) + 1, (i * 30) + 1, 30 - 1, 30 - 1, grid[i][j]);
            }
        }
    }
    bool CheckCollision(Piece* p, int dx, int dy) {

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (p->shape[i][j]) {

                    int newX = p->x + j + dx;
                    int newY = p->y + i + dy;


                    if (newX < 0 || newX >= Board_Width || newY > Board_Height)
                        return true;




                    if (!ColorIsEqual(grid[newY][newX], blank)) {


                        return true;
                    }

                }
            }
        }
        return false;
    }

    int LockPiece(Piece* p) {
        int Lx, Ly;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (p->shape[i][j]) {
                    Lx = p->x + j;
                    Ly = p->y + i;
                    grid[Ly][Lx] = p->color;
                }

            }
        }
        return ClearLines();
    }
    int ClearLines() {
        int count = 0;
        for (int i = Board_Height - 1; i >= 0; i--) {
            bool full = true;
            for (int j = 0; j < Board_Width; j++) {
                if (ColorIsEqual(grid[i][j], blank)) {
                    full = false;
                    break;
                }
            }

            if (full) {

                for (int c = i; c > 0; c--) {
                    for (int j = 0; j < Board_Width; j++) {
                        grid[c][j] = grid[c - 1][j];
                    }
                }

                for (int j = 0; j < Board_Width; j++) {
                    grid[0][j] = blank;
                }

                i++;
                count++;
            }
        }
        return count;
    }


};
int main() {
    bool re = true;
    Piece* currentPiece = NULL;
    Piece* nextPiece = NULL;
    while (re)
    {

        bool pause = false;
        Color darkBlue = { 44,44,127,255 };
        int Score = 0;
        InitWindow(700, 620, "Drop 'Til You Pop");
        if (WindowShouldClose()) {
            re = false;
            break;
        }

        SetTargetFPS(60);
        srand(time(0));
        DrawText(TextFormat("Score: %d", Score), 330, 100, 50, WHITE);

        Board board;
        int type = rand() % 7;


        switch (type) {
        case 0: currentPiece = new Ipiece(); break;
        case 1: currentPiece = new Opiece(); break;
        case 2: currentPiece = new Tpiece(); break;
        case 3: currentPiece = new Lpiece(); break;
        case 4: currentPiece = new Jpiece(); break;
        case 5: currentPiece = new Spiece(); break;
        case 6: currentPiece = new Zpiece(); break;
        }
        type = rand() % 7;
        switch (type) {
        case 0: nextPiece = new Ipiece(); break;
        case 1: nextPiece = new Opiece(); break;
        case 2: nextPiece = new Tpiece(); break;
        case 3: nextPiece = new Lpiece(); break;
        case 4: nextPiece = new Jpiece(); break;
        case 5: nextPiece = new Spiece(); break;
        case 6: nextPiece = new Zpiece(); break;
        }
        float timer = 0;
        float fallDelay = 1.0;

        while (!WindowShouldClose()) {
            timer += GetFrameTime();
            if (IsKeyPressed(KEY_P)) {
                pause = true;
            }

            while (pause && !WindowShouldClose()) {
                BeginDrawing();
                ClearBackground(DARKBLUE);

                DrawText("Game Paused", 80, 250, 80, WHITE);
                DrawText("Press P to Resume", 150, 330, 40, WHITE);
                EndDrawing();

                if (IsKeyPressed(KEY_P)) {
                    pause = false;
                }
            }

            if (IsKeyPressed(KEY_LEFT) && !board.CheckCollision(currentPiece, -1, 0))
                currentPiece->Move(-1, 0);

            if (IsKeyPressed(KEY_RIGHT) && !board.CheckCollision(currentPiece, 1, 0))
                currentPiece->Move(1, 0);

            if (IsKeyPressed(KEY_DOWN) && !board.CheckCollision(currentPiece, 0, 1)) {
                currentPiece->Move(0, 1);
            }

            if (IsKeyPressed(KEY_UP)) {
                currentPiece->rotate();

                if (board.CheckCollision(currentPiece, 0, 0)) {

                    currentPiece->rotate();
                    currentPiece->rotate();
                    currentPiece->rotate();
                }
            }
            // gravity
            if (timer >= fallDelay) {

                if (!board.CheckCollision(currentPiece, 0, 1)) {
                    currentPiece->Move(0, 1);
                }

                else {

                    int lines = board.LockPiece(currentPiece);
                    Score += lines * 10;
                    delete currentPiece;
                    currentPiece = nextPiece;
                    nextPiece = nullptr;
                    type = rand() % 7;
                    switch (type) {
                    case 0: nextPiece = new Ipiece(); break;
                    case 1: nextPiece = new Opiece(); break;
                    case 2: nextPiece = new Tpiece(); break;
                    case 3: nextPiece = new Lpiece(); break;
                    case 4: nextPiece = new Jpiece(); break;
                    case 5: nextPiece = new Spiece(); break;
                    case 6: nextPiece = new Zpiece(); break;
                    }
                    if (board.CheckCollision(currentPiece, 0, 0)) {
                        delete currentPiece;
                        delete nextPiece;
                        currentPiece = nullptr;
                        nextPiece = nullptr;
                        re = false;
                        break;

                    }
                }
                timer = 0;
            }

            BeginDrawing();
            ClearBackground(DARKBLUE);
            board.Draw();
            currentPiece->Draw();

            DrawText(TextFormat("Score: %d", Score), 360, 100, 50, WHITE);
            if (nextPiece != nullptr) {
                DrawRectangle(370, 200, 180, 180, blank);
                if (memcmp(nextPiece->shape, ipiece, sizeof(ipiece)) == 0) {
                    for (int i = 0; i < 4; i++)
                        DrawRectangle(400 + i * 30 + 1, 290 + 1, 29, 29, nextPiece->color);
                }
                else {
                    for (int i = 0; i < 2; i++) {
                        for (int j = 0; j < 3; j++) {

                            if (nextPiece->shape[i][j]) {
                                int px = 400 + j * 30 + 1;
                                int py = 260 + i * 30 + 1;
                                DrawRectangle(px, py, 29, 29, nextPiece->color);
                            }
                        }
                    }
                }
            }
            EndDrawing();
        }

        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(DARKBLUE);
            DrawText("Game Over", 90, 110, 100, WHITE);
            DrawText(TextFormat("Score: %d", Score), 210, 300, 50, WHITE);
            DrawText("Press R to restart", 50, 400, 60, WHITE);
            EndDrawing();
            if (IsKeyPressed(KEY_R)) {
                re = true;
                break;
            }
        }
        if (WindowShouldClose()) {
            re = false;
            break;
        }


    }
    if (currentPiece) {
        delete currentPiece;
        currentPiece = nullptr;
    }
    if (nextPiece) {
        delete nextPiece;
        nextPiece = nullptr;
    }
    CloseWindow();
    return 0;
}