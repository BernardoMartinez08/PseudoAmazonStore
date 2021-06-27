#include "NodoInvertidoLista.h"

NodoInvertidoLista::NodoInvertidoLista() {
	position = 0;
}

ostream& operator<<(ostream& stream, const NodoInvertidoLista& data) {
	stream
		<< data.position
		<< ",";
	return stream;
}

istream& operator>>(istream& stream, NodoInvertidoLista& data) {
	char _position[8];
	stream.getline(_position, 8, ',');
	data.position = atol(_position);
	return stream;
}