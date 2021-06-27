#include "NodoInvertido.h"
NodoInvertido::NodoInvertido() {
	id = 0;
	posicion = 0;
	lista = new vector<NodoInvertidoLista>;
}

ostream& operator<<(ostream& stream, const NodoInvertido& data) {
	stream
		<< data.id << ","
		<< data.posicion << ","
		<< data.lista->size() << ",";

	for (int i = 0; i < data.lista->size(); i++) {
		stream << data.lista->at(i);
	}
	return stream;
}

istream& operator>>(istream& stream, NodoInvertido& data) {
	//palabra
	char _id[32];
	stream.getline(_id, 32, ',');
	data.id = atoi(_id);

	//first
	char _first[32];
	stream.getline(_first, 32, ',');
	data.posicion = atol(_first);

	//Cantidad de pedidos a leer
	int cantidadPedidos = 32;
	char _cantidad[32];
	stream.getline(_cantidad, 32, ',');
	cantidadPedidos = atoi(_cantidad);

	for (int i = 0; i < cantidadPedidos; i++) {
		NodoInvertidoLista aux;
		stream >> aux;

		data.lista->push_back(aux);
	}

	return stream;
}