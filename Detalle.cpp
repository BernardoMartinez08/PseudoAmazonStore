#include "Detalle.h"

Detalle::Detalle() : factura_id(-1), producto_id(-1), cantidad(0), precio_unit(0) {
	size = 0;
	posicion = 0;
	id = -1;
}

Detalle::Detalle(int _factura_id, int _producto_id, int _cantidad, float _precio_unit) {

	id = getNextId();
	posicion = 0;
	size = 0;
}

int Detalle::Pack(DelimTextBuffer& _buffer) {
	int resultado;
	std::string tmp = std::to_string(id);
	resultado = _buffer.Pack(tmp.c_str());
	tmp = std::to_string(factura_id);
	resultado = resultado && _buffer.Pack(tmp.c_str());
	tmp = std::to_string(producto_id);
	resultado = resultado && _buffer.Pack(tmp.c_str());
	tmp = std::to_string(cantidad);
	resultado = resultado && _buffer.Pack(tmp.c_str());
	tmp = std::to_string(precio_unit);
	resultado = resultado && _buffer.Pack(tmp.c_str());

	return resultado;
}

int Detalle::Unpack(DelimTextBuffer& _buffer) {
	int resultado = 1;
	size = _buffer.BufferSize;
	resultado = id = atoi(_buffer.Unpack((char*)id));
	resultado = factura_id = atoi(_buffer.Unpack((char*)factura_id));
	resultado = producto_id = atoi(_buffer.Unpack((char*)producto_id));
	resultado = cantidad = atoi(_buffer.Unpack((char*)cantidad));
	resultado = precio_unit = atof(_buffer.Unpack((char*)&precio_unit));

	return resultado;
}

int Detalle::Read(istream& file, DelimTextBuffer& _delim) {
	int resultado = 0;
	resultado = _delim.Read(file);
	resultado = resultado && this->Unpack(_delim);
	return resultado;
}

int Detalle::Write(ostream& file, DelimTextBuffer& _delim) {
	int resultado = 0;
	posicion = file.tellp();
	resultado = this->Pack(_delim);
	resultado = resultado && _delim.Write(file);
	return resultado;
}

void Detalle::print() {
	cout << "\nId: " << id
		<< "\nId Factura: " << factura_id
		<< "\nId Producto: " << producto_id
		<< "\nCantidad: " << cantidad
		<< "\nPrecio Unitario: " << precio_unit 
		<< "\nPrecio Total: " << (precio_unit*cantidad) << "\n";
}







//Funciones Prototipo de funciones mas avanzadas.

int Detalle::getNextId(bool next) {
	ifstream auxID("detalles.index", ios::in | ios::binary | ios::_Nocreate);

	if (!auxID) {
		setNextId(0);
	}
	auxID.close();

	ifstream indiceIds("detalles.index", ios::in | ios::binary);

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

void Detalle::setNextId(int _lastId) {
	ofstream indiceIds("detalles.index", ios::out | ios::binary);

	if (!indiceIds) {
		cout << "Error al intentar abrir el archivo .index\n\n";
		return;
	}

	int newID = _lastId + 1;

	indiceIds.seekp(0, ios::beg);
	indiceIds.write(reinterpret_cast<const char*>(&newID), sizeof(newID));

	indiceIds.close();
}
