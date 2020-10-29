//
// Created by Helicoptera on 17.10.2020.
//

#ifndef BREAKOUT_GAMEITEM_H
#define BREAKOUT_GAMEITEM_H


#include <Windows.h>

typedef float measure;
#define MEASURE_MAX 100000

typedef struct Border {
    measure top;
    measure right;
    measure bottom;
    measure left;
} Border;

class GameItem {
public:
    virtual void Draw(HDC &hdc);

    GameItem(int left,
             int top,
             int width,
             int height);

    measure GetWidth() const;

    measure GetHeight() const;

    measure GetLeft() const;

    measure GetTop() const;

    measure GetRight() const;

    measure GetBottom() const;

    Border GetBorder() const;

protected:
    void SetLeft(int left);

    void SetTop(int top);

private:
    measure width;
    measure height;
    measure left;
    measure top;
    measure right;
    measure bottom;
};


#endif //BREAKOUT_GAMEITEM_H
