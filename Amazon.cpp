#include "Amazon.h"
#include "BusquedasSecuenciales.h"
#include<stdio.h>
#include<windows.h>

void Amazon::agregarCliente(const char* _code) {
	ofstream file("clientes.bin", ios::out | ios::app | ios::binary);

	if (!file) {
		cout << "Error al intentar abrir el archivo .bin de clientes\n\n";
		return;
	}

	cout << " ***** I N G R E S O  D E  C L I E N T E S ***** \n\n";

	char _codigo[13];
	if (_code == nullptr) {
		cin.ignore();
		cout << "INGRESE LOS DATOS PARA EL CLIENTE:\nIndique codigo: ";
		cin.getline(_codigo, 13);
	}
	else {
		strcpy_s(_codigo, strlen(_code) + 1, _code);
	}

	Cliente nuevo;
	DelimTextBuffer delim('^',300);

	int _id = nuevo.getNextId();
	nuevo.set_codigo(_codigo);

	char _primer_nombre[30];
	char _segundo_nombre[30];
	char _primer_apellido[30];
	char _segundo_apellido[30];
	char _genero[2];
	char _ciudad[50];
	char _region[50];
	char _pais[50];

	cout << "Indique el primer nombre:";
	cin >> _primer_nombre;
	nuevo.set_primer_nombre(_primer_nombre);

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

	cin.ignore();
	cout << "Indique la ciudad de residencia:";
	cin.getline(_ciudad,50);
	nuevo.set_ciudad(_ciudad);
	
	cout << "Indique la region donde se ubica:";
	cin.getline(_region,50);
	nuevo.set_region(_region);

	cout << "Indique su pais:";
	cin.getline(_pais,50);
	nuevo.set_pais(_pais);

	nuevo.posicion = 0;
	nuevo.size = 0;
	nuevo.id = _id;

	ofstream fileIndex("clientes.index", ios::out | ios::app | ios::binary);
	nuevo.Write(file, fileIndex, delim);

	file.close();
	fileIndex.close();

	cout << "\nCLIENTE AGREGADO CON EXITO!!!\n";
}

void Amazon::agregarProducto()
{
	ofstream file("productos.bin", ios::out | ios::app | ios::binary);

	if (!file)
	{
		cout << "Error al intentar abrir el archivo .bin de productos\n";
			return;
	}

	cout << " ***** I N G R E S O  D E  P R O D U C T O S ***** \n\n";
	
	Producto nuevo;
	
	DelimTextBuffer delim('^', 300);

	int id = nuevo.getNextId();
	cout << id;

	char codigo[10];
	char categoria[25];
	char _sub_categoria[25];
	char nombre[200];
	char descripcion[2000];
	float precio_actual;

	cout << "INGRESE LOS DATOS PARA EL PRODUCTO:\nIngrese el Codigo: ";
	cin.ignore();
	cin.getline(codigo,10);
	nuevo.set_codigo(codigo);
	
	cout << "Ingrese la Categoria: ";
	cin.getline(categoria,25);
	nuevo.set_categoria(categoria);

	cout << "Ingrese la Sub-Categoria: ";
	cin.getline(_sub_categoria,25);
	nuevo.set_sub_categoria(_sub_categoria);

	cout << "Ingese el Nombre: ";
	cin.getline(nombre,200);
	nuevo.set_nombre(nombre);
	
	cout << "Ingrese una Descripcion: ";
	cin.getline(descripcion,2000);
	nuevo.set_descripcion(descripcion);

	cout << "Ingrese el Precio del Producto: ";
	cin >> precio_actual;
	nuevo.precio_actual = precio_actual;

	nuevo.id = id;
	nuevo.posicion = 0;
	nuevo.size = 0;

	ofstream fileIndex("producto.index", ios::out | ios::app | ios::binary);
	nuevo.Write(file, fileIndex, delim);

	file.close();
	fileIndex.close();


	cout << "\nPRODUCTO AGREGADO CON EXITO!!!\n";
}

void Amazon::consultarCliente() {
	ifstream file("clientes.bin", ios::in | ios::binary | ios::_Nocreate);
	Busqueda buscador;

	if (!file) {
		cout << "Error al intentar abrir el archivo .bin\n\n";
		return;
	}

	cout << "\n\t ***** C O N S U L T A  D E  C L I E N T E S ***** \n\n";

	int opc = 0;
	cout << "Elige la forma de busqueda que desea realizar: "
		 << "\n1. Buscar por Nombre. \n2. Buscar por Codigo. \n3. Listar los Clientes.\n4. Salir \n";

	cout << "Ingrese una opcion: ";
	cin >> opc;
	
	switch (opc)
	{
	case 1:
		char _nombreCompleto[120];
		cin.ignore();
		cout << "\nIngrese el Nombre Completo del Cliente: ";
		cin.getline(_nombreCompleto,120);

		if (buscador.buscarClienteNombre(file,_nombreCompleto)) {
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

		if (buscador.buscarClienteCodigo(file, _codigo)) {
			DelimTextBuffer delim('^', 300);
			Cliente actual;

			actual.Read(file, delim);
			actual.print();
		}
		else
			cout << "\nNo se encontro el cliente que busca :(\n";

		break;

	case 3:
		if (!listarClientes())
			cout << "\n\nNO HAY REGISTROS QUE MOSTRAR\n";
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

void Amazon::consultarProducto(){
	ifstream file("productos.bin", ios::in | ios::binary | ios::_Nocreate);
	Busqueda buscador;

	if (!file)
	{
		cout << "Error al intentar abrir el archivo .bin \n\n";
		return;
	}

	cout << " ****** C O N S U L T A  D E  P R O D U C T O S **** \n\n";

	int opcion = 0;

	cout << "Elige la forma de busqueda :"
		<< "\n1.Buscar por Nombre.  \n2.Buscar por codigo. \n3.Listar los Producto.\n4.Salir \n";
	cout << "Ingrese una opcion:";
	cin >> opcion;

	cout << "\n";

	switch (opcion)
	{

	case 1:

		char _nombre[200];
		cin.ignore();
		cout << "\nIngrese el Nombre del Producto: ";
		cin.getline(_nombre,200);

		if (buscador.buscarProductoNombre(file, _nombre))
		{
			DelimTextBuffer delim('^', 300);
			Producto actual;

			actual.Read(file, delim);
			actual.print();
		}
		else
			cout << "\nNo se encontro el producto que buscaba \n";
		break;
	case 2:

		char codigo[10];
		cout << "\n Ingrese el Codigo de Producto: ";
		cin >> codigo;


		if (buscador.buscarProductoCodigo(file, codigo))
		{
			DelimTextBuffer delim('^', 300);
			Producto actual;

			actual.Read(file, delim);
			actual.print();
		}

		else
			cout << "\nNo se encontro el producto  que buscaba \n";

		break;
	case 3:
		if (!listarProductos())
			cout << "\n\nNO HAY REGISTROS QUE MOSTRAR\n";
		break;
	case 4:
		cout << "\n Saliendo ...\n";
		break;
	}

	file.close();
}

void Amazon::navegacionClientes() {
	ifstream file("clientes.bin", ios::in | ios::binary);
	file.seekg(0, ios::beg);

	Cliente actual;
	long posAnterior = 0;

	while (!file.eof()) {
		DelimTextBuffer delim('^', 300);
		Cliente actual;
		Cliente auxactual;

		cout << "\n\n ****** N A V E G A C I O N  D E  C L I E N T E S ****** \n\n";
		bool fin = false;
		long posicion = file.tellg();
		actual.Read(file, delim);

		long auxposicion = file.tellg();
		auxactual.Read(file, delim);

		if (actual.id != 0)
			actual.print();
		else
			cout << "\n\n **REGISTRO FUE BORRADO ANTERIORMENTE** \n\n";

		if (auxactual.id == 0) {
			fin = true;
		}
		file.seekg(auxposicion);


		if (posicion == 0) {
			int opc = 0;
			cout << "\n1. Regresar al menu anterior.\n2. Modificar Registro.\n3. Eliminar Registro.\n4. Siguiente Registro.\n5. Salir al menu.\n";
			cin >> opc;

			switch (opc) {
			case 1:
				cout << "Regresando......";
				return;
				break;

			case 2:
				if (actual.id != 0)
					modificarCliente(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 3:
				if (actual.id != 0)
					eliminarClientes(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 4:
				posAnterior = posicion;
				break;

			case 5:
				return;
				break;
			}

		}else if (posicion != 0 && fin == false) {
			int opc = 0;
			cout << "\n1. Registro anterior.\n2. Modificar Registro.\n3. Eliminar Registro.\n4. Siguiente Registro.\n5. Salir al menu.\n";
			cin >> opc;

			switch (opc) {
			case 1:
				file.seekg(posAnterior);
				break;

			case 2:
				if (actual.id != 0)
					modificarCliente(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 3:
				if (actual.id != 0)
					eliminarClientes(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 4:
				posAnterior = posicion;
				break;

			case 5:
				return;
				break;
			}
		}else if (fin == true) {
			int opc = 0;
			cout << "\n1. Registro anterior.\n2. Modificar Registro.\n3. Eliminar Registro.\n4. Salir al menu.\n";
			cin >> opc;

			switch (opc) {
			case 1:
				fin = false;
				file.seekg(posAnterior);
				break;

			case 2:
				if (actual.id != 0)
					modificarCliente(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 3:
				if (actual.id != 0)
					eliminarClientes(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 4:
				return;
				break;
			}
		}
	}

	file.close();
}

void Amazon::navegacionProductos()
{
	ifstream file("productos.bin", ios::in | ios::binary);
	file.seekg(0,ios::beg);

	Producto actual;

	long posAnterior = 0;

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Producto actual;
		Producto auxactual;

		cout << "\n\n ****** N A V E G A C I O N  D E  P R O D U C T O S **** \n\n";

		bool fin = false;
		long posicion = file.tellg();
		actual.Read(file, delim);

		long auxposicion = file.tellg();
		auxactual.Read(file, delim);

		if (actual.id != 0)
			actual.print();
		else
			cout << "\n\n **REGISTRO FUE BORRADO ANTERIORMENTE** \n\n";

		if (auxactual.id == 0) {
			fin = true;
		}
		file.seekg(auxposicion);

		if (posicion == 0) {
			int opc = 0;
			cout << "\n1. Regresar al menu anterior.\n2. Modificar Registro.\n3. Eliminar Registro.\n4. Siguiente Registro.\n5. Salir al menu.\n";
			cin >> opc;

			switch (opc) {
			case 1:
				cout << "Regresando......";
				return;
				break;

			case 2:
				if (actual.id != 0)
					modificarProducto(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 3:
				if (actual.id != 0)
					eliminarProducto(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 4:
				posAnterior = posicion;
				break;

			case 5:
				return;
				break;
			}

		}
		else if (posicion != 0 && fin == false) {
			int opc = 0;
			cout << "\n1. Registro anterior.\n2. Modificar Registro.\n3. Eliminar Registro.\n4. Siguiente Registro.\n5. Salir al menu.\n";
			cin >> opc;

			switch (opc) {
			case 1:
				file.seekg(posAnterior);
				break;

			case 2:
				if (actual.id != 0)
					modificarProducto(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 3:
				if (actual.id != 0)
					eliminarProducto(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 4:
				posAnterior = posicion;
				break;

			case 5:
				return;
				break;
			}
		}
		else if (fin == true) {
			int opc = 0;
			cout << "\n1. Registro anterior.\n2. Modificar Registro.\n3. Eliminar Registro.\n4. Salir al menu.\n";
			cin >> opc;

			switch (opc) {
			case 1:
				fin = false;
				file.seekg(posAnterior);
				break;

			case 2:
				if (actual.id != 0)
					modificarProducto(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 3:
				if (actual.id != 0)
					eliminarProducto(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 4:
				return;
				break;
			}
		}
	}
	file.close();
}

void Amazon::modificarCliente(const char* _code) {
	ifstream file("clientes.bin", ios::in | ios::binary);
	Busqueda buscador;

	if (!file) {
		cout << "Error al intentar abrir el archivo .bin\n\n";
		return;
	}

	cout << " ***** M O D I F I C A R  C L I E N T E S ***** \n\n";

	char* code;
	if (_code == nullptr) {
		code = new char[13];
		cout << "Ingrese el codigo del clientea a modificar :";
		cin >> code;
	}else {
		code = new char[strlen(_code)];
		strcpy_s(code, strlen(_code) + 1, _code);
	}

	Cliente actual;
	int posicion = -1;
	if (buscador.buscarClienteCodigo(file, code)) {
		DelimTextBuffer delim('^', 300);
		posicion = file.tellg();
		actual.Read(file, delim);
		file.close();
	}else {
		cout << "\nNo se encontro el cliente que busca :(\n";
		return;
	}

	fstream fileE("clientes.bin", ios::out | ios::in | ios::binary);
	ofstream fileIndex("clientes.index", ios::out | ios::app | ios::binary);
	Cliente modificado = actual;

	int opc = 0;
	bool modifico = false;
	while (opc != 10) {
		modificado.print();
		cout << "\nElige un parametro a editar: "
			<< "\n1. Modificar Codigo. \n2. Modificar Primer Nombre. \n3. Modificar Segundo Nombre. \n4. Modificar Primer Apellido."
			<< " \n5. Modificar Segundo Apellido. \n6. Modificar Genero. \n7. Modificar Ciudad. \n8. Modificar Region. \n9. Modificar Pais. \n10.Guardar Cambios y Salir.\n";
		cin >> opc;

		switch (opc) {
		case 1: {
			char _codigo[13];
			cout << "\nIngrese el nuevo Codigo: ";
			cin >> _codigo;
			modificado.codigo = nullptr;
			modificado.set_codigo(_codigo);
			modifico = true;
			cout << "\nMODIFICADO.......\n";
			break;
		}
		case 2: {
			char _primer_nombre[30];
			cout << "\nIngrese el nuevo primer nombre: ";
			cin >> _primer_nombre;
			modificado.primer_nombre = nullptr;
			modificado.set_primer_nombre(_primer_nombre);
			modifico = true;
			cout << "\nMODIFICADO.......\n";
			break;
		}
		case 3: {
			char _segundo_nombre[30];
			cout << "\nIngrese el nuevo segundo nombre: ";
			cin >> _segundo_nombre;
			modificado.segundo_nombre = nullptr;
			modificado.set_segundo_nombre(_segundo_nombre);
			modifico = true;
			cout << "\nMODIFICADO.......\n";
			break;
		}
		case 4: {
			char _primer_apellido[30];
			cout << "\nIngrese el nuevo primer apellido: ";
			cin >> _primer_apellido;
			modificado.primer_apellido = nullptr;
			modificado.set_primer_apellido(_primer_apellido);
			modifico = true;
			cout << "\nMODIFICADO.......\n";
			break;
		}
		case 5: {
			char _segundo_apellido[30];
			cout << "\nIngrese el nuevo segundo apellido: ";
			cin >> _segundo_apellido;
			modificado.segundo_apellido = nullptr;
			modificado.set_segundo_apellido(_segundo_apellido);
			modifico = true;
			cout << "\nMODIFICADO.......\n";
			break;
		}
		case 6: {
			char _genero[30];
			cout << "\nIngrese el nuevo genero: ";
			cin >> _genero;
			modificado.genero = nullptr;
			modificado.set_genero(_genero);
			modifico = true;
			cout << "\nMODIFICADO.......\n";
			break;
		}
		case 7: {
			char _ciudad[30];
			cout << "\nIngrese el nueva ciudad: ";
			cin >> _ciudad;
			modificado.ciudad = nullptr;
			modificado.set_ciudad(_ciudad);
			modifico = true;
			cout << "\nMODIFICADO.......\n";
			break;
		}
		case 8: {
			char _region[30];
			cout << "\nIngrese el nueva region: ";
			cin >> _region;
			modificado.region = nullptr;
			modificado.set_region(_region);
			modifico = true;
			cout << "\nMODIFICADO.......\n";
			break;
		}
		case 9: {
			char _pais[30];
			cout << "\nIngrese el nuevo pais: ";
			cin >> _pais;
			modificado.pais = nullptr;
			modificado.set_pais(_pais);
			modifico = true;
			cout << "\nMODIFICADO.......\n";
			break;
		}
		case 10:
			cout << "\nGuardando.......\n";
			break;

		default:
			cout << "\nOPCION INCORRECTA.......\n";
			break;
		}
	}

	if (modifico == true) {
		eliminarClienteAux(actual, fileE, posicion, fileIndex);

		fileE.seekp(0,ios::end);
		DelimTextBuffer delim('^', 300);
		modificado.Write(fileE, fileIndex, delim);
		cout << "\nCambios Guardados!!!\nSaliendo.......\n";
	}else {
		cout << "\nNO SE REALIZARON CAMBIOS EN EL REGISTRO.......\n";
		cout << "\nSaliendo.......\n";
	}

	file.close();
	fileE.close();
	fileIndex.close();
}

void Amazon::modificarProducto(const char* _code){
	ifstream file("productos.bin",ios::in | ios::binary);
	Busqueda buscador;

	if (!file)
	{
		cout << "Error al intentar abrir el archivo .bin \n\n";
		return;
	}

	cout << "*** M O D I F I C A R   P R O D U C T O S *** \n\n";

	char* code;
	if (_code == nullptr) {
		code = new char[13];
		cout << "Ingrese el codigo del producto a modificar :";
		cin >> code;
	}else {
		code = new char[strlen(_code)];
		strcpy_s(code, strlen(_code) + 1, _code);
	}

	Producto actual;
	int posicion = -1;
	if (buscador.buscarProductoCodigo(file, code))
	{
		DelimTextBuffer delim('^', 300);
		posicion = file.tellg();
		actual.Read(file, delim);
		file.close();
	}else
	{
		cout << "No se encontro el producto que buscaba \n";
		return;
	}

	fstream fileE("productos.bin", ios::out | ios::in | ios::binary);
	ofstream fileIndex("productos.bin", ios::out | ios::app | ios::binary);
	Producto modificado = actual;

	int opcion = 0;
	bool modifico = false;
	while (opcion != 7) {
		modificado.print();
		cout << "\nElige un parametro a editar: "
			<< "\n1.Modificar Codigo \n2.Modificar Categoria \n3.Modificar Sub-Categoria "
			<< "\n4.Modificar Nombre \n5.Modificar Descripcion  \n6.Modificar Precio Actual \n7.Guardar Cambios\n";
		cin >> opcion;

		switch (opcion){
		case 1: {
			char codigo[10];
			cout << "\nIngrese el nuevo Codigo: ";
			cin >> codigo;
			modificado.codigo = nullptr;
			modificado.set_codigo(codigo);
			modifico = true;
			cout << "\nMODIFICADO.......\n";
			break;
		}
		case 2: {
			char categoria[25];
			cout << "\n Ingrese la nueva categoria: ";
			cin >> categoria;
			modificado.categoria = nullptr;
			modificado.set_categoria(categoria);
			modifico = true;
			cout << "\nMODIFICADO.......\n";
			break;
		}
		case 3: {
			char sub_categoria[25];
			cout << "\n Ingrese la nueva sub-categoria: ";
			cin >> sub_categoria;
			modificado.sub_categoria = nullptr;
			modificado.set_sub_categoria(sub_categoria);
			modifico = true;
			cout << "\nMODIFICADO.......\n";
			break;

		}
		case 4: {
			char nombre[200];
			cout << "\Ingrese el nuevo Nombre: ";
			cin >> nombre;
			modificado.nombre = nullptr;
			modificado.set_nombre(nombre);
			modifico = true;
			cout << "\nMODIFICADO.......\n";
			break;

		}
		case 5: {
			char descripcion[2000];
			cout << "Ingrese Descripcion: ";
			cin >> descripcion;
			modificado.descripcion = nullptr;
			modificado.set_descripcion(descripcion);
			modifico = true;
			cout << "\nMODIFICADO.......\n";
			break;
		}
		case 6: {
			float precio_actual;
			cout << "Ingrese nuevo Precio: ";
			cin >> precio_actual;
			modificado.precio_actual = 0;
			modificado.precio_actual = (precio_actual);
			modifico = true;
			cout << "\nMODIFICADO.......\n";
			break;
		}
		case 7:
			cout << "\nGuardando .... \n";
			break;

		default:
			cout << "\nOPCION INCORRECTA.......\n";
			break;
		}
	}

	if (modifico == true) {
		eliminarProductoAux(actual, fileE, posicion, fileIndex);

		fileE.seekp(0,ios::end);
		DelimTextBuffer delim('^', 300);
		modificado.Write(fileE, fileIndex, delim);
		cout << "\nCambios Guardados!!!\nSaliendo.......\n";
	}
	else {
		cout << "\nNO SE REALIZARON CAMBIOS EN EL REGISTRO.......\n";
		cout << "\nSaliendo.......\n";
	}

	file.close();
	fileE.close();
	fileIndex.close();
}

bool Amazon::listarClientes() {
	ifstream file("clientes.bin", ios::in | ios::binary | ios::_Nocreate);

	if (!file){
		cout << "Error al intentar abrir el archivo .bin de clientes\n";
		return false;
	}

	cout << "\n\n***** L I S T A  D E  C L I E N T E S *****\n\n";
	file.seekg(0);

	Cliente actual;
	bool hay = false;
	while (!file.eof()) {
		DelimTextBuffer delim('^', 300);
		Cliente actual;

		actual.Read(file, delim);
		if (actual.id != 0) {
			actual.print();
			hay = true;
		}
	}

	file.close();
	return hay;
}

bool Amazon::listarProductos()
{
	ifstream file("productos.bin", ios::in | ios::binary | ios::_Nocreate);

	if (!file){
		cout << "Error al intentar abrir el archivo .bin de productos\n";
		return false;
	}

	cout << "\n\n*** L I S T A D O   D E  P R O D U C T O S ***\n\n";

	file.seekg(0);

	Producto actual;
	bool hay = false;
	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);

		Producto actual;

		actual.Read(file, delim);

		if (actual.id != 0) {
			actual.print();
			hay = true;
		}
	}

	file.close();
	return hay;
}

void Amazon::eliminarClientes(const char* _code){
	ifstream file("clientes.bin" ,ios::in | ios::binary | ios::_Nocreate);
	fstream fileE("clientes.bin", ios::out | ios::in | ios::binary | ios::_Nocreate);
	ofstream fileIndex("clientes.index", ios::out | ios::app | ios::binary | ios::_Nocreate);
	Busqueda buscador;

	if (!file && !fileE && !fileIndex)
	{
		cout << "Error al intentar abrir el archivo .bin\n\n";
		return;

	}

	cout << "\n\n**** E L I M I N A R  C L I E N T E ";
	char* code;
	if (_code == nullptr) {
		code = new char[13];
		cout << "\nIngrese el codigo del clientea a eliminar :";
		cin >> code;
	}
	else {
		code = new char[strlen(_code)];
		strcpy_s(code, strlen(_code) + 1, _code);
	}
		

	Cliente actual;
	int posicion = -1;
	int opcion;
	if (buscador.buscarClienteCodigo(file, code))
	{
		DelimTextBuffer delim('^', 300);
		posicion = file.tellg();
		actual.Read(file, delim);
		file.close();
	}
	else
	{
		cout << "\nNo se encontro el cliente que busca \n";
		return;
	}

	cout << "\n\nEsta seguro que Desea a eliminar el cliente completamente (1 Si) (2 No)"
		 << "\nIngrese una opcion:";
	cin >> opcion;

	switch (opcion)
	{
	case 1: {
		eliminarClienteAux(actual, fileE, posicion, fileIndex);
		cout << "... Cliente Eliminado....";

		break;
	}
	case 2:
		cout << "... Operacion Cancelada....";
		break;

	}

	file.close();
	fileE.close();
	fileIndex.close();
}

void Amazon::eliminarClienteAux(Cliente actual, fstream& fileE, long posicion, ofstream& fileIndex) {
	actual.id = 0;
	fileE.seekp(posicion, ios::beg);

	DelimTextBuffer delim('^', 300);
	actual.Write(fileE, fileIndex, delim);
}

void Amazon::eliminarProductoAux(Producto actual, fstream& fileE, long posicion, ofstream& fileIndex) {
	actual.id = 0;
	fileE.seekp(posicion, ios::beg);

	DelimTextBuffer delim('^', 300);
	actual.Write(fileE, fileIndex, delim);
}

void Amazon::eliminarProducto(const char* _code)
{
	ifstream file("productos.bin", ios::in | ios::binary | ios::_Nocreate);
	ifstream fileDetalles("detalles.bin", ios::in | ios::binary | ios::_Nocreate);
	fstream fileE("productos.bin", ios::out | ios::in | ios::binary | ios::_Nocreate);
	ofstream fileIndex("prodcutos.index", ios::out | ios::app | ios::binary | ios::_Nocreate);

	Busqueda buscador;

	if (!file && !fileDetalles && !fileE && !fileIndex)
	{
		cout << "Error al intentar abrir el archivo .bin\n\n";
		return;
	}

	cout << "\n\n**** E L I M I N A R  P R O D U C T O ";
	char* code;
	if (_code == nullptr) {
		code = new char[13];
		cout << "\nIngrese el codigo del producto a eliminar :";
		cin >> code;
	}
	else {
		code = new char[strlen(_code)];
		strcpy_s(code, strlen(_code) + 1, _code);
	}

	Producto  actual;
	int posicion = -1;
	int opcion;

	if (buscador.buscarProductoCodigo(file, code))
	{
		DelimTextBuffer delim('^', 300);
		posicion = file.tellg();
		actual.Read(file, delim);
		actual.print();
		file.close();
	}
	else
	{
		cout << "\nNo se encontro el producto que busca :(\n";
		return;
	}

	if (buscador.buscarDetalleProducto(fileDetalles, actual.id)) {
		cout << "\nEste producto tiene facturas asociadas, no puede eliminarse.";
		return;
	}

	cout << "\nEsta seguro que Desea a eliminar el  producto completamente (1 SI) (2 NO)"
		<< "\nIngrese una opcion:";
	cin >> opcion;

	switch (opcion)
	{
	case 1: {
		eliminarProductoAux(actual, fileE, posicion, fileIndex);
		cout << "... Producto  Eliminado....\n";
		break;
	}
	case 2:
		cout << "... Operacion Cancelada....\n";
		break;
	}

	file.close();
	fileE.close();
	fileDetalles.close();
	fileIndex.close();
}

void Amazon::RegistrarCompra() {
	Busqueda buscardor;
	Factura factura;

	factura.id = factura.getNextId();

	ofstream fileF("facturas.bin", ios::out | ios::app | ios::binary);
	ofstream fileFIndex("facturas.index", ios::out | ios::app | ios::binary);

	if (!fileF && !fileFIndex) {
		cout << "\nError al intentar abrir los archivos :(\n";
		return;
	}

	cout << factura.id;

	char _codigo[13];
	char* _hora= new char[6];

	cout << "\nDATOS DE FACTURA:\nIndique codigo para su Factura: ";
	cin >> _codigo;

	cout << "\nDatos de Fecha:\nIndique el dia de compra: ";
	cin >> factura.dia;
	cout << "Indique el mes de compra: ";
	cin >> factura.mes;
	cout << "Indique el anio de compra: ";
	cin >> factura.anio;
	cout << "Indique la hora de compra: ";
	cin >> _hora;
	factura.set_hora(_hora);

	cout << "\nDatos de Localizacion:\nIndique su cordenada X: ";
	cin >> factura.ubicacion_X;
	cout << "\nIndique su cordenada Y: ";
	cin >> factura.ubicacion_Y;

	factura.set_codigo(_codigo);

	char _codigoCliente[13];


	//Seleccionar el Cliente.
	cout << "\nINGRESE LOS DATOS PARA EL CLIENTE:\nIndique codigo: ";
	cin >> _codigoCliente;
	bool clienteEncontrado = false;
	
	while (clienteEncontrado == false) {
		ifstream fileC("clientes.bin", ios::in | ios::binary);
		fileC.seekg(0);

		if (buscardor.buscarClienteCodigo(fileC, _codigoCliente)) {
			Cliente cliente;
			DelimTextBuffer delim('^', 300);
			cliente.Read(fileC, delim);
			
			if (cliente.id != 0) {
				factura.cliente_id = cliente.id;
				clienteEncontrado = true;
				cout << "\nCliente: ";
				cliente.print();
				break;
			}
		}
		else {
			cout << "\nNo se encontro el cliente que busca, intente denuevo, Si desea crear uno precione 1, para intentar denuevo precione 2";
			int opc = 1;
			cin >> opc;

			switch (opc) {
			case 1:
				cin.ignore();
				cout << "INGRESE LOS DATOS PARA EL CLIENTE:\nIndique codigo: ";
				cin.getline(_codigoCliente, 13);
				agregarCliente(_codigoCliente);
				break;
			default:
				cout << "INGRESE LOS DATOS PARA EL CLIENTE:\nIndique codigo: ";
				cin >> _codigoCliente;
				break;
			}
			fileC.close();
		}
	}

	//Cargar Productos.
	cout << "\nDATOS DE PRODUCTOS:";
	bool agregarProd = true;
	vector<Detalle> carrito;
	while (agregarProd) {
		ifstream fileP("productos.bin", ios::in | ios::binary);
		char _codigoProducto[10]; 
		cout << "\nIndique codigo del producto: ";
		cin >> _codigoProducto;

		if (buscardor.buscarProductoCodigo(fileP,_codigoProducto)) {
			int cantidad =1;
			cout << "\nIndique la cantidad del producto: ";
			cin >> cantidad;

			Producto producto;
			Detalle detalle;
			DelimTextBuffer delim('^', 300);
			producto.Read(fileP, delim);

			if (producto.id != 0) {
				detalle.id = detalle.getNextId();
				detalle.factura_id = factura.id;
				detalle.producto_id = producto.id;
				detalle.cantidad = cantidad;
				detalle.precio_unit = producto.precio_actual;
				agregarAlCarrito(carrito,detalle);
				detalle.print();
				cout << "\nPRODUCTO AGREGADO AL CARRITO.\n";
			}

			int opc = 0;
			cout << "\nDesea Agregar Mas Productos al Carrito?? 1 (Si), 2(No): ";
			cin >> opc;

			switch (opc)
			{
			case 1:
				agregarProd = true;
				break;
			default:
				agregarProd = false;
				break;
			}
		}
		else {
			cout << "\nNo se encontro ese producto, intente con otro.";
		}
		fileP.close();
	}

	if (!carrito.empty()) {
		cout << "\n\nRESUMEN DE COMPRAS: ";
		ofstream fileD("detalles.bin", ios::out | ios::app | ios::binary);
		ofstream fileDIndex("detalles.index", ios::out | ios::binary);

		for (int i = 0; i < carrito.size(); i++) {
			factura.total_neto += (carrito[i].precio_unit * carrito[i].cantidad);
			DelimTextBuffer delim('^', 300);
			carrito[i].Write(fileD,fileDIndex,delim);
			carrito[i].print();
		}

		if (factura.total_neto != 0)
			factura.total_impuesto = (factura.total_neto * 0.15);
		else
			factura.total_impuesto = 0;

		DelimTextBuffer delim2('^', 300);
		factura.Write(fileF, fileFIndex, delim2);
		factura.print();
		
		cout << "\nTotal a pagar: " << (factura.total_neto + factura.total_impuesto) << "\n\nFACTURA PROCESADA.!!!!!!!";
	}
}

void Amazon::agregarAlCarrito(vector<Detalle>& _carrito, Detalle _producto) {
	bool existe = false;
	if (_carrito.empty()) {
		_carrito.push_back(_producto);
		//cout << "\nAgregado al Carrito!!!\n";
		return;
	}

	
	for (int i = 0; i < _carrito.size(); i++) {
		if (_carrito[i].producto_id== _producto.producto_id) {
			_carrito[i].cantidad += _producto.cantidad;
			existe = true;
			break;
		}
	}

	if (!existe)
		_carrito.push_back(_producto);

	//cout << "\nAgregado al Carrito!!!\n";
}

void Amazon::eliminarFactura(const char* _code) {
	ifstream file("facturas.bin", ios::in | ios::binary | ios::_Nocreate);
	fstream fileE("facturas.bin", ios::out | ios::in | ios::binary | ios::_Nocreate);
	ofstream fileIndex("facturas.index", ios::out | ios::app | ios::binary | ios::_Nocreate);
	Busqueda buscador;

	if (!file && !fileE && !fileIndex)
	{
		cout << "Error al intentar abrir el archivo .bin\n\n";
		return;

	}

	cout << "\n\n**** E L I M I N A R  F A C T U R A S ";
	char* code;
	if (_code == nullptr) {
		code = new char[13];
		cout << "\nIngrese el codigo de la factura a eliminar :";
		cin >> code;
	}
	else {
		code = new char[strlen(_code)];
		strcpy_s(code, strlen(_code) + 1, _code);
	}


	Factura actual;
	int posicion = -1;
	int opcion;
	if (buscador.buscarFacturaCodigo(file, code))
	{
		DelimTextBuffer delim('^', 300);
		posicion = file.tellg();
		actual.Read(file, delim);
		file.close();
	}
	else
	{
		cout << "\nNo se encontro la factura que busca que busca \n";
		return;
	}

	cout << "\n\nEsta seguro que Desea a eliminar esta Factura completamente (1 Si) (2 No)"
		<< "\nIngrese una opcion:";
	cin >> opcion;

	switch (opcion)
	{
	case 1: {
		eliminarFacturaAux(actual, fileE, posicion, fileIndex);
		buscador.eliminarDetallesFactura(actual.id);
		cout << "... Factura Eliminado....";

		break;
	}
	case 2:
		cout << "... Operacion Cancelada....";
		break;

	}

	file.close();
	fileE.close();
	fileIndex.close();
}

void Amazon::eliminarFacturaAux(Factura actual, fstream& fileE, long posicion, ofstream& fileIndex) {
	actual.id = 0;
	fileE.seekp(posicion, ios::beg);

	DelimTextBuffer delim('^', 300);
	actual.Write(fileE, fileIndex, delim);
}

void Amazon::navegacionFacturas() {
	ifstream file("facturas.bin", ios::in | ios::binary);
	file.seekg(0, ios::beg);

	Factura actual;
	long posAnterior = 0;

	while (!file.eof()) {
		DelimTextBuffer delim('^', 300);
		Cliente actual;
		Cliente auxactual;

		cout << "\n\n ****** N A V E G A C I O N  D E  F A C T U R A S ****** \n\n";
		bool fin = false;
		long posicion = file.tellg();
		actual.Read(file, delim);

		long auxposicion = file.tellg();
		auxactual.Read(file, delim);

		if (actual.id != 0)
			actual.print();
		else
			cout << "\n\n **REGISTRO FUE BORRADO ANTERIORMENTE** \n\n";

		if (auxactual.id == 0) {
			fin = true;
		}
		file.seekg(auxposicion);


		if (posicion == 0) {
			int opc = 0;
			cout << "\n1. Regresar al menu anterior.\n2. Mostrar Factura Completa.\n3. Eliminar Registro.\n4. Siguiente Registro.\n5. Salir al menu.\n";
			cin >> opc;

			switch (opc) {
			case 1:
				cout << "Regresando......";
				return;
				break;

			case 2:
				if (actual.id != 0)
					modificarCliente(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 3:
				if (actual.id != 0)
					eliminarFactura(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 4:
				posAnterior = posicion;
				break;

			case 5:
				return;
				break;
			}

		}
		else if (posicion != 0 && fin == false) {
			int opc = 0;
			cout << "\n1. Registro anterior.\n2. Mostrar Factura Completa.\n3. Eliminar Registro.\n4. Siguiente Registro.\n5. Salir al menu.\n";
			cin >> opc;

			switch (opc) {
			case 1:
				file.seekg(posAnterior);
				break;

			case 2:
				if (actual.id != 0)
					modificarCliente(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 3:
				if (actual.id != 0)
					eliminarFactura(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				file.close();
				break;

			case 4:
				posAnterior = posicion;
				break;

			case 5:
				return;
				break;
			}
		}
		else if (fin == true) {
			int opc = 0;
			cout << "\n1. Registro anterior.\n2. Mostrar Factura Completa.\n3. Eliminar Registro.\n4. Salir al menu.\n";
			cin >> opc;

			switch (opc) {
			case 1:
				fin = false;
				file.seekg(posAnterior);
				break;

			case 2:
				if (actual.id != 0)
					modificarCliente(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 3:
				if (actual.id != 0)
					eliminarFactura(actual.codigo);
				else
					cout << "\nNO ES POSIBLE REGISTRO YA DEJO DE EXISTIR";
				file.close();
				break;

			case 4:
				return;
				break;
			}
		}
	}

	file.close();
}

bool Amazon::listarDetallesDeFactura(int _id_factura) {
	ifstream file("detalles.bin", ios::in | ios::binary | ios::_Nocreate);

	if (!file) {
		cout << "Error al intentar abrir el archivo .bin de clientes\n";
		return false;
	}

	cout << "\n\n***** D E T A L L E S  D E  F A C T U R A *****\n\n";
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Detalle actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id != 0) {
			if (actual.factura_id == _id_factura){
				actual.print();
				return true;
			}
		}
	}

	return false;
}