#pragma once

#include <string>
#include <vector>

class BinaryReader
{

private:

	std::string m_fileName;
	std::string m_filePath;

	char* p_buffer;

public:
	BinaryReader();

	// Destructor
	~BinaryReader()
	{
		this->clean_buffer();
	}

	// fill a stream of characters into buffer
	bool read();
	bool customRead(std::streampos start, size_t size);

	//clean buffer vector
	void clean_buffer();

	// s_instance keeps track of the instances
	static unsigned int s_instances;

	// constructor assuming the path of the cpp as the filepath
	BinaryReader(const char* _fileName);
	BinaryReader(std::string _fileName);


	// constructor
	BinaryReader(const char* _fileName, const char* _filePath);
	BinaryReader(std::string _fileName, std::string _filePath);

	const char* getfileName() const;
	const char* getfilePath() const;

	void setfileName(const char* _fileName);
	void setfilePath(const char* _filePath);


	// return a pointer to the buffer 
	char* flush_buffer();
};