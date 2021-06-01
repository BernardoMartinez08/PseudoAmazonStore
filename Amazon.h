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
	static void modificarCliente();
	static void navegacionClientes();
	static void eliminarClientes();

	//Seccion Productos
	static void agregarProducto();
	static void consultarProducto();
	static void modificarProducto();
	static void navegacionProductos();
	static void eliminarProducto();
	
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
