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
using namespace std;


class Amazon {
public:
	//Seccion Clientes
	static void agregarCliente();
	static void consultarCliente();
	static void modificarCliente(const char* code = nullptr);
	static void navegacionClientes();
	static void eliminarClientes(const char* code = nullptr);
	static void eliminarClienteAux(Cliente actual, fstream& fileE, long posicion, ofstream& fileIndex);

	//Seccion Productos
	static void agregarProducto();
	static void consultarProducto();
	static void modificarProducto(const char* code = nullptr);
	static void navegacionProductos();
	static void eliminarProducto(const char* code = nullptr);
	static void eliminarProductoAux(Producto actual, fstream& fileE, long posicion, ofstream& fileIndex);
	
	//Seccion Clientes
	static bool listarClientes();

	//Seccion Productos
	static bool listarProductos();

	//Seccion Factura - Prototipo
	static void facturar();

private:
	static void agregarAlCarrito(vector<Detalle>&, Detalle);
};

#endif // !AMAZON_H
