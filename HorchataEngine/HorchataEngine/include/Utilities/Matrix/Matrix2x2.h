#pragma once
#include "../Utilities/EngineMath.h"
#include "../Vectors/Vector2.h"

namespace EngineMath {
  /*
    @brief A 2x2 matrix class for representing linear transformations in 2D space.
    @details This class provides basic matrix operations such as multiplication, scaling,
    rotation, and more. It is designed to be used in 2D graphics, game development, and physics calculations.
	*/
  class Matrix2x2 {
  public:
    float m[4];

    /*
      @brief Default constructor for the Matrix2x2 class.
      @details Initializes the matrix to the identity matrix.
		*/
    Matrix2x2() {
      m[0] = 1.0f; m[1] = 0.0f;
      m[2] = 0.0f; m[3] = 1.0f;
    }

    /*
      @brief Constructor for the Matrix2x2 class with specified elements.
      @param m00 The element at row 0, column 0.
      @param m01 The element at row 0, column 1.
      @param m10 The element at row 1, column 0.
      @param m11 The element at row 1, column 1.
			@details Initializes the matrix with the given values.
		*/
    Matrix2x2(float m00, float m01, float m10, float m11) {
      m[0] = m00; m[1] = m01;
      m[2] = m10; m[3] = m11;
    }

    /*
      @brief Factory method to create a translation matrix.
      @param tx The translation in the x direction.
      @param ty The translation in the y direction.
			@return A Matrix2x2 representing the translation.
			@details This method creates a translation matrix that can be used to translate points in 2D space.
		*/
    static Matrix2x2 
      rotation(float angleRad) {
      float c = EngineMath::cos(angleRad);
      float s = EngineMath::sin(angleRad);
      return Matrix2x2(c, -s,
        s, c);
    }

    /*
      @brief Factory method to create a scaling matrix.
      @param sx The scaling factor in the x direction.
			@param sy The scaling factor in the y direction.
      @return A Matrix2x2 representing the scaling.
      @details This method creates a scaling matrix that can be used to scale points in 2D space.
		*/
    static Matrix2x2 
      scale(float sx, float sy) {
      return Matrix2x2(sx, 0.0f,
        0.0f, sy);
    }

    /*
      @brief Factory method to create a scaling matrix from a Vector2.
      @param s The scaling vector containing x and y scaling factors.
      @return A Matrix2x2 representing the scaling.
      @details This method creates a scaling matrix that can be used to scale points in 2D space
      using a Vector2 for both x and y scaling factors.
		*/
    static Matrix2x2 
      scale(const Vector2& s) {
      return Matrix2x2(s.x, 0.0f,
        0.0f, s.y);
    }

    /*
      @brief Indexing operator for the Matrix2x2 class.
      @param index The index of the element to access (0 to 3).
      @return A reference to the element at the specified index.
      @details This operator allows access to the elements of the matrix using an index.
			If the index is out of bounds, it defaults to returning m[0] to avoid undefined behavior.
		*/
    float& 
      operator[](int index) { return m[index]; }
    const float& 
      operator[](int index) const { return m[index]; }

    /*
      @brief Multiplication operator for the Matrix2x2 class.
      @param other The matrix to multiply with this matrix.
      @return A new Matrix2x2 instance representing the result of the multiplication.
			@details This operator performs matrix multiplication, which is used to combine transformations.
		*/
    Matrix2x2 
      operator*(const Matrix2x2& other) const {
      Matrix2x2 result;
      result.m[0] = m[0] * other.m[0] + m[1] * other.m[2];
      result.m[1] = m[0] * other.m[1] + m[1] * other.m[3];
      result.m[2] = m[2] * other.m[0] + m[3] * other.m[2];
      result.m[3] = m[2] * other.m[1] + m[3] * other.m[3];
      return result;
    }

    /*
      @brief Multiplication operator for the Matrix2x2 class with a Vector2.
      @param vec The vector to multiply with this matrix.
      @return A new Vector2 instance representing the result of the multiplication.
      @details This operator applies the linear transformation defined by the matrix to a 2D vector.
		*/
    Vector2 
      operator*(const Vector2& vec) const {
      return Vector2(
        m[0] * vec.x + m[1] * vec.y,
        m[2] * vec.x + m[3] * vec.y
      );
    }

    /*
      @brief Compound assignment operator for matrix multiplication.
      @param other The matrix to multiply with this matrix.
      @return A reference to this matrix after multiplication.
			@details This operator performs matrix multiplication and updates this matrix with the result.
		*/
    Matrix2x2& 
      operator*=(const Matrix2x2& other) {
      *this = *this * other;
      return *this;
    }

    /*
      @brief Equality operator for the Matrix2x2 class.
      @param other The matrix to compare with this matrix.
      @return True if both matrices are equal, false otherwise.
      @details This operator compares the elements of two matrices for equality
			with a small tolerance to account for floating-point precision errors.
		*/
    bool 
      operator==(const Matrix2x2& other) const {
      for (int i = 0; i < 4; ++i) {
        if (!EngineMath::approxEqual(m[i], other.m[i])) {
          return false;
        }
      }
      return true;
    }

    /*
      @brief Inequality operator for the Matrix2x2 class.
      @param other The matrix to compare with this matrix.
      @return True if the matrices are not equal, false otherwise.
			@details This operator checks if two matrices are not equal by negating the equality check.
		*/
    bool 
      operator!=(const Matrix2x2& other) const {
      return !(*this == other);
    }

    /*
      @brief Computes the determinant of the matrix.
      @return The determinant of the matrix.
      @details This method calculates the determinant, which is useful for determining
			if the matrix is invertible and for solving linear equations.
    */
    float 
      determinant() const {
      return m[0] * m[3] - m[1] * m[2];
    }

    /*
      @brief Computes the transpose of the matrix.
      @return A new Matrix2x2 instance representing the transposed matrix.
			@details This method swaps the rows and columns of the matrix, which is useful in various mathematical operations.
		*/
    Matrix2x2 
      transpose() const {
      return Matrix2x2(m[0], m[2],
        m[1], m[3]);
    }

    /*
      @brief Computes the inverse of the matrix.
      @return A new Matrix2x2 instance representing the inverse of the matrix.
			@details This method calculates the inverse, which is useful for solving linear equations
      and for transforming coordinates back to their original space.
      If the determinant is zero, it returns a zero matrix to avoid division by zero.
		*/
    Matrix2x2 
      inverse() const {
      float det = determinant();
      if (EngineMath::approxEqual(det, 0.0f)) {
        return Matrix2x2(0.0f, 0.0f, 0.0f, 0.0f);
      }

      /*
        @brief Computes the inverse of the matrix.
        @return A new Matrix2x2 instance representing the inverse of the matrix.
        @details This method calculates the inverse, which is useful for solving linear equations
        and for transforming coordinates back to their original space.
        If the determinant is zero, it returns a zero matrix to avoid division by zero.
      */
      float invDet = 1.0f / det;
      return Matrix2x2(m[3] * invDet, -m[1] * invDet,
        -m[2] * invDet, m[0] * invDet);
    }

    /*
      @brief Transforms a Vector2 using this matrix.
      @param vec The vector to transform.
      @return A new Vector2 instance representing the transformed vector.
      @details This method applies the linear transformation defined by the matrix to a 2D vector.
		*/
    Vector2 
      transform(const Vector2& vec) const {
      return *this * vec;
    }

    /*
      @brief Transforms a Vector2 using this matrix and a translation vector.
      @param vec The vector to transform.
      @param translation The translation vector to apply after the transformation.
      @return A new Vector2 instance representing the transformed vector with translation.
      @details This method applies the linear transformation defined by the matrix to a 2D vector
      and then adds a translation vector to the result.
		*/
    Vector2 
      transform(const Vector2& vec, const Vector2& translation) const {
      return (*this * vec) + translation;
    }

    /*
      @brief Returns the identity matrix.
      @return A Matrix2x2 instance representing the identity matrix.
			@details The identity matrix is a special matrix that does not change vectors when multiplied.
		*/
    static const 
      Matrix2x2 Identity() {
      return Matrix2x2(1.0f, 0.0f, 0.0f, 1.0f);
    }
  };
} // namespace EngineMath
