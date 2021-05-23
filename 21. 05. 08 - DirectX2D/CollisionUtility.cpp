#include "stdafx.h"
#include "CollisionUtility.h"

namespace Collision {

	bool IsInRect(D2D_RECT_F from, D2D_RECT_F to)
	{
		if ((from.left <= to.right && from.right >= to.left) &&
			(from.top <= to.bottom && from.bottom >= to.top)) {
		
			return true;
		}
			return false;
	}
	bool IsInRectPoint(D2D_RECT_F from, POINT to)
	{
		if ((from.left <= to.x && from.right >= to.x) &&
			from.top <= to.y && from.bottom >= to.y)
			return true;

		return false;
	}
	bool IsInCirclePoint(float x, float y, D2D1_ELLIPSE circle)
	{
		float dx = circle.point.x - x;
		float dy = circle.point.y - y;

		float p = sqrtf(pow(dx, 2) + pow(dy, 2));

		return p<circle.radiusX;
	}
	bool isRectInCircle(D2D_RECT_F rect, D2D1_ELLIPSE circle)
	{
		if ((rect.left <= circle.point.x && rect.right >= circle.point.x) ||
			(rect.top <= circle.point.y && rect.bottom >= circle.point.y))
		{
			D2D_RECT_F temp = {
				rect.left - circle.radiusX,
				rect.top - circle.radiusX,
				rect.right + circle.radiusX,
				rect.bottom + circle.radiusX
			};

			if ((temp.left <= circle.point.x && temp.right >= circle.point.x) &&
				(temp.top <= circle.point.y&&temp.bottom >= circle.point.y))
				return true;
		}

		else
		{
			if (IsInCirclePoint(rect.left, rect.top, circle)) return true;
			if (IsInCirclePoint(rect.left, rect.bottom, circle)) return true;
			if (IsInCirclePoint(rect.right, rect.top, circle)) return true;
			if (IsInCirclePoint(rect.right, rect.bottom, circle)) return true;
		}
		return false;
	}
	float GetAngle(float x, float y, float ex, float ey)
	{
		float dx = ex = x;
		float dy = ey - y;

		float angle = atan2(dy, dx)*(180.0f / PI);
		if (angle < 0.0f)angle += 360.0f;

		return DegreeToRadian(angle);
	}
	float DegreeToRadian(float degree)
	{
		return degree * (PI / 180.0f);
	}
	float RadianToDegree(float radian)
	{
		return radian * (180.0f / PI);
	}
}