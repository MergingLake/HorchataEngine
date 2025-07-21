#pragma once
namespace EngineMath {
	
	// onstants for mathematical operations
	const float PI = 3.14159265358979323846f;
	const float EPSILON = 1.192092896e-07f;

	/*
		@brief Computes the square root of a number.
		Uses the Newton-Raphson method for approximation.
		@param value The number to compute the square root of.
		@return The square root of the number, or 0 if the input is negative or zero.
	*/
	inline float 
		sqrt(float value) {
			if (value < 0.0f) return 0.0f; // Handle negative input gracefully
			if (value == 0.0f) return 0.0f; // Return 0 for zero input

			float x = value;
			float y = 1.0f;

			for (int i = 0; i < 10; ++i) // Fixed number of iterations for simplicity
			{
				x = 0.5f * (x + value / x);
			}
			return x;
		}

	/*
		@brief Computes the square of a number.
		@param value The number to compute the square of.
		@return The square of the number.
	*/
	inline float 
		square(float value) { return value * value; }
	
	/*
		@brief Computes the cube of a number.
		@param value The number to compute the cube of.
		@return The cube of the number.
	*/
	inline float 
		cube(float value) { return value * value * value; }

	/*
		@brief Computes the power of a base raised to an exponent.
		@param base The base number.
		@param exponent The exponent to raise the base to.
		@return The result of base raised to the exponent.
	*/
	inline float 
		power(float base, float exponent) {
			float result = 1.0f;
			if (exponent < 0)
			{
				base = 1.0f / base;
				exponent = -exponent;
			}
			for (int i = 0; i < exponent; ++i)
			{
				result *= base;
			}
			return result;
		}

	/*
		@brief Computes the absolute value of a number.
		@param value The number to compute the absolute value of.
		@return The absolute value of the number.
	*/
	inline float 
		abs(float value) { return (value < 0.0f) ? -value : value; }

	/*
		@brief Computes the maximum of two values.
		@param a The first value.
		@param b The second value.
		@return The maximum of the two values.
	*/
	inline float 
		EMax(float a, float b) { return (a > b) ? a : b; }

	/*
		@brief Computes the minimum of two values.
		@param a The first value.
		@param b The second value.
		@return The minimum of the two values.
	*/
	inline float 
		EMin(float a, float b) { return (a < b) ? a : b; }

	/*
		@brief Computes the average of two values.
		@param a The first value.
		@param b The second value.
		@return The average of the two values.
	*/
	inline float 
		round(float value) {
			if (value >= 0.0f) return (float)(int)(value + 0.5f);
			else return (float)(int)(value - 0.5f);
		}

	/*
		@brief Computes the floor of a number.
		@param value The number to compute the floor of.
		@return The largest integer less than or equal to the number.
	*/
	inline float 
		floor(float value) {
		int i = (int)value;
		return (float)(value < 0 && value != i) ? (i - 1) : i;
	}

	/*
		@brief Computes the ceiling of a number.
		@param value The number to compute the ceiling of.
		@return The smallest integer greater than or equal to the number.
	*/
	inline float 
		ceil(float value) {
		int i = (int)value;
		return (float)(value > 0 && value != i) ? (i + 1) : i;
	}

	/*
		@brief Computes the absolute value of a float.
		@param value The float to compute the absolute value of.
		@return The absolute value of the float.
	*/
	inline float 
		fabs(float value) { return abs(value); }

	/*
		@brief Computes the modulus of two floats.
		@param x The dividend.
		@param y The divisor.
		@return The remainder of the division, or 0 if the divisor is zero.
	*/
	inline float 
		mod(float x, float y)
		{
			if (y == 0.0f) return 0.0f; // Handle division by zero gracefully
			return x - y * floor(x / y);
		}

	/*
		@brief Computes the sign of a float.
		@param value The float to compute the sign of.
		@return 1.0f if positive, -1.0f if negative, 0.0f if zero.
	*/
	inline float 
		exp(float value)
		{
			float term = 1.0f;
			float sum = 1.0f;
			for (int i = 1; i < 15; ++i) // Fixed number of terms for simplicity
			{
				term *= (value / i); // Calculate term n! = n * (n-1) * ... * 1
				sum += term;
			}
			return sum;
		}

	/*
		@brief Computes the natural logarithm of a value.
		@param value The value to compute the logarithm of.
		@return The natural logarithm of the value, or -999999.0f for non-positive input.
	*/
	inline float 
		log(float value)
		{
			if (value <= 0.0f) return -999999.0f; // Handle non-positive input gracefully
			float xMinus1 = value - 1.0f;
			float sum = 0.0f;
			float term = xMinus1;
			for (int i = 1; i < 15; ++i) // Fixed number of terms for simplicity
			{
				if (i % 2 == 1)
					sum += (term / i); // Add odd terms
				else
					sum -= (term / i); // Subtract even terms
				term *= xMinus1; // Update term for next iteration
			}
			return sum; // Return the logarithm
		}

	/*
		@brief Computes the base 10 logarithm of a value.
		@param value The value to compute the logarithm of.
		@return The base 10 logarithm of the value, or -999999.0f for non-positive input.
	*/
	inline float 
		log10(float value)
		{
			return log(value) / log(10.0f); // Change of base formula
		}

	/*
		@brief Computes the sine of an angle in radians.
		@param value The angle in radians.
		@return The sine of the angle.
	*/
	inline float 
		sin(float value)
		{
			value = mod(value, 2.0f * PI);
			if (value > PI) value -= 2.0f * PI; // Normalize to [-PI, PI]
			if (value < -PI) value += 2.0f * PI; // Normalize to [-PI, PI]

			// Use Taylor series expansion for sine
			float x = value;
			float x2 = x * x;
			float sum = x; // Start with the first term
			float term = x; // Initialize term for sine series

			term = -term * x2 / (3.0f * 2.0f * 1.0f); sum += term; // First term of sine series
			term = -term * x2 / (5.0f * 4.0f); sum += term; // Second term of sine series
			term = -term * x2 / (7.0f * 6.0f); sum += term; // Third term of sine series
			term = -term * x2 / (9.0f * 8.0f); sum += term; // Fourth term of sine series
			term = -term * x2 / (11.0f * 10.0f); sum += term; // Fifth term of sine series
			term = -term * x2 / (13.0f * 12.0f); sum += term; // Sixth term of sine series

			return sum;
		}

	/*
		@brief Computes the cosine of an angle in radians.
		@param value The angle in radians.
		@return The cosine of the angle.
	*/
	inline float 
		cos(float value)
		{
			value = mod(value, 2.0f * PI);
			if (value > PI) value -= 2.0f * PI; // Normalize to [-PI, PI]
			if (value < -PI) value += 2.0f * PI; // Normalize to [-PI, PI]

			// Use Taylor series expansion for cosine
			float x = value;
			float x2 = x * x;
			float sum = 1.0f; // Start with the first term
			float term = 1.0f; // Initialize term for cosine series

			term = -term * x2 / (2.0f * 1.0f); sum += term; // First term of cosine series
			term = -term * x2 / (4.0f * 3.0f); sum += term; // Second term of cosine series
			term = -term * x2 / (6.0f * 5.0f); sum += term; // Third term of cosine series
			term = -term * x2 / (8.0f * 7.0f); sum += term; // Fourth term of cosine series
			term = -term * x2 / (10.0f * 9.0f); sum += term; // Fifth term of cosine series
			term = -term * x2 / (12.0f * 11.0f); sum += term; // Sixth term of cosine series

			return sum;
		}

	/*
		@brief Computes the tangent of an angle in radians.
		@param value The angle in radians.
		@return The tangent of the angle.
	*/
	inline float 
		tan(float value)
		{
			return sin(value) / cos(value); // Return tangent as sine over cosine
		}

	/*
		@brief Computes the arcsine of a value.
		@param value The value to compute the arcsine of.
		@return The arcsine of the value, or 0 if the input is zero.
	*/
	inline float 
		asin(float value)
		{
			if (value < -1.0f) value = -1.0f; // Clamp to -1
			if (value > 1.0f) value = 1.0f; // Clamp to 1

			if (value == 0.0f)
			{
				float approx = sqrt(1.0f - value * value);
				if (approx == 0.0f) return PI / 2.0f; // Handle zero case
				return PI / 2.0f - asin(approx); // Use symmetry for approximation
			}
			else
			{
				return -asin(-value); // Use symmetry for negative values
			}
		}

	/*
		@brief Computes the arccosine of a value.
		@param value The value to compute the arccosine of.
		@return The arccosine of the value, or 0 if the input is zero.
	*/
	inline float 
		acos(float value)
		{
			return PI / 2.0f - asin(value); // Use complementary angle for acos
		}

	/*
		@brief Computes the arctangent of a value.
		@param value The value to compute the arctangent of.
		@return The arctangent of the value.
	*/
	inline float 
		atan(float value)
		{
			float sum = value; // Start with the first term
			float term = value; // Initialize term for atan series
			float x2 = value * value;
			for (int i = 1; i < 10; ++i) // Fixed number of terms for simplicity
			{
				term *= x2; // Update term for next iteration
				if (i % 2 == 1)
					sum -= (term / (2.0f * i + 1.0f)); // Add odd terms
				else
					sum += (term / (2.0f * i + 1.0f)); // Subtract even terms
			}
			return sum; // Return the arctangent
		}

	/*
	  @brief Computes the hyperbolic sine of a value.
	  @param value The value to compute the hyperbolic sine of.
	  @return The hyperbolic sine of the value.
	*/
	inline float 
		sinh(float value)
		{
			return (exp(value) - exp(-value)) / 2.0f; // Hyperbolic sine
		}

	/*
		@brief Computes the hyperbolic cosine of a value.
		@param value The value to compute the hyperbolic cosine of.
		@return The hyperbolic cosine of the value.
	*/
	inline float 
		cosh(float value)
		{
			return (exp(value) + exp(-value)) / 2.0f; // Hyperbolic cosine
		}

	/*
		@brief Computes the hyperbolic tangent of a value.
		@param value The value to compute the hyperbolic tangent of.
		@return The hyperbolic tangent of the value.
	*/
	inline float 
		tanh(float value)
		{
			float c = cosh(value);
			if (c == 0.0f) return (value >= 0) ? 1.0f : -1.0f; // Handle division by zero gracefully
			return sinh(value) / c; // Return hyperbolic tangent
		}

	/*
		@brief Computes the angle in radians from the x-axis to a point (x, y).
		@param x The x-coordinate of the point.
		@param y The y-coordinate of the point.
		@return The angle in radians.
	*/
	inline float 
		radians(float degrees) { return degrees * (PI / 180.0f); }

	/*
		@brief Computes the angle in degrees from the x-axis to a point (x, y).
		@param radians The angle in radians.
		@return The angle in degrees.
	*/
	inline float 
		degrees(float radians) { return radians * (180.0f / PI); }

	/*
		@brief Computes the area of a circle given its radius.
		@param radius The radius of the circle.
		@return The area of the circle.
	*/
	inline float 
		circleArea(float radius) { return PI * radius * radius; }

	/*
		@brief Computes the circumference of a circle given its radius.
		@param radius The radius of the circle.
		@return The circumference of the circle.
	*/
	inline float 
		circleCircumference(float radius) { return 2.0f * PI * radius; }

	/*
		@brief Computes the area of a rectangle given its width and height.
		@param width The width of the rectangle.
		@param height The height of the rectangle.
		@return The area of the rectangle.
	*/
	inline float 
		rectangleArea(float width, float height) { return width * height; }

	/*
		@brief Computes the perimeter of a rectangle given its width and height.
		@param width The width of the rectangle.
		@param height The height of the rectangle.
		@return The perimeter of the rectangle.
	*/
	inline float 
		rectanglePerimeter(float width, float height) { return 2.0f * (width + height); }

	/*
		@brief Computes the area of a triangle given its base and height.
		@param base The base of the triangle.
		@param height The height of the triangle.
		@return The area of the triangle.
	*/
	inline float 
		triangleArea(float base, float height) { return 0.5f * base * height; }

	/*
		@brief Computes the distance between two points (x1, y1) and (x2, y2).
		@param x1 The x-coordinate of the first point.
		@param y1 The y-coordinate of the first point.
		@param x2 The x-coordinate of the second point.
		@param y2 The y-coordinate of the second point.
		@return The distance between the two points.
	*/
	inline float 
		distance(float x1, float y1, float x2, float y2)
	{
		float dx = x2 - x1;
		float dy = y2 - y1;
		return sqrt(dx * dx + dy * dy); // Euclidean distance
	}

	/*
		@brief Computes the linear interpolation between two values a and b.
		@param a The start value.
		@param b The end value.
		@param t The interpolation factor (0.0 to 1.0).
		@return The interpolated value.
	*/
	inline float lerp(float a, float b, float t) { return a + t * (b - a); }
	
	/*
		@brief Computes the factorial of a non-negative integer n.
		@param n The non-negative integer to compute the factorial of.
		@return The factorial of n, or 1 if n is 0.
	*/
	inline unsigned long long factorial(unsigned int n)
	{
		if (n == 0) return 1ULL;
		unsigned long long result = 1ULL;
		for (unsigned int i = 1; i <= n; ++i)
		{
			result *= i; // Calculate factorial iteratively
		}
		return result; // Return the factorial result
	}

	/*
		@brief Checks if two floats are approximately equal within a given epsilon.
		@param a The first float.
		@param b The second float.
		@param epsilon The tolerance for comparison (default is EPSILON).
		@return True if the floats are approximately equal, false otherwise.
	*/
	inline bool approxEqual(float a, float b, float epsilon = EPSILON)
	{
		return abs(a - b) < epsilon; // Check if two floats are approximately equal
	}
} // namespace EngineMath