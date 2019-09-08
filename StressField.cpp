#include "StressField.h"
#include "linearIndex.h"

void StressField::readField()
{
	this->stressFieldReader.setFileName(this->stressFieldOptions.fileName);
	this->stressFieldReader.setFilePath(this->stressFieldOptions.filePath);
	this->field = this->stressFieldReader.readField
	(
		this->stressFieldOptions.gridSize[0] *
		this->stressFieldOptions.gridSize[1] *
		this->stressFieldOptions.gridSize[2] *
		sizeof(StressTensor)
	);

}



StressTensor StressField::getTensor(const float & x, const float & y, const float & z)
{
	StressTensor stressTensor = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

	size_t x0 = size_t(x);
	size_t y0 = size_t(y);
	size_t z0 = size_t(z);

	size_t x1 = x0;
	size_t y1 = y0;
	size_t z1 = z0;

	

	// In this way the boundries won't be a problem
	if (x0 != x)
		x1 += 1;

	if (y0 != y)
		y1 += 1;

	if (z0 != z)
		z1 += 1;
		
	float delta_x = x - x0;
	float delta_y = y - y0;
	float delta_z = z - z0;

	size_t3 edges[8] =
	{
		{x0,y0,z0},		//(0,0,0)	-> edges[0]
		{x1,y0,z0},		//(1,0,0)	-> edges[1]
		{x0,y1,z0},		//(0,1,0)	-> edges[2]
		{x0,y0,z1},		//(0,0,1)	-> edges[3]
		{x1,y0,z1},		//(1,0,1)	-> edges[4]
		{x0,y1,z1},		//(0,1,1)	-> edges[5]
		{x1,y1,z0},		//(1,1,0)	-> edges[6]
		{x1,y1,z1}		//(1,1,1)	-> edges[7]
	
	};

	size_t4 dim = 
	{ 
		this->stressFieldOptions.gridSize[0],
		this->stressFieldOptions.gridSize[1],
		this->stressFieldOptions.gridSize[2],
		6 // The Stress Tensor can be represented by 6 element as it is symmetric
	};
	
	size_t zz = linearIndex(edges[0], dim);

	StressTensor mm = this->field[zz];
	
	
	stressTensor =
		this->field[linearIndex(edges[0], dim)] * (1 - delta_x) * (1 - delta_y) * (1 - delta_z) +
		this->field[linearIndex(edges[1], dim)] * delta_x * (1 - delta_y) * (1 - delta_z) +
		this->field[linearIndex(edges[2], dim)] * (1 - delta_x) * delta_y * (1 - delta_z) +
		this->field[linearIndex(edges[3], dim)] * (1 - delta_x) * (1 - delta_y) * delta_z +
		this->field[linearIndex(edges[4], dim)] * delta_x * (1 - delta_y) * delta_z +
		this->field[linearIndex(edges[5], dim)] * (1 - delta_x) * delta_y* delta_z +
		this->field[linearIndex(edges[6], dim)] * delta_x * delta_y * (1 - delta_z) +
		this->field[linearIndex(edges[7], dim)] * delta_x * delta_y * delta_z;

	return stressTensor;
}
