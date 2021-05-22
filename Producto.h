#pragma once
#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <fstream>
#include <vector>
#include "DelimTextBuffer.h"
using namespace std;

class Producto {
public:
	//Constructores
	
	//codigo, categoria, sub_categoria, nombre, descripcion, precio_actual
	Producto(const char*, const char*, const char*, const char*, const char*, float);
	Producto();
	
	//Obtener la posicion del producto en el indice
	long searchProducto(int);
	
	bool set_codigo(const char*);
	bool set_categoria(const char*);
	bool set_sub_categoria(const char*);
	bool set_nombre(const char*);
	bool set_descripcion(const char*);

	//Funciones de Lectura y Escritura con Buffers
	int Write(ostream&, ostream&, DelimTextBuffer&);
	int Read(istream& file,DelimTextBuffer&, int posicion);
	int Pack(DelimTextBuffer&);
	int Unpack(DelimTextBuffer&);

	bool WriteDataonIndex(ostream& fileIndex);
	bool WriteDataonIndexByCode();
	bool WriteDataonIndexByName();

	//Atributos de la clase
	int id;
	char* codigo;
	char* categoria;
	char* sub_categoria;
	char* nombre;
	char* descripcion;
	float precio_actual;

	long posicion;
	long size;

private:
	//Obtener siguiente id autoIncremental
	int getNextId();
	void setNextId(int);
};

#endif // !PRODUCTO_H
