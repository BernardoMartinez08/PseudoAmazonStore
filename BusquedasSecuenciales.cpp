#include "BusquedasSecuenciales.h"
#include <cstring>
#include<stdlib.h>
#include<time.h>

BusquedaIndexada browser;

Busqueda::Busqueda(BusquedaIndexada _browser) {
	browser = _browser;
}

Busqueda::Busqueda() {

}

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
				DelimTextBuffer delim('^', 300);
				file.seekg(posicion);
				actual.id = 0;
				actual.Write(file, delim);
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
				DelimTextBuffer delim('^', 300);
				file.seekg(posicion);
				actual.id = 0;
				actual.Write(file, delim);
			}
		}
	}
	file.close();
	return true;
}





//Generando registros pseudo aleatorios Cliente
void Busqueda::generarArchivoNombres() {
	ofstream fileM("nombresM.rand", ios::out | ios::app | ios::binary);
	ofstream fileF("nombresF.rand", ios::out | ios::app | ios::binary);

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
	ofstream file("apellidos.rand", ios::out | ios::app | ios::binary);

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
	ofstream file("ubicaciones.rand", ios::out | ios::app | ios::binary);

	if (!file) {
		cout << "Error al intentar abrir el archivo .bin de clientes\n\n";
		return;
	}

	string ubicaciones[25] = {"San Pedro Sula,Cortes,Honduras","Tegucigalpa,Fransco. Morazan,Honduras","San Salvador,San Salvador,El Salvador","Sonsonate,Sonsonate,El Salvador","Miami,Florida,USA","Los Angeles,California,USA","Sevilla,Andalucia,España","Barcelona,Cataluña,España","Mexico City,Mexico DF,Mexico","Santiago,Santiago,Chile","Rio de Janeiro,Rio de Janeiro,Brasil","London,Inglaterra,Reino Unido","Buenos Aires,La Plata,Argentina","Orlando,Florida,USA","La Ceiba,Atlantida,Honduras","Guatemala City,Guatemala,Guatemala","Puerto Barrios,Izabal,Guatemala","Las Vegas,Nevada,USA","Medellin,Antioquia,Colombia","Cartagena,Bolívar,Colombia","Panama City,Pamana,Panama","Monterrey,Nuevo Leon,Mexico","Merida,Yucatan,Mexico","Lima,Cortes,Honduras","Copan Ruinas,Copan,Honduras"};

	for (int i = 0; i < 25; i++) {
		file << ubicaciones[i] << "/";
	}

	file.close();
}

vector<string> Busqueda::extraerNombresHombres() {
	ifstream fileNombres("nombresM.rand", ios::in | ios::binary | ios::_Nocreate);
	vector<string> hombres;

	if (!fileNombres)
		return hombres;

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
	ifstream fileNombres("nombresF.rand", ios::in | ios::binary | ios::_Nocreate);
	vector<string> mujeres;

	if (!fileNombres)
		return mujeres;

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
	ifstream fileApellidos("apellidos.rand", ios::in | ios::binary | ios::_Nocreate);
	vector<string> apellidos;

	if (!fileApellidos)
		return apellidos;

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
	ifstream fileUbicaciones("ubicaciones.rand", ios::binary | ios::_Nocreate);

	vector<ubicacion> ubicaciones;

	if (!fileUbicaciones)
		return ubicaciones;

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
		fileUbicaciones.getline(pais, 30, '/');
		ubi.pais = pais;

		ubicaciones.push_back(ubi);
	}
	fileUbicaciones.close();
	return ubicaciones;
}

void Busqueda::generarClientes(int cantidad) {
	vector<string> hombres = extraerNombresHombres();
	vector<string> mujeres = extraerNombresMujeres();
	vector<string> apellidos = extraerApellidos();
	vector<ubicacion> ubicaciones = extraerUbicaciones();

	if (hombres.empty() || mujeres.empty() || apellidos.empty() || ubicaciones.empty()) {
		cout << "\nANTES DE GENERAR CLIENTES, DEBE GENERAR EL ARCHIVO CON DATOS!!!";
		return;
	}

	int genero, edad;
	while (cantidad != 0) {
		ofstream file("clientes.bin", ios::out | ios::app | ios::binary);
		Cliente nuevo;
		nuevo.id = nuevo.getNextId();
		nuevo.codigo = new char[13];
		generarCodigoAleatorio(nuevo.codigo, sizeof(nuevo.codigo));
		//Numero aleatoria entre 0 y 1, 0 = hombre, 1 = mujer
		genero = rand() % 1;

		int _aux;
		if (genero == 0) {
			_aux = rand() % hombres.size();
			nuevo.set_primer_nombre(hombres[_aux].c_str());
			_aux = rand() % 25;
			nuevo.set_segundo_nombre(hombres[_aux].c_str());
			nuevo.set_genero("M");
		}
		else {
			_aux = rand() % mujeres.size();
			nuevo.set_primer_nombre(mujeres[_aux].c_str());
			_aux = rand() % 25;
			nuevo.set_primer_nombre(mujeres[_aux].c_str());
			nuevo.set_genero("F");
		}

		_aux = rand() % apellidos.size();
		nuevo.set_primer_apellido(apellidos[_aux].c_str());
		_aux = rand() % 50;
		nuevo.set_segundo_apellido(apellidos[_aux].c_str());

		int _edad = 18 + rand() % (81 - 18);

		_aux = rand() % ubicaciones.size();
		nuevo.set_ciudad(ubicaciones[_aux].ciudad.c_str());
		nuevo.set_region(ubicaciones[_aux].region.c_str());
		nuevo.set_pais(ubicaciones[_aux].pais.c_str());

		file.seekp(ios::ate);
		nuevo.posicion = file.tellp();

		DelimTextBuffer delim('^', 300);
		nuevo.Write(file, delim);
		TipoBusquedaSec _tipo = TipoBusquedaSec::tCliente;
		browser.agregar(nuevo.codigo, nuevo.nombreCompleto(), nuevo.id, nuevo.posicion, _tipo);
		browser.ordenar(_tipo);
		cantidad--;
		file.close();
	}
}







//Generando registros pseudo aleatorios Productos
void Busqueda::generarArchivoCategorias()
{
	ofstream fileCategoria("categorias.rand", ios::out | ios::app | ios::binary);

	if (!fileCategoria) {
		cout << "Error al intentar abrir el archivo .bin de categorias\n\n";
		return;
	}

	string categorias[5] = { "Electronicos","Hogar","Deporte","Moda","Videojuegos" };

	for (int i = 0; i < 5; i++) {
		fileCategoria << categorias[i] << "/";
	}
	fileCategoria.close();
}

void Busqueda::generarArchivoSubCategoria()
{
	ofstream fileSubcategoria("subcategorias.rand", ios::out | ios::app | ios::binary);
	ofstream filePrecios("preciosproductos.rand", ios::out | ios::app | ios::binary);

	if (!fileSubcategoria || !filePrecios) {
		cout << "Error al intentar abrir el archivo .bin de sub_categorias\n\n";
		return;
	}

	string subcategorias[5] = { "Computadora,Smartphone,SmartTV,Electro-Domesticos,Sonido",
								"Muebles Sala,Comedor,Cocina,Utencilios,Decoracion", 
								"Balones,Raqueta,Redes,Pesas,Proteccion",
								"Pantalones,Camisas,Gala,Pijamas,Playa", 
								"PS5,XBOX,Terror,Suspenso,Shooters" };

	string precios[5] = { "27344-45633,17744-28993,38893-78332,11099-23342,5003-15922",
						  "17344-45633,10744-23211,18223-21992,100-800,1000-5000",
						  "1000-4633,108-453,300-4999,1000-3788,200-800",
						  "890-1744,873-1782,5992-1000,100-500,100-933",
						  "1000-2000,1500-2000,1000-1800,1000-1800,1000-1800", };

	for (int i = 0; i < 5; i++) {
		fileSubcategoria << subcategorias[i] << "/";
		filePrecios << precios[i] << "/";
	}
	fileSubcategoria.close();
	filePrecios.close();
}

void Busqueda::generarArchivoProducto()
{
	ofstream fileProducto("productos.rand", ios::out | ios::app | ios::binary);

	if (!fileProducto) {
		cout << "Error al intentar abrir el archivo .bin de producto\n\n";
		return;
	}

	string productos[25] = {"Samsung NoteBook 9,DELL Inspiron 7600,MSI Pro+",
							"Samsung Galaxy Note20 Ultra 5G, Samsung Galaxy S21 Ultra 5G, Apple iPhone 12 ProMax",
							"LG WEBOS SMART TV OLED 65',Samsung QLED SmartTV 75' 4K HDR4, SONY BRAVIA 7783 PRO 65'",
							"MABE CeramicStove,GE Fridge 783 Model S,LG Fridge UltronFresh",
							"LG BOOM Space Sound,Samsung HomeTheather K783,Samsung UltraSound Boss Station",
							"^Jiraf MagicSofa,Juliany SolidState Sillones,Susan StreetSpaceJam Sala Completa",
							"Jiraf Comedor MagicDiner, Sundare CircleStation, MagesticDinner Barra/Bar",
							"MABE Microwave, BlackNDeker Licuadroa, MABE Vatidora Magic Level",
							"Set de Cucharas Acero Incoxidable,Set de cuchillas ultra filosas,MagicFood set de cubiertos",
							"Flowers Florero Grande,Majestic Candelabro Central,Majestic Lampara",
							"^FIFA BrazilWorldCup Balon,UEFA 2021 Balon, Sudafrica WorldCup Balon firmado por Shakira",
							"Joma Raqueta, Addidas Raqueta X732, Joma Raqueta Pro",
							"Joma Red de Voleyball, Joma Red de Tenis, Joma Red de Ping-Pong",
							"Pesas de 10LB, Pesas de 35LB, Set de pesas 5Lb, 15Lb, 25Lb y 35Lb",
							"Rodilleras,Pecheras,Casco",
							"^Pepe MenJeans,Pacer SlimWomen,Zara BlueJeans",
							"Columbian Enterprice,Bershka Buso Completo,Zara SumerColection",
							"Gucci Traje Comepleto for Men,Moccino Dress SummerColection,Prada Nightmare",
							"Lou Pijama for woman,Liam Pijama for men,Lizo Pijama for kids",
							"Pacer VikiniSX,YoungStage for Men, Shorts UniSex",
							"^Demon's Souls,Destruction All Stars,NBA 2K21",
							"Devil May Cry 5: Special Edition,Godfall,Unexplored 2: The Wayfarer's Legacy",
							"Alien: Isolation,Alone in the Dark,Amnesia: The Dark Descent",
							"Fatal Frame II: Crimson Butterfly,Five Night’s at Freddy's VR: Help Wanted,Layers of Fear",
							"Fortnite,CallOfDutty BlackOPS,Batlefild 2055" };

	for (int i = 0; i < 25; i++) {
		fileProducto << productos[i] << "/";
	}
	fileProducto.close();
}

void Busqueda::generarArchivoDescripcion() {
	ofstream fileDescripciones("descripciones.rand", ios::out | ios::app | ios::binary);

	if (!fileDescripciones) {
		cout << "Error al intentar abrir el archivo .bin de descripciones\n\n";
		return;
	}

	string productos[200] = {"bueno","bonito","nn buen estado","nuevo","Usado", "caja Abierta", "caja Cerrada", "sin Caja", "con caja", "origial",
							 "vercion","Vercion China","Sin uso","dias","recien", "compradp", "bloqueado", "5G", "ultima", "tecnologia",
							 "venta","ingresado","recuperado","reusado","baratp", "para", "de", "vista", "grande", "65'",
							 "vendido","reseller","entreda","FEDEX","inmediato", "Paypal", "rosa", "transferencia", "pantalla", "4k HDR", 
						     "colores","vivos","ingresado","dia","brillo", "maximo", "enorme", "grande", "naranja", "vivo", 
							 "xiami","samsung","exportado","made in","verde", "reparado", "ventajas", "devoluciones", "entregas", "ventas",
							 "Hojar","brilla","ahora","oferta","subasta", "proximamente", "capacidad", "estado", "animado", "tamano",
							 "marco","ultima","novedad","novedoso","extravagante", "ultimamente", "rentable", "comparable", "pendiente", "maniobrar",
							 "manipular","estirar","incorporado","maleabre","reciclable", "estampado", "empacado", "como", "de", "paquete",
							 "preguntas","consultas","extra","negativo","producto", "ingresado", "desbloqueado", "feliz", "enojado", "fuerte",
							 "vibrante","espectacular","novedoso","negro","blaco", "importaciones", "banco", "ruedas", "perfecto", "moldeable",
							 "melancolia","unido","separado","enamorado","verdoso", "toxico", "rociado", "olores", "olfato", "cocina"
							 "sala","comedor","habitacion","casa","hogar", "estado de salud", "sanidad", "saludable", "ajustado", "estira",
							 "enrollable","fancy","sedoso","tela","suave", "bordado", "peaado", "calidad", "inmediato", "verdadera",
							 "cuatro","ocho","8KUHD","HDR","sonido", "envolvente", "capaz", "entrante", "saliente", "WIFI6",
							 "bluthooth","conexion","carga","descarga","enantium", "refrigerante", "venda", "deslumbrante", "WOW", "boom",
							 "extravagante","inucual","vanidoso","musica","volumen", "cargador", "vibrador", "aroma", "validez", "ticket",
							 "politica","maravilla","estatura","deportuvo","GYM", "hombre", "mujer", "verdaderamente", "cierto", "falso",
							 "mantenimiento","agenda","correo","telefono","numero", "amor", "contacto", "estamos", "relativamente", "cerca",
							 "lejos","variante","modelo","aniversario","exclusivo", "prendas", "trabajoo", "devoluciones", "entregas", "ventas",
							 "xiami" };


	for (int i = 0; i < 200; i++) {
		fileDescripciones << productos[i] << "/";
	}
	fileDescripciones.close();
}

vector <string> Busqueda::extraerCategorias()
{
	ifstream fileCategorias("categorias.rand",  ios::binary | ios::_Nocreate);
	vector<string> categorias;

	if (!fileCategorias)
		return categorias;

	while (!fileCategorias.eof()) {
		char categoria[25];
		fileCategorias.getline(categoria, 25, '/');
		categorias.push_back(categoria);
	}
	fileCategorias.close();
	return categorias;
}

vector <vector<string>> Busqueda::extraerSubcategoria()
{
	ifstream fileSubCategorias("subcategorias.rand", ios::binary | ios::_Nocreate);
	vector<vector<string>>subcategorias;

	if (!fileSubCategorias)
		return subcategorias;

	while (!fileSubCategorias.eof())
	{
		vector<string> aux;
		char sub_categoria[2000];
		fileSubCategorias.getline(sub_categoria, 2000, '/');
	
		std::istringstream isstream(sub_categoria);
		std::string palabra;

		while (std::getline(isstream, palabra, ',')) {
			aux.push_back(palabra);
		}

		subcategorias.push_back(aux);
	}
	fileSubCategorias.close();
	return subcategorias;
}

vector<vector<vector<string>>> Busqueda::extraerProductos()
{
	ifstream fileProductos("productos.rand", ios::binary | ios::_Nocreate);
	vector<vector<vector<string>>> productos;

	if (!fileProductos)
		return productos;

	while (!fileProductos.eof()) {
		vector<vector<string>> fila;
		char _products[10000];
		fileProductos.getline(_products, 10000, '^');

		std::istringstream isstream(_products);
		std::string palabra;
		
		while (std::getline(isstream, palabra, '/')) {
			vector<string> casilla;
			std::istringstream isstream2(palabra);
			std::string palabra2;

			while (std::getline(isstream2, palabra2, ',')) {
				casilla.push_back(palabra2);
			}
			fila.push_back(casilla);
		}

		productos.push_back(fila);
	}
	fileProductos.close();
	return productos;
}

vector <vector<precio>> Busqueda::extraerPrecios()
{
	ifstream filePrecios("preciosproductos.rand",  ios::binary | ios::_Nocreate);

	vector<vector<precio>> precios;

	if (!filePrecios)
		return precios;

	while (!filePrecios.eof()) {
		vector<precio> aux;
		char _precios[2000];
		filePrecios.getline(_precios, 2000, '/');

		std::istringstream isstream(_precios);
		std::string palabra;

		while (std::getline(isstream, palabra, ',')) {
			precio price;

			std::istringstream isstream2(palabra);
			std::string palabra2;

			std::getline(isstream2, palabra2, '-');
			price.precioMin = std::stoi(palabra2);
			std::getline(isstream2, palabra2, ',');
			price.precioMax = std::stoi(palabra2);
			aux.push_back(price);
		}
		precios.push_back(aux);
	}
	filePrecios.close();
	return precios;
}

vector<string> Busqueda::extraerDescripcion() {
	ifstream fileDescrip("descripciones.rand", ios::in | ios::binary | ios::_Nocreate);
	vector<string> descripciones;

	if (!fileDescrip)
		return descripciones;

	//Extraer los Hombres
	while (!fileDescrip.eof()) {
		char palabra[25];
		fileDescrip.getline(palabra, 25, '/');
		descripciones.push_back(palabra);
	}
	fileDescrip.close();
	return descripciones;
}

void Busqueda::generarProductos(int cantidad) {
	vector<string> categorias = extraerCategorias();
	vector<string> descripciones = extraerDescripcion();
	vector<vector<string>> subcategorias = extraerSubcategoria();
	vector<vector<vector<string>>>  productos = extraerProductos();
	vector<vector<precio>> precios = extraerPrecios();

	if (categorias.empty() || subcategorias.empty() || productos.empty() || precios.empty() || descripciones.empty()) {
		cout << "\nANTES DE GENERAR PRODUCTOS, DEBE GENERAR EL ARCHIVO CON DATOS!!!";
		return;
	}

	while (cantidad != 0) {
		ofstream file("productos.bin", ios::out | ios::app | ios::binary);
		Producto nuevo;
		nuevo.id = nuevo.getNextId();
		nuevo.codigo = new char[13];
		generarCodigoAleatorio(nuevo.codigo, sizeof(nuevo.codigo));

		int _catego = rand() % (categorias.size()-1);
		nuevo.set_categoria(categorias[_catego].c_str());

		int _subcatego = rand() % (subcategorias[_catego].size() - 1);
		nuevo.set_sub_categoria(subcategorias[_catego][_subcatego].c_str());

		int _nombre = rand() % (productos[_catego][_subcatego].size()-1);
		nuevo.set_nombre(productos[_catego][_subcatego][_nombre].c_str());

		int _cantidadWords = 6 + rand() % (26 - 6);
		string _descripcion;
		for (int i = 0; i < _cantidadWords; i++) {
			int _palabra = rand() % (descripciones.size()-1);
			_descripcion += (descripciones[_palabra] + " ");
		}
		nuevo.set_descripcion(_descripcion.c_str());
		
		int minprecio = precios[_catego][_subcatego].precioMin;
		int maxprecio = precios[_catego][_subcatego].precioMax;
		int _precio = minprecio + rand() % (maxprecio - minprecio);
		nuevo.precio_actual = _precio;

		file.seekp(ios::ate);
		nuevo.posicion = file.tellp();

		DelimTextBuffer delim('^', 300);
		nuevo.Write(file, delim);

		TipoBusquedaSec _tipo = TipoBusquedaSec::tProducto;
		browser.agregar(nuevo.codigo, nuevo.nombre, nuevo.id, nuevo.posicion, _tipo);
		browser.ordenar(_tipo);
		cantidad--;
		file.close();
	}
}










//Generando registros pseudo aleatorios Facturas

void Busqueda::generarArchivoCoordenadas() {
	ofstream file("coordenadas.rand", ios::out | ios::app | ios::binary);

	if (!file) {
		cout << "Error al intentar abrir el archivo .rand de coordenadas\n\n";
		return;
	}

	vector<string> ubicaciones = { "San Pedro Sula,15.564877242982087,-88.02325207801289","Tegucigalpa,14.04813698106949,-87.17419423132576","San Salvador,13.702648910071172,-89.22297562951584","Sonsonate,13.722476787669432,-89.72802351238985","Miami,25.78940863951333,-80.13362686347472","Los Angeles,34.055867713060955,-118.26725667328384","Sevilla,37.38652414304934,-5.971188061145621",
		"Barcelona,41.406812022835155,2.199268100569772","Mexico City,19.43564893262118,-99.1421641684178","Santiago,-33.44707219572787,-70.68896772798135","Rio de Janeiro,-22.885588295946594,-43.342989675191106","London,51.50499304581129,-0.14156354716660746","Buenos Aires,-34.91319499307613,-57.94167218445688","Orlando,28.534145916996486,-81.37289035226657","La Ceiba,15.777033449877322,-86.7979023084204",
		"Guatemala City,14.599544320812768,-90.51256381568146","Puerto Barrios,15.727553570674463,-88.58743231902963","Las Vegas,36.16517526015255,-115.09099566810283","Medellin,6.2342988875425265,-75.59202897210693","Cartagena,10.390721032906304,-75.48277449399906","Panama City,9.063942895635334,-79.50544888723604","Monterrey,25.683043688450468,-100.2912373813602",
		"Merida,20.964362222078375,-89.61824177863531","Lima,15.442668853208417,-87.90731770821549","Copan Ruinas,14.841181875113923,-89.15594161247" };

	for (int i = 0; i < ubicaciones.size(); i++) {
		coordenada nueva;
		std::istringstream isstream(ubicaciones[i]);
		std::string palabra;

		std::getline(isstream, palabra, ',');
		nueva.ciudad = (palabra);
		std::getline(isstream, palabra, ',');
		nueva._x = std::stof(palabra);

		std::getline(isstream, palabra);
		nueva._y = std::stof(palabra);
		file << nueva.ciudad << "," << nueva._x << "," << nueva._y << "/";
	}

	file.close();
}

vector<coordenada> Busqueda::extraerCoordenadas() {
	ifstream fileCordenadas("coordenadas.rand", ios::binary || ios::_Nocreate);

	vector<coordenada> coordenadas;

	if (!fileCordenadas)
		return coordenadas;

	coordenada actual;
	
	while (!fileCordenadas.eof()) {
		char _coordenada[2000];
		fileCordenadas.getline(_coordenada, 2000, '/');
		if(strcmp(_coordenada, "") == 1) {
			std::istringstream isstream(_coordenada);
			std::string palabra;

			std::getline(isstream, palabra, ',');
			actual.ciudad = palabra;
			std::getline(isstream, palabra, ',');
			actual._x = std::stof(palabra);
			std::getline(isstream, palabra);
			actual._y = std::stof(palabra);
			coordenadas.push_back(actual);

			coordenadas.push_back(actual);
		}
	}

	fileCordenadas.close();
	return coordenadas;
}

void Busqueda::generarFacturas(int cantidad) {
	vector<coordenada> ubicaciones = extraerCoordenadas();
	TipoBusquedaSec _tipoC = TipoBusquedaSec::tCliente;
	TipoBusquedaSec _tipoP = TipoBusquedaSec::tProducto;
	TipoBusquedaSec _tipoF = TipoBusquedaSec::tFactura;
	TipoBusquedaSec _tipoD = TipoBusquedaSec::tDetalle;
	
	if (ubicaciones.empty()) {
		cout << "\nANTES DE GENERAR FACTURAS, DEBE GENERAR EL ARCHIVO CON DATOS!!!";
		return;
	}

	int mindia = 0, maxdia = 0, minmes = 0, maxmes = 0, minyear = 0, maxyear = 0, minhora, maxhora;

	cout << "\nIngrese el Rando de Fechas y Horas:\nMinimos:\nIndique el dia minimo: ";
	cin >> mindia;
	cout << "Indique el mes minimo: ";
	cin >> minmes;
	cout << "Indique el anio minimo: ";
	cin >> minyear;
	cout << "Indique la hora minima: ";
	cin >> minhora;
	cout << "\nMaximos:\nIndique el dia maximo: ";
	cin >> maxdia;
	cout << "Indique el mes maximo: ";
	cin >> maxmes;
	cout << "Indique el anio maximo: ";
	cin >> maxyear;
	cout << "Indique la hora maximo: ";
	cin >> maxhora;

	while (cantidad != 0) {
		//Datos de Hora y Fecha
		int dia, mes, anio, hora, minutos;
		dia = mindia + rand() % ((maxdia + 1) - mindia);
		mes = minmes + rand() % ((maxmes + 1) - minmes);
		anio = minyear + rand() % ((maxyear + 1) - minyear);
		hora = minhora + rand() % ((maxhora + 1) - minhora);
		minutos = rand() % 60;

		Factura nueva;
		nueva.dia = dia; 
		nueva.mes = mes; 
		nueva.anio = anio;
		string _hora = to_string(hora) + ":" + to_string(minutos);
		nueva.set_hora(_hora.c_str());

		nueva.id = nueva.getNextId();

		ofstream fileF("facturas.bin", ios::out | ios::app | ios::binary);
		ofstream fileFIndex("facturas.index", ios::out | ios::app | ios::binary);

		nueva.codigo = new char[13];
		generarCodigoAleatorio(nueva.codigo, sizeof(nueva.codigo));



		//Datos de Cliente
		Cliente* auxc = new Cliente();
		int maxCliente = auxc->getNextId(false);
		delete auxc;
		bool clienteEncontrado = false;

		while (!clienteEncontrado) {
			ifstream fileC("clientes.bin", ios::in | ios::binary);
			fileC.seekg(0);
			int _id = rand() % maxCliente - 1;

			if (browser.buscarID(fileC, _id, _tipoC) == true) {
				DelimTextBuffer delim('^', 300);
				Cliente cliente;
				cliente.Read(fileC, delim);
				cliente.print();

				if (cliente.id != 0) {
					nueva.cliente_id = cliente.id;
					for (int i = 0; i < ubicaciones.size(); i++) {
						if (strcmp(toLowerCase(cliente.ciudad), toLowerCase((ubicaciones[i].ciudad).c_str())) == 0) {
							nueva.ubicacion_X = ubicaciones[i]._x;
							nueva.ubicacion_Y = ubicaciones[i]._y;
							break;
						}
					}
				}
				clienteEncontrado = 1;
			}
			fileC.close();
		}


		//Datos de Productos
		Amazon tienda;
		Producto* auxp = new Producto();
		int maxProducto = auxp->getNextId(false);
		int cantidadProductos = 1 + rand() % (11 - 1);
		delete auxp;

		vector<Detalle> carrito;
		for (int i = 0; i < cantidadProductos; i++) {
			bool ProductoEncontrado = false;
			while (!ProductoEncontrado) {
				ifstream fileP("productos.bin", ios::in | ios::binary);
				fileP.seekg(0);
				int _id = rand() % maxProducto - 1;

				if (browser.buscarID(fileP, _id, _tipoP)) {
					DelimTextBuffer delim('^', 300);
					Producto producto;
					producto.Read(fileP, delim);
					//producto.print();

					Detalle detalle;
					if (producto.id != 0) {
						detalle.id = detalle.getNextId();
						detalle.factura_id = nueva.id;
						detalle.producto_id = producto.id;
						detalle.precio_unit = producto.precio_actual;

						if (producto.precio_actual < 100)
							detalle.cantidad = 1 + rand() % (51 - 1);
						else if (producto.precio_actual > 100 && producto.precio_actual < 1000)
							detalle.cantidad = 1 + rand() % (11 - 1);
						else if (producto.precio_actual > 1000 && producto.precio_actual < 10000)
							detalle.cantidad = 1 + rand() % (6 - 1);
						else if (producto.precio_actual > 10000)
							detalle.cantidad = 1 + rand() % (3 - 1);

						tienda.agregarAlCarrito(carrito, detalle);
						//detalle.print();
					}
					ProductoEncontrado = 1;
					cout << ProductoEncontrado;
				}
				fileP.close();
			}
		}



		//Procesar las compras
		if (!carrito.empty()) {
			ofstream fileD("detalles.bin", ios::out | ios::app | ios::binary);

			for (int i = 0; i < carrito.size(); i++) {
				nueva.total_neto += (carrito[i].precio_unit * carrito[i].cantidad);
				DelimTextBuffer delim('^', 300);
				fileD.seekp(ios::ate);
				carrito[i].posicion = fileD.tellp();
				carrito[i].Write(fileD, delim);
				carrito[i].print();
				browser.agregar(nullptr, nullptr, carrito[i].id, carrito[i].posicion, _tipoD);
			}
			browser.ordenar(_tipoD);

			if (nueva.total_neto != 0)
				nueva.total_impuesto = (nueva.total_neto * 0.15);
			else
				nueva.total_impuesto = 0;

			DelimTextBuffer delim2('^', 300);
			fileF.seekp(ios::ate);
			nueva.posicion = fileF.tellp();
			nueva.Write(fileF, delim2);
			browser.agregar(nueva.codigo, nullptr, nueva.id, nueva.posicion, _tipoF);
			browser.ordenar(_tipoF);
			fileD.close();
		}

		fileF.close();
		fileFIndex.close();
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

void Busqueda::generarCodigoAleatorio(char* code, const int len) {
	//srand(time(NULL));
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i) {
		code[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	code[len] = 0;
}