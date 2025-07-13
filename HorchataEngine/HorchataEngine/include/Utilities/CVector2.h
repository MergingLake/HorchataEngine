#pragma once

#include <cmath>

class 
	CVector2 {
public:
	float x;
	float y;

	CVector2() : x(0.0f), y(0.0f) {}
	CVector2(float x, float y) : x(x), y(y) {}

	CVector2 operator+(const CVector2& other) const {
		return CVector2(x + other.x, y + other.y);
	}
	
	CVector2 operator-(const CVector2& other) const {
		return CVector2(x - other.x, y - other.y);
	}
	
	CVector2 operator*(float scalar) const {
		return CVector2(x * scalar, y * scalar);
	}

	CVector2 operator/(float scalar) const {
		if (scalar != 0.0f) {
			return CVector2(x / scalar, y / scalar);
		}
		return CVector2(0.0f, 0.0f); // Avoid division by zero
	}

	friend CVector2 operator*(float scalar, const CVector2& vec) {
		return CVector2(vec.x * scalar, vec.y * scalar);
	}

	CVector2 operator-() const {
		return CVector2(-x, -y);
	}

	CVector2& operator+=(const CVector2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	CVector2& operator-=(const CVector2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	CVector2& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	CVector2& operator/=(float scalar) {
		if (scalar != 0.0f) {
			x /= scalar;
			y /= scalar;
		}
		return *this; // Avoid division by zero
	}

	bool operator==(const CVector2& other) const {
		const float EPSILON = 1e-6f; // Tolerance for floating-point comparison
		return (std::fabs(x - other.x) < EPSILON) && (std::fabs(y - other.y) < EPSILON);
	}

	bool operator!=(const CVector2& other) const {
		return !(*this == other);
	}

	float& operator[](int index) {
		if (index == 0) return x;
		if (index == 1) return y;

		return x; // Default return to avoid undefined behavior
	}

	const float& operator[](int index) const {
		if (index == 0) return x;
		if (index == 1) return y;
		return x; // Default return to avoid undefined behavior
	}

	float lengthSq() const {
		return x * x + y * y;
	}

	float length() const {
		return std::sqrt(lengthSq());
	}

	float dot(const CVector2& other) const {
		return x * other.x + y * other.y;
	}

	float cross(const CVector2& other) const {
		return x * other.y - y * other.x;
	}

	CVector2 normalized() const {
		float len = length();
		if (len == 0.0f) {
			return CVector2(0.0f, 0.0f);
		}
		return *this / len;
	}

	void normalize() {
		float len = length();
		if (len != 0.0f) {
			*this /= len;
		}
	}

	static float distance(const CVector2& a, const CVector2& b) {
		return (a - b).length();
	}

	static CVector2 lerp(const CVector2& a, const CVector2& b, float t) {
		return a + (b - a) * t;
	}

	static const CVector2 Zero;

	static const CVector2 One;
};

const CVector2 CVector2::Zero(0.0f, 0.0f);
const CVector2 CVector2::One(1.0f, 1.0f);