#include "Cliente.h"

Cliente::Cliente() : codigo(nullptr), primer_nombre(nullptr), segundo_nombre(nullptr), primer_apellido(nullptr), segundo_apellido(nullptr), genero(nullptr), pais(nullptr), region(nullptr), ciudad(nullptr) {
	size = 0;
	posicion = 0;
	id = 0;
}

Cliente::Cliente(const char* _codigo, const char* _primer_nombre, const char* _segundo_nombre, const char* _primer_apellido, const char* _segundo_apellido, const char* _genero, const char* _ciudad, const char* _region, const char* _pais) {

	set_codigo(_codigo);
	set_primer_nombre(_primer_nombre);
	set_segundo_nombre(segundo_nombre);
	set_primer_apellido(primer_apellido);
	set_segundo_apellido(_segundo_apellido);
	set_genero(_genero);
	set_ciudad(_ciudad);
	set_region(_region);
	set_pais(_pais);

	id = getNextId();
	posicion = 0;
	size = 0;
}

bool Cliente::set_id(int _id){
	return this->id = _id;
}

bool Cliente::set_codigo(const char* _codigo) {
	if (codigo != nullptr)
		delete codigo;


	codigo = new char[strlen(_codigo)];
	return strcpy_s(codigo, strlen(_codigo) + 1, _codigo);
}

bool Cliente::set_primer_nombre(const char* _primer_nombre) {
	if (primer_nombre != nullptr)
		delete primer_nombre;


	primer_nombre = new char[strlen(_primer_nombre)];
	return strcpy_s(primer_nombre, strlen(_primer_nombre) + 1, _primer_nombre);
}

bool Cliente::set_segundo_nombre(const char* _segundo_nombre) {
	if (segundo_nombre != nullptr)
		delete segundo_nombre;

	segundo_nombre = new char[strlen(_segundo_nombre)];
	return strcpy_s(segundo_nombre, strlen(_segundo_nombre) + 1, _segundo_nombre);
}

bool Cliente::set_primer_apellido(const char* _primer_apellido) {
	if (primer_apellido != nullptr)
		delete primer_apellido;


	primer_apellido = new char[strlen(_primer_apellido)];
	return strcpy_s(primer_apellido, strlen(_primer_apellido) + 1, _primer_apellido);
}

bool Cliente::set_segundo_apellido(const char* _segundo_apellido) {
	if (segundo_apellido != nullptr)
		delete segundo_apellido;


	segundo_apellido = new char[strlen(_segundo_apellido)];
	return strcpy_s(segundo_apellido, strlen(_segundo_apellido) + 1, _segundo_apellido);
}

bool Cliente::set_genero(const char* _genero) {
	if (genero != nullptr)
		delete genero;


	genero = new char[strlen(_genero)];
	return strcpy_s(genero, strlen(_genero) + 1, _genero);
}

bool Cliente::set_region(const char* _region) {
	if (region != nullptr)
		delete region;


	region = new char[strlen(_region)];
	return strcpy_s(region, strlen(_region) + 1, _region);
}

bool Cliente::set_pais(const char* _pais) {
	if (pais != nullptr)
		delete pais;


	pais = new char[strlen(_pais)];
	return strcpy_s(pais, strlen(_pais) + 1, _pais);
}

bool Cliente::set_ciudad(const char* _ciudad) {
	if (ciudad != nullptr)
		delete ciudad;


	ciudad = new char[strlen(_ciudad)];
	return strcpy_s(ciudad, strlen(_ciudad) + 1, _ciudad);
}

int Cliente::Pack(DelimTextBuffer& _buffer) {
	int resultado;
	std::string tmp = std::to_string(id);
	resultado = _buffer.Pack(tmp.c_str());
	resultado = resultado && _buffer.Pack(codigo);
	resultado = resultado && _buffer.Pack(primer_nombre);
	resultado = resultado && _buffer.Pack(segundo_nombre);
	resultado = resultado && _buffer.Pack(primer_apellido);
	resultado = resultado && _buffer.Pack(segundo_apellido);
	resultado = resultado && _buffer.Pack(genero);
	resultado = resultado && _buffer.Pack(ciudad);
	resultado = resultado && _buffer.Pack(region);
	resultado = resultado && _buffer.Pack(pais);

	return resultado;
}

int Cliente::Unpack(DelimTextBuffer& _buffer) {
	int resultado = 1;
	size = _buffer.BufferSize;
	resultado = set_id(atoi(_buffer.Unpack((char*)id)));
	resultado = set_codigo(_buffer.Unpack(codigo));
	resultado = set_primer_nombre(_buffer.Unpack(primer_nombre));
	resultado = set_segundo_nombre(_buffer.Unpack(segundo_nombre));
	resultado = set_primer_apellido(_buffer.Unpack(primer_apellido));
	resultado = set_segundo_apellido(_buffer.Unpack(segundo_apellido));
	resultado = set_genero(_buffer.Unpack(genero));
	resultado = set_ciudad(_buffer.Unpack(ciudad));
	resultado = set_region(_buffer.Unpack(region));
	resultado = set_pais(_buffer.Unpack(pais));

	return resultado;
}

int Cliente::Read(istream& file, DelimTextBuffer& _delim) {
	int resultado = 0;
	resultado = _delim.Read(file);
	resultado = resultado && this->Unpack(_delim);
	return resultado;
}

int Cliente::Write(ostream& file, DelimTextBuffer& _delim) {
	int resultado = 0;
	posicion = file.tellp();
	resultado = this->Pack(_delim);
	resultado = resultado && _delim.Write(file);
	//resultado = resultado && WriteDataonIndex(fileIndex);
	return resultado;
}

void Cliente::print() {
	cout << "\nId: " << id 
		 << "\nCodigo: " << codigo
		 << "\nNombre: " << primer_nombre << " " << segundo_nombre << " " << primer_apellido << " " << segundo_apellido
	     << "\nGenero: " << genero
		 << "\nCiudad: " << ciudad
		 << "\nRegion: " << region
		 << "\nPais: " << pais << "\n";
}







//Funciones Prototipo de funciones mas avanzadas.

int Cliente::getNextId(bool next) {
	ifstream auxID("clientes.index", ios::in | ios::binary | ios::_Nocreate);
	
	if (!auxID) {
		setNextId(0);
	}
	auxID.close();

	ifstream indiceIds("clientes.index", ios::in | ios::binary);

	if (!indiceIds) {
		cout << "Error al intentar abrir el archivo .index\n\n";
		return -1;
	}

	indiceIds.seekg(0, ios::beg);

	int _nextId;
	indiceIds.read(reinterpret_cast<char*>(&_nextId), 4);

	indiceIds.close();

	if(next == true)
		setNextId(_nextId);

	return _nextId;
}

void Cliente::setNextId(int _lastId) {
	ofstream indiceIds("clientes.index", ios::out | ios::binary);

	if (!indiceIds) {
		cout << "Error al intentar abrir el archivo .index\n\n";
		return;
	}

	int newID = _lastId + 1;

	indiceIds.seekp(0, ios::beg);
	indiceIds.write(reinterpret_cast<const char*>(&newID), sizeof(newID));

	indiceIds.close();
}

