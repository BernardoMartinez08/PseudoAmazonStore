#include "Cliente.h"

Cliente::Cliente() : codigo(nullptr), primer_nombre(nullptr), segundo_nombre(nullptr), primer_apellido(nullptr), segundo_apellido(nullptr), genero(nullptr), pais(nullptr), region(nullptr), ciudad(nullptr) {

}

Cliente::Cliente(char* _codigo, char* _primer_nombre, char* _segundo_nombre, char* _primer_apellido, char* _segundo_apellido, char* _genero, char* _ciudad, char* _region, char* _pais) {

	codigo = new char[strlen(_codigo)];
	strcpy_s(codigo, strlen(_codigo) + 1, _codigo);

	primer_nombre = new char[strlen(_primer_nombre)];
	strcpy_s(primer_nombre, strlen(_primer_nombre) + 1, _primer_nombre);

	segundo_nombre = new char[strlen(_segundo_nombre)];
	strcpy_s(segundo_nombre, strlen(_segundo_nombre) + 1, _segundo_nombre);

	primer_apellido = new char[strlen(_primer_apellido)];
	strcpy_s(primer_apellido, strlen(_primer_apellido) + 1, _primer_apellido);

	segundo_apellido = new char[strlen(_segundo_apellido)];
	strcpy_s(segundo_apellido, strlen(_segundo_apellido) + 1, _segundo_apellido);

	genero = new char[strlen(_genero)];
	strcpy_s(genero, strlen(_genero) + 1, _genero);

	ciudad = new char[strlen(_ciudad)];
	strcpy_s(ciudad, strlen(_ciudad) + 1, _ciudad);

	region = new char[strlen(_region)];
	strcpy_s(region, strlen(_region) + 1, _region);

	pais = new char[strlen(_pais)];
	strcpy_s(pais, strlen(_pais) + 1, _pais);

	id = getNextId();
	posicion = 0;
	size = 0;
}

void Cliente::set_codigo(char* _codigo) {
	if (codigo != nullptr)
		delete codigo;


	codigo = new char[strlen(_codigo)];
	strcpy_s(codigo, strlen(_codigo) + 1, _codigo);
}

void Cliente::set_primer_nombre(char* _primer_nombre) {
	if (primer_nombre != nullptr)
		delete primer_nombre;


	primer_nombre = new char[strlen(_primer_nombre)];
	strcpy_s(primer_nombre, strlen(_primer_nombre) + 1, _primer_nombre);
}

void Cliente::set_segundo_nombre(char* _segundo_nombre) {
	if (_segundo_nombre != nullptr)
		delete segundo_nombre;


	segundo_nombre = new char[strlen(_segundo_nombre)];
	strcpy_s(segundo_nombre, strlen(_segundo_nombre) + 1, _segundo_nombre);
}

void Cliente::set_primer_apellido(char* _primer_apellido) {
	if (primer_apellido != nullptr)
		delete primer_apellido;


	primer_apellido = new char[strlen(_primer_apellido)];
	strcpy_s(primer_apellido, strlen(_primer_apellido) + 1, _primer_apellido);
}

void Cliente::set_segundo_apellido(char* _segundo_apellido) {
	if (segundo_apellido != nullptr)
		delete segundo_apellido;


	segundo_apellido = new char[strlen(_segundo_apellido)];
	strcpy_s(segundo_apellido, strlen(_segundo_apellido) + 1, _segundo_apellido);
}

void Cliente::set_genero(char* _genero) {
	if (genero != nullptr)
		delete genero;


	genero = new char[strlen(_genero)];
	strcpy_s(genero, strlen(_genero) + 1, _genero);
}

void Cliente::set_region(char* _region) {
	if (region != nullptr)
		delete region;


	region = new char[strlen(_region)];
	strcpy_s(region, strlen(_region) + 1, _region);
}

void Cliente::set_pais(char* _pais) {
	if (pais != nullptr)
		delete pais;


	pais = new char[strlen(_pais)];
	strcpy_s(pais, strlen(_pais) + 1, _pais);
}

void Cliente::set_ciudad(char* _ciudad) {
	if (ciudad != nullptr)
		delete ciudad;


	ciudad = new char[strlen(_ciudad)];
	strcpy_s(ciudad, strlen(_ciudad) + 1, _ciudad);
}

void Cliente::set_posicion(long _posicion) {
	this->posicion = _posicion;
}

void Cliente::set_size(long _size) {
	this->size = _size;
}

char* Cliente::get_codigo() {
	return this->codigo;
}

char* Cliente::get_primer_nombre() {
	return this->primer_nombre;
}

char* Cliente::get_segundo_nombre() {
	return this->segundo_nombre;
}

char* Cliente::get_primer_apellido() {
	return this->primer_apellido;
}

char* Cliente::get_segundo_apellido() {
	return this->segundo_apellido;
}

char* Cliente::get_genero() {
	return this->genero;
}

char* Cliente::get_region() {
	return this->region;
}

char* Cliente::get_pais() {
	return this->pais;
}

char* Cliente::get_ciudad() {
	return this->ciudad;
}

long Cliente::get_posicion() {
	return this->posicion;
}

long Cliente::get_size() {
	return this->size;
}

int Cliente::getNextId() {
	ifstream indiceIds("indiceIdClient.index", ios::in | ios::binary);

	if (!indiceIds) {
		cout << "Error al intentar abrir el archivo .index\n\n";
		return;
	}

	indiceIds.seekg(0, ios::beg);

	int _nextId;
	indiceIds.read(reinterpret_cast<char*>(&_nextId), 4);

	indiceIds.close();

	setNextId(_nextId);

	return _nextId;
}

void Cliente::setNextId(int _lastId) {
	ofstream indiceIds("indiceIdClient.index", ios::out | ios::app | ios::binary);

	if (!indiceIds) {
		cout << "Error al intentar abrir el archivo .index\n\n";
		return;
	}

	int newID = _lastId + 1;

	indiceIds.seekp(0, ios::beg);
	indiceIds.write(reinterpret_cast<const char*>(&newID), sizeof(_lastId));

	indiceIds.close();
}