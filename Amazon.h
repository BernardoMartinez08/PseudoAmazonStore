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
	static void modificarCliente(const char* = nullptr);
	static void navegacionClientes();


	//Seccion Productos
	static void agregarProducto();
	static void consultarProducto();
	static void modificarProducto(const char* = nullptr);
	static void navegacionProductos();
	
private:
	//Seccion Clientes
	static bool buscarClienteCodigo(istream&, const char* _codigo);
	static bool buscarClienteNombre(istream&, const char* _nombreCompleto);
	static bool listarClientes(istream&);

	//Seccion Productos

	static bool buscarProductoCodigo(ifstream&, const char* _codigo);
	static bool buscarProductoNombre(ifstream&, const char* _nombre);
	static bool listarProductos(ifstream&);
};

#endif // !AMAZON_H
