#include "BusquedasSecuenciales.h"
#include <cstring>
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

void Busqueda::imprimirFacturasCliente(istream& file, int _id_cliente) {
	file.seekg(0);

	int total = 0;
	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Factura actual;

		buscarFacturaCliente(file,_id_cliente);
		actual.Read(file, delim);

		if (actual.id != 0) {
			if (actual.cliente_id == _id_cliente)
			{
				actual.print();
				total++;
			}
		}
	}

	if (total != 0)
		cout << "\n\nEste cliente tiene " << total << " facturas asociadas.";
	else
		cout << "\n\nNo hay Facturas Asociadas a este cliente.";
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

void Busqueda::imprimirVentasProducto(istream& fileFacturas, istream& fileDetalles, int _id_producto) {
	fileFacturas.seekg(0);
	vector<Detalle> ventas[12];
	string meses[12] = { "Enero" "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };

	while (!fileFacturas.eof())
	{
		DelimTextBuffer delim('^', 300);
		Factura actualF;

		actualF.Read(fileFacturas, delim);

		if (actualF.id != 0) {
			fileDetalles.seekg(0);
			while (!fileDetalles.eof()) {
				DelimTextBuffer delim2('^', 300);
				Detalle actualD;

				buscarDetalleFactura(fileDetalles, actualF.id);
				actualD.Read(fileDetalles, delim);

				if (actualD.id != 0) {
					if (actualD.producto_id == _id_producto)
					{
						if (actualF.mes >= 1 && actualF.mes <= 12) {
							ventas[actualF.mes - 1].push_back(actualD);
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < 12; i++) {
		cout << "\n\nVentas Correspondientes a: " << meses[i] << ":\n";
		for (int j = 0; i < ventas[i].size(); j++) {
			ventas[i][j].print();
		}

		cout << "\n\nEste producto se vendio: " << ventas[i].size() << " en el mes de: " << meses[i] << ".";
	}
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





//SECCION DETALLE DE FACTURA
bool Busqueda::buscarDetalleFactura(istream& file, int _id_factura) {
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