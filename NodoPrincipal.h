#pragma once
#ifndef NODO_PRINCIPAL_H
#define NODO_PRINCIPAL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class NodoPrincipal {
	friend ostream& operator<<(ostream&, const NodoPrincipal&);
	friend istream& operator>>(istream&, NodoPrincipal&);
public:
	NodoPrincipal();

	int id;
	long posicion;
};
#endif // !NODO_PRINCIPAL_H