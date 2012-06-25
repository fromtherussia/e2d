#ifndef CGL_RECT_H
#define CGL_RECT_H

#include "Types.h"

namespace RectResizeDirection {
	enum Direction {
		Center = 0,
		Left = 1,
		Right = 2
	};
};

// TODO: add Rect(const vec4&) ctor or kinda that
template <class vec2type>
class RectTy {
	typedef typename vec2type::value_type choordType;
public:
	choordType x1;
	choordType y1;
	choordType x2;
	choordType y2;
	RectTy():x1(0),x2(0),y1(0),y2(0) {}
	RectTy(choordType _x1, choordType _y1, choordType _x2, choordType _y2):x1(_x1),x2(_x2),y1(_y1),y2(_y2) {}
	RectTy(const vec2type &v1, const vec2type &v2):x1(v1.x),x2(v2.x),y1(v1.y),y2(v2.y) {}
	RectTy(const RectTy &r):x1(r.x1),x2(r.x2),y1(r.y1),y2(r.y2) {}
	
	// �������������� ����� ��������������
	vec2type Center(void) const {
		return vec2type((x2 + x1) * 0.5f, (y2 + y1) * 0.5f);
	}
	
	// ��������, ��������� �� ����� ������ ��������������
	bool IsIntersects(const vec2type& v) const {
		return v.x <= x2 && v.x >= x1 && v.y <= y2 && v.y >= y1;
	}
	
	// ������������
	RectTy& operator =(const RectTy& r) {
		x1 = r.x1;
		y1 = r.y1;
		x2 = r.x2;
		y2 = r.y2;
		return *this;
	}

	// ������������
	RectTy& operator *=(const choordType& v) {
		x1 *= v;
		y1 *= v;
		x2 *= v;
		y2 *= v;
		return *this;
	}

	// ������������
	RectTy& operator /=(const choordType& v) {
		if (v == 0) {
			throw std::logic_error("");
		}
		x1 /= v;
		y1 /= v;
		x2 /= v;
		y2 /= v;
		return *this;
	}

	// ��������
	RectTy& operator +=(const vec2type& v) {
		x1 += v.x;
		y1 += v.y;
		x2 += v.x;
		y2 += v.y;
		return *this;
	}

	// ��������
	RectTy& operator -=(const vec2type& v) {
		x1 += v.x;
		y1 += v.y;
		x2 += v.x;
		y2 += v.y;
		return *this;
	}

	// ����������
	void Resize(const vec2type& v, RectResizeDirection::Direction xrd = RectResizeDirection::Center, RectResizeDirection::Direction yrd = RectResizeDirection::Center) {
		switch (xrd) {
			case RectResizeDirection::Left:
				x1 -= v.x;
				break;
			case RectResizeDirection::Right:
				x2 += v.x;
				break;
			case RectResizeDirection::Center:
				x1 -= v.x * 0.5f;
				x2 += v.x * 0.5f;
				break;
		}
		switch (yrd) {
			case RectResizeDirection::Left:
				y1 -= v.y;
				break;
			case RectResizeDirection::Right:
				y2 += v.y;
				break;
			case RectResizeDirection::Center:
				y1 -= v.y * 0.5f;
				y2 += v.y * 0.5f;
				break;
		}
	}

	// ������ ��������������
	choordType Width(void) const {
		return abs(x2 - x1);
	}

	// ������ ��������������
	choordType Height(void) const {
		return abs(y2 - y1);
	}	

	// �������� ��������������
	RectTy operator +(const vec2type& v) const {
		return RectTy(x1 + v.x, y1 + v.y, x2 + v.x, y2 + v.y);
	}

	// �������� ��������������
	RectTy operator -(const vec2type& v) const {
		return RectTy(x1 - v.x, y1 - v.y, x2 - v.x, y2 - v.y);
	}

	// ��������, ��� ���������� ������ ������� ���� ����� � ���� ������� ��������
	bool Validate() const {
		return x2 >= x1 && y2 >= y1;
	}

	// ��� �� ���������� �������������
	bool IsPositive() const {
		return x1 >= 0 && y1 >= 0 && x2 >= 0 && y2 >= 0;
	}

	// ���������� ������ ������� �����
	vec2type LeftBottomCorner() const {
		return vec2type(x1, y1);
	}

	// ���������� ������� �������� �����
	vec2type RightTopCorner() const {
		return vec2type(x2, y2);
	}

	// ���������� ������ �������� �����
	vec2type LeftTopCorner() const {
		return vec2type(x1, y2);
	}

	// ���������� ������� ������� �����
	vec2type RightBottomCorner() const {
		return vec2type(x2, y1);
	}

	// ���������� ������ ������� �����
	vec2type BottomEdgeCenter() const {
		return vec2type((x1 + x2) * 0.5f, y1);
	}

	// ���������� ������ �������� �����
	vec2type TopEdgeCenter() const {
		return vec2type((x1 + x2) * 0.5f, y2);
	}

	// ���������� ������ ������ �����
	vec2type LeftEdgeCenter() const {
		return vec2type(x1, (y1 + y2) * 0.5f);
	}

	// ���������� ������ ������� �����
	vec2type RightEdgeCenter() const {
		return vec2type(x2, (y1 + y2) * 0.5f);
	}

	// ��������� ������������ ���������, ����� ����������� ������� x1 <= x2, y1 <= y2
	void Normalize() {
		float tx1 = x1;
		float ty1 = y1;
		x1 = glm::min(x1, x2);
		y1 = glm::min(y1, y2);
		x2 = glm::max(tx1, x2);
		y2 = glm::max(ty1, y2);
	}
};

typedef RectTy<ivec2> RectI;
typedef RectTy<vec2> Rect;

#endif