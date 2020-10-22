//
// Created by Helicoptera on 17.10.2020.
//

#include "Game.h"

#define BRICK_ROW_COUNT 15
#define BRICK_COLUMN_COUNT 15
#define PLATE_SPEED = 15;

void Game::Initialize() {

}

Game::Game(int width, int height) {
    this->bricks = new list<Brick *>;
    int brickWidth = width / BRICK_ROW_COUNT;
    int brickHeight = height / BRICK_ROW_COUNT / 2;
    for (int i = 0; i < BRICK_ROW_COUNT; i++) {
        for (int j = 0; j < BRICK_COLUMN_COUNT; j++) {
            auto *brick = new Brick(i * brickWidth, j * brickHeight, brickWidth, brickHeight, j, BRICK_COLUMN_COUNT);
            this->bricks->push_front(brick);
        }

    }
    const int plateHeight = 20;
    const int plateWidth = 400;
    const int plateSpeed = 15;
    const int plateTop = height - plateHeight;
    const int leftPlate = (width / 2) - (plateWidth / 2);
    this->plate = new Plate(leftPlate, plateTop, plateWidth, plateHeight, plateSpeed);
    const int ballDiameter = 40;
    const int leftBall = (width / 2) - (ballDiameter / 2);
    const int topBall = height - plateHeight - ballDiameter;
    this->ball = new Ball(leftBall, topBall, ballDiameter);
}

void Game::Draw(HDC hdc) {
    for (Brick *brick: *this->bricks) {
        brick->Draw(hdc);
    }
    this->plate->Draw(hdc);
    this->plate->Draw(hdc);
}

void Game::GetInput(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_KEYDOWN:
            std::set<Direction> directions;
            if (LOWORD(wParam == VK_RIGHT)) {
              directions.insert(RIGHT);
            }
            this->plate->move(directions);
            break;
    }
}
