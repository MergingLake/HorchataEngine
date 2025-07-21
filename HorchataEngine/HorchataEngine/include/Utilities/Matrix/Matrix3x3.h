#pragma once
#include "../Utilities/EngineMath.h"
#include "../Vectors/Vector3.h"

namespace EngineMath {
  /*
    @brief A 3x3 matrix class for representing linear transformations in 3D space.
    @details This class provides basic matrix operations such as multiplication, scaling,
    rotation, and more. It is designed to be used in 3D graphics, game development, and physics calculations.
	*/
  class Matrix3x3 {
  public:
    float m[9];

    /*
      @brief Default constructor for the Matrix3x3 class.
			@details Initializes the matrix to the identity matrix.
		*/
    Matrix3x3() {
      m[0] = 1.0f; m[1] = 0.0f; m[2] = 0.0f;
      m[3] = 0.0f; m[4] = 1.0f; m[5] = 0.0f;
      m[6] = 0.0f; m[7] = 0.0f; m[8] = 1.0f;
    }

    /*
      @brief Constructor for the Matrix3x3 class with specified elements.
      @param m00 The element at row 0, column 0.
      @param m01 The element at row 0, column 1.
      @param m02 The element at row 0, column 2.
      @param m10 The element at row 1, column 0.
      @param m11 The element at row 1, column 1.
      @param m12 The element at row 1, column 2.
      @param m20 The element at row 2, column 0.
      @param m21 The element at row 2, column 1.
			@param m22 The element at row 2, column 2.
      @details Initializes the matrix with the given values.
		*/
    Matrix3x3(float m00, float m01, float m02,
      float m10, float m11, float m12,
      float m20, float m21, float m22) {
      m[0] = m00; m[1] = m01; m[2] = m02;
      m[3] = m10; m[4] = m11; m[5] = m12;
      m[6] = m20; m[7] = m21; m[8] = m22;
    }

    /*
      @brief Factory method to create a translation matrix.
      @param tx The translation in the x direction.
      @param ty The translation in the y direction.
      @param tz The translation in the z direction.
      @return A Matrix3x3 representing the translation.
			@details This method creates a translation matrix that can be used to translate points in 3D space.
    */
    static Matrix3x3 
      rotationX(float angleRad) {
      float c = EngineMath::cos(angleRad);
      float s = EngineMath::sin(angleRad);
      return Matrix3x3(1.0f, 0.0f, 0.0f,
        0.0f, c, -s,
        0.0f, s, c);
    }

    /*
      @brief Factory method to create a rotation matrix around the Y-axis.
      @param angleRad The angle in radians to rotate around the Y-axis.
      @return A Matrix3x3 representing the rotation.
      @details This method creates a rotation matrix that can be used to rotate points around the Y-axis in 3D space.
		*/
    static Matrix3x3 
      rotationY(float angleRad) {
      float c = EngineMath::cos(angleRad);
      float s = EngineMath::sin(angleRad);
      return Matrix3x3(c, 0.0f, s,
        0.0f, 1.0f, 0.0f,
        -s, 0.0f, c);
    }

    /*
      @brief Factory method to create a rotation matrix around the Z-axis.
      @param angleRad The angle in radians to rotate around the Z-axis.
      @return A Matrix3x3 representing the rotation.
      @details This method creates a rotation matrix that can be used to rotate points around the Z-axis in 3D space.
    */
    static Matrix3x3 
      rotationZ(float angleRad) {
      float c = EngineMath::cos(angleRad);
      float s = EngineMath::sin(angleRad);
      return Matrix3x3(c, -s, 0.0f,
        s, c, 0.0f,
        0.0f, 0.0f, 1.0f);
    }

    /*
      @brief Factory method to create a scaling matrix.
      @param sx The scaling factor in the x direction.
      @param sy The scaling factor in the y direction.
      @param sz The scaling factor in the z direction.
      @return A Matrix3x3 representing the scaling.
      @details This method creates a scaling matrix that can be used to scale points in 3D space.
    */
    static Matrix3x3 
      scale(float sx, float sy, float sz) {
      return Matrix3x3(sx, 0.0f, 0.0f,
        0.0f, sy, 0.0f,
        0.0f, 0.0f, sz);
    }

    /*
      @brief Factory method to create a scaling matrix from a Vector3.
      @param s The scaling vector containing x, y, and z scaling factors.
      @return A Matrix3x3 representing the scaling.
      @details This method creates a scaling matrix that can be used to scale points in 3D space
      using a Vector3 for all three scaling factors.
    */
    static Matrix3x3 
      scale(const Vector3& s) {
      return scale(s.x, s.y, s.z);
    }

    /*
      @brief Indexing operator for the Matrix3x3 class.
      @param index The index of the element to access (0 to 8).
      @return A reference to the element at the specified index.
      @details This operator allows access to the elements of the matrix using an index.
      If the index is out of bounds, it defaults to returning m[0] to avoid undefined behavior.
    */
    float& 
      operator[](int index) {
      return m[index];
    }

    /*
      @brief Const indexing operator for the Matrix3x3 class.
      @param index The index of the element to access (0 to 8).
      @return A const reference to the element at the specified index.
      @details This operator allows read-only access to the elements of the matrix using an index.
      If the index is out of bounds, it defaults to returning m[0] to avoid undefined behavior.
		*/
    const float& 
      operator[](int index) const {
      return m[index];
    }

    /*
      @brief Multiplication operator for the Matrix3x3 class.
      @param other The matrix to multiply with this matrix.
      @return A new Matrix3x3 instance representing the result of the multiplication.
      @details This operator performs matrix multiplication, which is used to combine transformations.
    */
    Matrix3x3 
      operator*(const Matrix3x3& other) const {
      Matrix3x3 result;
      for (int i = 0; i < 3; ++i) { 
        for (int j = 0; j < 3; ++j) { 
          result.m[i * 3 + j] = 0.0f;
          for (int k = 0; k < 3; ++k) { 
            result.m[i * 3 + j] += m[i * 3 + k] * other.m[k * 3 + j];
          }
        }
      }
      return result;
    }

    /*
      @brief Multiplication operator for the Matrix3x3 class with a Vector3.
      @param vec The vector to multiply with this matrix.
      @return A new Vector3 instance representing the result of the multiplication.
      @details This operator applies the linear transformation defined by the matrix to a 3D vector.
    */
    Vector3 
      operator*(const Vector3& vec) const {
      return Vector3(
        m[0] * vec.x + m[1] * vec.y + m[2] * vec.z,
        m[3] * vec.x + m[4] * vec.y + m[5] * vec.z,
        m[6] * vec.x + m[7] * vec.y + m[8] * vec.z
      );
    }

    /*
      @brief Compound assignment operator for matrix multiplication.
      @param other The matrix to multiply with this matrix.
      @return A reference to this matrix after multiplication.
      @details This operator performs matrix multiplication and updates this matrix with the result.
    */
    Matrix3x3& 
      operator*=(const Matrix3x3& other) {
      *this = *this * other; 
      return *this;
    }

    /*
      @brief Equality operator for the Matrix3x3 class.
      @param other The matrix to compare with this matrix.
      @return True if both matrices are equal, false otherwise.
      @details This operator compares the elements of two matrices for equality
      with a small tolerance to account for floating-point precision errors.
    */
    bool 
      operator==(const Matrix3x3& other) const {
      for (int i = 0; i < 9; ++i) {
        if (!EngineMath::approxEqual(m[i], other.m[i])) {
          return false;
        }
      }
      return true;
    }

    /*
      @brief Inequality operator for the Matrix3x3 class.
      @param other The matrix to compare with this matrix.
      @return True if the matrices are not equal, false otherwise.
			@details This operator checks if two matrices are not equal by negating the equality check.
    */
    bool 
      operator!=(const Matrix3x3& other) const {
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
      return m[0] * (m[4] * m[8] - m[5] * m[7]) -
        m[1] * (m[3] * m[8] - m[5] * m[6]) +
        m[2] * (m[3] * m[7] - m[4] * m[6]);
    }

    /*
      @brief Computes the transpose of the matrix.
      @return A new Matrix3x3 instance representing the transposed matrix.
      @details This method swaps the rows and columns of the matrix, which is useful in various mathematical operations.
    */
    Matrix3x3 
      transpose() const {
      return Matrix3x3(m[0], m[3], m[6],
        m[1], m[4], m[7],
        m[2], m[5], m[8]);
    }

    /*
      @brief Computes the inverse of the matrix.
      @return A new Matrix3x3 instance representing the inverse of the matrix.
      @details This method calculates the inverse, which is useful for solving linear equations
      and for transforming coordinates back to their original space.
      If the determinant is zero, it returns a zero matrix to avoid division by zero.
    */
    Matrix3x3 
      inverse() const {
      float det = determinant();
      if (EngineMath::approxEqual(det, 0.0f)) {
        return Matrix3x3(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
      }

      float invDet = 1.0f / det;

      float c00 = (m[4] * m[8] - m[5] * m[7]);
      float c01 = (m[2] * m[7] - m[1] * m[8]);
      float c02 = (m[1] * m[5] - m[2] * m[4]);

      float c10 = (m[5] * m[6] - m[3] * m[8]);
      float c11 = (m[0] * m[8] - m[2] * m[6]);
      float c12 = (m[2] * m[3] - m[0] * m[5]);

      float c20 = (m[3] * m[7] - m[4] * m[6]);
      float c21 = (m[1] * m[6] - m[0] * m[7]);
      float c22 = (m[0] * m[4] - m[1] * m[3]);

      return Matrix3x3(c00 * invDet, c01 * invDet, c02 * invDet,
        c10 * invDet, c11 * invDet, c12 * invDet,
        c20 * invDet, c21 * invDet, c22 * invDet);
    }

    /*
      @brief Returns the identity matrix.
      @return A Matrix3x3 instance representing the identity matrix.
      @details The identity matrix is a special matrix that does not change any vector when multiplied by it.
		*/
    static const 
      Matrix3x3 Identity() {
      return Matrix3x3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    }
  };
} // namespace EngineMath
