#include <thread>
#include "Game.h"

#define BRICK_ROW_COUNT 15
#define BRICK_COLUMN_COUNT 15
#define PLATE_SPEED 15
#define BALL_SPEED 15

Game::Game(const HWND hwnd,
           const int width,
           const int height) {
    this->hWnd = hWnd;
    this->width = width;
    this->height = height;

    //
    this->bricks = new list<Brick *>;
    this->gameItems = new list<GameItem *>;
    int brickWidth = width / BRICK_ROW_COUNT;
    int brickHeight = height / BRICK_ROW_COUNT / 2;
    for (int i = 0; i < BRICK_ROW_COUNT; i++) {
        for (int j = 0; j < BRICK_COLUMN_COUNT; j++) {
            auto *brick = new Brick(i * brickWidth, j * brickHeight, brickWidth, brickHeight, j, BRICK_COLUMN_COUNT);
            this->bricks->push_front(brick);
            gameItems->push_front(brick);
        }

    }
    const int plateHeight = 20;
    const int plateWidth = 400;
    const int plateSpeed = 20;
    const int plateTop = height - plateHeight;
    const int leftPlate = (width / 2) - (plateWidth / 2);
    this->plate = new Plate(leftPlate, plateTop, plateWidth, plateHeight, plateSpeed);
    this->gameItems->push_front(plate);
    const int ballDiameter = 40;
    const int leftBall = (width / 2) - (ballDiameter / 2);
    const int topBall = height - plateHeight - ballDiameter;
    this->ball = new Ball(leftBall, topBall, ballDiameter, BALL_SPEED);
    this->gameItems->push_front(ball);

//    std::thread thread(&Game::Click, this);
}

void Game::Click() {
//    while (active) {
//        Sleep(1000 / 60);
//        const measure ballSpeed = 1;
//        const Vector vector = {{1, ballSpeed}, {1, 0}};
//        this->ball->Move(vector);
//        InvalidateRect(hWnd, NULL, true);
//        UpdateWindow(hWnd);
//    }
}

void Game::Draw(HWND hWnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    HDC memHdc = CreateCompatibleDC(hdc);
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);

    HBITMAP bmp = CreateCompatibleBitmap(hdc, clientRect.right, clientRect.bottom);
    HBITMAP oldBmp = (HBITMAP) SelectObject(memHdc, bmp);

    HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 0));
    FillRect(memHdc, &ps.rcPaint, hbrush);


    for (Brick *brick: *this->bricks) {
        brick->Draw(memHdc);
    }
    this->plate->Draw(memHdc);
    this->ball->Draw(memHdc);

    BitBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, memHdc, 0, 0, SRCCOPY);
    SelectObject(hdc, oldBmp);
    DeleteObject(bmp);
    DeleteDC(memHdc);

    EndPaint(hWnd, &ps);
}

void Game::GetInput(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_KEYDOWN:
            Vector vector;
            const measure plateSpeed = plate->GetSpeed();
            switch (lParam) {
                case VK_RIGHT:
                    vector = {{1, plateSpeed}, {1, 0}};
                    break;
                case VK_LEFT:
                    vector  = {{-1, plateSpeed}, {1, 0}};
                    break;
                case VK_UP:
                    vector = {{1, 0}, {-1, plateSpeed}};
                    break;
                case VK_DOWN:
                    vector = {{1, 0}, {1, plateSpeed}};
                    break;
            }
            this->plate->Move(vector);
            InvalidateRect(hWnd, NULL, true);
            UpdateWindow(hWnd);
            break;
    }

}

measure Game::GetMinGameItemMeasure() {
    int minMeasure = INT_MAX;
    for (const GameItem *gameItem : *gameItems) {
        const int gameItemWidth = gameItem->GetWidth();
        const int gameItemHeight = gameItem->GetHeight();
        if (gameItemWidth < minMeasure) {
            minMeasure = gameItemWidth;
        }
        if (gameItemHeight < minMeasure) {
            minMeasure = gameItemHeight;
        }
    }
    return minMeasure;
}

measure Game::GetMaxAvailableDistance(const GameItem *gameItem,
                                      const Vector vector) {
    measure minDistance = MEASURE_MAX;
    if (vector.yVector.direction == POSITIVE) {
        const measure topDistance = gameItem->GetTop();
        if (topDistance < minDistance) {
            minDistance = topDistance;
        }
    } else {
        const measure bottomDistance = height - gameItem->GetBottom();
        if (bottomDistance < minDistance) {
            minDistance = bottomDistance;
        }
    }
    if (vector.xVector.direction == POSITIVE) {
        const measure rightDistance = width - gameItem->GetRight();
        if (rightDistance < minDistance) {
            minDistance = rightDistance;
        }
    } else {
        const measure leftDistance = gameItem->GetLeft();
        if (leftDistance < minDistance) {
            minDistance = leftDistance;
        }
    }
    if (vector.xVector.value < minDistance) {
        minDistance = vector.xVector.value;
    }
    if (vector.yVector.value < minDistance) {
        minDistance = vector.yVector.value;
    }
    return GetMaxAvailableDistance(gameItem, vector, minDistance);
}

measure Game::GetMaxAvailableDistance(const GameItem *gameItem,
                                      const Vector vector,
                                      const measure maxAvailableDistance) {
    measure xOffset = 0;
    measure yOffset = 0;
    //TODO откуда считать?
    measure xPos = gameItem->GetLeft();
    measure yPos = gameItem->GetTop();
    const measure step = GetMinGameItemMeasure() / 2;
    const measure maxSpeedValue = max(vector.xVector.value, vector.yVector.value);
    const measure xStep = (vector.xVector.value / maxSpeedValue) * step;
    const measure yStep = (vector.yVector.value / maxSpeedValue) * step;
    while (!IsBetweenHorizontalEdge(yPos) &&
           !IsBetweenVerticalEdge(xPos) &&
           xOffset + xStep < maxAvailableDistance &&
           yOffset + yStep < maxAvailableDistance) {
        xOffset += xStep;
        yOffset += yStep;
        xPos = gameItem->GetLeft() + (xOffset * vector.xVector.direction);
        yPos = gameItem->GetTop() + (yOffset * vector.yVector.direction);
    }
    return min(xOffset, yOffset);
}

bool Game::IsBetweenHorizontalEdge(const measure yPos) {
    for (const GameItem *gameItem : *gameItems) {
        if ((yPos > gameItem->GetTop()) && (yPos < gameItem->GetBottom())) {
            return true;
        }
    }
    return false;
}

bool Game::IsBetweenVerticalEdge(const measure xPos) {
    for (const GameItem *gameItem : *gameItems) {
        if ((xPos > gameItem->GetLeft()) && (xPos < gameItem->GetRight())) {
            return true;
        }
    }
    return false;
}


