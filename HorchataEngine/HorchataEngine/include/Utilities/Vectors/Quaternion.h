#pragma once
#include "../Utilities/EngineMath.h"
#include "Vector3.h"

namespace EngineMath {
	/*
		@brief A quaternion class for representing rotations in 3D space.
		@details This class provides basic quaternion operations such as addition, subtraction,
		scalar multiplication, normalization, and more. It is designed to be used in 3D graphics,
		game development, and physics calculations.
	*/
	class Quaternion {
	public:
		float w;
		float x;
		float y;
		float z;

		/*
			@brief Default constructor for the Quaternion class.
			@details Initializes the quaternion to (1, 0, 0, 0), representing no rotation.
		*/
		Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}

		/*
			@brief Constructor for the Quaternion class with specified components.
			@param w The scalar component of the quaternion.
			@param x The x component of the quaternion.
			@param y The y component of the quaternion.
			@param z The z component of the quaternion.
			@details Initializes the quaternion with the given components.
		*/
		Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

		/*
			@brief Copy constructor for the Quaternion class.
			@param other The quaternion to copy from.
			@details Initializes the quaternion with the values from another Quaternion instance.
		*/
		Quaternion(const Vector3& axis, float angle) {
			float halfAngle = angle * 0.5f;
			float s = sin(halfAngle);
			w = cos(halfAngle);
			x = axis.x * s;
			y = axis.y * s;
			z = axis.z * s;
			normalize();
		}

		/*
			@brief addition operator for the Quaternion class.
			@param other The quaternion to add to this quaternion.
			@return A new Quaternion instance representing the result of the addition.
			@details This operator adds the components of another quaternion to this quaternion.
		*/
		Quaternion 
			operator+(const Quaternion& other) const {
			return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
		}

		/*
			@brief Subtraction operator for the Quaternion class.
			@param other The quaternion to subtract from this quaternion.
			@return A new Quaternion instance representing the result of the subtraction.
			@details This operator subtracts the components of another quaternion from this quaternion.
		*/
		Quaternion 
			operator-(const Quaternion& other) const {
			return Quaternion(w - other.w, x - other.x, y - other.y, z - other.z);
		}

		/*
			@brief Scalar multiplication operator for the Quaternion class.
			@param scalar The scalar value to multiply the quaternion by.
			@return A new Quaternion instance representing the result of the multiplication.
			@details This operator multiplies all components of the quaternion by a scalar value.
		*/
		Quaternion 
			operator*(float scalar) const {
			return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
		}

		/*
			@brief Scalar division operator for the Quaternion class.
			@param scalar The scalar value to divide the quaternion by.
			@return A new Quaternion instance representing the result of the division.
			@details This operator divides all components of the quaternion by a scalar value.
			If the scalar is zero, it returns a zero quaternion to avoid division by zero.
		*/
		Quaternion 
			operator/(float scalar) const {
			if (scalar != 0.0f) {
				return Quaternion(w / scalar, x / scalar, y / scalar, z / scalar);
			}
			return Quaternion(0.0f, 0.0f, 0.0f, 0.0f); // Avoid division by zero
		}

		/*
			@brief Quaternion multiplication operator.
			@param other The quaternion to multiply with this quaternion.
			@return A new Quaternion instance representing the result of the multiplication.
			@details This operator performs quaternion multiplication, which is not commutative.
		*/
		Quaternion 
			operator*(const Quaternion& other) const {
			return Quaternion(
				w * other.w - x * other.x - y * other.y - z * other.z,
				w * other.x + x * other.w + y * other.z - z * other.y,
				w * other.y - x * other.z + y * other.w + z * other.x,
				w * other.z + x * other.y - y * other.x + z * other.w
			);
		}

		/*
			@brief rotate a vector using the quaternion.
			@param vector The vector to rotate.
			@return A new Vector3 instance representing the rotated vector.
			@details This method applies the quaternion rotation to a 3D vector.
		*/
		Vector3 
			rotate(const Vector3& vector) const {
			Quaternion vectorQuat(0.0f, vector.x, vector.y, vector.z);
			Quaternion conjugate = this->conjugate();
			Quaternion result = (*this * vectorQuat) * conjugate;
			return Vector3(result.x, result.y, result.z);
		}

		/*
			@brief operator for indexing the quaternion components.
			@param index The index of the component to access (0 for w, 1 for x, 2 for y, 3 for z).
			@return A reference to the component at the specified index.
			@details This operator allows access to the components of the quaternion using an index.
		*/
		Quaternion& 
			operator+=(const Quaternion& other) {
			w += other.w; x += other.x; y += other.y; z += other.z;
			return *this;
		}

		/*
			@brief operator for subtracting another quaternion from this quaternion.
			@param other The quaternion to subtract from this quaternion.
			@return A reference to this quaternion after subtraction.
			@details This operator subtracts the components of another quaternion from this quaternion.
		*/
		Quaternion& 
			operator-=(const Quaternion& other) {
			w -= other.w; x -= other.x; y -= other.y; z -= other.z;
			return *this;
		}

		/*
			@brief operator for scalar multiplication.
			@param scalar The scalar value to multiply this quaternion by.
			@return A reference to this quaternion after multiplication.
			@details This operator multiplies all components of the quaternion by a scalar value.
		*/
		Quaternion& 
			operator*=(float scalar) {
			w *= scalar; x *= scalar; y *= scalar; z *= scalar;
			return *this;
		}

		/*
			@brief operator for scalar division.
			@param scalar The scalar value to divide this quaternion by.
			@return A reference to this quaternion after division.
			@details This operator divides all components of the quaternion by a scalar value.
			If the scalar is zero, it avoids division by zero.
		*/
		Quaternion& 
			operator/=(float scalar) {
			if (scalar != 0.0f) {
				w /= scalar; x /= scalar; y /= scalar; z /= scalar;
			}
			return *this; // Avoid division by zero
		}

		/*
			@brief operator for quaternion multiplication.
			@param other The quaternion to multiply with this quaternion.
			@return A reference to this quaternion after multiplication.
			@details This operator performs quaternion multiplication, which is not commutative.
		*/
		Quaternion& 
			operator*=(const Quaternion& other) {
			*this = *this * other;
			return *this;
		}

		/*
			@brief operator for equality comparison.
			@param other The quaternion to compare with this quaternion.
			@return True if the quaternions are equal, false otherwise.
			@details This operator checks if all components of the quaternions are equal within a small tolerance.
		*/
		bool 
			operator==(const Quaternion& other) const {
			const float EPSILON = 1e-6f; // Tolerance for floating-point comparison
			return (fabs(w - other.w) < EPSILON) &&
						 (fabs(x - other.x) < EPSILON) &&
						 (fabs(y - other.y) < EPSILON) &&
						 (fabs(z - other.z) < EPSILON);
		}

		/*
			@brief operator for inequality comparison.
			@param other The quaternion to compare with this quaternion.
			@return True if the quaternions are not equal, false otherwise.
			@details This operator checks if the quaternions are not equal by negating the equality check.
		*/
		bool 
			operator!=(const Quaternion& other) const {
			return !(*this == other);
		}

		/*
			@brief Calculates the squared length of the quaternion.
			@return The squared length of the quaternion.
		*/
		float 
			lengthSq() const {
			return w * w + x * x + y * y + z * z;
		}

		/*
			@brief Calculates the length of the quaternion.
			@return The length of the quaternion.
			@details This method calculates the Euclidean length of the quaternion
			using the square root of the squared length.
		*/
		float 
			length() const {
			return sqrt(lengthSq());
		}

		/*
			@brief Normalizes the quaternion to unit length.
			@return A new Quaternion instance representing the normalized quaternion.
			@details This method scales the quaternion to have a length of 1. If the quaternion is zero,
			it returns a zero quaternion to avoid division by zero.
		*/
		void 
			normalize() {
			float len = length();
			if (len != 0.0f && len != 1.0f) {
				*this /= len; // Scale the quaternion to unit length
			}
		}

		/*
			@brief Returns a normalized version of the quaternion.
			@return A new Quaternion instance representing the normalized quaternion.
			@details This method scales the quaternion to have a length of 1. If the quaternion is zero,
			it returns a zero quaternion to avoid division by zero.
		*/
		Quaternion 
			normalized() const {
			float len = length();
			if (len == 0.0f) {
				return Quaternion(0.0f, 0.0f, 0.0f, 0.0f); // Return zero quaternion to avoid division by zero
			}
			return *this / len; // Return a normalized quaternion
		}

		/*
			@brief Computes the conjugate of the quaternion.
			@return A new Quaternion instance representing the conjugate of this quaternion.
			@details The conjugate of a quaternion is obtained by negating the vector part (x, y, z).
		*/
		Quaternion 
			conjugate() const {
			return Quaternion(w, -x, -y, -z);
		}

		/*
			@brief Computes the inverse of the quaternion.
			@return A new Quaternion instance representing the inverse of this quaternion.
			@details The inverse of a quaternion is its conjugate divided by its squared length.
			If the length is zero, it returns a zero quaternion to avoid division by zero.
		*/
		Quaternion 
			inverse() const {
			float lenSq = lengthSq();
			if (lenSq == 0.0f) {
				return Quaternion(0.0f, 0.0f, 0.0f, 0.0f); // Avoid division by zero
			}
			return conjugate() / lenSq; // Return the conjugate divided by the squared length
		}

		/*
			@brief Computes the dot product of this quaternion with another quaternion.
			@param other The other quaternion to compute the dot product with.
			@return The dot product of the two quaternions.
		*/
		float 
			dot(const Quaternion& other) const {
			return w * other.w + x * other.x + y * other.y + z * other.z;
		}

		/*
			@brief Creates a quaternion from an axis and an angle.
			@param axis The axis of rotation as a Vector3.
			@param angle The angle of rotation in radians.
			@return A new Quaternion instance representing the rotation.
			@details This method constructs a quaternion from an axis-angle representation,
			where the axis is normalized and the angle is converted to radians.
		*/
		static Quaternion 
			fromAxisAngle(const Vector3& axis, float angle) {
			float halfAngle = angle * 0.5f;
			float s = sin(halfAngle);
			return Quaternion(cos(halfAngle), axis.x * s, axis.y * s, axis.z * s);
		}

		/*
			@brief Returns a pointer to the quaternion data.
			@return A pointer to the quaternion data as an array of floats.
			@details This method provides access to the quaternion components as a float array,
			allowing for easy manipulation and access to the underlying data.
		*/
		const float* 
			data() const {
			return &w; // Return a pointer to the quaternion data
		}
	};
} // namespace EngineMath