#include "BusquedasSecuenciales.h"
#include <cstring>
#include<stdlib.h>
#include<time.h>

//SECCION DE CLIENTES
bool Busqueda::buscarClienteCodigo(istream& file, const char* _codigo) {
	file.seekg(ios::beg);

	while (!file.eof()) {
		DelimTextBuffer delim('^', 300);
		Cliente actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id != 0) {
			
			if (strcmp(actual.codigo, _codigo) == 0) {
				file.seekg(posicion);
				return true;
			}
		}
	}
	return false;
}

bool Busqueda::buscarClienteNombre(istream& file, const char* _nombre) {
	file.seekg(0);

	while (!file.eof()) {
		DelimTextBuffer delim('^', 300);
		Cliente actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id != 0) {
			char* nombreCompreto = new char[strlen(actual.primer_nombre)];
			strcpy_s(nombreCompreto, strlen(actual.primer_nombre) + 1, actual.primer_nombre);
			strcat_s(nombreCompreto, strlen(nombreCompreto) + 2, " ");
			strcat_s(nombreCompreto, strlen(nombreCompreto) + strlen(actual.segundo_nombre) + 1, actual.segundo_nombre);
			strcat_s(nombreCompreto, strlen(nombreCompreto) + 2, " ");
			strcat_s(nombreCompreto, strlen(nombreCompreto) + strlen(actual.primer_apellido) + 1, actual.primer_apellido);
			strcat_s(nombreCompreto, strlen(nombreCompreto) + 2, " ");
			strcat_s(nombreCompreto, strlen(nombreCompreto) + strlen(actual.segundo_apellido) + 1, actual.segundo_apellido);

			if (strcmp(toLowerCase(_nombre),toLowerCase(nombreCompreto)) == 0) {
				file.seekg(posicion);
				return true;
			}
		}
	}
	return false;
}

bool Busqueda::buscarClienteID(istream& file, int _id) {
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);

		Producto actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id != 0) {
			if (actual.id == _id)
			{
				file.seekg(posicion);
				return true;
			}
		}
	}

	return false;
}

void Busqueda::imprimirFacturasCliente(istream& file, int _id_cliente) {
	file.seekg(0);

	int total = 0;
	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Factura actual;

		buscarFacturaCliente(file,_id_cliente);
		actual.Read(file, delim);

		if (actual.id != 0) {
			if (actual.cliente_id == _id_cliente)
			{
				actual.print();
				total++;
			}
		}
	}

	if (total != 0)
		cout << "\n\nEste cliente tiene " << total << " facturas asociadas.";
	else
		cout << "\n\nNo hay Facturas Asociadas a este cliente.";
}







//SECCION DE PRODUCTO
bool Busqueda::buscarProductoCodigo(istream& file, const char* _codigo){
	file.seekg(ios::beg);

	while (!file.eof()) {
		DelimTextBuffer delim('^', 300);
		Producto actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id != 0) {

			if (strcmp(actual.codigo, _codigo) == 0) {
				file.seekg(posicion);
				return true;
			}
		}
	}
	return false;
}

bool Busqueda::buscarProductoNombre(istream& file, const char* _nombre){
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Producto actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);
		char* nombre = actual.nombre;
		nombre = toLowerCase(nombre);
		_nombre = toLowerCase(_nombre);

		if (actual.id != 0) {
			if (strcmp(_nombre,nombre) == 0)
			{
				file.seekg(posicion);

				return true;
			}
		}
	}

	return false;
}

bool Busqueda::buscarProductoID(istream& file, int _id) {
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);

		Producto actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id != 0) {
			if (actual.id == _id)
			{
				file.seekg(posicion);
				return true;
			}
		}
	}

	return false;
}

void Busqueda::imprimirVentasProducto(istream& fileFacturas, istream& fileDetalles, int _id_producto) {
	fileFacturas.seekg(0);
	vector<Detalle> ventas[12];
	string meses[12] = { "Enero" "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };

	while (!fileFacturas.eof())
	{
		DelimTextBuffer delim('^', 300);
		Factura actualF;

		actualF.Read(fileFacturas, delim);

		if (actualF.id != 0) {
			fileDetalles.seekg(0);
			while (!fileDetalles.eof()) {
				DelimTextBuffer delim2('^', 300);
				Detalle actualD;

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
			}
		}
	}

	for (int i = 0; i < 12; i++) {
		cout << "\n\nVentas Correspondientes a: " << meses[i] << ":\n";
		for (int j = 0; i < ventas[i].size(); j++) {
			ventas[i][j].print();
		}

		cout << "\n\nEste producto se vendio: " << ventas[i].size() << " en el mes de: " << meses[i] << ".";
	}
}





//SECCION DE FACTURA
bool Busqueda::buscarFacturaCodigo(istream& file, const char* _codigo){
	if (!file) {
		return false;
	}
	
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Factura actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id != 0) {
			if (strcmp(actual.codigo,_codigo) == 0)
			{
				file.seekg(posicion);
				return true;
			}
		}
	}

	return false;
}

bool Busqueda::buscarFacturaCliente(istream& file, int _id_cliente){
	if (!file) {
		return false;
	}
	
	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Factura actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);
		
		if (actual.id != 0) {
			if (actual.cliente_id == _id_cliente)
			{
				file.seekg(posicion);

				return true;
			}
		}
	}

	return false;
}

bool Busqueda::buscarFacturaID(istream& file, int _id) {
	if (!file) {
		return false;
	}
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);

		Factura actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id != 0) {
			if (actual.id == _id)
			{
				file.seekg(posicion);
				return true;
			}
		}
	}

	return false;
}

bool Busqueda::eliminarFacturasCliente(int _id_cliente) {
	fstream file("facturas.bin", ios::in | ios::out | ios::binary | ios::_Nocreate);
	ofstream fileIndex("facturas.index", ios::in | ios::binary | ios::_Nocreate);

	if (!file && !fileIndex) {
		return false;
	}

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Factura actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id != 0) {
			if (actual.cliente_id == _id_cliente)
			{
				DelimTextBuffer delim('^', 300);
				file.seekg(posicion);
				actual.id = 0;
				actual.Write(file, fileIndex, delim);
			}
		}
	}

	file.close();
	return true;
}





//SECCION DETALLE DE FACTURA
bool Busqueda::buscarDetalleFactura(istream& file, int _id_factura) {
	if (!file) {
		return false;
	}
	
	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Detalle actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id != 0) {
			if (actual.factura_id == _id_factura)
			{
				file.seekg(posicion);

				return true;
			}
		}
	}

	return false;
}

bool Busqueda::buscarDetalleProducto(istream& file, int _id_producto) {
	if (!file) {
		return false;
	}
	
	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Detalle actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id != 0) {
			if (actual.producto_id == _id_producto)
			{
				file.seekg(posicion);

				return true;
			}
		}
	}

	return false;
}

bool Busqueda::buscarDetalleID(istream& file, int _id) {
	if (!file) {
		return false;
	}
	file.seekg(0);

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);

		Detalle actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id != 0) {
			if (actual.id == _id)
			{
				file.seekg(posicion);
				return true;
			}
		}
	}

	return false;
}

bool Busqueda::eliminarDetallesFactura(int _id_factura) {
	fstream file("detalles.bin", ios::in | ios::binary | ios::_Nocreate);
	ofstream fileIndex("detalles.index", ios::in | ios::binary | ios::_Nocreate);
	
	if (!file && !fileIndex) {
		return false;
	}

	while (!file.eof())
	{
		DelimTextBuffer delim('^', 300);
		Detalle actual;

		int posicion = -1;
		posicion = file.tellg();

		actual.Read(file, delim);

		if (actual.id != 0) {
			if (actual.factura_id == _id_factura)
			{
				DelimTextBuffer delim('^', 300);
				file.seekg(posicion);
				actual.id = 0;
				actual.Write(file, fileIndex, delim);
			}
		}
	}
	file.close();
	return true;
}





//Generando registros seudo aleatorios
void Busqueda::generarArchivoNombres() {
	ofstream fileM("nombresM.bin", ios::out | ios::app | ios::binary);
	ofstream fileF("nombresF.bin", ios::out | ios::app | ios::binary);

	if (!fileM && !fileF) {
		cout << "Error al intentar abrir el archivo .bin de clientes\n\n";
		return;
	}

	string Masculinos[25] = {"Carlos","Jose","Mario","Ricardo","Esteban","Joel","Jesus","Jack","Jake","Kevin","Caleb","Daniel","David","Jonnathan","Jorge","Luis","Alexander","Arndold","Dylan","Joel","Issac","Fernando","Omar","Samuel","Polo"};
	string Femeninos[25] = { "Julie","Sky","Nicole","Michelle","Karoline","Karina","Fabiola","Marlen","Rosa","Rocio","Calletana","Lucrecia","Carla","Nadia","Jose","Maria","Esthela","Esther","Lohanny","Mariel","Martha","Ariana","Taylor","Megan","Olivia" };

	for (int i = 0; i < 25; i++) {
		fileM << Masculinos[i] << ",";
		fileF << Femeninos[i] << ",";
	}

	fileM.close();
	fileF.close();
}

void Busqueda::generarArchivoApellidos() {
	ofstream file("apellidos.bin", ios::out | ios::app | ios::binary);

	if (!file) {
		cout << "Error al intentar abrir el archivo .bin de clientes\n\n";
		return;
	}

	string Apellidos[50] = { "Martinez","Romero","Vallecillo","Oseguera","Puerto","Sanchez","Pineda","Amador","Amaya","Hernandez","Alvarado","Sosa","Sandoval","Arias","Menjivar","Melendez","Pinel","Padilla","Lamberth","Castro","Acosta","Ramos","Salas","Munguia","Moon",
		"Aguirre","Gomez","Salinas","Navarro","Espinosa","Maldonado","Guzman","Cabrera","Rosa","Oviedo","Castel","Castillo","Ruiz","Saldivar","Salazar","Backer","Beltran","Ortega","Blanco","Cardona","Villegas","Rios","Montealban","Villalobos","Grand"};

	for (int i = 0; i < 50; i++) {
		file << Apellidos[i] << ",";
	}

	file.close();
}

void Busqueda::generarArchivoUbicaciones() {
	ofstream file("ubicaciones.bin", ios::out | ios::app | ios::binary);

	if (!file) {
		cout << "Error al intentar abrir el archivo .bin de clientes\n\n";
		return;
	}

	string ubicaciones[25] = {"San Pedro Sula,Cortes,Honduras","Tegucigalpa,Fransco. Morazan,Honduras","San Salvador,San Salvador,El Salvador","Sonsonate,Sonsonate,El Salvador","Miami,Florida,USA","Los Angeles,California,USA","Sevilla,Andalucia,España","Barcelona,Cataluña,España","Mexico City,Mexico DF,Mexico","Santiago,Santiago,Chile","Rio de Janeiro,Rio de Janeiro,Brasil","London,Inglaterra,Reino Unido","Buenos Aires,La Plata,Argentina","Orlando,Florida,USA","La Ceiba,Atlantida,Honduras","Ciudad de Guatemala,Guatemala,Guatemala","Puerto Barrios,Izabal,Guatemala","Las Vegas,Nevada,USA","Medellin,Antioquia,Colombia","Cartagena,Bolívar,Colombia","Ciudad de Panama,Pamana,Panama","Monterrey,Nuevo Leon,Mexico","Merida,Yucatan,Mexico","Lima,Cortes,Honduras","Copan Ruinas,Copan,Honduras"};

	for (int i = 0; i < 25; i++) {
		file << ubicaciones[i] << "/";
	}

	file.close();
}

vector<string> Busqueda::extraerNombresHombres() {
	ifstream fileNombres("nombresM.bin", ios::out | ios::app | ios::binary);
	vector<string> hombres;
	//Extraer los Hombres
	while (!fileNombres.eof()) {
		char nombre[25];
		fileNombres.getline(nombre, 25, ',');
		hombres.push_back(nombre);
	}
	fileNombres.close();
	return hombres;
}

vector<string> Busqueda::extraerNombresMujeres() {
	ifstream fileNombres("nombresF.bin", ios::out | ios::app | ios::binary);
	vector<string> mujeres;
	//Extraer las Mujeres
	while (!fileNombres.eof()) {
		char nombre[25];
		fileNombres.getline(nombre, 25, ',');
		mujeres.push_back(nombre);
	}
	fileNombres.close();
	return mujeres;
}

vector<string> Busqueda::extraerApellidos() {
	ifstream fileApellidos("apellidos.bin", ios::out | ios::app | ios::binary);
	vector<string> apellidos;
	//Extraer los Apellidos
	while (!fileApellidos.eof()) {
		char apellido[30];
		fileApellidos.getline(apellido, 30, ',');
		apellidos.push_back(apellido);
	}
	fileApellidos.close();
	return apellidos;
}

vector<ubicacion> Busqueda::extraerUbicaciones() {
	ifstream fileUbicaciones("ubicaciones.bin", ios::out | ios::app | ios::binary);
	vector<ubicacion> ubicaciones;
	//Extraer los Apellidos
	while (!fileUbicaciones.eof()) {
		ubicacion ubi;
		char ciudad[30];
		fileUbicaciones.getline(ciudad, 30, ',');
		ubi.ciudad = ciudad;

		char region[30];
		fileUbicaciones.getline(region, 30, ',');
		ubi.region = region;

		char pais[30];
		fileUbicaciones.getline(pais, 30, ',');
		ubi.pais = pais;

		ubicaciones.push_back(ubi);
	}
	fileUbicaciones.close();
	return ubicaciones;
}

void Busqueda::generarArchivoCategorias()
{
	ofstream fileCategoria("categorias.bin", ios::out | ios::app | ios::binary);

	if (!fileCategoria) {
		cout << "Error al intentar abrir el archivo .bin de productos\n\n";
		return;
	}

	string categorias[5] = { "Electronicos","Hogar" ,"Deporte" "Moda", "Videojuegos" };

	for (int i = 0; i < 5; i++) {
		fileCategoria << categorias[i] << ",";
	}
	fileCategoria.close();
}

void Busqueda::generarArchivoSubCategoria()
{
	ofstream fileSubcategoria("subcategorias.bin", ios::out | ios::app | ios::binary);

	if (!fileSubcategoria) {
		cout << "Error al intentar abrir el archivo .bin de productos\n\n";
		return;
	}

	string subcategorias[5] = { "Computadora","Muebles" ,"Balones" "Ropa de Hombre", "PS5" };

	for (int i = 0; i < 5; i++) {
		fileSubcategoria << subcategorias[i] << ",";
	}
	fileSubcategoria.close();
}

void Busqueda::generarArchivoProducto()
{

}

vector <string> Busqueda::extraerCategorias()
{
	ifstream fileCategorias("categorias.bin", ios::out | ios::app | ios::binary);
	vector<string> categorias;

	while (!fileCategorias.eof())
	{
		char categoria[5];
		fileCategorias.getline(categoria, 5, ',');
		categorias.push_back(categoria);

	}
	fileCategorias.close();
	return categorias;
}

vector <string> Busqueda::extraerSubcategoria()
{
	ifstream fileSubCategorias("subcategorias.bin", ios::out | ios::app | ios::binary);
	vector<string>subcategorias;

	while (!fileSubCategorias.eof())
	{
		char subcategoria[5];
		fileSubCategorias.getline(subcategoria, 5, ',');
		subcategorias.push_back(subcategoria);

	}
	fileSubCategorias.close();
	return subcategorias;
}

void Busqueda::generarClientes(ostream& file, int cantidad) {
	srand(time(NULL));

	vector<string> hombres = extraerNombresHombres();
	vector<string> mujeres = extraerNombresMujeres();
	vector<string> apellidos = extraerApellidos();
	vector<ubicacion> ubicaciones = extraerUbicaciones();

	int genero, edad;
	while (cantidad != 0) {
		Cliente nuevo;
		nuevo.id = nuevo.getNextId();
		//Numero aleatoria entre 0 y 1, 0 = hombre, 1 = mujer
		genero = rand() % 1;

		int _aux;
		if (genero == 0) {
			_aux = rand() % 25;
			nuevo.set_primer_nombre(hombres[_aux].c_str());
			_aux = rand() % 25;
			nuevo.set_segundo_nombre(hombres[_aux].c_str());
			nuevo.set_genero("M");
		}
		else {
			_aux = rand() % 25;
			nuevo.set_primer_nombre(mujeres[_aux].c_str());
			_aux = rand() % 25;
			nuevo.set_primer_nombre(mujeres[_aux].c_str());
			nuevo.set_genero("F");
		}

		_aux = rand() % 50;
		nuevo.set_primer_apellido(apellidos[_aux].c_str());
		_aux = rand() % 50;
		nuevo.set_segundo_apellido(apellidos[_aux].c_str());

		int _edad = 18 + rand() % (81 - 18);

		_aux = rand() % 25;
		nuevo.set_ciudad(ubicaciones[_aux].ciudad.c_str());
		nuevo.set_region(ubicaciones[_aux].region.c_str());
		nuevo.set_pais(ubicaciones[_aux].pais.c_str());

		DelimTextBuffer delim('^', 300);
		nuevo.Write(file,file,delim);
		cantidad--;
	}
}

char* Busqueda::toLowerCase(const char* cadena) {
	char* nueva = new char[strlen(cadena) + 1];
	for (int i = 0; i < strlen(cadena); i++){
		nueva[i] = tolower(cadena[i]);
	}

	return nueva;
}