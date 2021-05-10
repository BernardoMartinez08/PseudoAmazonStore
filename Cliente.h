#pragma once
#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <fstream>
using namespace std;

class Cliente {
public:
	//Constructores

	//codigo, primer_nombre, segundo_nombre, primer_apellido, segundo_apellido, genero, ciudad, region, pais
	Cliente(char*, char*, char*, char*, char*, char*, char*, char*, char*);
	Cliente();


	//Guardar cliente en el archivo principal
	void guardar_en_archivo(Cliente*);
	//Guardar cliente en los archivos de Indices
	void guardar_en_indices(Cliente*);

	//Obtener la posicion del cliente en el indice
	long searchPosicion(int);

	void set_codigo(char*);
	void set_primer_nombre(char*);
	void set_segundo_nombre(char*);
	void set_primer_apellido(char*);
	void set_segundo_apellido(char*);
	void set_genero(char*);
	void set_ciudad(char*);
	void set_region(char*);
	void set_pais(char*);
	void set_posicion(long);
	void set_size(long);

	char* get_codigo();
	char* get_primer_nombre();
	char* get_segundo_nombre();
	char* get_primer_apellido();
	char* get_segundo_apellido();
	char* get_genero();
	char* get_ciudad();
	char* get_region();
	char* get_pais();
	long get_posicion();
	long get_size();


private:
	int id;
	char* codigo;
	char* primer_nombre;
	char* segundo_nombre;
	char* primer_apellido;
	char* segundo_apellido;
	char* genero;
	char* ciudad;
	char* region;
	char* pais;

	long posicion;
	long size;

	//Obtener siguiente id autoIncremental
	int getNextId();
	void setNextId(int);
};

#endif // !CLIENTE_H
