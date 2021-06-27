#pragma once
#ifndef FACTURA_H
#define FACTURA_H

#include <iostream>
#include <fstream>
#include <vector>
#include "DelimTextBuffer.h"
#include <string>
using namespace std;

class Factura {
public:
	//Constructores

	//codigo, cliente_id, dia, mes, anio, hora, total_neto, total_impuesto, ubicacion.y, ubicacion.x
	Factura(const char*, int, int, int, int, const char*, float, float, float, float);
	Factura();

	bool set_codigo(const char*);
	bool set_hora(const char*);

	//Funciones de Lectura y Escritura con Buffers
	int Write(ostream&, DelimTextBuffer&);
	int Read(istream&, DelimTextBuffer&);
	int Pack(DelimTextBuffer&);
	int Unpack(DelimTextBuffer&);

	void print();
	//Atributos
	int id;
	char* codigo;
	int cliente_id;
	int dia;
	int mes;
	int anio;
	char* hora;
	float total_neto;
	float total_impuesto;
	float ubicacion_Y;
	float ubicacion_X;

	int posicion;
	int size;

	int getNextId(bool next = true);
private:
	bool set_id(int);
	void setNextId(int);
};

#endif // !FACTURA_H