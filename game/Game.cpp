#include <thread>
#include "Game.h"

#define BRICK_ROW_COUNT 15
#define BRICK_COLUMN_COUNT 15
#define PLATE_SPEED 15
#define BALL_SPEED 3
#define ACCURACY = 0.01L

void Game::Initialize() {
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
    const measure plateHeight = 20;
    const measure plateWidth = 400;
    const measure plateSpeed = 20;
    const measure plateTop = height - plateHeight;
    const measure leftPlate = (width / 2) - (plateWidth / 2);
    this->plate = new Plate(leftPlate, plateTop, plateWidth, plateHeight, plateSpeed);
    this->gameItems->push_front(plate);
    const measure ballDiameter = 40;
    const measure leftBall = (width / 2) - (ballDiameter / 2);
    const measure topBall = height - plateHeight - ballDiameter;
    this->ball = new Ball(leftBall, topBall, ballDiameter, BALL_SPEED);
    this->gameItems->push_front(ball);
}

Game::Game(const HWND hwnd,
           const int width,
           const int height) {
    this->hWnd = hWnd;
    this->width = width;
    this->height = height;
    Initialize();
}

void Game::Click() {
    Vector vector = ball->GetVector();
    Vector availableVector{vector};
    const measure availablePercent = GetAvailableVectorPercent(ball, vector);
    availableVector.xVector.value = vector.xVector.value * availablePercent;
    availableVector.yVector.value = vector.yVector.value * availablePercent;
    ball->Move(availableVector);
//    if (vector.xVector.value == minValue) {
//        ball->InverseHorizontal();
//    }
//    if (vector.yVector.value == minValue) {
//        ball->InverseVertical();
//    }
    const float notAvailablePercent = 1 - availablePercent;
    Vector notAvailableVector{vector};
    notAvailableVector.xVector.value = vector.xVector.value * notAvailablePercent;
    notAvailableVector.yVector.value = vector.yVector.value * notAvailablePercent;
    ball->Move(notAvailableVector);
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

void Game::GetInput(HWND hWnd,
                    UINT uMsg,
                    WPARAM wParam,
                    LPARAM lParam) {
    switch (uMsg) {
        case WM_KEYDOWN:
            Vector vector;
            const measure plateSpeed = plate->GetSpeed();
            switch (lParam) {
                case VK_RIGHT:
                    vector = {{1, plateSpeed},
                              {0, 0}};
                    break;
                case VK_LEFT:
                    vector = {{-1, plateSpeed},
                              {0,  0}};
                    break;
                default:
                    vector = {{0, 0},
                              {0, 0}};
                    break;
            }
            const measure maxAvailable = GetAvailableVectorPercent(plate, vector);
            vector.xVector.value = min(maxAvailable, vector.xVector.value);
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

float Game::GetAvailableVectorPercent(const GameItem *gameItem,
                                      Vector &vector) {
    measure minDistance = MEASURE_MAX;
    if (vector.yVector.direction < 0) {
        const measure topDistance = gameItem->GetTop();
        if (topDistance < minDistance) {
            minDistance = topDistance;
        }
    }
    if (vector.xVector.direction > 0) {
        const measure rightDistance = width - gameItem->GetRight();
        if (rightDistance < minDistance) {
            minDistance = rightDistance;
        }
    }
    if (vector.xVector.direction < 0) {
        const measure leftDistance = gameItem->GetLeft();
        if (leftDistance < minDistance) {
            minDistance = leftDistance;
        }
    }
    if (vector.yVector.direction > 0) {
        const measure bottomDistance = height - gameItem->GetBottom();
        if (bottomDistance == 0) {
            GameOver();
            return 0.0;
        }
        if (bottomDistance < minDistance) {
            minDistance = bottomDistance;
        }
    }
    return GetAvailableVectorPercent(gameItem, vector, minDistance);
}

float Game::GetAvailableVectorPercent(const GameItem *gameItem,
                                      Vector &vector,
                                      const measure maxAvailableDistance) {
    if (maxAvailableDistance != 0) {
        measure xOffset = 0;
        measure yOffset = 0;

        //TODO откуда считать?
        measure xPos = gameItem->GetLeft() + gameItem->GetWidth() / 2;
        measure yPos = gameItem->GetTop() + gameItem->GetHeight() / 2;

        const measure step = 0.1;//min(GetMinGameItemMeasure() / 2, maxAvailableDistance);
        const measure maxSpeedValue = max(vector.xVector.value, vector.yVector.value);
        measure xStep = (vector.xVector.value / maxSpeedValue) * step;
        measure yStep = (vector.yVector.value / maxSpeedValue) * step;

        GameItem *nearestGameItem = GetNearestGameItem(gameItem, vector, xPos, yPos);
        while ((nearestGameItem == nullptr) &&
               (xOffset < maxAvailableDistance && xOffset < vector.xVector.value) &&
               (yOffset < maxAvailableDistance && yOffset < vector.yVector.value)) {
            if (xOffset + xStep >= maxAvailableDistance) {
                const measure coefficient = (maxAvailableDistance - xOffset) / xStep;
                xStep = xStep * coefficient;
                yStep = yStep * coefficient;
            }
            if (yOffset + yStep >= maxAvailableDistance) {
                const measure coefficient = (maxAvailableDistance - yOffset) / yStep;
                xStep = xStep * coefficient;
                yStep = yStep * coefficient;
            }
            xOffset += xStep;
            yOffset += yStep;
            xPos = gameItem->GetLeft() + (xOffset * vector.xVector.direction);
            yPos = gameItem->GetTop() + (yOffset * vector.yVector.direction);
            nearestGameItem = GetNearestGameItem(gameItem, vector, xPos, yPos);
        }
        if (vector.xVector.direction != 0) {
            return (float) xOffset / (float) vector.xVector.value;
        }
        if (vector.yVector.direction != 0) {
            return (float) yOffset / (float) vector.yVector.value;
        }
        return 0.0;
    } else {
        return 0.0;
    }
}

//TODO разобраться с константами в функциях
GameItem *Game::GetNearestGameItem(const GameItem *gameItem,
                                   Vector &vector,
                                   const measure xCenterPos,
                                   const measure yCenterPos) const {
    const measure gameItemHeight = gameItem->GetHeight();
    const measure gameItemWidth = gameItem->GetWidth();
    const measure edgeXPos = xCenterPos + (gameItemWidth / 2) * vector.xVector.direction;
    const measure edgeYPos = yCenterPos + (gameItemHeight / 2) * vector.yVector.direction;
    for (GameItem *gameItem : *gameItems) {
        if ((edgeYPos > gameItem->GetTop()) && (edgeYPos < gameItem->GetBottom()) &&
            (edgeXPos > gameItem->GetLeft()) && (edgeXPos < gameItem->GetRight())) {
            const measure minVerticalDiff =
                    min(
                            abs(gameItem->GetTop() - edgeYPos),
                            abs(gameItem->GetBottom() - edgeYPos));
            const measure minHorizontalDiff =
                    min(
                            abs(gameItem->GetLeft() - edgeXPos),
                            abs(gameItem->GetRight() - edgeXPos));
            const measure minDiff = min(minHorizontalDiff, minVerticalDiff);
            if (minDiff == minVerticalDiff) {
                vector.ChangeVerticalDirection();
            }
            if (minDiff == minHorizontalDiff) {
                vector.ChangeVerticalDirection();
            }
            return gameItem;
        }
    }
    return nullptr;
}

void Game::GameOver() {

}



