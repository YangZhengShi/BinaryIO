#pragma once


#include "StringConverter.h"
#include <Windows.h>
#include <string>


// Create Error Logging for GPU
#define gpuErrchk(ans) { ErrorLogger::Log((ans), __FILE__, __LINE__); }

class ErrorLogger
{
public:
	static void Log(std::string message);
}; 


