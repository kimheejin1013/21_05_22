#pragma once

#define PI 3.141592f

namespace Collision
{
	bool IsInRect(D2D_RECT_F from, D2D_RECT_F to);
	bool IsInRectPoint(D2D_RECT_F from, POINT to);
	
	bool IsInCirclePoint(float x, float y, D2D1_ELLIPSE circle);
	bool isRectInCircle(D2D_RECT_F rect, D2D1_ELLIPSE circle);
	
	inline float GetDistance(float x, float y, float ex, float ey)
	{
		return sqrtf(pow(x - ex, 2) + pow(y - ey, 2));
	}
	float GetAngle(float x, float y, float ex, float ey);
	float DegreeToRadian(float degree);
	float RadianToDegree(float radian);

}