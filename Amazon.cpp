#include "Amazon.h"
#include "BusquedasSecuenciales.h"

void Amazon::agregarCliente() {
	ofstream file("clientes.bin", ios::out | ios::app | ios::binary);

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
	nuevo.id = _id;

	ofstream fileIndex("clientes.index", ios::out | ios::app | ios::binary);
	nuevo.Write(file, fileIndex, delim);

	file.close();
	fileIndex.close();
}
//--error
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

	char codigo[10];
	char categoria[25];
	char _sub_categoria[25];
	char nombre[200];
	char descripcion[2000];
	float precio_actual;

	cout << "INGRESE LOS DATOS PARA EL PRODUCTO:\nIngrese  codigo: ";
	cin >> codigo;
	
	nuevo.set_codigo(codigo);
	//cout << "\nCodigo: " << nuevo.codigo << endl;
	
	cout << "Ingrese Categoria: ";
	cin >> categoria;
	nuevo.set_categoria(categoria);

	cout << "Ingrese Sub-Categoria: ";
	cin >> _sub_categoria;
	nuevo.set_sub_categoria(_sub_categoria);

	cout << "Ingese Nombre: ";
	cin >> nombre;
	nuevo.set_nombre(nombre);
	

	cout << "Ingrese Descripcion: ",
	cin >> descripcion;
	nuevo.set_descripcion(descripcion);

	cout << "Ingrese el Precio del Producto: ";
	cin >> precio_actual;
	nuevo.precio_actual = precio_actual;


	nuevo.posicion = 0;
	nuevo.size = 0;

	ofstream fileIndex("producto.index", ios::out | ios::app | ios::binary);
	nuevo.Write(file, fileIndex, delim);

	file.close();
	fileIndex.close();



}

void Amazon::consultarCliente() {
	ifstream file("clientes.bin", ios::in | ios::binary);
	Busqueda buscador;

	if (!file) {
		cout << "Error al intentar abrir el archivo .bin\n\n";
		return;
	}

	cout << " ***** C O N S U L T A  D E  C L I E N T E S ***** \n\n";

	int opc = 0;
	cout << "Elige la forma de busqueda que desea realizar: "
		 << "\n1. Buscar por Nombre. \n2. Buscar por Codigo. \n3. Listar los Clientes.\n4. Salir";
	
	//agregue  esto
	cout << "Ingrese una opcion: ";
	cin >> opc;
	
	switch (opc)
	{
	case 1:
		char _nombreCompleto[120];
		cout << "\nIngrese el Nombre Completo del Cliente: ";
		cin >> _nombreCompleto;

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
		listarClientes(file);
		break;

	case 4:
		cout << "\nSaliendo......\n";
		break;
	default:
		//cout << "\nOPCION INCORRECTA.\n";
		break;
	}

	file.close();
}

void Amazon::consultarProducto(){
	ifstream file("productos.bin", ios::in | ios::binary);
	Busqueda buscador;

	if (!file)
	{
		cout << "Error al intentar abrir el archivo .bin \n\n";
		return;
	}

	cout << " ****** C O N S U L T A  D E  P R O D U C T O S **** \n\n";

	int opcion = 0;

	cout << "Elige la forma de busqueda :"
		<< "\n 1.Buscar por Nombre  \n2.Buscar por codigo";
	cout << "Ingrese una opcion:";
	cin >> opcion;

	cout << "\n";

	switch (opcion)
	{

	case 1:

		char _nombre[200];
		cout << "\n Ingrese el Nombre del Producto: ";
		cin >> _nombre;

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

		listarProductos(file);
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

		actual.Read(file, delim);
		actual.print();

		if (file.tellg() == 0) {
			int opc = 0;
			cout << "1. Regresar al menu anterior.\n2. Modificar Registro.\n3. Eliminar Registro.\n4. Siguiente Registro.\n5. Salir al menu.\n";
			cin >> opc;

			switch (opc) {
			case 1:
				cout << "Regresando......";
				return;
				break;

			case 2:
				modificarCliente();
				file.close();
				break;

			case 3:
				//Pendiente.
				file.close();
				break;

			case 4:
				posAnterior = file.tellg();
				break;

			case 5:
				return;
				break;
			}

		}else if (file.tellg() != 0 && file.tellg() != file.eof()) {
			int opc = 0;
			cout << "1. Registro anterior.\n2. Modificar Registro.\n3. Eliminar Registro.\n4. Siguiente Registro.\n5. Salir al menu.\n";
			cin >> opc;

			switch (opc) {
			case 1:
				file.seekg(posAnterior);
				break;

			case 2:
				modificarCliente();
				file.close();
				break;

			case 3:
				posAnterior = file.tellg();
				//Pendiente.
				file.close();
				break;

			case 4:
				posAnterior = file.tellg();
				break;

			case 5:
				return;
				break;
			}
		}
		else if (file.tellg() == file.eof()) {
			int opc = 0;
			cout << "1. Registro anterior.\n2. Modificar Registro.\n3. Eliminar Registro.\n4. Salir al menu.\n";
			cin >> opc;

			switch (opc) {
			case 1:
				file.seekg(posAnterior);
				break;

			case 2:
				modificarCliente();
				file.close();
				break;

			case 3:
				posAnterior = file.tellg();
				//Pendiente.
				file.close();
				break;

			case 4:
				return;
				break;
			}
		}
	}
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

		actual.Read(file, delim);
		actual.print();

		if (file.tellg() == 0)
		{
			int opcion = 0;

			cout << "1. Regresar al menu anterior.\n2. Modificar Registro.\n3. Eliminar Registro.\n4. Siguiente Registro.\n5. Salir al menu.\n";

			cin >> opcion;

			switch (opcion)
			{
			case 1:
				cout << "Regresando......";
				return;
				break;
			case 2:
				modificarProducto();
				file.close();
				break;
			case 3:

				file.close();
			case 4:
				posAnterior = file.tellg();
			case 5:

				return;
				break;
			}

		}
		else if (file.tellg() == file.eof())
		{
			int opcion = 0;

			cout << "1. Registro anterior.\n2. Modificar Registro.\n3. Eliminar Registro.\n4. Salir al menu.\n";
			cin >> opcion;

			switch (opcion)
			{
			case 1:
				file.seekg(posAnterior);
				break;

			case 2:
				modificarProducto();
				file.close();
				break;


			case 3:
				posAnterior = file.tellg();

				file.close();
				break;

			case 4:
				break;
			}


		}
	}
}

void Amazon::modificarCliente() {
	ifstream file("clientes.bin", ios::in | ios::binary);
	Busqueda buscador;

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
	if (buscador.buscarClienteCodigo(file, _code)) {
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
	cout << "Elige un parametro a editar: "
		<< "\n1. Modificar Codigo. \n2. Modificar Primer Nombre. \n3. Modificar Segundo Nombre. \n4. Modificar Primer Apellido." 
		<< " \n5. Modificar Segundo Apellido. \n6. Modificar Genero. \n7. Modificar Ciudad. \n8. Modificar Region. \n9. Modificar Pais. \n10.Salir.";

	ofstream fileE("clientes.bin", ios::out | ios::binary | ios::app);
	ofstream fileIndex("clientes.index", ios::out | ios::app | ios::binary);

	switch (opc) {
	case 1: {
		char _codigo[13];
		cout << "\nIngrese el nuevo Codigo: ";
		cin >> _codigo;

		actual.set_codigo(_codigo);
		fileE.seekp(posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;
	}
	case 2: {
		char _primer_nombre[30];
		cout << "\nIngrese el nuevo primer nombre: ";
		cin >> _primer_nombre;

		actual.set_primer_nombre(_primer_nombre);
		fileE.seekp(posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;
	}
	case 3: {
		char _segundo_nombre[30];
		cout << "\nIngrese el nuevo segundo nombre: ";
		cin >> _segundo_nombre;

		actual.set_segundo_nombre(_segundo_nombre);
		fileE.seekp(posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;
	}
	case 4: {
		char _primer_apellido[30];
		cout << "\nIngrese el nuevo primer apellido: ";
		cin >> _primer_apellido;

		actual.set_primer_apellido(_primer_apellido);
		fileE.seekp(posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;
	}
	case 5: {
		char _segundo_apellido[30];
		cout << "\nIngrese el nuevo segundo apellido: ";
		cin >> _segundo_apellido;

		actual.set_segundo_apellido(_segundo_apellido);
		fileE.seekp(posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;
	}
	case 6: {
		char _genero[30];
		cout << "\nIngrese el nuevo genero: ";
		cin >> _genero;

		actual.set_genero(_genero);
		fileE.seekp(posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;
	}
	case 7: {
		char _ciudad[30];
		cout << "\nIngrese el nueva ciudad: ";
		cin >> _ciudad;

		actual.set_ciudad(_ciudad);
		fileE.seekp(posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;
	}
	case 8: {
		char _region[30];
		cout << "\nIngrese el nueva region: ";
		cin >> _region;

		actual.set_region(_region);
		fileE.seekp(posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;
	}
	case 9: {
		char _pais[30];
		cout << "\nIngrese el nuevo primer apellido: ";
		cin >> _pais;

		actual.set_pais(_pais);
		fileE.seekp(posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "\nMODIFICADO.......\n";
		break;
	}
	case 10:
		cout << "\nSaliendo.......\n";
		break;
	
	default:
		cout << "\nOPCION INCORRECTA.......\n";
		break;
	}
}

void Amazon::modificarProducto(){
	ifstream file("productos.bin",ios::in | ios::binary);
	Busqueda buscador;

	if (!file)
	{
		cout << "Error al intentar abrir el archivo .bin \n\n";
		return;
	}


	cout << "*** M O D I F I C A R   P R O D U C T O S *** \n\n";

	char code[10];
	cout << "\n Ingrese el Codigo del Producto: ";
	cin >> code;


	Producto actual;

	int posicion = -1;
	if (buscador.buscarProductoCodigo(file, code))
	{
		DelimTextBuffer delim('^', 300);
		posicion = file.tellg();
		actual.Read(file, delim);
		file.close();
	}
	else
	{
		cout << "No se encontro el producto que buscaba \n";
		return;
	}

	//codigo=10, categoria 25  subcategoria 25 , nombre 200 
	//descripcion-  2000 precio float

	int opcion = 0;

	cout << "Elige un numero para editar: "
		<< "\n1.Modificar Codigo \n2.Modificar Categoria \n3.Modificar Sub-Categoria "
		<< "\n4.Modificar Nombre \n5.Modificar Descripcion  \n6.Modificar Precio Actual \n.7 Salir";

	ofstream fileE("productos.bin", ios::out | ios::binary | ios::app);
	ofstream fileIndex("clientes.bin", ios::out | ios::app | ios::binary);


	switch (opcion)

	{
	case 1: {

		char codigo[10];
		cout << "\nIngrese el nuevo Codigo: ";
		cin >> codigo;

		actual.set_codigo(codigo);
		fileE.seekp(posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "Se esta Modificando ........... \n";

		break;
	}
	case 2: {

		char categoria[25];
		cout << "\n Ingrese la nueva categoria: ";
		cin >> categoria;

		actual.set_categoria(categoria);
		fileE.seekp(posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "Se esta Modificando ........... \n";

		break;
	}
	case 3: {
		char sub_categoria[25];

		cout << "\n Ingrese la nueva sub-categoria: ";
		cin >> sub_categoria;

		actual.set_sub_categoria(sub_categoria);
		fileE.seekp(posicion);
		fileE << "*";

		file.seekg(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "Se esta Modificando ........... \n";
		break;

	}
	case 4: {
		char nombre[200];

		cout << "\Ingrese el nuevo Nombre: ";
		cin >> nombre;

		actual.set_nombre(nombre);
		fileE.seekp(posicion);
		fileE << "*";

		fileE.seekp(ios::end);
		DelimTextBuffer delim('^', 300);

		actual.Write(fileE, fileIndex, delim);


		cout << "Se esta Modificando ........... \n";


		break;

	}
	case 5: {

		char descripcion[2000];
		cout << "Ingrese Descripcion: ";
		cin >> descripcion;

		actual.set_descripcion(descripcion);
		fileE.seekp(posicion);

		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "Se esta Modificando ........... \n";
		break;
	}
	case 6: {
		float precio_actual;

		cout << "Ingrese nuevo Precio: ";
		cin >> precio_actual;

		actual.precio_actual = (precio_actual);
		fileE.seekp(posicion);

		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "Se esta Modificando ........... \n";

		break;
	}
	case 7:
		cout << "\nSaliendo .... \n";
		break;

	default:
		cout << "\n Opcion Incorrecta \n";
		break;
	}

}

bool Amazon::listarClientes(istream& file) {
	cout << " ***** L I S T A  D E  C L I E N T E S ***** \n\n";
	file.seekg(0);

	Cliente actual;
	while (!file.eof()) {
		DelimTextBuffer delim('^', 300);
		Cliente actual;

		actual.Read(file, delim);
		actual.print();
	}

	return true;
}

bool Amazon::listarProductos(ifstream& file)
{
	cout << "*** L I S T A D O   D E  P R O D U C T O S ** \n\n";

	file.seekg(0);

	Producto actual;

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);

		Producto actual;

		actual.Read(file, delim);

		actual.print();
	}

	return true;
}

void Amazon::eliminarClientes()
{
	ifstream file("clientes.bin" ,ios::in | ios::binary);
	ofstream fileE("clientes.bin" , ios::out | ios::app | ios::binary)
	Busqueda buscador;

	if (!file)
	{
		cout << "Error al intentar abrir el archivo .bin\n\n";
		return;

	}

	char code[13];
	cout << "**** E L I M I N A R  C L I E N T E ";
	cout << "Ingrese el codigo del clientea a eliminar :";
	cin >> code;

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
		return
	}


	cout << "�Esta seguro que Desea a eliminar el cliente completamente ? (1 Si) (2 No)"
		cout << "Ingrese una opcion:";
	cin >> opcion;

	switch (opcion)
	{
	case 1:
		actual.set_codigo("*");
		fileE.seekp(posicion);

		file.seekg(ios::end);
		DelimTextBuffer delim('^', 300);
		actual.Write(fileE, fileIndex, delim);

		cout << "... Cliente Eliminado...."

		break;

	case 2:
		break;

	}
}

void Amazon::eliminarProducto()
{
	ifstream file("clientes.bin", ios::in | ios::binary);
	ofstream fileE("clientes.bin", ios::out | ios::app | ios::binary);

	Busqueda buscador;

	if (!file)
	{
		cout << "Error al intentar abrir el archivo .bin\n\n";
		return;

	}

	char code[10];
	cout << "**** E L I M I N A R  P R O D U C T O  S  ";
	cout << "Ingrese el codigo del producto  a eliminar :";
	cin >> code;



	Producto  actual;
	int posicion = -1;
	int opcion;

	if (buscador.buscarProductoCodigo(file, code))
	{
		DelimTextBuffer delim('^', 300);
		posicion = file.tellg();
		actual.Read(file, delim);
		file.close();
	}
	else
	{
		cout << "\nNo se encontro el producto que busca :(\n";
		return
	}


	cout << "�Esta seguro que Desea a eliminar el  producto completamente ? (1 Si) (2 No)"
		cout << "Ingrese una opcion:";
		cin >> opcion;



		switch (opcion)
		{
		case 1:


			actual.set_codigo("*");
			fileE.seekp(posicion);

			file.seekg(ios::end);
			DelimTextBuffer delim('^', 300);
			actual.Write(fileE, fileIndex, delim);

			cout << "... Producto  Eliminado...."
			break;

		
		}
	

	



}

