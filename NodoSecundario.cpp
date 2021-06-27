#include "NodoSecundario.h"

NodoSecundario::NodoSecundario() {
	key = nullptr;
	id = 0;
}

bool NodoSecundario::set_key(const char* _key) {
	if (key != nullptr)
		delete key;


	key = new char[strlen(_key)];
	return strcpy_s(key, strlen(_key) + 1, _key);
}


ostream& operator<<(ostream& stream, const NodoSecundario& data) {
	stream
		<< data.key
		<< ","
		<< data.id
		<< ",";
	return stream;
}

istream& operator>>(istream& stream, NodoSecundario& data) {
	//Key
	char _key[25];
	stream.getline(_key, 25, ',');
	data.set_key(_key);
	
	//ID
	char _id[8];
	stream.getline(_id, 8, ',');
	data.id = atoi(_id);
	return stream;
}