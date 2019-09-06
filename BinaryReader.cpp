
#include "BinaryReader.h"
#include <fstream>
#include <filesystem>

// define fs namespace for convenience
namespace fs = std::experimental::filesystem;

// keep track fo instantiation  
unsigned int BinaryReader::s_instances = 0;


// constructor
BinaryReader::BinaryReader(const char* _fileName)
{

	//increment number of instances
	s_instances += 1;

	this->m_fileName = _fileName;

	// extract the current path
	fs::path path_currentPath = fs::current_path();
	this->m_filePath = path_currentPath.u8string();

	// add a backslash at the end of path
	this->m_filePath += "\\";

}

// constructor
BinaryReader::BinaryReader(const char* _fileName, const char* _filePath)
	: m_fileName(_fileName), m_filePath(_filePath)
{}

// getter functions
const char* BinaryReader::getfileName() const
{
	return m_fileName.c_str();
}
const char* BinaryReader::getfilePath() const
{
	return m_filePath.c_str();
}

// setter
void BinaryReader::setfileName(const char* _fileName)
{
	m_fileName = std::string(_fileName);
}
void BinaryReader::setfilePath(const char* _filePath)
{
	m_filePath = std::string(_filePath);
}


bool BinaryReader::customRead(std::streampos start, std::streampos end)
{

	// define the istream
	std::ifstream myFile;

	std::string fullPath = this->m_filePath + this->m_fileName;
	myFile = std::ifstream(fullPath, std::ios::binary);

	// check whether the file is open
	if (!myFile.is_open())
		return false;


	// return to starting position
	myFile.seekg(start);

	// size of the buffer
	size_t buffer_size = static_cast<size_t>(end - start);


	this->p_buffer = new char[buffer_size];

	//read file and store it into buffer 
	myFile.read(this->p_buffer, buffer_size);

	// close the file
	myFile.close();

	return true;

}
bool BinaryReader::read()
{
	// define the istream
	std::ifstream myFile;

	std::string fullPath = m_filePath + m_fileName;
	myFile = std::ifstream(fullPath, std::ios::binary);

	// check whether the file is open
	if (!myFile.is_open())
		return false;

	// get the starting position
	std::streampos start = myFile.tellg();

	// go to the end
	myFile.seekg(0, myFile.end);

	// get the ending position
	std::streampos end = myFile.tellg();

	// return to starting position
	myFile.seekg(0, myFile.beg);

	// size of the buffer
	size_t buffer_size = static_cast<int>(end - start);

	this->p_buffer = new char[buffer_size];

	//read file and store it into buffer 
	myFile.read(this->p_buffer, buffer_size);

	// close the file
	myFile.close();

	return true;
}


char* BinaryReader::flush_buffer()
{
	return this->p_buffer;
}

void BinaryReader::clean_buffer()
{
	delete[] this->p_buffer;
}

BinaryReader::BinaryReader()
{
	this->m_fileName = "";
	this->m_filePath = "";
}
