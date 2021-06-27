#pragma once
#ifndef DETALLE_H
#define DETALLE_H

#include <iostream>
#include <fstream>
#include <vector>
#include "DelimTextBuffer.h"
#include <string>
using namespace std;

class Detalle {
public:
	//Constructores

	//factura_id, producto_id, cantidad, prrecio_unit
	Detalle(int, int, int, float);
	Detalle();

	//Funciones de Lectura y Escritura con Buffers
	int Write(ostream&, DelimTextBuffer&);
	int Read(istream&, DelimTextBuffer&);
	int Pack(DelimTextBuffer&);
	int Unpack(DelimTextBuffer&);

	void print();
	//Atributos
	int id;
	int factura_id;
	int producto_id;
	int cantidad;
	float precio_unit;

	int posicion;
	int size;

	int getNextId(bool next = true);
private:
	//Obtener siguiente id autoIncremental
	void setNextId(int);
};

#endif // !DETALLE_H