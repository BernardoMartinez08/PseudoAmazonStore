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

		if (actual.id != 0) {
			
			if (strcmp(actual.codigo, _codigo) == 0) {
				file.seekg(posicion);
				cout << "AQUI";
				return true;
			}
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

		if (actual.id != 0) {
			char* nombreCompreto = new char[strlen(actual.primer_nombre)];
			strcpy_s(nombreCompreto, strlen(actual.primer_nombre) + 1, actual.primer_nombre);
			strcat_s(nombreCompreto, strlen(nombreCompreto) + strlen(actual.segundo_nombre) + 1, actual.segundo_nombre);
			strcat_s(nombreCompreto, strlen(nombreCompreto) + strlen(actual.primer_apellido) + 1, actual.primer_apellido);
			strcat_s(nombreCompreto, strlen(nombreCompreto) + strlen(actual.segundo_apellido) + 1, actual.segundo_apellido);

			if (strcmp(_nombre,nombreCompreto) == 0) {
				file.seekg(posicion);
				cout << "AQUI";
				return true;
			}
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

		if (actual.id != 0) {
			if (actual.id == _id)
			{
				file.seekg(posicion);
				return true;
			}
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

		if (actual.id != 0) {
			if (strcmp(actual.codigo,_codigo) == 0)
			{
				file.seekg(posicion);
				return true;
			}
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

		if (actual.id != 0) {
			if (strcmp(_nombre,nombre) == 0)
			{
				file.seekg(posicion);

				return true;
			}
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

		if (actual.id != 0) {
			if (actual.id == _id)
			{
				file.seekg(posicion);
				return true;
			}
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

		if (actual.id != 0) {
			if (strcmp(actual.codigo,_codigo) == 0)
			{
				file.seekg(posicion);
				return true;
			}
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
		
		if (actual.id != 0) {
			if (actual.cliente_id == _id_cliente)
			{
				file.seekg(posicion);

				return true;
			}
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

		if (actual.id != 0) {
			if (actual.id == _id)
			{
				file.seekg(posicion);
				return true;
			}
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

		if (actual.id != 0) {
			if (actual.factura_id == _id_factura)
			{
				file.seekg(posicion);

				return true;
			}
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

		if (actual.id != 0) {
			if (actual.producto_id == _id_producto)
			{
				file.seekg(posicion);

				return true;
			}
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

		if (actual.id != 0) {
			if (actual.id == _id)
			{
				file.seekg(posicion);
				return true;
			}
		}
	}

	return false;
}






//SECCION DE BORRAR HISTORIAL
bool Busqueda::eliminarFacturasCliente(int _id_cliente) {
	fstream file("facturas.bin", ios::in | ios::out | ios::binary);
	ofstream fileIndex("facturas.index", ios::in | ios::binary);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Factura actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id != 0) {
			if (actual.cliente_id == _id_cliente)
			{
				DelimTextBuffer delim('^', 300);
				file.seekg(posicion);
				actual.id = 0;
				actual.Write(file, fileIndex, delim);
			}
		}
	}

	file.close();
	return true;
}

bool Busqueda::eliminarDetallesFactura(int _id_factura) {
	fstream file("detalles.bin", ios::in | ios::binary);
	ofstream fileIndex("detalles.index", ios::in | ios::binary);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Detalle actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id != 0) {
			if (actual.factura_id == _id_factura)
			{
				DelimTextBuffer delim('^', 300);
				file.seekg(posicion);
				actual.id = 0;
				actual.Write(file, fileIndex, delim);
			}
		}
	}
	file.close();
	return true;
}