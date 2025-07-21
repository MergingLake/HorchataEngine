#pragma once
#include "../Utilities/EngineMath.h"
#include "../Vectors/Vector3.h"
#include "../Vectors/Vector4.h"

namespace EngineMath {
  /*
    @brief A 4x4 matrix class for representing linear transformations in 3D space.
    @details This class provides basic matrix operations such as multiplication, scaling,
    rotation, translation, and more. It is designed to be used in 3D graphics, game development, and physics calculations.
	*/
  class Matrix4x4 {
  public:
    float m[16];
    
    /*
      @brief Default constructor for the Matrix4x4 class.
      @details Initializes the matrix to the identity matrix.
		*/
    Matrix4x4() {
      m[0] = 1.0f; m[1] = 0.0f; m[2] = 0.0f; m[3] = 0.0f;
      m[4] = 0.0f; m[5] = 1.0f; m[6] = 0.0f; m[7] = 0.0f;
      m[8] = 0.0f; m[9] = 0.0f; m[10] = 1.0f; m[11] = 0.0f;
      m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
    }

    /*
      @brief Constructor for the Matrix4x4 class with specified elements.
      @param m00 The element at row 0, column 0.
      @param m01 The element at row 0, column 1.
      @param m02 The element at row 0, column 2.
      @param m03 The element at row 0, column 3.
      @param m10 The element at row 1, column 0.
      @param m11 The element at row 1, column 1.
      @param m12 The element at row 1, column 2.
      @param m13 The element at row 1, column 3.
      @param m20 The element at row 2, column 0.
      @param m21 The element at row 2, column 1.
      @param m22 The element at row 2, column 2.
      @param m23 The element at row 2, column 3.
      @param m30 The element at row 3, column 0.
      @param m31 The element at row 3, column 1.
      @param m32 The element at row 3, column 2.
			@param m33 The element at row 3, column 3.
      @details Initializes the matrix with the given values.
		*/
    Matrix4x4(float m00, float m01, float m02, float m03,
      float m10, float m11, float m12, float m13,
      float m20, float m21, float m22, float m23,
      float m30, float m31, float m32, float m33) {
      m[0] = m00; m[1] = m01; m[2] = m02; m[3] = m03;
      m[4] = m10; m[5] = m11; m[6] = m12; m[7] = m13;
      m[8] = m20; m[9] = m21; m[10] = m22; m[11] = m23;
      m[12] = m30; m[13] = m31; m[14] = m32; m[15] = m33;
    }
    
    /*
      @brief Factory method to create a translation matrix.
      @param tx The translation in the x direction.
      @param ty The translation in the y direction.
      @param tz The translation in the z direction.
      @return A Matrix4x4 representing the translation.
      @details This method creates a translation matrix that can be used to translate points in 3D space.
		*/
    static Matrix4x4 
      translation(float tx, float ty, float tz) {
      return Matrix4x4(1.0f, 0.0f, 0.0f, tx,
        0.0f, 1.0f, 0.0f, ty,
        0.0f, 0.0f, 1.0f, tz,
        0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    /*
      @brief Factory method to create a translation matrix from a Vector3.
      @param t The translation vector containing x, y, and z components.
      @return A Matrix4x4 representing the translation.
      @details This method creates a translation matrix that can be used to translate points in 3D space
			using a Vector3 for the translation components.
		*/
    static Matrix4x4 
      translation(const Vector3& t) {
      return translation(t.x, t.y, t.z);
    }
    
    /*
      @brief Factory method to create a rotation matrix around the X-axis.
      @param angleRad The angle in radians to rotate around the X-axis.
      @return A Matrix4x4 representing the rotation.
			@details This method creates a rotation matrix that can be used to rotate points around the X-axis.
		*/
    static Matrix4x4 
      rotationX(float angleRad) {
      float c = EngineMath::cos(angleRad);
      float s = EngineMath::sin(angleRad);
      return Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, c, -s, 0.0f,
        0.0f, s, c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    /*
      @brief Factory method to create a rotation matrix around the Y-axis.
      @param angleRad The angle in radians to rotate around the Y-axis.
      @return A Matrix4x4 representing the rotation.
			@details This method creates a rotation matrix that can be used to rotate points around the Y-axis.
		*/
    static Matrix4x4 
      rotationY(float angleRad) {
      float c = EngineMath::cos(angleRad);
      float s = EngineMath::sin(angleRad);
      return Matrix4x4(c, 0.0f, s, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        -s, 0.0f, c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    /*
      @brief Factory method to create a rotation matrix around the Z-axis.
      @param angleRad The angle in radians to rotate around the Z-axis.
      @return A Matrix4x4 representing the rotation.
      @details This method creates a rotation matrix that can be used to rotate points around the Z-axis.
		*/
    static Matrix4x4 
      rotationZ(float angleRad) {
      float c = EngineMath::cos(angleRad);
      float s = EngineMath::sin(angleRad);
      return Matrix4x4(c, -s, 0.0f, 0.0f,
        s, c, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    /*
      @brief Factory method to create a scaling matrix.
      @param sx The scaling factor in the x direction.
      @param sy The scaling factor in the y direction.
      @param sz The scaling factor in the z direction.
      @return A Matrix4x4 representing the scaling.
			@details This method creates a scaling matrix that can be used to scale points in 3D space.
		*/
    static Matrix4x4 
      scale(float sx, float sy, float sz) {
      return Matrix4x4(sx, 0.0f, 0.0f, 0.0f,
        0.0f, sy, 0.0f, 0.0f,
        0.0f, 0.0f, sz, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    /*
      @brief Factory method to create a scaling matrix from a Vector3.
      @param s The scaling vector containing x, y, and z scaling factors.
      @return A Matrix4x4 representing the scaling.
			@details This method creates a scaling matrix that can be used to scale points in 3D space
			using a Vector3 for all three scaling factors.
		*/
    static Matrix4x4 
      scale(const Vector3& s) {
      return scale(s.x, s.y, s.z);
    }
    
    /*
      @brief Indexing operator for the Matrix4x4 class.
      @param index The index of the element to access (0 to 15).
      @return A reference to the element at the specified index.
      @details This operator allows access to the elements of the matrix using an index.
      If the index is out of bounds, it defaults to returning m[0] to avoid undefined behavior.
		*/
    float& 
      operator[](int index) {
      return m[index];
    }

    /*
      @brief Const indexing operator for the Matrix4x4 class.
      @param index The index of the element to access (0 to 15).
      @return A const reference to the element at the specified index.
      @details This operator allows read-only access to the elements of the matrix using an index.
			If the index is out of bounds, it defaults to returning m[0] to avoid undefined behavior.
    */
    const float& 
      operator[](int index) const {
      return m[index];
    }
    
    /*
      @brief Multiplication operator for the Matrix4x4 class.
      @param other The matrix to multiply with this matrix.
      @return A new Matrix4x4 instance representing the result of the multiplication.
      @details This operator performs matrix multiplication, which is used to combine transformations.
		*/
    Matrix4x4 
      operator*(const Matrix4x4& other) const {
      Matrix4x4 result;
      for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
          result.m[i * 4 + j] = 0.0f;
          for (int k = 0; k < 4; ++k) {
            result.m[i * 4 + j] += m[i * 4 + k] * other.m[k * 4 + j];
          }
        }
      }
      return result;
    }
    
    /*
      @brief Multiplication operator for the Matrix4x4 class with a Vector4.
      @param vec The vector to multiply with this matrix.
      @return A new Vector4 instance representing the result of the multiplication.
      @details This operator performs matrix-vector multiplication, which is used to transform vectors in 3D space.
		*/
    Vector4 
      operator*(const Vector4& vec) const {
      return Vector4(
        m[0] * vec.x + m[1] * vec.y + m[2] * vec.z + m[3] * vec.w,
        m[4] * vec.x + m[5] * vec.y + m[6] * vec.z + m[7] * vec.w,
        m[8] * vec.x + m[9] * vec.y + m[10] * vec.z + m[11] * vec.w,
        m[12] * vec.x + m[13] * vec.y + m[14] * vec.z + m[15] * vec.w
      );
    }
    
    /*
      @brief Multiplication assignment operator for the Matrix4x4 class.
      @param other The matrix to multiply with this matrix.
      @return A reference to this matrix after multiplication.
			@details This operator performs matrix multiplication and assigns the result to this matrix.
		*/
    Matrix4x4& 
      operator*=(const Matrix4x4& other) {
      *this = *this * other;
      return *this;
    }
    
    /*
      @brief Equality operator for the Matrix4x4 class.
      @param other The matrix to compare with this matrix.
      @return True if the matrices are approximately equal, false otherwise.
			@details This operator checks if two matrices are approximately equal using a small epsilon value
			to account for floating-point precision errors.
		*/
    bool 
      operator==(const Matrix4x4& other) const {
      for (int i = 0; i < 16; ++i) {
        if (!EngineMath::approxEqual(m[i], other.m[i])) {
          return false;
        }
      }
      return true;
    }
    
    /*
      @brief Inequality operator for the Matrix4x4 class.
      @param other The matrix to compare with this matrix.
      @return True if the matrices are not equal, false otherwise.
			@details This operator checks if two matrices are not equal by negating the equality check.
		*/
    bool 
      operator!=(const Matrix4x4& other) const {
      return !(*this == other);
    }
    
    /*
      @brief Transpose the matrix.
      @return A new Matrix4x4 instance that is the transpose of this matrix.
			@details This method swaps rows and columns of the matrix, which is useful in various mathematical operations.
		*/
    Matrix4x4 
      transpose() const {
      return Matrix4x4(m[0], m[4], m[8], m[12],
        m[1], m[5], m[9], m[13],
        m[2], m[6], m[10], m[14],
        m[3], m[7], m[11], m[15]);
    }
    
    /*
      @brief Computes the determinant of the matrix.
      @return The determinant of the matrix.
			@details This method calculates the determinant, which is useful for determining if the matrix is invertible
			and for solving linear equations.
		*/
    float 
      determinant() const {
      return m[0] * getMinorDeterminant(1, 2, 3, 1, 2, 3) -
        m[1] * getMinorDeterminant(0, 2, 3, 1, 2, 3) +
        m[2] * getMinorDeterminant(0, 1, 3, 1, 2, 3) -
        m[3] * getMinorDeterminant(0, 1, 2, 1, 2, 3);
    }
    
    /*
      @brief Computes the minor determinant for a 3x3 submatrix.
      @param r0 The first row index of the submatrix.
      @param r1 The second row index of the submatrix.
      @param r2 The third row index of the submatrix.
      @param c0 The first column index of the submatrix.
      @param c1 The second column index of the submatrix.
      @param c2 The third column index of the submatrix.
			@return The determinant of the specified 3x3 submatrix.
			@details This method calculates the determinant of a 3x3 submatrix formed by the specified rows and columns.
		*/
    float 
      getMinorDeterminant(int r0, int r1, int r2, int c0, int c1, int c2) const {
      float m00 = m[r0 * 4 + c0];
      float m01 = m[r0 * 4 + c1];
      float m02 = m[r0 * 4 + c2];

      float m10 = m[r1 * 4 + c0];
      float m11 = m[r1 * 4 + c1];
      float m12 = m[r1 * 4 + c2];

      float m20 = m[r2 * 4 + c0];
      float m21 = m[r2 * 4 + c1];
      float m22 = m[r2 * 4 + c2];

      return m00 * (m11 * m22 - m12 * m21) -
        m01 * (m10 * m22 - m12 * m20) +
        m02 * (m10 * m21 - m11 * m20);
    }

    /*
      @brief Computes the inverse of the matrix.
      @return A new Matrix4x4 instance that is the inverse of this matrix.
      @details This method calculates the inverse of the matrix, which is useful for undoing transformations.
			If the matrix is not invertible, it returns a zero matrix.
		*/
    Matrix4x4 
      inverse() const {
      float det = determinant();
      if (EngineMath::approxEqual(det, 0.0f)) {
        // Matriz no invertible.
        return Matrix4x4(0.0f, 0.0f, 0.0f, 0.0f,
          0.0f, 0.0f, 0.0f, 0.0f,
          0.0f, 0.0f, 0.0f, 0.0f,
          0.0f, 0.0f, 0.0f, 0.0f);
      }
      
      float invDet = 1.0f / det;
      Matrix4x4 result;

      result.m[0] = (m[5] * (m[10] * m[15] - m[11] * m[14]) -
        m[6] * (m[9] * m[15] - m[11] * m[13]) +
        m[7] * (m[9] * m[14] - m[10] * m[13])) * invDet;

      result.m[4] = (m[6] * (m[11] * m[12] - m[8] * m[15]) -
        m[4] * (m[10] * m[15] - m[11] * m[14]) -
        m[7] * (m[9] * m[12] - m[8] * m[13])) * invDet;

      result.m[0] = (m[5] * m[10] * m[15] + m[6] * m[11] * m[13] + m[7] * m[9] * m[14] -
        m[7] * m[10] * m[13] - m[6] * m[9] * m[15] - m[5] * m[11] * m[14]) * invDet;
      result.m[4] = (m[1] * m[11] * m[14] + m[2] * m[15] * m[13] + m[3] * m[9] * m[14] -
        m[3] * m[10] * m[13] - m[2] * m[9] * m[15] - m[1] * m[11] * m[14]) * invDet;
      result.m[8] = (m[1] * m[6] * m[15] + m[2] * m[7] * m[13] + m[3] * m[5] * m[14] -
        m[3] * m[6] * m[13] - m[2] * m[5] * m[15] - m[1] * m[7] * m[14]) * invDet;
      result.m[12] = (m[1] * m[7] * m[10] + m[2] * m[4] * m[11] + m[3] * m[5] * m[9] -
        m[3] * m[6] * m[9] - m[2] * m[5] * m[11] - m[1] * m[4] * m[10]) * invDet;

      result.m[1] = (m[3] * m[10] * m[13] + m[2] * m[9] * m[15] + m[1] * m[11] * m[14] -
        m[1] * m[10] * m[15] - m[2] * m[11] * m[13] - m[3] * m[9] * m[14]) * invDet;
      result.m[5] = (m[0] * m[10] * m[15] + m[2] * m[11] * m[12] + m[3] * m[8] * m[14] -
        m[3] * m[10] * m[12] - m[2] * m[8] * m[15] - m[0] * m[11] * m[14]) * invDet;
      result.m[9] = (m[0] * m[6] * m[15] + m[2] * m[7] * m[12] + m[3] * m[4] * m[14] -
        m[3] * m[6] * m[12] - m[2] * m[4] * m[15] - m[0] * m[7] * m[14]) * invDet;
      result.m[13] = (m[0] * m[7] * m[10] + m[2] * m[4] * m[11] + m[3] * m[5] * m[8] -
        m[3] * m[6] * m[8] - m[2] * m[5] * m[11] - m[0] * m[4] * m[10]) * invDet;

      result.m[2] = (m[3] * m[6] * m[13] + m[2] * m[4] * m[15] + m[1] * m[7] * m[14] -
        m[1] * m[6] * m[15] - m[2] * m[7] * m[13] - m[3] * m[4] * m[14]) * invDet;
      result.m[6] = (m[0] * m[6] * m[15] + m[2] * m[7] * m[12] + m[3] * m[4] * m[14] -
        m[3] * m[6] * m[12] - m[2] * m[4] * m[15] - m[0] * m[7] * m[14]) * invDet;
      result.m[10] = (m[0] * m[5] * m[15] + m[1] * m[7] * m[12] + m[3] * m[4] * m[13] -
        m[3] * m[5] * m[12] - m[1] * m[4] * m[15] - m[0] * m[7] * m[13]) * invDet;
      result.m[14] = (m[0] * m[7] * m[9] + m[1] * m[4] * m[11] + m[3] * m[5] * m[8] -
        m[3] * m[6] * m[8] - m[1] * m[5] * m[11] - m[0] * m[4] * m[10]) * invDet;

      result.m[3] = (m[3] * m[6] * m[13] + m[2] * m[4] * m[15] + m[1] * m[7] * m[14] -
        m[1] * m[6] * m[15] - m[2] * m[7] * m[13] - m[3] * m[4] * m[14]) * invDet;
      result.m[7] = (m[0] * m[6] * m[15] + m[2] * m[7] * m[12] + m[3] * m[4] * m[14] -
        m[3] * m[6] * m[12] - m[2] * m[4] * m[15] - m[0] * m[7] * m[14]) * invDet;
      result.m[11] = (m[0] * m[5] * m[15] + m[1] * m[7] * m[12] + m[3] * m[4] * m[13] -
        m[3] * m[5] * m[12] - m[1] * m[4] * m[15] - m[0] * m[7] * m[13]) * invDet;
      result.m[15] = (m[0] * m[5] * m[10] + m[1] * m[6] * m[8] + m[2] * m[4] * m[9] -
        m[2] * m[5] * m[8] - m[1] * m[4] * m[10] - m[0] * m[6] * m[9]) * invDet;

      return result;
    }
    
    /*
      @brief Transforms a point in 3D space using the matrix.
      @param point The point to transform.
      @return A new Vector3 representing the transformed point.
			@details This method applies the matrix transformation to a point, converting it from local space to world space.
		*/
    Vector3 
      transformPoint(const Vector3& point) const {
      Vector4 temp(point.x, point.y, point.z, 1.0f);
      temp = (*this) * temp;

      if (EngineMath::approxEqual(temp.w, 0.0f)) {
        return Vector3(temp.x, temp.y, temp.z);
      }
      return Vector3(temp.x / temp.w, temp.y / temp.w, temp.z / temp.w);
    }
    
    /*
      @brief Transforms a direction vector using the matrix.
      @param direction The direction vector to transform.
      @return A new Vector3 representing the transformed direction.
      @details This method applies the matrix transformation to a direction vector, which does not include translation.
      The w component is set to 0.0f to indicate that it is a direction rather than a point.
		*/
    Vector3 
      transformDirection(const Vector3& direction) const {
      Vector4 temp(direction.x, direction.y, direction.z, 0.0f);
      temp = (*this) * temp;
      return Vector3(temp.x, temp.y, temp.z);
    }
    
    /*
      @brief Transforms a normal vector using the matrix.
      @param normal The normal vector to transform.
      @return A new Vector3 representing the transformed normal.
      @details This method applies the matrix transformation to a normal vector, which is used for lighting calculations.
			The w component is set to 0.0f to indicate that it is a direction rather than a point.
		*/
    static const 
      Matrix4x4 Identity() {
      return Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
    }
  };
} // namespace EngineMath