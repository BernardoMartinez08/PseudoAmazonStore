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
	Producto(char*, char*, char*, char*, char*, float);
	Producto();


	//Guardar producto en el archivo principal
	void guardar_en_archivo(Producto*);
	//Guardar producto en los archivos de Indices
	void guardar_en_indices(Producto*);

	//Obtener la posicion del producto en el indice
	long searchPosicion(int);
	
	
	void set_codigo(char*);
	void set_categoria(char*);
	void set_sub_categoria(char*);
	void set_nombre(char*);
	void set_descripcion(char*);
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
