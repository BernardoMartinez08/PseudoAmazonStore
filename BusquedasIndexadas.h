#pragma once
#ifndef BUSQUEDAS_INDEXADAS_H
#define BUSQUEDAS_INDEXADAS_H

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
#include <stdlib.h>
#include <ctime>
#include <sstream>
#include "Amazon.h"
#include "NodoInvertido.h"
#include "NodoInvertidoLista.h"
#include "NodoPrincipal.h"
#include "NodoSecundario.h"

using namespace std;

enum TipoBusquedaSec {
	tCliente,
	tProducto,
	tFactura,
	tDetalle
};

enum TipoBusquedaInv {
	tFacturaCliente,
	tDetalleFactura,
	tDetalleProducto
};

class BusquedaIndexada {
public:
	BusquedaIndexada();

	//Archivos de Indices
	string fileProductosPrincipalIndex{ "productos.index" };
	string fileClientesPrincipalIndex{ "clientes.index" };
	string fileFacturasPrincipalIndex{ "facturas.index" };
	string fileDetallesPrincipalIndex{ "detalles.index" };

	string fileProdSecNamesIndex{ "productos_names.secundaryindex" };
	string fileClieSecNamesIndex{ "clientes_names.secundaryindex" };
	string fileFactSecCodeIndex{ "facturas_codes.secundaryindex" };
	string fileProdSecCodeIndex{ "productos_codes.secundaryindex" };
	string fileClieSecCodeIndex{ "clientes_codes.secundaryindex" };

	string fileFactClieInvertedIndex{ "facturas_cliente.invertedindex" };
	string fileDetFactInvertedIndex{ "detalles_factura.invertedindex" };
	string fileDetProdInvertedIndex{ "detalles_producto.invertedindex" };


	//Indices en Memoria
	vector<NodoSecundario>* IndiceClientesNombre;
	vector<NodoSecundario>* IndiceClientesCodigo;
	vector<NodoSecundario>* IndiceProductosNombre;
	vector<NodoSecundario>* IndiceProductosCodigo;
	vector<NodoSecundario>* IndiceFacturasCodigo;
	
	vector<NodoPrincipal>* IndiceClientesId;
	vector<NodoPrincipal>* IndiceProductosId;
	vector<NodoPrincipal>* IndiceFacturasId;
	vector<NodoPrincipal>* IndiceDetallesId;

	vector<NodoInvertido>* IndiceFacturasCliente;
	vector<NodoInvertido>* IndiceDetallesFactura;
	vector<NodoInvertido>* IndiceDetallesProducto;

	//Seccion Busquedas Por Nombre, Codigo e Id
	bool buscarCodigo(istream&, const char* _codigo, TipoBusquedaSec);
	bool buscarNombre(istream&, const char* _nombreCompleto, TipoBusquedaSec);
	bool buscarID(istream&, int _id, TipoBusquedaSec);

	//Seccion Listados
	void imprimirVentasProducto(istream&, int _id_producto);
	void imprimirFacturasCliente(istream&, int _id_cliente);

	//Seccion Busquedas Invertidas
	vector<long> buscarInvertidos(int _id, TipoBusquedaInv);
	
	//Seccion de Historial
	bool eliminarFacturasCliente(int _id_cliente);
	bool eliminarDetallesFactura(int _id_factura);

	//Seccion de Modificaciones en los Indices
	bool borrar(int _id, TipoBusquedaSec);
	bool borrarFacturas(int _id);
	bool borrarDetalles(int _id);

	bool agregar(const char* _code, const char* _name, int _id, long _posicion, TipoBusquedaSec _tipo);
	bool agregraFacturas(const char* _code, int _id, long _pocision);
	bool agregraDetalle(int _id, long _pocision);

	//Cargar Indices En Memoria
	bool cargarPrincipales();
	bool cargarSecundarios();

	//Guardar Indices En Disco

	//Seccion de Extras
	char* toLowerCase(const char*);
};

#endif // !BUSQUEDAS_INDEXADAS_H