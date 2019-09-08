#pragma once

#include "BinaryReader.h"
#include <string>
#include "StressTensor.h"


// It is an child of BinaryReader
// The only difference is that this class returns a pointer
// of type StressTensor

class StressFieldReader : public BinaryReader
{

private:

	StressTensor* tensorField = nullptr;

public:


	StressFieldReader() {}

	StressTensor * getField()
	{
		return this->tensorField;
	}


	StressTensor* readField(size_t size)
	{
		this->customRead(0, size);
		this->tensorField = reinterpret_cast<StressTensor*>(this->flush_buffer());
		return tensorField;
	}

};