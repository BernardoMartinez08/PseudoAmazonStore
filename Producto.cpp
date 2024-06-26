#include "Producto.h"

Producto::Producto() : codigo(nullptr), categoria(nullptr), sub_categoria(nullptr), nombre(nullptr), descripcion(nullptr), precio_actual(0), id(0), posicion(0), size(0){

}

Producto::Producto(const char* _codigo, const char* _categoria, const char* _sub_categoria, const char* _nombre, const char* _descripcion, float _precio_actual) {
	set_codigo(_codigo);
	set_categoria(_categoria);
	set_sub_categoria(_sub_categoria);
	set_nombre(_nombre);
	set_descripcion(descripcion);
	precio_actual = _precio_actual;

	id = getNextId();
	posicion = 0;
	size = 0;
}

bool Producto::set_codigo(const char* _codigo) {
	if (codigo != nullptr)
		delete codigo;

	codigo = new char[strlen(_codigo)];
	return strcpy_s(codigo, strlen(_codigo) + 1, _codigo);
}

bool Producto::set_categoria(const char* _categoria) {
	if (categoria != nullptr)
		delete categoria;

	categoria = new char[strlen(_categoria)];
	return strcpy_s(categoria, strlen(_categoria) + 1, _categoria);
}

bool Producto::set_sub_categoria(const char* _sub_categoria) {
	if (sub_categoria != nullptr)
		delete sub_categoria;

	sub_categoria = new char[strlen(_sub_categoria)];
	return strcpy_s(sub_categoria, strlen(_sub_categoria) + 1, _sub_categoria);
}

bool Producto::set_nombre(const char* _nombre) {
	if (nombre != nullptr)
		delete nombre;

	nombre = new char[strlen(_nombre)];
	return strcpy_s(nombre, strlen(_nombre) + 1, _nombre);
}

bool Producto::set_descripcion(const char* _descripcion) {
	if (descripcion != nullptr)
		delete descripcion;

	descripcion = new char[strlen(_descripcion)];
	return strcpy_s(descripcion, strlen(_descripcion) + 1, _descripcion);
}

int Producto::Pack(DelimTextBuffer& _buffer){
	int resultado;

	std::string tmp = std::to_string(id);
	resultado = _buffer.Pack(tmp.c_str());
	resultado = resultado && _buffer.Pack(codigo);
	resultado = resultado && _buffer.Pack(categoria);
	resultado = resultado && _buffer.Pack(sub_categoria);
	resultado = resultado && _buffer.Pack(nombre);
	resultado = resultado && _buffer.Pack(descripcion);
	tmp = std::to_string(precio_actual);
	resultado = resultado && _buffer.Pack(tmp.c_str());

	return resultado;
}

int Producto::Unpack(DelimTextBuffer& _buffer)
{
	int resultado = 1;
	size = _buffer.BufferSize;
	resultado = id = atoi(_buffer.Unpack((char*)id));
	resultado = set_codigo(_buffer.Unpack(codigo));
	resultado = set_categoria(_buffer.Unpack(categoria));
	resultado = set_sub_categoria(_buffer.Unpack(sub_categoria));
	resultado = set_nombre(_buffer.Unpack(nombre));
	resultado = set_descripcion(_buffer.Unpack(descripcion));
	resultado = precio_actual = atof(_buffer.Unpack((char*)&precio_actual));

	return resultado;


}

int Producto::Read(istream& file, DelimTextBuffer& _delim) {
	int resultado = 0;
	resultado = _delim.Read(file);
	resultado = resultado && this->Unpack(_delim);
	return resultado;
}

int Producto::Write(ostream& file, DelimTextBuffer& _delim) {
	int resultado = 0;
	resultado = this->Pack(_delim);
	posicion = file.tellp();
	resultado = resultado && _delim.Write(file);
	return resultado;
}







//Funciones Prototipo de funciones mas avanzadas

int Producto::getNextId(bool next) {
	ifstream auxID("identifiers.index", ios::in | ios::binary | ios::_Nocreate);

	if (!auxID) {
		setNextId(1);
	}
	auxID.close();

	ifstream indiceIds("identifiers.index", ios::in | ios::binary);

	if (!indiceIds) {
		cout << "Error al intentar abrir el archivo .index\n\n";
		return -1;
	}

	indiceIds.seekg(5, ios::beg);

	int _nextId;
	indiceIds.read(reinterpret_cast<char*>(&_nextId), 4);

	indiceIds.close();

	if (_nextId < 0) {
		setNextId(1);
		_nextId = 2;
	}

	if (_nextId < 0) {
		setNextId(1);
		_nextId = 2;
	}

	if(next == true)
		setNextId(_nextId);

	return _nextId;
}

void Producto::setNextId(int _lastId) {
	fstream indiceIds("identifiers.index", ios::out | ios::in | ios::binary);

	if (!indiceIds) {
		cout << "Error al intentar abrir el archivo .index\n\n";
		return;
	}

	int newID = _lastId + 1;

	indiceIds.seekp(5, ios::beg);
	indiceIds.write(reinterpret_cast<const char*>(&newID), sizeof(newID));

	indiceIds.close();
}

void Producto::print() {
	cout << "\nId: " << id
		<< "\nCodigo: " << codigo
		<< "\nCategoria: " << categoria
		<< "\nSub Categoria: " << sub_categoria
		<< "\nNombre: " << nombre
		<< "\nDescripcion: " << descripcion
		<< "\nPrecio Actual: " << precio_actual << "\n";
}

