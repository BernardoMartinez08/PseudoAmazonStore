#pragma once
#ifndef FACTURA_H
#define FACTURA_H

#include <iostream>
#include <fstream>
#include <vector>
#include "DelimTextBuffer.h"
using namespace std;

class Factura {
public:
	//Constructores

	//codigo, cliente_id, fecha, hora, total_neto, total_impuesto, ubicacion.y, ubicacion.x
	Factura(const char*, int, const char*, const char*, float, float, float, float);
	Factura();

	bool set_codigo(const char*);
	bool set_fecha(const char*);
	bool set_hora(const char*);

	//Obtener la posicion del cliente en el indice
	vector<int> searchCliente(int);

	bool WriteDataonIndex(ostream& fileIndex);
	bool WriteDataonIndexByCode();
	bool WriteDataonIndexByName();

	//Funciones de Lectura y Escritura con Buffers
	int Write(ostream&, ostream&, DelimTextBuffer&);
	int Read(istream&, DelimTextBuffer&);
	int Pack(DelimTextBuffer&);
	int Unpack(DelimTextBuffer&);

	//Buscar en los indices por codigo y por nombre.
	int searchFacturaByCode(const char*);
	int searchFacturaByCliente(int);

	void print();
	//Atributos
	int id;
	char* codigo;
	int cliente_id;
	char* fecha;
	char* hora;
	float total_neto;
	float total_impuesto;
	float ubicacion_Y;
	float ubicacion_X;

	int posicion;
	int size;

	int getNextId();
private:
	bool set_id(int);
	//Obtener siguiente id autoIncremental
	void setNextId(int);

	vector<vector<int>>* getIndiceID();
};

#endif // !FACTURA_H