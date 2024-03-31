#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <intrin.h>

float Q_rsqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long*)&y;                       // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);               // what the fuck?
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y));   // 1st iteration
	// y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

float sqrt_approx(float z)
{
	union { float f; uint32_t i; } val = { z };
	val.i -= 1 << 23;    /* Subtract 2^m. */
	val.i >>= 1;        /* Divide by 2. */
	val.i += 1 << 29;    /* Add ((b + 1) / 2) * 2^m. */

	return val.f;        /* Interpret again as float */
}

int main()
{
	float True = 0;
	double secondapproximation = 0;
	int y = 0;
	int approximation = 0;
	float fltapproximation = 0;
	float v2fltapproximation = 0;
	float thirdapproximation = 0;
	float x = 0;

	float value = 213992410

		;
	double dovalue = 20394298

		;
	int intvalue = 0;
	clock_t time;

	time = clock();
	for (int i = 0; i < 1000000; i++) {
		True = sqrt(value);
	}
	time = clock() - time;
	std::cout << "Base function time took " << std::setprecision(5) << (float)time / CLOCKS_PER_SEC << "\n";

	time = clock();
	for (int i = 0; i < 1000000; i++) {
		secondapproximation = sqrt_approx(value);
	}
	time = clock() - time;
	std::cout << "test function time took " << std::setprecision(5) << (float)time / CLOCKS_PER_SEC << "\n";

	/*time = clock();
	for (int i = 0; i < 1000000; i++) {
		long t;

		std::memcpy(&t, &value, sizeof(float));
		t = 0x1fbd3f7d + (t >> 1);

		float y;
		std::memcpy(&y, &t, sizeof(float));

		secondapproximation = (((y * y) + value) / (y)) * 0.5;
	}
	time = clock() - time;
	std::cout << "Quake similar method took " << std::setprecision(5) << (float)time / CLOCKS_PER_SEC << "\n";
	*/
	time = clock();
	for (int i = 0; i < 1000000; i++) {
		thirdapproximation = 1 / Q_rsqrt(value);
	}
	time = clock() - time;
	std::cout << "1/Quake method took " << std::setprecision(5) << (float)time / CLOCKS_PER_SEC << "\n";
	time = clock();
	for (int i = 0; i < 1000000; i++) {
		intvalue = (int)value;
		y = 32 - (int)_lzcnt_u32(intvalue);
		approximation = intvalue >> (y >> 1);
		intvalue = intvalue & (1 << (y - 1));
		approximation += intvalue >> ((y - 1) >> 1);
		approximation = approximation >> 1;
		fltapproximation = 0.5 * (approximation + value / approximation);
	}
	time = clock() - time;
	std::cout << "My v1 function time took " << std::setprecision(5) << (float)time / CLOCKS_PER_SEC << "\n";
	float halfvalue = 0;
	time = clock();
	for (int i = 0; i < 1000000; i++) {
		intvalue = (int)value;
		y = 32 - _lzcnt_u32(intvalue);
		approximation = intvalue >> (y >> 1);
		v2fltapproximation = (float)approximation;
	}
	time = clock() - time;
	std::cout << "My v2 function time took " << (float)time / CLOCKS_PER_SEC << "\n";
	std::cout << "\n\nInitial value: ";
	std::cout << std::setprecision(10) << value;
	std::cout << "\n\n";
	std::cout << "\n\ntest approximation: ";
	std::cout << std::setprecision(10) << secondapproximation;
	std::cout << "\n\n";
	std::cout << "\n\n1/Quake approximation: ";
	std::cout << std::setprecision(10) << thirdapproximation;
	std::cout << "\n\n";
	std::cout << "\n\nMy v1 approximation: ";
	std::cout << std::setprecision(10) << fltapproximation;
	std::cout << "\n\n";
	std::cout << "\n\nMy v2 approximation: ";
	std::cout << std::setprecision(10) << v2fltapproximation;
	std::cout << "\n\n";
	std::cout << "\n\nTrue value: ";
	std::cout << std::setprecision(10) << True;
	std::cout << "\n\n";
}