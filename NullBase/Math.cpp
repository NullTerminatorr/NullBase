#include "Includes.h"
#include <intrin.h>

D3DXVECTOR3 CalcAngle(register const D3DXVECTOR3& src, register const D3DXVECTOR3& dst)
{
	//square root func faster than normal func youd use
	const auto sqrtss = [](float in) {
		__m128 reg = _mm_load_ss(&in);
		return _mm_mul_ss(reg, _mm_rsqrt_ss(reg)).m128_f32[0];
	};


	D3DXVECTOR3 angles;

	//getting delta between source and destination vectors
	D3DXVECTOR3 delta = src - dst;

	//finding the hypoteneuse using pythagoras theorem a squared + b squared = c squared
	//this gives us the vector to our enemy
	float hyp = sqrtss(delta.x * delta.x + delta.y * delta.y);

	//now we need to find the angle needed to aim at the vector (aim angles)
	angles.x = asinf(delta.z / hyp)		* (180.0f / M_PI);
	angles.y = atanf(delta.y / delta.x)	* (180.0f / M_PI) + !((*(DWORD*)&delta.x) >> 31 & 1) * 180.0f;

	//!((*(DWORD*)&delta.x) >> 31 & 1) * 180.0f; is basically the if statement bellow - it removes code branching for better performance
	//if (delta.x >= 0.0)
	//	angles.y += 180.0;

	angles.z = 0.0f;

	return angles;
}
