#pragma once
#ifndef NODO_INVERTIDO_LISTA_H
#define NODO_INVERTIDO_LISTA_H

#include <iostream>
#include <fstream>
using namespace std;

class NodoInvertidoLista {
	friend ostream& operator<<(ostream&, const NodoInvertidoLista&);
	friend istream& operator>>(istream&, NodoInvertidoLista&);
public:
	NodoInvertidoLista();

	long position;
};

#endif // !NODO_INVERTIDO_LISTA_H