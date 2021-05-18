#include "Producto.h"

Producto::Producto() : codigo(nullptr), categoria(nullptr), sub_categoria(nullptr), nombre(nullptr), descripcion(nullptr), precio_actual(0), id(0), posicion(0), size(0){

}

Producto::Producto(const char* _codigo, const char* _categoria, const char* _sub_categoria, const char* _nombre, const char* _descripcion, float _precio_actual) {

	codigo = new char[strlen(_codigo)];
	strcpy_s(codigo, strlen(_codigo) + 1, _codigo);

	categoria = new char[strlen(_categoria)];
	strcpy_s(categoria, strlen(_categoria) + 1, _categoria);

	sub_categoria = new char[strlen(_sub_categoria)];
	strcpy_s(sub_categoria, strlen(_sub_categoria) + 1, _sub_categoria);

	nombre = new char[strlen(_nombre)];
	strcpy_s(nombre, strlen(_nombre) + 1, _nombre);

	descripcion = new char[strlen(_descripcion)];
	strcpy_s(descripcion, strlen(_descripcion) + 1, _descripcion);

	precio_actual = _precio_actual;

	id = getNextId();
	posicion = 0;
	size = 0;
}

void Producto::set_codigo(const char* _codigo) {
	if (codigo != nullptr)
		delete codigo;


	codigo = new char[strlen(_codigo)];
	strcpy_s(codigo, strlen(_codigo) + 1, _codigo);
}

void Producto::set_categoria(const char* _categoria) {
	if (categoria != nullptr)
		delete categoria;


	categoria = new char[strlen(_categoria)];
	strcpy_s(categoria, strlen(_categoria) + 1, _categoria);
}

void Producto::set_sub_categoria(const char* _sub_categoria) {
	if (sub_categoria != nullptr)
		delete sub_categoria;


	sub_categoria = new char[strlen(_sub_categoria)];
	strcpy_s(sub_categoria, strlen(_sub_categoria) + 1, _sub_categoria);
}

void Producto::set_nombre(const char* _nombre) {
	if (nombre != nullptr)
		delete nombre;


	nombre = new char[strlen(_nombre)];
	strcpy_s(nombre, strlen(_nombre) + 1, _nombre);
}

void Producto::set_descripcion(const char* _descripcion) {
	if (descripcion != nullptr)
		delete descripcion;


	descripcion = new char[strlen(_descripcion)];
	strcpy_s(descripcion, strlen(_descripcion) + 1, _descripcion);
}

void Producto::set_precio_actual(float _precio_actual) {
	this->precio_actual = _precio_actual;
}

void Producto::set_posicion(long _posicion) {
	this->posicion = _posicion;
}

void Producto::set_size(long _size) {
	this->size = _size;
}

char* Producto::get_codigo() {
	return this->codigo;
}

char* Producto::get_categoria() {
	return this->categoria;
}

char* Producto::get_sub_categoria() {
	return this->sub_categoria;
}

char* Producto::get_nombre() {
	return this->nombre;
}

char* Producto::get_descripcion() {
	return this->descripcion;
}

int Producto::get_precio_actual() {
	return this->precio_actual;
}

long Producto::get_posicion() {
	return this->posicion;
}

long Producto::get_size() {
	return this->size;
}

int Producto::getNextId() {
	ifstream indiceIds("indiceIdProduct.index", ios::in | ios::binary);

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

void Producto::setNextId(int _lastId) {
	ofstream indiceIds("indiceIdProduct.index", ios::out | ios::app | ios::binary);

	if (!indiceIds) {
		cout << "Error al intentar abrir el archivo .index\n\n";
		return;
	}

	int newID = _lastId + 1;

	indiceIds.seekp(0, ios::beg);
	indiceIds.write(reinterpret_cast<const char*>(&newID), sizeof(_lastId));

	indiceIds.close();
}

long Producto::searchProducto(int _id) {
	ifstream indiceIds("indiceIdProduct.index", ios::in | ios::binary);

	if (!indiceIds) {
		cout << "Error al intentar abrir el archivo .index\n\n";
		return;
	}

	indiceIds.seekg(0, ios::beg);

	int _idAux;
	int _posicionAux;
	int _sizeAux;

	indiceIds.read(reinterpret_cast<char*>(&_idAux), 4);
	indiceIds.read(reinterpret_cast<char*>(&_posicionAux), 4);
	indiceIds.read(reinterpret_cast<char*>(&_sizeAux), 4);

	while (!indiceIds.eof()) {
		if (_id != _idAux) {
			indiceIds.read(reinterpret_cast<char*>(&_idAux), 4);
			indiceIds.read(reinterpret_cast<char*>(&_posicionAux), 4);
			indiceIds.read(reinterpret_cast<char*>(&_sizeAux), 4);
		}
		else {
			indiceIds.close();
			return _posicionAux;
		}
	}

	indiceIds.close();
	return -1;
}

//Trabajare aqui 


int Producto::Pack(DelimTextBuffer& _buffer)
{
	int resultado;

	resultado = _buffer.Pack((char*)id);
	resultado = resultado && _buffer.Pack(codigo);
	resultado = resultado && _buffer.Pack(categoria)
	resultado = resultado && _buffer.Pack(sub_categoria);
	resultado = resultado && _buffer.Pack(nombre);
	resultado = resultado && _buffer.Pack(descripcion);
	resultado = resultado && _buffer.Pack(precio_actual);


	return resultado;
}

int Producto::Unpack(DelimTextBuffer& _buffer)
{
	int resultado = 1;
	resultado = set_size(_ buffer.BufferSize);
	resultado = resultado && set_codigo(_buffer.Unpack(codigo));
	resultado = resultado && set_categoria(_buffer.Unpack(categoria));
	resultado = resultado && set_sub_categoria(_buffer.Unpack(sub_categoria));
	resultado = resultado && set_nombre(_buffer.Unpack(nombre));
	resultado = resultado && set_descripcion(_ buffer.Unpack(descripcion));
	resultado = resultado && set_precio_actual(_buffer.Unpack(precio_actual));

	return resultado;


}

int Producto::Read(DelimTextBuffer& _delim, int _id)
{
	//Revision->
	vector<int> _datos = searchProducto(_id);

	int resultado = 0;

	if (_datos.size() != 0)
	{
		int posicion = _datos[1];

		//Revision ->
		ifstream file("indiceIdProduct.data", ios::in | ios::binary);

		vector<int> _datos = searchProducto(_id);

		resultado = _delim.Read(file, posicion);
		resultado = resultado && this->Upack(_delim);

		file.close();
	}

	return resultado;
}

int Producto::Write(DelimTextBuffer& _delim)
{
	int resultado = 0;

	ofstream file("indiceIdProduct.data", ios::out | ios::app | ios::binary);
	ofstream fileIndex("indiceProduct.index", ios::out | ios::app | ios::binary);


	resultado = this->Pack(_delim);
	posicion = file.tellp();
	resultado = resultado && _delim.Write(file);

	//Revision -> me salio bien solo con &
	resultado = resultado & WriteDataonIndex(fileIndex);

	fill.close();

	fileIndex.close();

	return resultado;
}


bool Producto::WriteDataonIndex(ofstream& fileIndex)
{
	int resultado;
	//Revision && doble 
	resultado = resultado &fileIndex << "|";
	resultado = resultado & fileIndex << id;
	resultado = resultado & fileIndex << "|";
	resultado = resultado & fileIndex << posicion;

	resultado = resultado & WriteDataonIndexByCode();
	resultado = resultado & WriteDataonIndexByName();
	return resultado;

}

bool Producto::WriteDataonIndexByCode()
{
	ofstream fileIndex("indiceIdProduct.index", ios::out | ios::app | ios::binary);

	fileIndex << (char)codigo;
	fileIndex << "|";
	fileIndex << id;
	fileIndex << "|";

	fileIndex.close();
	return fileIndex.good();
}