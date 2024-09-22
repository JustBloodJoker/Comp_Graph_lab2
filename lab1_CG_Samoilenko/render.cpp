#include "render.h"

render::render()
    : WinWindow(L"Lab1_ComputerGraphicsSamoilenko", 800, 600, false)
{
}

void render::UserAfterD2DInit()
{
    rtv = GetRenderTarget();
    brush = GetBrush();
}

void render::UserD2DLoop()
{
    rtv->Clear(D2D1::ColorF(D2D1::ColorF::White));
    
    
    //drawSurnameBresenham();
    if(drawHandler) drawHandler();

   



}

void render::UserD2DClose()
{
}

void render::ChildKeyPressed(WPARAM param)
{
    if (param == VK_F1) {
        drawHandler = [this]() { drawSurnameDDA(); };
    }
    else if (param == VK_F2) {
        drawHandler = [this]() { drawSurnameWu(); };
    }  
    else if (param == VK_F3) {
        drawHandler = [this]() { drawSurnameBresenham(); };
    }
    else if (param == VK_F4) {
        drawHandler = [this]() {
            brush->SetOpacity(1.0f);
            SetMainBrushColor(D2D1::ColorF::Green);
            DDALine(1, 10, 1, 10);
            SetMainBrushColor(D2D1::ColorF::Blue);
            BresenhamLine(10, 20, 1, 10);

            SetMainBrushColor(D2D1::ColorF::Red);
            BresenhamCircle(20,20,10);
            SetMainBrushColor(D2D1::ColorF::Purple);
            WuLine(20, 30, 1, 10);
           
        };
    }
}

void render::BresenhamLine(int x1, int x2, int y1, int y2)
{
    int dx = abs(x2 - x1);
    int dy = -abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int error = dx + dy;
    while (true) {
        rtv->FillRectangle(pixel(x1, y1), brush);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * error;
        if (e2 >= dy) {
            error += dy;
            x1 += sx;
        }
        if (e2 <= dx) {
            error += dx;
            y1 += sy;
        }
    }
}

void render::BresenhamCircle(int xc, int yc, int r)
{
    int x = r;
    int y = 0;
    int radiusError = 1 - x;
    while (x >= y) {
        rtv->FillRectangle(pixel(xc + x, yc - y), brush);
        rtv->FillRectangle(pixel(xc - x, yc - y), brush);
        rtv->FillRectangle(pixel(xc + y, yc - x), brush);
        rtv->FillRectangle(pixel(xc - y, yc - x), brush);
        if (x != y) {
            rtv->FillRectangle(pixel(xc + y, yc + x), brush);
            rtv->FillRectangle(pixel(xc - y, yc + x), brush);
            rtv->FillRectangle(pixel(xc + x, yc + y), brush);
            rtv->FillRectangle(pixel(xc - x, yc + y), brush);
        }
        y++;
        if (radiusError < 0) {
            radiusError += 2 * y + 1;
        }
        else {
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
}

void render::DDALine(float x1, float x2, float y1, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    int steps = max(abs(dx), abs(dy));
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;
    for (int i = 0; i <= steps; i++) {
        int x = round(x1 + i * xIncrement);
        int y = round(y1 + i * yIncrement);
        rtv->FillRectangle(pixel(x, y), brush);
    }
}

void render::WuLine(int x1, int x2, int y1, int y2)
{
    bool isSteep = abs(y2 - y1) > abs(x2 - x1);
    if (isSteep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }
    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    int dx = x2 - x1;
    int dy = y2 - y1;
    float gradient = static_cast<float>(dy) / static_cast<float>(dx);
    float intery = y1 + gradient;
    for (int x = x1; x <= x2; x++) {
        float intensity1 =(1 - intery + floor(intery));
        float intensity2 =(intery - floor(intery));
        if (isSteep) {
            brush->SetOpacity(intensity1);
            rtv->FillRectangle(pixel(floor(intery), x), brush);
            brush->SetOpacity(intensity2);
            rtv->FillRectangle(pixel(ceil(intery), x), brush);
        }
        else {
            brush->SetOpacity(intensity1);
            rtv->FillRectangle(pixel(x, floor(intery)), brush); 
            brush->SetOpacity(intensity2);
            rtv->FillRectangle(pixel(x, ceil(intery)), brush);
        }
        intery += gradient;
    }
}

void render::drawSurnameBresenham()
{
    brush->SetOpacity(1.0f);
    GetTimer()->Reset();
    GetTimer()->Start();
    // S
    BresenhamLine(2, 20, 2, 2);
    BresenhamLine(2, 2, 2, 10);
    BresenhamLine(2, 20, 10, 10);
    BresenhamLine(20, 20, 10, 20);
    BresenhamLine(2, 20, 20, 20);
    //// A
    BresenhamLine(25, 30, 20, 2);
    BresenhamLine(30, 40, 2, 20);
    BresenhamLine(25, 35, 9, 9);
    //// M
    BresenhamLine(40, 40, 20, 2);
    BresenhamLine(40, 45, 2, 10);
    BresenhamLine(45, 50, 10, 2);
    BresenhamLine(50, 50, 2, 20);
    //// O
    BresenhamCircle(61, 11, 9);
    //// I
    BresenhamLine(73, 73, 20, 2);
    BresenhamLine(71, 75, 2, 2);
    BresenhamLine(71, 75, 20, 20);
    //// L
    BresenhamLine(77, 77, 20, 2);
    BresenhamLine(77, 85, 20, 20);
    //// E
    BresenhamLine(87,87,20,2);
    BresenhamLine(87,93,20,20);
    BresenhamLine(87,93,11,11);
    BresenhamLine(87,93,2,2);
    //// N
    BresenhamLine(95, 95, 2, 20);
    BresenhamLine(95, 103, 2, 20);
    BresenhamLine(103, 103, 2, 20);
    //// K
    BresenhamLine(105, 105, 2, 20);
    BresenhamLine(105, 110, 11,2);
    BresenhamLine(105, 110, 11,20);
    //// O
    BresenhamCircle(120, 11, 9);

    GetTimer()->Stop();

    auto time = GetTimer()->GetTime();
    std::cout << "TIME: " << time << std::endl;
}

void render::drawSurnameDDA()
{
    brush->SetOpacity(1.0f);
    GetTimer()->Reset();
    GetTimer()->Start();
    // S
    DDALine(2, 20, 2, 2);
    DDALine(2, 2, 2, 10);
    DDALine(2, 20, 10, 10);
    DDALine(20, 20, 10, 20);
    DDALine(2, 20, 20, 20);
    //// A
    DDALine(25, 30, 20, 2);
    DDALine(30, 40, 2, 20);
    DDALine(25, 35, 9, 9);
    //// M
    DDALine(40, 40, 20, 2);
    DDALine(40, 45, 2, 10);
    DDALine(45, 50, 10, 2);
    DDALine(50, 50, 2, 20);
    //// O
    DDALine(52, 52, 20, 2);
    DDALine(52, 68, 20, 20);
    DDALine(68, 68, 20, 2);
    DDALine(68, 52, 2, 2);
    //// I
    DDALine(73, 73, 20, 2);
    DDALine(71, 75, 2, 2);
    DDALine(71, 75, 20, 20);
    //// L
    DDALine(77, 77, 20, 2);
    DDALine(77, 85, 20, 20);
    //// E
    DDALine(87, 87, 20, 2);
    DDALine(87, 93, 20, 20);
    DDALine(87, 93, 11, 11);
    DDALine(87, 93, 2, 2);
    //// N
    DDALine(95, 95, 2, 20);
    DDALine(95, 103, 2, 20);
    DDALine(103, 103, 2, 20);
    //// K
    DDALine(105, 105, 2, 20);
    DDALine(105, 110, 11, 2);
    DDALine(105, 110, 11, 20);
    //// O
    DDALine(112, 112, 20, 2);
    DDALine(112, 127, 20, 20);
    DDALine(127, 127, 20, 2);
    DDALine(127, 112, 2, 2);

    GetTimer()->Stop();

    auto time = GetTimer()->GetTime();
    std::cout << "TIME: " << time << std::endl;
}

void render::drawSurnameWu()
{
    brush->SetOpacity(1.0f);
    GetTimer()->Reset();
    GetTimer()->Start();

    // S
    WuLine(2, 20, 2, 2);
    WuLine(2, 2, 2, 10);
    WuLine(2, 20, 10, 10);
    WuLine(20, 20, 10, 20);
    WuLine(2, 20, 20, 20);
    //// A
    WuLine(25, 30, 20, 2);
    WuLine(30, 40, 2, 20);
    WuLine(25, 35, 9, 9);
    //// M
    WuLine(40, 40, 20, 2);
    WuLine(40, 45, 2, 10);
    WuLine(45, 50, 10, 2);
    WuLine(50, 50, 2, 20);
    //// O
    WuLine(52, 52, 20, 2);
    WuLine(52, 68, 20, 20);
    WuLine(68, 68, 20, 2);
    WuLine(68, 52, 2, 2);
    //// I
    WuLine(73, 73, 20, 2);
    WuLine(71, 75, 2, 2);
    WuLine(71, 75, 20, 20);
    //// L
    WuLine(77, 77, 20, 2);
    WuLine(77, 85, 20, 20);
    //// E
    WuLine(87, 87, 20, 2);
    WuLine(87, 93, 20, 20);
    WuLine(87, 93, 11, 11);
    WuLine(87, 93, 2, 2);
    //// N
    WuLine(95, 95, 2, 20);
    WuLine(95, 103, 2, 20);
    WuLine(103, 103, 2, 20);
    //// K
    WuLine(105, 105, 2, 20);
    WuLine(105, 110, 11, 2);
    WuLine(105, 110, 11, 20);
    //// O
    WuLine(112, 112, 20, 2);
    WuLine(112, 127, 20, 20);
    WuLine(127, 127, 20, 2);
    WuLine(127, 112, 2, 2);


    GetTimer()->Stop();

    auto time = GetTimer()->GetTime();
    std::cout << "TIME: " << time << std::endl;
}
