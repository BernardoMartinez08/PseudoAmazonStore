#include "Factura.h"

Factura::Factura() : codigo(nullptr), cliente_id(-1), dia(0), mes(0), anio(0), hora(nullptr), total_neto(0), total_impuesto(0), ubicacion_Y(0), ubicacion_X(0){
	size = 0;
	posicion = 0;
	id = -1;
}

Factura::Factura(const char* _codigo, int _cliente_id, int _dia, int _mes, int _anio, const char* _hora, float _total_neto, float _total_impuesto, float _ubicacion_Y, float _ubicacion_X) {
	set_codigo(_codigo);
	cliente_id = _cliente_id;
	dia = _dia;
	mes = _mes;
	anio = _anio;
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
	tmp = std::to_string(cliente_id);
	resultado = resultado && _buffer.Pack(tmp.c_str());
	tmp = std::to_string(dia);
	resultado = resultado && _buffer.Pack(tmp.c_str());
	tmp = std::to_string(mes);
	resultado = resultado && _buffer.Pack(tmp.c_str());
	tmp = std::to_string(anio);
	resultado = resultado && _buffer.Pack(tmp.c_str());
	resultado = resultado && _buffer.Pack(hora);
	tmp = std::to_string(total_neto);
	resultado = resultado && _buffer.Pack(tmp.c_str());
	tmp = std::to_string(total_impuesto);
	resultado = resultado && _buffer.Pack(tmp.c_str());
	tmp = std::to_string(ubicacion_Y);
	resultado = resultado && _buffer.Pack(tmp.c_str());
	tmp = std::to_string(ubicacion_X);
	resultado = resultado && _buffer.Pack(tmp.c_str());
	return resultado;
}

int Factura::Unpack(DelimTextBuffer& _buffer) {
	int resultado = 1;
	resultado = this->size = _buffer.BufferSize;
	resultado = set_id(atoi(_buffer.Unpack((char*)id)));
	resultado = set_codigo(_buffer.Unpack(codigo));
	resultado = cliente_id = atoi(_buffer.Unpack((char*)cliente_id));
	resultado = dia = atoi(_buffer.Unpack((char*)dia));
	resultado = mes = atoi(_buffer.Unpack((char*)mes));
	resultado = anio = atoi(_buffer.Unpack((char*)anio));
	resultado = set_hora(_buffer.Unpack(hora));
	resultado = total_neto = atof(_buffer.Unpack((char*)&total_neto));
	resultado = total_impuesto = atof(_buffer.Unpack((char*)&total_impuesto));
	resultado = ubicacion_Y = atof(_buffer.Unpack((char*)&ubicacion_Y));
	resultado = ubicacion_X = atof(_buffer.Unpack((char*)&ubicacion_X));

	return resultado;
}

int Factura::Read(istream& file, DelimTextBuffer& _delim) {
	int resultado = 0;
	resultado = _delim.Read(file);
	resultado = resultado && this->Unpack(_delim);
	return resultado;
}

int Factura::Write(ostream& file, DelimTextBuffer& _delim) {
	int resultado = 0;
	posicion = file.tellp();
	resultado = this->Pack(_delim);
	resultado = resultado && _delim.Write(file);
	return resultado;
}

void Factura::print() {
	cout << "\nId: " << id
		<< "\nCodigo: " << codigo
		<< "\nId Cliente: " << cliente_id
		<< "\nFecha: " << dia << "/" << mes << "/" << anio
		<< "\nHora: " << hora
		<< "\nTotal Neto: " << total_neto
		<< "\nTotal Impuestos: " << total_impuesto
		<< "\nUbicacion (X,Y): " << "(" << ubicacion_X << "," << ubicacion_Y << ")\n";
}







//Funciones Prototipo de funciones mas avanzadas.

int Factura::getNextId(bool next) {
	ifstream auxID("facturas.index", ios::in | ios::binary | ios::_Nocreate);

	if (!auxID) {
		setNextId(0);
	}
	auxID.close();

	ifstream indiceIds("facturas.index", ios::in | ios::binary);

	if (!indiceIds) {
		cout << "Error al intentar abrir el archivo .index\n\n";
		return -1;
	}

	indiceIds.seekg(0, ios::beg);

	int _nextId;
	indiceIds.read(reinterpret_cast<char*>(&_nextId), 4);
	indiceIds.close();

	if (next == true)
		setNextId(_nextId);

	return _nextId;
}

void Factura::setNextId(int _lastId) {
	ofstream indiceIds("facturas.index", ios::out | ios::binary);

	if (!indiceIds) {
		cout << "Error al intentar abrir el archivo .index\n\n";
		return;
	}

	int newID = _lastId + 1;

	indiceIds.seekp(0, ios::beg);
	indiceIds.write(reinterpret_cast<const char*>(&newID), sizeof(newID));

	indiceIds.close();
}

