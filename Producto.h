#pragma once
#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <fstream>
using namespace std;

class Producto {
public:
	//Constructores
	
	//codigo, categoria, sub_categoria, nombre, descripcion, precio_actual
	Producto(const char*, const char*, const char*, const char*, const char*, float);
	Producto();


	//Guardar producto en el archivo principal
	void guardar_en_archivo(Producto*);
	//Guardar producto en los archivos de Indices
	void guardar_en_indices(Producto*);

	//Obtener la posicion del producto en el indice
	long searchPosicion(int);
	
	
	void set_codigo(const char*);
	void set_categoria(const char*);
	void set_sub_categoria(const char*);
	void set_nombre(const char*);
	void set_descripcion(const char*);
	void set_precio_actual(float);
	void set_posicion(long);
	void set_size(long);

	char* get_codigo();
	char* get_categoria();
	char* get_sub_categoria();
	char* get_nombre();
	char* get_descripcion();
	int get_precio_actual();
	long get_posicion();
	long get_size();


	//Funciones de Lectura y Escritura con Buffers
	int Write(DelimTextBuffer&);
	int Read(DelimTextBuffer&, int posicion);
	int Pack(DelimTextBuffer&);
	int Unpack(DelimTextBuffer&);


private:
	int id;
	char* codigo;
	char* categoria;
	char* sub_categoria;
	char* nombre;
	char* descripcion;
	float precio_actual;

	long posicion;
	long size;

	//Obtener siguiente id autoIncremental
	int getNextId();
	void setNextId(int);
};

#endif // !PRODUCTO_H
