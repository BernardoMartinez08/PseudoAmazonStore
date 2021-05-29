#include "Cliente.h"

Cliente::Cliente() : codigo(nullptr), primer_nombre(nullptr), segundo_nombre(nullptr), primer_apellido(nullptr), segundo_apellido(nullptr), genero(nullptr), pais(nullptr), region(nullptr), ciudad(nullptr) {
	size = 0;
	posicion = 0;
	id = -1;
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
	resultado = _buffer.Pack((char*)id);
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
	resultado = this->size = (int)_buffer.Unpack((char*)size);
	resultado = resultado && set_id((int)_buffer.Unpack((char*)id));
	resultado = resultado && set_codigo(_buffer.Unpack(codigo));
	resultado = resultado && set_primer_nombre(_buffer.Unpack(primer_nombre));
	resultado = resultado && set_segundo_nombre(_buffer.Unpack(segundo_nombre));
	resultado = resultado && set_primer_apellido(_buffer.Unpack(primer_apellido));
	resultado = resultado && set_segundo_apellido(_buffer.Unpack(segundo_apellido));
	resultado = resultado && set_genero(_buffer.Unpack(genero));
	resultado = resultado && set_ciudad(_buffer.Unpack(ciudad));
	resultado = resultado && set_region(_buffer.Unpack(region));
	resultado = resultado && set_pais(_buffer.Unpack(pais));

	return resultado;
}

int Cliente::Read(istream& file, DelimTextBuffer& _delim) {
	int resultado = 0;
	resultado = _delim.Read(file);
	resultado = resultado && this->Unpack(_delim);
	return resultado;
}

int Cliente::Write(ostream& file, ostream& fileIndex, DelimTextBuffer& _delim) {
	int resultado = 0;
	posicion = file.tellp();
	resultado = this->Pack(_delim);
	resultado = resultado && _delim.Write(file);
	resultado = resultado && WriteDataonIndex(fileIndex);
	return resultado;
}

void Cliente::print() {
	cout << "\nId: " << id 
		 << "\nCodigo: " << codigo
		 << "\Nombre: " << primer_nombre << " " << segundo_nombre << " " << primer_apellido << " " << segundo_apellido
	     << "\nGenero: " << genero
		 << "\nCiudad: " << ciudad
		 << "\nRegion: " << region
		 << "\nPais: " << pais << "\n";
}







//Funciones Prototipo de funciones mas avanzadas.

int Cliente::getNextId() {
	ifstream indiceIds("clientes.index", ios::in | ios::binary);

	if (!indiceIds) {
		cout << "Error al intentar abrir el archivo .index\n\n";
		return -1;
	}

	indiceIds.seekg(0, ios::beg);

	int _nextId;
	indiceIds.read(reinterpret_cast<char*>(&_nextId), 4);

	indiceIds.close();

	setNextId(_nextId);

	return _nextId;
}

void Cliente::setNextId(int _lastId) {
	ofstream indiceIds("clientes.index", ios::out | ios::app | ios::binary);

	if (!indiceIds) {
		cout << "Error al intentar abrir el archivo .index\n\n";
		return;
	}

	int newID = _lastId + 1;

	indiceIds.seekp(0, ios::beg);
	indiceIds.write(reinterpret_cast<const char*>(&newID), sizeof(newID));

	indiceIds.close();
}

vector<vector<int>>* Cliente::getIndiceID() {
	ifstream indiceIds("clientes.index", ios::in | ios::binary);

	if (!indiceIds) {
		cout << "Error al intentar abrir el archivo .index\n\n";
		return nullptr;
	}

	indiceIds.seekg(0, ios::beg);

	int _id = 0;
	long _posicion = 0;

	indiceIds.read(reinterpret_cast<char*>(&_id), 4);

	vector<vector<int>>* aux = nullptr;
	while (!indiceIds.eof()) {
		indiceIds.read(reinterpret_cast<char*>(&_id), 4);
		indiceIds.read(reinterpret_cast<char*>(&_posicion), 8);

		vector<int> auxDato;
		auxDato.push_back(_id);
		auxDato.push_back(_posicion);

		aux->push_back(auxDato);
	}

	return aux;
}

vector<int> Cliente::searchCliente(int _id) {
	
	vector<vector<int>>* _datos = getIndiceID();

	if (_datos != nullptr) {

		int derecha = _datos->size() - 1;
		int izquierda = 0;
		int centro;

		while (izquierda <= derecha)
		{
			centro = (derecha + izquierda) / 2;
			if (_datos->at(centro).at(0) == _id)
				return _datos->at(centro);
			else
				if (_id < _datos->at(centro).at(0))
					derecha = centro - 1;
				else
					izquierda = centro + 1;
		}
	}

	vector<int> aux;
	return aux;
}

bool Cliente::WriteDataonIndex(ostream& fileIndex) {
	int resultado = 0;
	resultado = resultado && fileIndex << "|";
	resultado = resultado && fileIndex << id;
	resultado = resultado && fileIndex << "|";
	resultado = resultado && fileIndex << posicion;

	//resultado = resultado && WriteDataonIndexByCode();
	//resultado = resultado && WriteDataonIndexByName();
	return resultado;
}

bool Cliente::WriteDataonIndexByCode() {
	ofstream fileIndex("clientesCode.index", ios::out | ios::app | ios::binary);

	fileIndex << (char*)codigo;
	fileIndex << "|";
	fileIndex << id;
	fileIndex << "|";

	fileIndex.close();
	return fileIndex.good();
}

bool Cliente::WriteDataonIndexByName() {
	ofstream fileIndex("clientesName.index", ios::out | ios::app | ios::binary);

	fileIndex << primer_nombre;
	fileIndex << "|";
	fileIndex << segundo_nombre;
	fileIndex << "|";
	fileIndex << primer_apellido;
	fileIndex << "|";
	fileIndex << segundo_apellido;
	fileIndex << "|";
	fileIndex << id;
	fileIndex << "|";

	fileIndex.close();
	return fileIndex.good();
}

int Cliente::searchClienteByCode(int _code) {
	ifstream fileIndex("clientesCode.index", ios::in | ios::binary);

	while (!fileIndex.eof()) {
		char code[13];
		fileIndex.getline(code, 15, '|');

		char aux[32];
		int _id = -1;
		fileIndex.getline(aux, 4, '|');
		_id = int(aux);

		if (_code == (int)code) {
			return _id;
			break;
		}
	}

	return -1;
}

int Cliente::searchClienteByName(const char* _name) {
	ifstream fileIndex("clientesName.index", ios::in | ios::binary);

	while (!fileIndex.eof()) {
		char _primer_nombre[30];
		fileIndex.getline(_primer_nombre, 32, '|');

		char _segundo_nombre[30];
		fileIndex.getline(_segundo_nombre, 32, '|');

		char _primer_apellido[30];
		fileIndex.getline(_primer_apellido, 32, '|');

		char _segundo_apellido[30];
		fileIndex.getline(_segundo_apellido, 32, '|');

		char aux[32];
		int _id = -1;
		fileIndex.getline(aux, 4, '|');
		_id = int(aux);

		char* name = new char[strlen(primer_nombre)];
		strcpy_s(name, strlen(_primer_nombre) + 1, _primer_nombre);
		strcat_s(name, strlen(name) + 2, " ");
		strcat_s(name, strlen(name) + strlen(_segundo_nombre), _segundo_nombre);
		strcat_s(name, strlen(name) + 2, " ");
		strcat_s(name, strlen(name) + strlen(_primer_apellido), _primer_apellido);
		strcat_s(name, strlen(name) + 2, " ");
		strcat_s(name, strlen(name) + strlen(_segundo_apellido), _segundo_apellido);

		if (name == _name) {
			return _id;
			break;
		}
	}

	return -1;
}