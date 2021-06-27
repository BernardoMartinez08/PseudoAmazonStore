#pragma once
#ifndef AMAZON_H
#define AMAZON_H

#include <iostream>
#include <fstream>
#include "Producto.h"
#include "Cliente.h"
#include "DelimTextBuffer.h"
#include <vector>
#include "Detalle.h"
#include "Factura.h"
#include "BusquedasIndexadas.h"
using namespace std;


class Amazon {
public:	
	BusquedaIndexada browser;
	Amazon();
	void salir();
	//Seccion Clientes
	void agregarCliente(const char* code = nullptr);
	void consultarCliente();
	void modificarCliente(const char* code = nullptr);
	void navegacionClientes();
	void eliminarClientes(const char* code = nullptr);
	void eliminarClienteAux(Cliente actual, fstream& fileE, long posicion);

	//Seccion Productos
	void agregarProducto();
	void consultarProducto();
	void modificarProducto(const char* code = nullptr);
	void navegacionProductos();
	void eliminarProducto(const char* code = nullptr);
	void eliminarProductoAux(Producto actual, fstream& fileE, long posicion);
	
	//Seccion Clientes
	bool listarClientes();

	//Seccion Productos
	bool listarProductos();

	//Seccion Factura - Prototipo
	void RegistrarCompra();
	void navegacionFacturas();
	void eliminarFactura(const char* code = nullptr);
	void eliminarFacturaAux(Factura actual, fstream& fileE, long posicion);
	bool listarDetallesDeFactura(int _id_factura);

	void agregarAlCarrito(vector<Detalle>&, Detalle);
private:
};

#endif // !AMAZON_H
