#include "DelimBuffer.h"

DelimBuffer::DelimBuffer(char _delim, int _maxBytes) {
	this->Delim = _delim;
	this->MaxBytes = _maxBytes;
	this->Buffer = nullptr;
	this->BufferSize = 0;
	this->NextByte = 0;
}

