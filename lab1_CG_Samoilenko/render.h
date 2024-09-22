#pragma once
#define _DISABLE_FDW_MACROSES
#include <D2DFWStandalone.h>

#define size 5

struct pixel : public D2D1_RECT_F {
	pixel(int x, int y) {
		x *= size;
		y *= size;
		left = x; 
		right = x + size;
		top = y;
		bottom = y + size;
	}
};

class render :
	public FD2DW::D2DFWStandalone
{
public:
	render();
	virtual ~render() = default;

public:
	virtual void UserAfterD2DInit() override;
	virtual void UserD2DLoop() override;
	virtual void UserD2DClose() override;
	virtual void ChildKeyPressed(WPARAM) override;
public:
	//Bresenham
	void BresenhamLine(int x1, int x2, int y1, int y2);
	void BresenhamCircle(int xc, int yc, int r);
	//DDA
	void DDALine(float x1, float x2, float y1, float y2);
	//Wu
	void WuLine(int x1, int x2, int y1, int y2);

	void drawSurnameBresenham();
	void drawSurnameDDA();
	void drawSurnameWu();
protected:
	ID2D1HwndRenderTarget* rtv;
	ID2D1SolidColorBrush* brush;

	std::function<void(void)> drawHandler;

};

