#pragma once
#ifndef BUSQUEDAS_SECUENCIALES_H
#define BUSQUEDAS_SECUENCIALES_H

#include <iostream>
#include <fstream>
#include "Producto.h"
#include "Cliente.h"
#include "Factura.h"
#include "Detalle.h"
#include "DelimTextBuffer.h"
#include <cstring>
#include <vector>
#include <string>
using namespace std;

struct ubicacion{
	string ciudad;
	string region;
	string pais;
};

class Busqueda {
public:
	//Seccion Clientes
	static bool buscarClienteCodigo(istream&, const char* _codigo);
	static bool buscarClienteNombre(istream&, const char* _nombreCompleto);
	static bool buscarClienteID(istream&, int _id);
	static void imprimirFacturasCliente(istream&, int _id_cliente);

	//Seccion Productos
	static bool buscarProductoCodigo(istream&, const char* _codigo);
	static bool buscarProductoNombre(istream&, const char* _nombre);
	static bool buscarProductoID(istream&, int _id);
	static void imprimirVentasProducto(istream&, istream&,  int _id_producto);

	//Seccion de Factura
	static bool buscarFacturaCodigo(istream&, const char* _codigo);
	static bool buscarFacturaCliente(istream&, int _id_cliente);
	static bool buscarFacturaID(istream&, int _id);

	//Seccion de Detalle
	static bool buscarDetalleFactura(istream&, int _id_factura);
	static bool buscarDetalleProducto(istream&, int _id_producto);
	static bool buscarDetalleID(istream&, int _id);


	//Seccion de Historial
	static bool eliminarFacturasCliente(int _id_cliente);
	static bool eliminarDetallesFactura(int _id_factura);


	//Generando registros seudo aleatorios
	//Registros
	static void generarArchivoNombres();
	static void generarArchivoApellidos();
	static void generarArchivoUbicaciones();
	
	static vector<string> extraerNombresHombres();
	static vector<string> extraerNombresMujeres();
	static vector<string> extraerApellidos();
	static vector<ubicacion> extraerUbicaciones();

	//Generadores
	static void generarClientes(ostream& ,int);

	//Generando Productos
	static void generarArchivoCategorias();
	static void generarArchivoSubCategoria();
	static void generarArchivoProducto();

	static vector<string> extraerCategorias();
	static vector<string> extraerSubcategoria();

	static char* toLowerCase(const char*);
};

#endif // !BUSQUEDAS_SECUENCIALES_H
