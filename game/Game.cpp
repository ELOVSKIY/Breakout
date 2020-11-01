#include "Game.h"

#define BRICK_ROW_COUNT 25
#define BRICK_COLUMN_COUNT 25
#define PLATE_SPEED 25
#define BALL_SPEED 10

void Game::Initialize() {
    this->active = true;
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
    const measure plateTop = height - plateHeight;
    const measure leftPlate = (width / 2) - (plateWidth / 2);
    this->plate = new Plate(leftPlate, plateTop, plateWidth, plateHeight, PLATE_SPEED);
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
    this->hWnd = hwnd;
    this->width = width;
    this->height = height;
    Initialize();
}

void Game::Click() {
    if (active) {
        Vector vector = ball->GetVector();
        Vector availableVector{vector};
        const measure availablePercent = GetAvailableVectorPercent(ball, vector);
        ball->SetVector(vector);
        availableVector.xVector.value = vector.xVector.value * availablePercent;
        availableVector.yVector.value = vector.yVector.value * availablePercent;
        ball->Move(availableVector);
        InvalidateRect(hWnd, NULL, true);
        UpdateWindow(hWnd);

        const float notAvailablePercent = 1 - availablePercent;
        Vector notAvailableVector{vector};
        notAvailableVector.xVector.value = vector.xVector.value * notAvailablePercent;
        notAvailableVector.yVector.value = vector.yVector.value * notAvailablePercent;
        ball->Move(notAvailableVector);
        InvalidateRect(hWnd, NULL, true);
        UpdateWindow(hWnd);
    }
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
                case VK_SPACE:
                    if (!active) {
                        Initialize();
                    }
                    break;
                case VK_ESCAPE:
                    SendMessageA(this->hWnd,WM_DESTROY, 0, 0);
                    break;
                default:
                    vector = {{0, 0},
                              {0, 0}};
                    break;
            }
            if (active) {
                Vector availableVector{vector};
                const measure availableVectorPercent = GetAvailableVectorPercent(plate, vector);
                availableVector.xVector.value = availableVector.xVector.value * availableVectorPercent;
                this->plate->Move(availableVector);
                InvalidateRect(hWnd, NULL, true);
                UpdateWindow(hWnd);
                break;
            }
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
    measure xOffset = 0;
    measure yOffset = 0;

    //TODO откуда считать?
    measure xPos = gameItem->GetLeft() + gameItem->GetWidth() / 2 +
                   (gameItem->GetWidth() / 2 * vector.xVector.direction);
    measure yPos = gameItem->GetTop() + gameItem->GetHeight() / 2 +
                   (gameItem->GetHeight() / 2 * vector.yVector.direction);

    const measure step = GetMinGameItemMeasure() / 2;
    const measure maxSpeedValue = max(vector.xVector.value, vector.yVector.value);
    measure xStep = (vector.xVector.value / maxSpeedValue) * (step * vector.xVector.direction);
    measure yStep = (vector.yVector.value / maxSpeedValue) * (step * vector.yVector.direction);

    bool calculating = true;
    while (calculating) {
        GameItem *nearestGameItem =
                GetNearestGameItem(gameItem, vector, xPos + xOffset, yPos + yOffset);
        if (nearestGameItem != nullptr) {
            const measure gameItemXPos = nearestGameItem->GetLeft() + nearestGameItem->GetWidth() / 2 +
                                         (nearestGameItem->GetWidth() / 2 * (-vector.xVector.direction));
            const measure gameItemYPos = nearestGameItem->GetTop() + nearestGameItem->GetHeight() / 2 +
                                         (nearestGameItem->GetHeight() / 2 * (-vector.yVector.direction));
            const measure xDiff = ABS(gameItemXPos - xPos);
            const measure yDiff = ABS(gameItemYPos - yPos);
            //есть баг думает что от угла отскакивает
            if (xDiff > vector.xVector.value && yDiff > vector.yVector.value) {
                return 1.0;
            } else {
                float availableXPercent = 1.0;
                float availableYPercent = 1.0;
                if (vector.xVector.value != 0) {
                    availableXPercent = (float) xDiff / vector.xVector.value;
                }
                if (vector.yVector.value != 0) {
                    availableYPercent = (float) yDiff / vector.yVector.value;
                }
                const float minPercent = min(availableXPercent, availableYPercent);
                if (minPercent == availableXPercent) {
                    vector.ChangeHorizontalDirection();
                }
                if (minPercent == availableYPercent) {
                    vector.ChangeVerticalDirection();
                }
                if (Brick* brick = dynamic_cast<Brick*>(nearestGameItem)) {
                    bricks->remove(brick);
                    gameItems->remove(brick);
                }
                return min(availableXPercent, availableYPercent);
            }
        }

        float availableXPercent = 1;
        float availableYPercent = 1;
        if (vector.xVector.value != 0) {
            if (xPos + xOffset > width) {
                const measure xDiff = width - xPos;
                availableXPercent = (float) ABS(xDiff / vector.xVector.value);
                vector.ChangeHorizontalDirection();
            }
            if (xPos + xOffset < 0) {
                const measure xDiff = xPos;
                availableXPercent = (float) xDiff / vector.xVector.value;
                vector.ChangeHorizontalDirection();
            }
        }
        if (vector.yVector.value != 0) {
            if (yPos + yOffset > height) {
                GameOver();
                const measure yDiff = height - yPos;
                availableYPercent = (float) yDiff / vector.yVector.value;
                vector.ChangeVerticalDirection();
            }
            if (yPos + yOffset < 0) {
                const measure yDiff = yPos;
                availableYPercent = (float) yDiff / vector.yVector.value;
                vector.ChangeVerticalDirection();
            }
        }
        if ((availableXPercent != 1) || (availableYPercent != 1)) {
            return min(availableXPercent, availableYPercent);
        }
        if (ABS(xOffset) > vector.xVector.value && ABS(yOffset) > vector.yVector.value) {
            return 1.0;
        } else {
            xOffset += xStep;
            yOffset += yStep;
        }
    }
}

GameItem *Game::GetNearestGameItem(const GameItem *movableGameItem,
                                   Vector &vector,
                                   const measure xCenterPos,
                                   const measure yCenterPos) const {
    const measure gameItemHeight = movableGameItem->GetHeight();
    const measure gameItemWidth = movableGameItem->GetWidth();
    const measure edgeXPos = xCenterPos + (gameItemWidth / 2) * vector.xVector.direction;
    const measure edgeYPos = yCenterPos + (gameItemHeight / 2) * vector.yVector.direction;
    for (GameItem * const gameItem : *gameItems) {
        if ((edgeYPos > gameItem->GetTop()) && (edgeYPos < gameItem->GetBottom()) &&
            (edgeXPos > gameItem->GetLeft()) && (edgeXPos < gameItem->GetRight())) {
            return gameItem;
        }
    }
    return nullptr;
}

void Game::GameOver() {
//    this->active = false;
}



