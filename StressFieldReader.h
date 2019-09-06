#pragma once

#include "BinaryReader.h"
#include <vector>
#include <string>

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
	) : sigma_x(_sigma_x),sigma_y(_sigma_y),sigma_z(_sigma_z), 
		tau_zy(_tau_zy), tau_zx(_tau_zx), tau_xy(_tau_xy)
	{}


	float sigma_x;
	float sigma_y;
	float sigma_z;

	float tau_zy;
	float tau_zx;
	float tau_xy;
};





class StressFieldReader
{

private:
	std::string fileName = "";
	std::string filePath = "";

	BinaryReader binaryReader;
	std::vector<char> Buffer;

	StressTensor* tensorField = nullptr;

	int gridSize[3] = { 0,0,0 };
	float gridDiameter[3] = { 0.0f,0.0f,0.0f };

public:

	StressFieldReader(std::string _fileName, std::string _filePath)
	{
		this->fileName = _fileName;
		this->filePath = _filePath;
	}
	StressTensor * getField()
	{
		return this->tensorField;
	}

	void setFileName(std::string _fileName)
	{
		this->fileName = _fileName;
	}

	void setFilePath(std::string _filePath)
	{
		this->filePath = _filePath;
	}

	void setGridSize(int* _gridSize)
	{
		this->gridSize[0] = _gridSize[0];
		this->gridSize[1] = _gridSize[1];
		this->gridSize[2] = _gridSize[2];
	}

	void setGridDiameter(float* _gridDiameter)
	{
		this->gridDiameter[0] = _gridDiameter[0];
		this->gridDiameter[1] = _gridDiameter[1];
		this->gridDiameter[2] = _gridDiameter[2];
	}

	StressTensor* readField()
	{
		this->binaryReader.setfileName(this->fileName.c_str());
		this->binaryReader.setfilePath(this->filePath.c_str());
		this->binaryReader.customRead(0, (size_t)gridSize[0] * (size_t)gridSize[1] * (size_t)gridSize[2] * sizeof(StressTensor));
		this->tensorField = reinterpret_cast<StressTensor*>(this->binaryReader.flush_buffer());

		return tensorField;
	}

	void cleanBuffer()
	{
		this->binaryReader.clean_buffer();
	}
};