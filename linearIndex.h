#pragma once


typedef unsigned int uint;

struct size_t4
{
	size_t4(size_t _x, size_t _y, size_t _z, size_t _w) :
		x(_x), y(_y), z(_z), w(_w) {};

	size_t x;
	size_t y;
	size_t z;
	size_t w;
};

struct size_t3
{
	size_t3(size_t _x, size_t _y, size_t _z) :
		x(_x), y(_y), z(_z) {};

	size_t x;
	size_t y;
	size_t z;

};


struct int4
{
	int4(int _x, int _y, int _z, int _w) :
		x(_x), y(_y), z(_z), w(_w) {};

	int x;
	int y;
	int z;
	int w;
};

struct int3
{
	int3(int _x, int _y, int _z) :
		x(_x), y(_y), z(_z) {};

	int x;
	int y;
	int z;

};

struct float3
{
	float3(float _x, float _y, float _z) :
		x(_x), y(_y), z(_z) {};

	float x;
	float y;
	float z;

};



//return the index of an element in the sequential form based on its index in tensor form (4D)
inline size_t linearIndex(uint x, uint y, uint z, uint w, size_t4 & dim)
{
	size_t index = 0;
	index += (size_t)x * dim.y *dim.z * dim.w;
	index += (size_t)y * dim.z * dim.w;
	index += (size_t)z * dim.w;
	index += (size_t)w;

	return index;
}

inline size_t linearIndex(int4 & position, size_t4 & dim)
{
	size_t index = 0;
	index += (size_t)position.x * dim.y * dim.z * dim.w;
	index += (size_t)position.y * dim.z * dim.w;
	index += (size_t)position.z * dim.w;
	index += (size_t)position.w;

	return index;
}



//return the index of an element in the sequential form based on its index in tensor form (3D)
inline size_t linearIndex(uint x, uint y, uint z, size_t4 & dim)
{
	size_t index = 0;
	index += (size_t)x * dim.y *dim.z;
	index += (size_t)y * dim.z;
	index += (size_t)z;


	return index;
}

inline size_t linearIndex(size_t3 position, size_t4& dim)
{
	size_t index = 0;
	index += position.x * dim.y * dim.z;
	index += position.y * dim.z;
	index += position.z;


	return index;
}