#pragma once
#ifndef DELIM_BUFFER
#define DELIM_BUFFER

#include <iostream>
#include <fstream>

using namespace std;

class DelimBuffer {
public:
	DelimBuffer(char,int);

	int read(istream &);
	int write(ostream &);
	int pack(const char*, int);
	int unpack(const char*);

private:
	char Delim;
	char* Buffer;
	int BufferSize;
	int MaxBytes;
	int NextByte;
};

#endif // !DELIM_BUFFER
