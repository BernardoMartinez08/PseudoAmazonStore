#pragma once
#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <fstream>
#include <vector>
#include "DelimTextBuffer.h"
#include <string>
#include <cstdlib>
using namespace std;

class Producto {
public:
	//Constructores
	
	//codigo, categoria, sub_categoria, nombre, descripcion, precio_actual
	Producto(const char*, const char*, const char*, const char*, const char*, float);
	Producto();
	
	//Obtener la posicion del producto en el indice
	long searchProducto(int);
	
	bool WriteDataonIndexByCode();
	bool WriteDataonIndexByName();


	bool set_codigo(const char*);
	bool set_categoria(const char*);
	bool set_sub_categoria(const char*);
	bool set_nombre(const char*);
	bool set_descripcion(const char*);


	//Funciones de Lectura y Escritura con Buffers
	int Write(ostream&, ostream&, DelimTextBuffer&);
	int Read(istream& file,DelimTextBuffer&);
	int Pack(DelimTextBuffer&);
	int Unpack(DelimTextBuffer&);

	bool WriteDataonIndex(ostream& fileIndex);


	void print();
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

	int getNextId(bool next = true);
private:
	//Obtener siguiente id autoIncremental
	void setNextId(int);
};

#endif // !PRODUCTO_H
