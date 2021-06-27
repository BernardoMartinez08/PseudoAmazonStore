#pragma once
#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <fstream>
#include <vector>
#include "DelimTextBuffer.h"
#include <string>
#include <cstdlib>

using namespace std;

class Cliente {
public:
	//Constructores

	//codigo, primer_nombre, segundo_nombre, primer_apellido, segundo_apellido, genero, ciudad, region, pais
	Cliente(const char*, const char*, const char*, const char*, const char*, const char*, const char*, const char*, const char*);
	Cliente();

	bool set_codigo(const char*);
	bool set_primer_nombre(const char*);
	bool set_segundo_nombre(const char*);
	bool set_primer_apellido(const char*);
	bool set_segundo_apellido(const char*);
	bool set_genero(const char*);
	bool set_ciudad(const char*);
	bool set_region(const char*);
	bool set_pais(const char*);

	//Funciones de Lectura y Escritura con Buffers
	int Write(ostream&, DelimTextBuffer&);
	int Read(istream&, DelimTextBuffer&);
	int Pack(DelimTextBuffer&);
	int Unpack(DelimTextBuffer&);

	void print();
	//Atributos
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

	int posicion;
	int size;
	char* nombreCompleto();

	int getNextId(bool next = true);
	void setNextId(int);
private:
	bool set_id(int);
	//Obtener siguiente id autoIncremental
};

#endif // !CLIENTE_H
