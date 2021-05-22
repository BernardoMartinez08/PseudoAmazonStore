#include "Amazon.h"

void Amazon::agregarCliente() {
	ofstream file("clientes.bin", ios::out | ios::app | ios::binary);
	ofstream fileIndex("clientes.index", ios::out | ios::app | ios::binary);

	if (!file) {
		cout << "Error al intentar abrir el archivo .bin de clientes\n\n";
		return;
	}

	cout << " ***** I N G R E S O  D E  C L I E N T E S ***** \n\n";

	Cliente nuevo;
	DelimTextBuffer delim('^',300);

	int _id = nuevo.getNextId();

	char _codigo[13];
	char _primer_nombre[30];
	char _segundo_nombre[30];
	char _primer_apellido[30];
	char _segundo_apellido[30];
	char _genero[2];
	char _ciudad[50];
	char _region[50];
	char _pais[50];

	cout << "INGRESE LOS DATOS PARA EL CLIENTE:\nIndique codigo: ";
	cin >> _codigo;
	nuevo.set_codigo(_codigo);
	cout << "\nCodigo: " << nuevo.codigo << endl;

	cout << "Indique el primer nombre:";
	cin >> _primer_nombre;
	nuevo.set_primer_nombre(_primer_nombre);
	cout << "\nCodigo: " << nuevo.primer_nombre << endl;

	cout << "Indique el segundo nombre:";
	cin >> _segundo_nombre;
	nuevo.set_segundo_nombre(_segundo_nombre);

	cout << "Indique el primer apellido:";
	cin >> _primer_apellido;
	nuevo.set_primer_apellido(_primer_apellido);

	cout << "Indique el segundo apellido:";
	cin >> _segundo_apellido;
	nuevo.set_segundo_apellido(_segundo_apellido);

	cout << "Indique el genero:";
	cin >> _genero;
	nuevo.set_genero(_genero);

	cout << "Indique la ciudad de residencia:";
	cin >> _ciudad;
	nuevo.set_ciudad(_ciudad);

	cout << "Indique la region donde se ubica:";
	cin >> _region;
	nuevo.set_region(_region);

	cout << "Indique su pais:";
	cin >> _pais;
	nuevo.set_pais(_pais);

	nuevo.posicion = 0;
	nuevo.size = 0;

	nuevo.Write(file, fileIndex, delim);

	file.close();
	fileIndex.close();
}

void Amazon::consultarCliente() {
	ifstream file("clientes.bin", ios::in | ios::binary);

	if (!file) {
		cout << "Error al intentar abrir el archivo .bin\n\n";
		return;
	}

	cout << " ***** C O N S U L T A  D E  C L I E N T E S ***** \n\n";

	int opc = 0;
	cout << "Elige la forma de busqueda que desea realizar: "
		 << "\n1. Buscar por Nombre. \n2. Buscar por Codigo. \n3. Listar los Clientes.\n4. Salir";
	
	switch (opc)
	{
	case 1:
		char _nombreCompleto[120];
		cout << "\nIngrese el Nombre Completo del Cliente: ";
		cin >> _nombreCompleto;

		if (buscarClienteNombre(file,_nombreCompleto)) {
			DelimTextBuffer delim('^', 300);
			Cliente actual;

			actual.Read(file, delim);
			actual.print();
		}
		else
			cout << "\nNo se encontro el cliente que busca :(\n";

		break;

	case 2:
		char _codigo[13];
		cout << "\nIngrese el Codigo del Cliente: ";
		cin >> _codigo;

		if (buscarClienteCodigo(file, _codigo)) {
			DelimTextBuffer delim('^', 300);
			Cliente actual;

			actual.Read(file, delim);
			actual.print();
		}
		else
			cout << "\nNo se encontro el cliente que busca :(\n";

		break;

	case 3:
		listarClientes(file);
		break;

	case 4:
		cout << "\nSaliendo......\n";
		break;
	default:
		cout << "\nOPCION INCORRECTA.\n";
		break;
	}

	file.close();
}

void Amazon::modificarCliente() {
	ifstream file("clientes.bin", ios::in | ios::binary);

	if (!file) {
		cout << "Error al intentar abrir el archivo .bin\n\n";
		return;
	}

	cout << " ***** M O D I F I C A R  C L I E N T E S ***** \n\n";

	char _code[13];
	cout << "\nIngrese el Codigo del Cliente: ";
	cin >> _code;

	Cliente actual;
	int posicion = -1;
	if (buscarClienteCodigo(file, _code)) {
		DelimTextBuffer delim('^', 300);
		posicion = file.tellg();
		actual.Read(file, delim);
		file.close();
	}
	else {
		cout << "\nNo se encontro el cliente que busca :(\n";
		return;

	}

	int opc = 0;
	cout << "Elige un paramtro a editar: "
		<< "\n1. Modificar Codigo. \n2. Modificar Primer Nombre. \n3. Modificar Segundo Nombre. \n4. Modificar Primer Apellido." 
		<< " \n5. Modificar Segundo Apellido. \n6. Modificar Genero. \n7. Modificar Ciudad. \n8. Modificar Region. \n9. Modificar Pais. \n10.Salir.";

	ofstream fileE("clientes.bin", ios::out | ios::binary | ios::app);
	ofstream fileIndex("clientes.index", ios::out | ios::app | ios::binary);

	switch (opc) {
	case 1:
		char _codigo[13];
		cout << "\nIngrese el nuevo Codigo: ";
		cin >> _codigo;

		actual.set_codigo(_codigo);
		fileE.seekp(ios::beg, posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE,fileIndex,delim);

		cout << "\nMODIFICADO.......\n";
		break;

	case 2:
		char _primer_nombre[30];
		cout << "\nIngrese el nuevo primer nombre: ";
		cin >> _primer_nombre;

		actual.set_primer_nombre(_primer_nombre);
		fileE.seekp(ios::beg, posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;

	case 3:
		char _segundo_nombre[30];
		cout << "\nIngrese el nuevo segundo nombre: ";
		cin >> _segundo_nombre;

		actual.set_segundo_nombre(_segundo_nombre);
		fileE.seekp(ios::beg, posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;

	case 4:
		char _primer_apellido[30];
		cout << "\nIngrese el nuevo primer apellido: ";
		cin >> _primer_apellido;

		actual.set_primer_apellido(_primer_apellido);
		fileE.seekp(ios::beg, posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;

	case 5:
		char _segundo_apellido[30];
		cout << "\nIngrese el nuevo segundo apellido: ";
		cin >> _segundo_apellido;

		actual.set_segundo_apellido(_segundo_apellido);
		fileE.seekp(ios::beg, posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;

	case 6:
		char _genero[30];
		cout << "\nIngrese el nuevo genero: ";
		cin >> _genero;

		actual.set_genero(_genero);
		fileE.seekp(ios::beg, posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;

	case 7:
		char _ciudad[30];
		cout << "\nIngrese el nueva ciudad: ";
		cin >> _ciudad;

		actual.set_ciudad(_ciudad);
		fileE.seekp(ios::beg, posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;

	case 8:
		char _region[30];
		cout << "\nIngrese el nueva region: ";
		cin >> _region;

		actual.set_region(_region);
		fileE.seekp(ios::beg, posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;

	case 9:
		char _pais[30];
		cout << "\nIngrese el nuevo primer apellido: ";
		cin >> _pais;

		actual.set_pais(_pais);
		fileE.seekp(ios::beg, posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;
	case 10:
		cout << "\nSaliendo.......\n";
		break;
	
	default:
		cout << "\nOPCION INCORRECTA.......\n";
		break;
	}
}

bool Amazon::buscarClienteCodigo(istream& file, const char* _codigo) {
	file.seekg(0, ios::beg);

	while (!file.eof()) {
		DelimTextBuffer delim('^', 300);
		Cliente actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.codigo == _codigo) {
			file.seekg(ios::beg, posicion);
			return true;
		}
	}
	return false;
}

bool Amazon::buscarClienteNombre(istream& file, const char* _nombre) {
	file.seekg(0, ios::beg);

	while (!file.eof()) {
		DelimTextBuffer delim('^', 300);
		Cliente actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		char* nombreCompreto = new char[strlen(actual.primer_nombre)];
		strcpy_s(nombreCompreto, strlen(actual.primer_nombre) + 1, actual.primer_nombre);
		strcat_s(nombreCompreto, strlen(nombreCompreto) + strlen(actual.segundo_nombre) + 1, actual.segundo_nombre);
		strcat_s(nombreCompreto, strlen(nombreCompreto) + strlen(actual.primer_apellido) + 1, actual.primer_apellido);
		strcat_s(nombreCompreto, strlen(nombreCompreto) + strlen(actual.segundo_apellido) + 1, actual.segundo_apellido);

		if (_nombre == nombreCompreto) {
			file.seekg(ios::beg, posicion);
			return true;
		}
	}
	return false;
}

bool Amazon::listarClientes(istream& file) {
	cout << " ***** L I S T A  D E  C L I E N T E S ***** \n\n";
	file.seekg(0, ios::beg);

	Cliente actual;
	while (!file.eof()) {
		DelimTextBuffer delim('^', 300);
		Cliente actual;

		actual.Read(file, delim);
		actual.print();
	}

	return true;
}