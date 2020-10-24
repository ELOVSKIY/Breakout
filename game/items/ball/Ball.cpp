#include "Ball.h"
//#include <gdiplus.h>

//using namespace Gdiplus;

void Ball::Draw(HDC &hdc) {
    HBRUSH hbrush = CreateSolidBrush(RGB(140, 50, 200));
    SelectObject(hdc, hbrush);
    Ellipse(hdc, GetLeft(), GetTop(), GetRight(), GetBottom());
    DeleteObject(hbrush);
//
//    Graphics graphics(hdc);
//    Gdiplus::LinearGradientBrush linGrBrush(
//            Point(0, 10),
//            Point(200, 10),
//            Color(255, 255, 0, 0),   // opaque red
//            Color(255, 0, 0, 255));  // opaque blue
//
//    Pen pen(&linGrBrush);
//
//    graphics.DrawLine(&pen, 0, 10, 200, 10);
//    graphics.FillEllipse(&linGrBrush, 0, 30, 200, 100);
//    graphics.FillRectangle(&linGrBrush, 0, 155, 500, 30);

}

Ball::Ball(int left, int top, int radius, int speed) : MovableGameItem(left, top, radius, radius, speed){

}
