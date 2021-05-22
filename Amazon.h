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
	static void agregarCliente();
	static void consultarCliente();
	static void modificarCliente();

private:
	static bool buscarClienteCodigo(istream&, const char* _codigo);
	static bool buscarClienteNombre(istream&, const char* _nombreCompleto);
	static bool listarClientes(istream&);
};

#endif // !AMAZON_H
