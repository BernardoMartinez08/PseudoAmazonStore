#include "BusquedasSecuenciales.h"

//SECCION DE CLIENTES
bool Busqueda::buscarClienteCodigo(istream& file, const char* _codigo) {
	file.seekg(ios::beg);

	while (!file.eof()) {
		DelimTextBuffer delim('^', 300);
		Cliente actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.codigo == _codigo) {
			file.seekg(posicion);
			return true;
		}
	}
	return false;
}

bool Busqueda::buscarClienteNombre(istream& file, const char* _nombre) {
	file.seekg(0);

	while (!file.eof()) {
		DelimTextBuffer delim('^', 300);
		Cliente actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		char* nombreCompreto = new char[strlen(actual.primer_nombre)];
		strcpy_s(nombreCompreto, strlen(actual.primer_nombre) + 1, actual.primer_nombre);
		strcat_s(nombreCompreto, strlen(nombreCompreto) + strlen(actual.segundo_nombre) + 1, actual.segundo_nombre);
		strcat_s(nombreCompreto, strlen(nombreCompreto) + strlen(actual.primer_apellido) + 1, actual.primer_apellido);
		strcat_s(nombreCompreto, strlen(nombreCompreto) + strlen(actual.segundo_apellido) + 1, actual.segundo_apellido);

		if (_nombre == nombreCompreto) {
			file.seekg(posicion);
			return true;
		}
	}
	return false;
}

bool Busqueda::buscarClienteID(istream& file, int _id) {
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);

		Producto actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id == _id)
		{
			file.seekg(posicion);
			return true;
		}
	}

	return false;
}







//SECCION DE PRODUCTO
bool Busqueda::buscarProductoCodigo(istream& file, const char* _codigo){
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);

		Producto actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.codigo == _codigo)
		{
			file.seekg(posicion);
			return true;
		}
	}

	return false;
}

bool Busqueda::buscarProductoNombre(istream& file, const char* _nombre){
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Producto actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);
		char* nombre = actual.nombre;

		if (_nombre == nombre)
		{
			file.seekg(posicion);

			return true;
		}
	}

	return false;
}

bool Busqueda::buscarProductoID(istream& file, int _id) {
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);

		Producto actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id == _id)
		{
			file.seekg(posicion);
			return true;
		}
	}

	return false;
}







//SECCION DE FACTURA
bool Busqueda::buscarFacturaCodigo(istream& file, const char* _codigo){
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);

		Factura actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.codigo == _codigo)
		{
			file.seekg(posicion);
			return true;
		}
	}

	return false;
}

bool Busqueda::buscarFacturaCliente(istream& file, int _id_cliente){
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Factura actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);
		
		if (actual.cliente_id == _id_cliente)
		{
			file.seekg(posicion);

			return true;
		}
	}

	return false;
}

bool Busqueda::buscarFacturaID(istream& file, int _id) {
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);

		Factura actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id == _id)
		{
			file.seekg(posicion);
			return true;
		}
	}

	return false;
}






//SECCION DETALLE DE FACTURA
bool Busqueda::buscarDetalleFactura(istream& file, int _id_factura) {
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Detalle actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.factura_id == _id_factura)
		{
			file.seekg(posicion);

			return true;
		}
	}

	return false;
}

bool Busqueda::buscarDetalleProducto(istream& file, int _id_producto) {
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Detalle actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.producto_id == _id_producto)
		{
			file.seekg(posicion);

			return true;
		}
	}

	return false;
}

bool Busqueda::buscarDetalleID(istream& file, int _id) {
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);

		Detalle actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id == _id)
		{
			file.seekg(posicion);
			return true;
		}
	}

	return false;
}