#include "BusquedasIndexadas.h"
#include <cstring>
#include <stdlib.h>
#include <time.h>

BusquedaIndexada::BusquedaIndexada() {
	IndiceClientesNombre = new vector<NodoSecundario>;
	IndiceClientesCodigo = new vector<NodoSecundario>;;
	IndiceProductosNombre = new vector<NodoSecundario>;;
	IndiceProductosCodigo = new vector<NodoSecundario>;;
	IndiceFacturasCodigo = new vector<NodoSecundario>;

	IndiceClientesId = new vector<NodoPrincipal>;
	IndiceProductosId = new vector<NodoPrincipal>;
	IndiceFacturasId = new vector<NodoPrincipal>;
	IndiceDetallesId = new vector<NodoPrincipal>;

	IndiceFacturasCliente = new vector<NodoInvertido>;
	IndiceDetallesFactura = new vector<NodoInvertido>;
	IndiceDetallesProducto = new vector<NodoInvertido>;
}

bool BusquedaIndexada::buscarCodigo(istream& file, const char* _codigo, TipoBusquedaSec _tipo)
{
	vector<NodoSecundario>* indice = new vector<NodoSecundario>;
	if (_tipo == TipoBusquedaSec::tCliente)
		indice = IndiceClientesCodigo;
	else if (_tipo == TipoBusquedaSec::tProducto)
		indice = IndiceProductosCodigo;
	else if (_tipo == TipoBusquedaSec::tFactura)
		indice = IndiceFacturasCodigo;
	else if (_tipo == TipoBusquedaSec::tDetalle)
		return false;

	for (int i = 0; i < indice->size(); i++ ) {
		NodoSecundario actual = indice->at(i);
		if (strcmp(actual.key, _codigo) == 0) {
			if(buscarID(file,actual.id,_tipo))
				return true;
		}
	}
}

bool BusquedaIndexada::buscarNombre(istream& file, const char* _nombre , TipoBusquedaSec _tipo) {
	vector<NodoSecundario>* indice = new vector<NodoSecundario>;
	if (_tipo == TipoBusquedaSec::tCliente)
		indice = IndiceClientesNombre;
	else if (_tipo == TipoBusquedaSec::tProducto)
		indice = IndiceProductosNombre;
	else if (_tipo == TipoBusquedaSec::tFactura)
		return false;
	else if (_tipo == TipoBusquedaSec::tDetalle)
		return false;
	
	for (int i = 0; i < indice->size(); i++) {
		NodoSecundario actual = indice->at(i);
		if (strcmp(toLowerCase(_nombre), toLowerCase(actual.key)) == 0) {
			if (buscarID(file, actual.id, _tipo))
				return true;
		}
	}
	return false;
}

bool BusquedaIndexada::buscarID(istream& file, int _id, TipoBusquedaSec _tipo) {
	vector<NodoPrincipal>* indice = new vector<NodoPrincipal>;
	if (_tipo == TipoBusquedaSec::tCliente)
		indice = IndiceClientesId;
	else if (_tipo == TipoBusquedaSec::tProducto)
		indice = IndiceProductosId;
	else if (_tipo == TipoBusquedaSec::tFactura)
		indice = IndiceFacturasId;
	else if (_tipo == TipoBusquedaSec::tDetalle)
		indice = IndiceDetallesId;
	
	int derecha = indice->size() - 1;
	int izquierda = 0;
	int centro;

	while (izquierda <= derecha)
	{
		centro = (derecha + izquierda) / 2;
		if (indice->at(centro).id == _id) {
			file.seekg(indice->at(centro).posicion);
			return true;
		}
		else {
			if (_id < indice->at(centro).id)
				derecha = centro - 1;
			else
				izquierda = centro + 1;
		}
	}
	return false;
}

vector<long> BusquedaIndexada::buscarInvertidos(int _id, TipoBusquedaInv _tipo) {
	vector<NodoInvertido>* indice = new vector<NodoInvertido>;
	if (_tipo == TipoBusquedaInv::tFacturaCliente)
		indice = IndiceFacturasCliente;
	else if (_tipo == TipoBusquedaInv::tDetalleFactura)
		indice = IndiceDetallesFactura;
	else if (_tipo == TipoBusquedaInv::tDetalleProducto)
		indice = IndiceDetallesProducto;
	
	vector<long> aux;
	for (int i = 0; i < indice->size(); i++) {
		if (indice->at(i).id == _id) {
			for (int j = 0; j < indice->at(i).lista->size(); j++) {
				aux.push_back(indice->at(i).lista->at(j).position);
			}
		}
	}
	return aux;
}

bool BusquedaIndexada::borrar(int _id, TipoBusquedaSec _tipo)
{
	vector<NodoPrincipal>* indicePrincipal = new vector<NodoPrincipal>;
	vector<NodoSecundario>* indiceSecundarioCode = new vector<NodoSecundario>;
	vector<NodoSecundario>* indiceSecundarioName = new vector<NodoSecundario>;
	if (_tipo == TipoBusquedaSec::tCliente) {
		indicePrincipal = IndiceClientesId;
		indiceSecundarioCode = IndiceClientesCodigo;
		indiceSecundarioName = IndiceClientesNombre;
	}
	else if (_tipo == TipoBusquedaSec::tProducto) {
		indicePrincipal = IndiceProductosId;
		indiceSecundarioCode = IndiceProductosCodigo;
		indiceSecundarioName = IndiceClientesNombre;
	}
	else if (_tipo == TipoBusquedaSec::tFactura)
		return borrarFacturas(_id);
	else if (_tipo == TipoBusquedaSec::tDetalle)
		return borrarDetalles(_id);

	int derecha = indicePrincipal->size() - 1;
	int izquierda = 0;
	int centro;
	bool borrado = false;
	while (izquierda <= derecha)
	{
		centro = (derecha + izquierda) / 2;
		if (indicePrincipal->at(centro).id == _id) {
			indicePrincipal->at(centro).id = 0;
			borrado = true;
		}
		else {
			if (_id < indicePrincipal->at(centro).id)
				derecha = centro - 1;
			else
				izquierda = centro + 1;
		}
	}

	for (int i = 0; i < indiceSecundarioName->size(); i++) {
		NodoSecundario actual = indiceSecundarioName->at(i);
		if (actual.id == _id) {
			actual.id = 0;
			borrado = true;
		}
	}

	for (int i = 0; i < indiceSecundarioCode->size(); i++) {
		NodoSecundario actual = indiceSecundarioCode->at(i);
		if (actual.id == _id) {
			actual.id = 0;
			borrado = true;
		}
	}

	if (borrado)
		return true;
	else
		return false;
}

bool BusquedaIndexada::borrarFacturas(int _id)
{
	vector<NodoPrincipal>* indicePrincipal = IndiceFacturasId;
	vector<NodoSecundario>* indiceSecundarioCodigo = IndiceFacturasCodigo;
	
	int derecha = indicePrincipal->size() - 1;
	int izquierda = 0;
	int centro;
	bool borrado = false;
	while (izquierda <= derecha)
	{
		centro = (derecha + izquierda) / 2;
		if (indicePrincipal->at(centro).id == _id) {
			indicePrincipal->at(centro).id = 0;
			borrado = true;
		}
		else {
			if (_id < indicePrincipal->at(centro).id)
				derecha = centro - 1;
			else
				izquierda = centro + 1;
		}
	}

	for (int i = 0; i < indiceSecundarioCodigo->size(); i++) {
		NodoSecundario actual = indiceSecundarioCodigo->at(i);
		if (actual.id == _id) {
			actual.id = 0;
			borrado = true;
		}
	}

	if (borrado)
		return true;
	else
		return false;
}

bool BusquedaIndexada::borrarDetalles(int _id)
{
	vector<NodoPrincipal>* indicePrincipal = IndiceDetallesId;
	
	int derecha = indicePrincipal->size() - 1;
	int izquierda = 0;
	int centro;
	bool borrado = false;
	while (izquierda <= derecha)
	{
		centro = (derecha + izquierda) / 2;
		if (indicePrincipal->at(centro).id == _id) {
			indicePrincipal->at(centro).id = 0;
			borrado = true;
		}
		else {
			if (_id < indicePrincipal->at(centro).id)
				derecha = centro - 1;
			else
				izquierda = centro + 1;
		}
	}

	if (borrado)
		return true;
	else
		return false;
}

bool BusquedaIndexada::agregar(const char* _code, const char* _name, int _id, long _posicion, TipoBusquedaSec _tipo)
{
	vector<NodoPrincipal>* indicePrincipal = new vector<NodoPrincipal>;
	vector<NodoSecundario>* indiceSecundarioCode = new vector<NodoSecundario>;
	vector<NodoSecundario>* indiceSecundarioName = new vector<NodoSecundario>;
	if (_tipo == TipoBusquedaSec::tCliente) {
		indicePrincipal = IndiceClientesId;
		indiceSecundarioCode = IndiceClientesCodigo;
		indiceSecundarioName = IndiceClientesNombre;
	}
	else if (_tipo == TipoBusquedaSec::tProducto) {
		indicePrincipal = IndiceProductosId;
		indiceSecundarioCode = IndiceProductosCodigo;
		indiceSecundarioName = IndiceClientesNombre;
	}
	else if (_tipo == TipoBusquedaSec::tFactura)
		return agregraFacturas(_code,_id,_posicion);
	else if (_tipo == TipoBusquedaSec::tDetalle)
		return agregraDetalle(_id, _posicion);

	NodoPrincipal NodoPrin;
	NodoPrin.id = _id;
	NodoPrin.posicion = _posicion;

	NodoSecundario NodoName;
	NodoName.id = _id;
	NodoName.set_key(_name);

	NodoSecundario NodoCode;
	NodoCode.id = _id;
	NodoCode.set_key(_code);

	indicePrincipal->push_back(NodoPrin);
	indiceSecundarioName->push_back(NodoName);
	indiceSecundarioCode->push_back(NodoCode);

	return true;
}

bool BusquedaIndexada::agregraFacturas(const char* _code, int _id, long _posicion)
{
	vector<NodoPrincipal>* indicePrincipal = IndiceFacturasId;
	vector<NodoSecundario>* indiceSecundarioCode = IndiceFacturasCodigo;
	
	NodoPrincipal NodoPrin;
	NodoPrin.id = _id;
	NodoPrin.posicion = _posicion;

	NodoSecundario NodoCode;
	NodoCode.id = _id;
	NodoCode.set_key(_code);

	indicePrincipal->push_back(NodoPrin);
	indiceSecundarioCode->push_back(NodoCode);

	return true;
}

bool BusquedaIndexada::agregraDetalle(int _id, long _posicion)
{
	vector<NodoPrincipal>* indicePrincipal = IndiceDetallesId;

	NodoPrincipal NodoPrin;
	NodoPrin.id = _id;
	NodoPrin.posicion = _posicion;

	indicePrincipal->push_back(NodoPrin);

	return true;
}

bool BusquedaIndexada::cargarPrincipales()
{
	string indicesFileNames[4] = {fileClientesPrincipalIndex,fileProductosPrincipalIndex,fileDetallesPrincipalIndex,fileFacturasPrincipalIndex};
	for (int i = 0; i < 4; i++) {
		ifstream file(indicesFileNames[i], ios::in || ios::binary);
		vector<NodoPrincipal>* indicePrincipal = new vector<NodoPrincipal>;
		if (i == 0)
			indicePrincipal = IndiceClientesId;
		else if (i == 2)
			indicePrincipal = IndiceProductosId;
		else if (i == 3)
			indicePrincipal = IndiceFacturasId;
		else if (i == 4)
			indicePrincipal = IndiceDetallesId;

		while (!file.eof()) {
			NodoPrincipal nuevo;
			file >> nuevo;
			indicePrincipal->push_back(nuevo);
		}
		file.close();
	}
	return true;
}

bool BusquedaIndexada::cargarSecundarios()
{
	string indicesFileNames[5] = { fileClieSecCodeIndex,fileClieSecNamesIndex,fileProdSecCodeIndex,fileProdSecNamesIndex,fileFactSecCodeIndex };
	for (int i = 0; i < 5; i++) {
		ifstream file(indicesFileNames[i], ios::in || ios::binary);
		vector<NodoSecundario>* indiceSecundario = new vector<NodoSecundario>;
		if (i == 0)
			indiceSecundario = IndiceClientesCodigo;
		else if (i == 2)
			indiceSecundario = IndiceClientesNombre;
		else if (i == 3)
			indiceSecundario = IndiceProductosCodigo;
		else if (i == 4)
			indiceSecundario = IndiceProductosNombre;
		else if (i == 5)
			indiceSecundario = IndiceFacturasCodigo;

		while (!file.eof()) {
			NodoSecundario nuevo;
			file >> nuevo;
			indiceSecundario->push_back(nuevo);
		}
		file.close();
	}
	return true;
}

char* BusquedaIndexada::toLowerCase(const char* cadena) {
	char* nueva = new char[strlen(cadena) + 1];
	for (int i = 0; i < strlen(cadena); i++) {
		nueva[i] = tolower(cadena[i]);
	}

	return nueva;
}

void BusquedaIndexada::imprimirVentasProducto(istream& fileDetalles, int _id_producto) {
	vector<Detalle> ventas[12];
	string meses[12] = { "Enero" "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };

	/*vector<long> posiciones = buscarInvertidos(_id_producto, TipoBusquedaInv::tDetalleProducto);
	for(int i = 0; i < posiciones.size(); i++){
		
		buscarDetalleFactura(fileDetalles, actualF.id);
		actualD.Read(fileDetalles, delim);

		if (actualD.id != 0) {
			if (actualD.producto_id == _id_producto)
			{
				if (actualF.mes >= 1 && actualF.mes <= 12) {
					ventas[actualF.mes - 1].push_back(actualD);
				}
			}
		}
	}*/

	for (int i = 0; i < 12; i++) {
		cout << "\n\nVentas Correspondientes a: " << meses[i] << ":\n";
		for (int j = 0; i < ventas[i].size(); j++) {
			ventas[i][j].print();
		}

		cout << "\n\nEste producto se vendio: " << ventas[i].size() << " en el mes de: " << meses[i] << ".";
	}
}