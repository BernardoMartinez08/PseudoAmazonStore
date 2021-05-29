#pragma once
#ifndef AMAZON_H
#define AMAZON_H

#include <iostream>
#include <fstream>
#include "Producto.h"
#include "Cliente.h"
#include "DelimTextBuffer.h"
using namespace std;


class Amazon {
public:
	//Seccion Clientes
	static void agregarCliente();
	static void consultarCliente();
	static void modificarCliente();
	static void navegacionClientes();


	//Seccion Productos
	static void agregarProducto();
	static void consultarProducto();
	static void modificarProducto();
	static void navegacionProductos();
	
private:
	//Seccion Clientes
	static bool listarClientes(istream&);

	//Seccion Productos
	static bool listarProductos(ifstream&);
};

#endif // !AMAZON_H
