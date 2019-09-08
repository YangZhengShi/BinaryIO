#pragma once
// Data structure of the stress tensor 

/*
Stress Tensor:

	|								|
	| simga_x,	tau_xy,		tau_zx	|
	|								|
	| tau_xy,	sigma_y,	tau_yz	|
	|								|
	| tau_zx,	tau_yz,		sigma_z	|
	|								|

*/


#define IDENTITY StressTensor(1.0f,1.0f,1.0f,0,0,0)
#define PI 3.14159265358979323
struct StressTensor
{
	StressTensor
	(
		float _sigma_x,
		float _sigma_y,
		float _sigma_z,
		float _tau_zy,
		float _tau_zx,
		float _tau_xy
	) : sigma_x(_sigma_x), sigma_y(_sigma_y), sigma_z(_sigma_z),
		tau_zy(_tau_zy), tau_zx(_tau_zx), tau_xy(_tau_xy)
	{}

	float sigma_x;
	float sigma_y;
	float sigma_z;

	float tau_zy;
	float tau_zx;
	float tau_xy;


	
};

inline StressTensor operator+(const StressTensor& lhs, const StressTensor& rhs)
{
	StressTensor result
	{
		 lhs.sigma_x + rhs.sigma_x,
		 lhs.sigma_y + rhs.sigma_y,
		 lhs.sigma_z + rhs.sigma_z,

		 lhs.tau_xy + rhs.tau_xy,
		 lhs.tau_zx + rhs.tau_zx,
		 lhs.tau_zy + rhs.tau_zy
	};

	return result;
}

inline StressTensor operator-(const StressTensor& lhs, const StressTensor& rhs)
{
	StressTensor result
	{
		 lhs.sigma_x - rhs.sigma_x,
		 lhs.sigma_y - rhs.sigma_y,
		 lhs.sigma_z - rhs.sigma_z,

		 lhs.tau_xy - rhs.tau_xy,
		 lhs.tau_zx - rhs.tau_zx,
		 lhs.tau_zy - rhs.tau_zy
	};

	return result;
}

inline StressTensor operator*(const StressTensor& lhs, const float & rhs)
{
	StressTensor result
	{
		 lhs.sigma_x * rhs,
		 lhs.sigma_y * rhs,
		 lhs.sigma_z * rhs,

		 lhs.tau_xy * rhs,
		 lhs.tau_zx * rhs,
		 lhs.tau_zy * rhs
	};

	return result;
}



inline StressTensor operator*(const float& lhs, const StressTensor& rhs)
{
	StressTensor result
	{
		 rhs.sigma_x * lhs,
		 rhs.sigma_y * lhs,
		 rhs.sigma_z * lhs,

		 rhs.tau_xy * lhs,
		 rhs.tau_zx * lhs,
		 rhs.tau_zy * lhs
	};

	return result;
}

