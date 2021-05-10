#pragma once
#ifndef AMAZON_H
#define AMAZON_H

#include <iostream>
#include "Producto.h"
using namespace std;


class Amazon {


	//id, codigo, categoria, sub_categoria, nombre, descripcion, precio_actual
	bool agregar_producto(int, char*, char*, char*, char*, char*, float);
	//Busquera por id
	Producto* consultar_productoId(int);
	//Busqueda por codigo
	Producto* consultar_productoCode(char*);
	//Busqueda por nombre
	Producto* consultar_productoName(char*);
	//Modificar producto
	bool modificar_producto(Producto*);
	//Eliminar producto
	bool eliminar_producto(Producto*);

};

#endif // !AMAZON_H
