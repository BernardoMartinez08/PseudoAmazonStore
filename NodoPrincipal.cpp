#include "NodoPrincipal.h"

NodoPrincipal::NodoPrincipal() {
	id = 0;
	posicion = 0;
}

ostream& operator<<(ostream& stream, const NodoPrincipal& data) {
	stream
		<< data.id
		<< ","
		<< data.posicion
		<< ",";
	return stream;
}

istream& operator>>(istream& stream, NodoPrincipal& data) {
	//ID
	char _id[8];
	stream.getline(_id, 8, ',');
	data.id = atoi(_id);

	//Posicion
	char _position[8];
	stream.getline(_position, 8, ',');
	data.posicion = atol(_position);
	return stream;
}