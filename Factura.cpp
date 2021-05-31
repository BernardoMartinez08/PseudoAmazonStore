#include "Factura.h"

Factura::Factura() : codigo(nullptr), cliente_id(-1), fecha(nullptr), hora(nullptr), total_neto(0), total_impuesto(0), ubicacion_Y(0), ubicacion_X(0){
	size = 0;
	posicion = 0;
	id = -1;
}

Factura::Factura(const char* _codigo, int _cliente_id, const char* _fecha, const char* _hora, float _total_neto, float _total_impuesto, float _ubicacion_Y, float _ubicacion_X) {
	set_codigo(_codigo);
	cliente_id = _cliente_id;
	set_fecha(_fecha);
	set_hora(_hora);
	total_neto = _total_neto;
	total_impuesto = _total_impuesto;
	ubicacion_Y = _ubicacion_Y;
	ubicacion_X = _ubicacion_X;

	id = getNextId();
	posicion = 0;
	size = 0;
}

bool Factura::set_id(int _id) {
	return this->id = _id;
}

bool Factura::set_codigo(const char* _codigo) {
	if (codigo != nullptr)
		delete codigo;


	codigo = new char[strlen(_codigo)];
	return strcpy_s(codigo, strlen(_codigo) + 1, _codigo);
}

bool Factura::set_fecha(const char* _fecha) {
	if (fecha != nullptr)
		delete fecha;


	fecha = new char[strlen(_fecha)];
	return strcpy_s(fecha, strlen(_fecha) + 1, _fecha);
}

bool Factura::set_hora(const char* _hora) {
	if (hora != nullptr)
		delete hora;

	hora = new char[strlen(_hora)];
	return strcpy_s(hora, strlen(_hora) + 1, _hora);
}


int Factura::Pack(DelimTextBuffer& _buffer) {
	int resultado;
	std::string tmp = std::to_string(id);
	resultado = _buffer.Pack(tmp.c_str());
	resultado = resultado && _buffer.Pack(codigo);
	resultado = resultado && _buffer.Pack((char*)cliente_id);
	resultado = resultado && _buffer.Pack(fecha);
	resultado = resultado && _buffer.Pack(hora);
	resultado = resultado && _buffer.Pack((char*)&total_neto);
	resultado = resultado && _buffer.Pack((char*)&total_impuesto);
	resultado = resultado && _buffer.Pack((char*)&ubicacion_Y);
	resultado = resultado && _buffer.Pack((char*)&ubicacion_X);

	return resultado;
}

int Factura::Unpack(DelimTextBuffer& _buffer) {
	int resultado = 1;
	resultado = this->size = _buffer.BufferSize;
	resultado = set_id(atoi(_buffer.Unpack((char*)id)));
	resultado = set_codigo(_buffer.Unpack(codigo));
	resultado = cliente_id = atoi(_buffer.Unpack((char*)cliente_id));
	resultado = set_fecha(_buffer.Unpack(fecha));
	resultado = set_hora(_buffer.Unpack(hora));
	resultado = total_neto = (float)strtod(_buffer.Unpack((char*)&total_neto), NULL);
	resultado = total_impuesto = (float)strtod(_buffer.Unpack((char*)&total_impuesto), NULL);
	resultado = ubicacion_Y = (float)strtod(_buffer.Unpack((char*)&ubicacion_Y), NULL);
	resultado = ubicacion_X = (float)strtod(_buffer.Unpack((char*)&ubicacion_X), NULL);

	return resultado;
}

int Factura::Read(istream& file, DelimTextBuffer& _delim) {
	int resultado = 0;
	resultado = _delim.Read(file);
	resultado = resultado && this->Unpack(_delim);
	return resultado;
}

int Factura::Write(ostream& file, ostream& fileIndex, DelimTextBuffer& _delim) {
	int resultado = 0;
	posicion = file.tellp();
	resultado = this->Pack(_delim);
	resultado = resultado && _delim.Write(file);
	return resultado;
}

void Factura::print() {
	cout << "\nId: " << id
		<< "\nCodigo: " << codigo
		<< "\Id Cliente: " << cliente_id
		<< "\Fecha: " << fecha
		<< "\nHora: " << hora
		<< "\nTotal Neto: " << total_neto
		<< "\nTotal Impuestos: " << total_impuesto
		<< "\nUbicacion (X,Y): " << "(" << ubicacion_X << "," << ubicacion_Y << ")\n";
}







//Funciones Prototipo de funciones mas avanzadas.

int Factura::getNextId() {
	ifstream auxID("factura.index", ios::in | ios::binary | ios::_Nocreate);

	if (!auxID) {
		setNextId(0);
	}
	
	ifstream indiceIds("factura.index", ios::in | ios::binary);

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

void Factura::setNextId(int _lastId) {
	ofstream indiceIds("factura.index", ios::out | ios::app | ios::binary);

	if (!indiceIds) {
		cout << "Error al intentar abrir el archivo .index\n\n";
		return;
	}

	int newID = _lastId + 1;

	indiceIds.seekp(0, ios::beg);
	indiceIds.write(reinterpret_cast<const char*>(&newID), sizeof(newID));

	indiceIds.close();
}

vector<vector<int>>* Factura::getIndiceID() {
	ifstream indiceIds("factura.index", ios::in | ios::binary);

	if (!indiceIds) {
		cout << "Error al intentar abrir el archivo .index\n\n";
		return nullptr;
	}

	indiceIds.seekg(0, ios::beg);

	int _id = 0;
	long _posicion = 0;

	indiceIds.read(reinterpret_cast<char*>(&_id), 4);

	vector<vector<int>>* aux = new vector<vector<int>>;
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
