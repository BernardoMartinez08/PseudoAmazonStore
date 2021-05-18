#pragma once
#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <fstream>
#include <vector>
#include "DelimTextBuffer.h"
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
	bool set_posicion(long);
	bool set_size(long);

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

	//Obtener la posicion del cliente en el indice
	vector<int> searchCliente(int);

	bool WriteDataonIndex(ofstream& fileIndex);
	bool WriteDataonIndexByCode();
	bool WriteDataonIndexByName();

	int Write(DelimTextBuffer&);
	int Read(DelimTextBuffer&, int posicion);
	int Pack(DelimTextBuffer&);
	int Unpack(DelimTextBuffer&);

	int searchClienteByCode(int);
	int searchClienteByName(const char*);

private:
	bool set_id(int);
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

	//Obtener siguiente id autoIncremental
	int getNextId();
	void setNextId(int);

	vector<vector<int>>* getIndiceID();
};

#endif // !CLIENTE_H
