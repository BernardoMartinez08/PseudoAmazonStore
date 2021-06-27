#pragma once
#ifndef NODO_INVERTIDO_H
#define NODO_INVERTIDO_H

#include <iostream>
#include <fstream>
#include <string>
#include "NodoInvertidoLista.h"
#include <vector>

using namespace std;

class NodoInvertido {
	friend ostream& operator<<(ostream&, const NodoInvertido&);
	friend istream& operator>>(istream&, NodoInvertido&);
public:
	NodoInvertido();

	int id;
	long posicion;
	vector<NodoInvertidoLista>* lista;
};
#endif // !NODO_INVERTIDO_H