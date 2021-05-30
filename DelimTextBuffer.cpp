#include "DelimTextBuffer.h"


DelimTextBuffer::DelimTextBuffer(char _delim, int _maxBytes) {
	this->Delim = _delim;
	this->MaxBytes = _maxBytes;

	this->Buffer = new char[_maxBytes];
	this->BufferSize = 0;
	this->NextByte = 0;
}

int DelimTextBuffer::Read(istream& file) {
	Clear();
	file.read((char*)&BufferSize, sizeof(BufferSize));

	if (file.fail())
		return false;

	if (BufferSize > MaxBytes)
		return false;

	file.read(Buffer, BufferSize);
	return file.good();
}

int DelimTextBuffer::Write(ostream& file) const{
	file.write((char*)&BufferSize, sizeof(BufferSize));
	
	if (file.fail())
		return false;

	file.write(Buffer, BufferSize);
	return file.good();
}

void DelimTextBuffer::Clear() {
	BufferSize = 0;
	NextByte = 0;
}

int DelimTextBuffer::Pack(const char* _cadena, int _size) {
	int tamanio = -1;
	int start = NextByte;

	cout << "\n\nTo Pack: " << _cadena;
	if (_size >= 0)
		tamanio = _size;
	else
		tamanio = strlen(_cadena);

	if (tamanio > strlen(_cadena))
		return false;

	NextByte += tamanio + 1;
	if (NextByte > MaxBytes)
		return false;

	memcpy(&Buffer[start], _cadena, tamanio);
	Buffer[start + tamanio] = Delim;

	BufferSize = NextByte;
	return true;
}

void DelimTextBuffer::setNextByte(int _nextbyte) {
	NextByte = _nextbyte;
}

char* DelimTextBuffer::Unpack(char* _cadena) {
	int tamanio = -1;
	int start = NextByte;

	for (int i = start; i < BufferSize; i++) {
		if (Buffer[i] == Delim) {
			tamanio = i - start;
			break;
		}
	}

	if (tamanio == -1)
		return nullptr;

	NextByte += tamanio + 1;

	if (NextByte > BufferSize)
		return nullptr;

	_cadena = new char[tamanio + 1];
	memcpy(_cadena, &Buffer[start], tamanio);
	_cadena[tamanio] = '\0';
	
	return _cadena;
}