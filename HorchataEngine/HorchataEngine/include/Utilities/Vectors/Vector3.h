#pragma once
#include "../Utilities/EngineMath.h"

namespace EngineMath {
  /*
    @brief A 3D vector class for representing points or directions in 3D space.
    @details This class provides basic vector operations such as addition, subtraction,
    scalar multiplication, normalization, and more. It is designed to be used in 3D graphics,
    game development, and physics calculations.
	*/
  class 
    Vector3 {
  public:
    float x;
    float y;
    float z;

    /*
      @brief Default constructor for the Vector3 class.
      @details Initializes the vector to (0, 0, 0).
    */
    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

    /*
      @brief Constructor for the Vector3 class with specified x, y, and z components.
      @param x The x component of the vector.
      @param y The y component of the vector.
      @param z The z component of the vector.
      @details Initializes the vector with the given x, y, and z values.
		*/
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    /*
      @brief Copy constructor for the Vector3 class.
      @param other The vector to copy from.
      @details Initializes the vector with the values from another Vector3 instance.
		*/
    Vector3 
      operator+(const Vector3& other) const {
      return Vector3(x + other.x, y + other.y, z + other.z);
    }

    /*
      @brief Subtraction operator for the Vector3 class.
      @param other The vector to subtract from this vector.
      @return A new Vector3 instance representing the result of the subtraction.
			@details This operator subtracts the components of another vector from this vector.
		*/
    Vector3 
      operator-(const Vector3& other) const {
      return Vector3(x - other.x, y - other.y, z - other.z);
    }

    /*
      @brief Scalar multiplication operator for the Vector3 class.
      @param scalar The scalar value to multiply the vector by.
      @return A new Vector3 instance representing the result of the multiplication.
      @details This operator multiplies both components of the vector by a scalar value.
		*/
    Vector3 
      operator*(float scalar) const {
      return Vector3(x * scalar, y * scalar, z * scalar);
    }

    /*
      @brief Scalar division operator for the Vector3 class.
      @param scalar The scalar value to divide the vector by.
      @return A new Vector3 instance representing the result of the division.
      @details This operator divides both components of the vector by a scalar value.
			If the scalar is zero, it returns a zero vector to avoid division by zero.
		*/
    Vector3 
      operator/(float scalar) const {
      if (scalar != 0.0f) {
        return Vector3(x / scalar, y / scalar, z / scalar);
      }
      return Vector3(0.0f, 0.0f, 0.0f); // Evitar división por cero
    }

    /*
      @brief Scalar multiplication operator for the Vector3 class.
      @param scalar The scalar value to multiply the vector by.
      @return A new Vector3 instance representing the result of the multiplication.
			@details This operator allows scalar multiplication in the form of scalar * vector.
		*/
    friend Vector3 
      operator*(float scalar, const Vector3& vec) {
      return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }

    /*
      @brief Unary negation operator for the Vector3 class.
      @return A new Vector3 instance representing the negated vector.
			@details This operator negates both components of the vector.
		*/
    Vector3 
      operator-() const {
      return Vector3(-x, -y, -z);
    }

    /*
      @brief Compound assignment operator for addition.
      @param other The vector to add to this vector.
      @return A reference to this vector after addition.
      @details This operator adds the components of another vector to this vector.
		*/
    Vector3& 
      operator+=(const Vector3& other) {
      x += other.x;
      y += other.y;
      z += other.z;
      return *this;
    }

    /*
      @brief Compound assignment operator for subtraction.
      @param other The vector to subtract from this vector.
      @return A reference to this vector after subtraction.
			@details This operator subtracts the components of another vector from this vector.
		*/
    Vector3& 
      operator-=(const Vector3& other) {
      x -= other.x;
      y -= other.y;
      z -= other.z;
      return *this;
    }

    /*
      @brief Compound assignment operator for scalar multiplication.
      @param scalar The scalar value to multiply this vector by.
      @return A reference to this vector after multiplication.
			@details This operator multiplies both components of the vector by a scalar value.
		*/
    Vector3& 
      operator*=(float scalar) {
      x *= scalar;
      y *= scalar;
      z *= scalar;
      return *this;
    }

    /*
      @brief Compound assignment operator for scalar division.
      @param scalar The scalar value to divide this vector by.
      @return A reference to this vector after division.
			@details This operator divides both components of the vector by a scalar value.
			If the scalar is zero, it avoids division by zero.
		*/
    Vector3& 
      operator/=(float scalar) {
      if (scalar != 0.0f) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
      }
      return *this; // Evitar división por cero
    }

    /*
      @brief Equality operator for the Vector3 class.
      @param other The vector to compare with this vector.
      @return True if both vectors are equal, false otherwise.
      @details This operator compares the components of two vectors for equality
			with a small tolerance to account for floating-point precision errors.
    */
    bool 
      operator==(const Vector3& other) const {
      const float EPSILON = 1e-6f; // Tolerancia para comparación de punto flotante
      return (fabs(x - other.x) < EPSILON) &&
        (fabs(y - other.y) < EPSILON) &&
        (fabs(z - other.z) < EPSILON);
    }

    /*
      @brief Inequality operator for the Vector3 class.
      @param other The vector to compare with this vector.
      @return True if the vectors are not equal, false otherwise.
      @details This operator checks if two vectors are not equal by negating the equality check.
		*/
    bool 
      operator!=(const Vector3& other) const {
      return !(*this == other);
    }

    /*
      @brief Indexing operator for the Vector3 class.
      @param index The index of the component to access (0 for x, 1 for y, 2 for z).
      @return A reference to the component at the specified index.
      @details This operator allows read and write access to the components of the vector using an index.
      If the index is out of bounds, it defaults to returning x to avoid undefined behavior.
		*/
    float& 
      operator[](int index) {
      if (index == 0) return x;
      if (index == 1) return y;
      if (index == 2) return z;
      
      return x;
    }
    
    /*
      @brief Const indexing operator for the Vector3 class.
      @param index The index of the component to access (0 for x, 1 for y, 2 for z).
      @return A const reference to the component at the specified index.
      @details This operator allows read-only access to the components of the vector using an index.
      If the index is out of bounds, it defaults to returning x to avoid undefined behavior.
		*/
    const float& 
      operator[](int index) const {
      if (index == 0) return x;
      if (index == 1) return y;
      if (index == 2) return z;
      
      return x;
    }

    /*
      @brief Computes the squared length of the vector.
      @return The squared length of the vector.
      @details This method calculates the square of the length of the vector,
      which is useful for comparisons without needing to compute the square root.
		*/
    float 
      lengthSq() const {
      return x * x + y * y + z * z;
    }

    /*
      @brief Computes the length of the vector.
      @return The length of the vector.
      @details This method calculates the Euclidean length of the vector
			using the square root of the squared length.
		*/
    float 
      length() const {
      return sqrt(lengthSq());
    }

    /*
     * @brief Computes the dot product of this vector and another vector.
     * @param other The other vector to compute the dot product with.
     * @return The dot product of the two vectors.
     * @details This method calculates the dot product, which is the sum of the products
     * of the corresponding components of the two vectors.
     */
    float 
      dot(const Vector3& other) const {
      return x * other.x + y * other.y + z * other.z;
    }

    /*
      @brief Computes the cross product of this vector with another vector.
      @param other The other vector to compute the cross product with.
      @return A new Vector3 instance representing the result of the cross product.
      @details This method calculates the cross product, which is a vector that is perpendicular
			to both this vector and the other vector, following the right-hand rule.
		*/
    Vector3 
      cross(const Vector3& other) const {
      return Vector3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
      );
    }

    /*
      @brief Normalizes the vector to unit length.
      @return A new Vector3 instance representing the normalized vector.
      @details This method scales the vector to have a length of 1. If the vector is zero,
			it returns a zero vector to avoid division by zero.
		*/
    Vector3 
      normalized() const {
      float len = length();
      if (len == 0.0f) {
        return Vector3(0.0f, 0.0f, 0.0f);
      }
      return *this / len;
    }

    /*
      @brief Normalizes the vector in place.
      @details This method modifies the vector to have a length of 1. If the vector is zero,
      it does nothing to avoid division by zero.
		*/
    void 
      normalize() {
      float len = length();
      if (len != 0.0f) {
        *this /= len;
      }
    }

    /*
      @brief Computes the distance between two vectors.
      @param a The first vector.
      @param b The second vector.
      @return The distance between the two vectors.
			@details This method calculates the Euclidean distance between two vectors
      using the formula: distance = sqrt((a.x - b.x)^2 + (a.y - b.y)^2 + (a.z - b.z)^2).
		*/
    static float 
      distance(const Vector3& a, const Vector3& b) {
      return (a - b).length();
    }

    /*
      @brief Computes the linear interpolation between two vectors.
      @param a The start vector.
      @param b The end vector.
      @param t The interpolation factor (0.0 to 1.0).
      @return A new Vector3 instance representing the interpolated vector.
      @details This method computes the linear interpolation between two vectors,
      where t = 0 returns vector a and t = 1 returns vector b.
		*/
    static Vector3 
      lerp(const Vector3& a, const Vector3& b, float t) {
      return a + (b - a) * t;
    }

		// Static constants for common vectors
    static const Vector3 Zero() {
			return Vector3(0.0f, 0.0f, 0.0f);
    }

    static const Vector3 One() {
			return Vector3(1.0f, 1.0f, 1.0f);
    }

    static const Vector3 Up() {
			return Vector3(0.0f, 1.0f, 0.0f);
    }     // (0, 1, 0)

    static const Vector3 Down() {
			return Vector3(0.0f, -1.0f, 0.0f);
    }   // (0, -1, 0)

    static const Vector3 Left() {
			return Vector3(-1.0f, 0.0f, 0.0f);
    }   // (-1, 0, 0)

    static const Vector3 Right() {
			return Vector3(1.0f, 0.0f, 0.0f);
    }  // (1, 0, 0)

    static const Vector3 Forward() {
			return Vector3(0.0f, 0.0f, 1.0f);
    }// (0, 0, 1)

    static const Vector3 Back() {
			return Vector3(0.0f, 0.0f, -1.0f);
    }// (0, 0, -1)
  };
}
