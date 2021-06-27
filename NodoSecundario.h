#pragma once
#ifndef NODO_SECUNDARIO_H
#define NODO_SECUNDARIO_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class NodoSecundario {
	friend ostream& operator<<(ostream&, const NodoSecundario&);
	friend istream& operator>>(istream&, NodoSecundario&);
public:
	NodoSecundario();

	bool set_key(const char*);

	char* key;
	int id;
};
#endif // !NODO_SECUNDARIO_H