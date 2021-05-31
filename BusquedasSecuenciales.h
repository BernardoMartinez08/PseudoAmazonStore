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
using namespace std;


class Busqueda {
public:
	//Seccion Clientes
	static bool buscarClienteCodigo(istream&, const char* _codigo);
	static bool buscarClienteNombre(istream&, const char* _nombreCompleto);
	static bool buscarClienteID(istream&, int _id);

	//Seccion Productos
	static bool buscarProductoCodigo(istream&, const char* _codigo);
	static bool buscarProductoNombre(istream&, const char* _nombre);
	static bool buscarProductoID(istream&, int _id);

	//Seccion de Factura
	static bool buscarFacturaCodigo(istream&, const char* _codigo);
	static bool buscarFacturaCliente(istream&, int _id_cliente);
	static bool buscarFacturaID(istream&, int _id);

	//Seccion de Detalle
	static bool buscarDetalleFactura(istream&, int _id_factura);
	static bool buscarDetalleProducto(istream&, int _id_producto);
	static bool buscarDetalleID(istream&, int _id);

};

#endif // !BUSQUEDAS_SECUENCIALES_H