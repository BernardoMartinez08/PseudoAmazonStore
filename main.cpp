#include <conio.h>
#include <iostream>
#include "Amazon.h"
#include "BusquedasSecuenciales.h"
#include <cstdlib> 
#include <ctime> 
#include <windows.h>
#include <string>
#include "BusquedasIndexadas.h"
void clientes();
void productos();
void facturas();
void generadores();
Amazon tienda;
Busqueda buscador(tienda.browser);
using namespace std;
int main()
{
	srand(time(NULL));
	Cliente aux;
	int opcion = 0;
	int producto;

	while (opcion != 5) {
		cout << "\n********* TIENDA VIRTUAL DE AMAZON *********\n\n";

		cout << "1.Clientes \n2.Productos\n3.Facturas\n4.Generar Datos\n5.Salir\n ";
		cout << "Ingrese una opcion:";
		cin >> opcion;

		cout << "\n";

		switch (opcion)
		{
		case 1:
			clientes();
			break;

		case 2:
			productos();
			break;

		case 3:
			cout << "\n...EN CONSTRUCCION....";
			tienda.RegistrarCompra();
			break;

		case 4:
			generadores();
			break;

		case 5:
			cout << "\n...Saliendo....";
			tienda.salir();

			cout << "\nSE GUARDARON LOS INDICES, PRECIONE UNA TECLA PARA CERRAR.";
			break;
		default:
			cout << "\nOPCION NO VALIDA";
			break;
		}
	}
	_getch();
}


void clientes()
{
	int cliente = 0;
	while (cliente != 7) {
		cout << "\n***** SECCION CLIENTE  *****\n\n";
		cout << "1.Agregar Cliente\n2.Consultar Clientes (Secuenciales)\n3.Navegacion de Clientes \n4.Modificar Clientes\n5.Listar Clientes\n6.Eliminar Cliente \n7. Volver al Menu Anterior";

		cout << "\nIngrese una opcion:";
		cin >> cliente;
		switch (cliente)
		{
		case 1:
			tienda.agregarCliente();
			break;
		case 2:
			tienda.consultarCliente();
		
			break;
		case 3:
			tienda.navegacionClientes();
			break;

		case 4:
			tienda.modificarCliente();
			break;

		case 5:
			if (!tienda.listarClientes())
				cout << "\n\nNO HAY REGISTROS QUE MOSTRAR\n";
			break;

		case 6:
			tienda.eliminarClientes();
			break;

		case 7:
			cout << "\nVOLVIENDO AL MENU ANTERIOR";
			break;

		default:
			cout << "\nOPCION NO VALIDA";
			break;
		}
	}
}

void productos()
{
	int producto = 0;
	while (producto != 7) {
		cout << "\n**** SECCION PRODUCTO **** \n\n";
		cout << "1. Agregar Producto\n2. Consultar Producto (Secuenciales) \n3. Modificar Producto \n4. Navegacion Producto\n5. Listar Productos \n6. Eliminar Producto \n7. Volver al Menu Anterior";

		cout << "\nIngrese una opcion: ";
		cin >> producto;

		switch (producto)
		{
		case 1:
			tienda.agregarProducto();
			break;

		case 2:
			tienda.consultarProducto();
			break;

		case 3:
			tienda.modificarProducto();
			break;

		case 4:
			tienda.navegacionProductos();
			break;

		case 5:
			if (!tienda.listarProductos())
				cout << "\n\nNO HAY REGISTROS QUE MOSTRAR\n";
			break;

		case 6:
			tienda.eliminarProducto();
			break;

		case 7:
			cout << "\nVOLVIENDO AL MENU ANTERIOR";
			break;

		default:
			cout << "\nOPCION NO VALIDA";
			break;
		}
	}
}


void facturas() {
	int producto = 0;
	while (producto != 5) {
		cout << "\n**** SECCION FACTURAS **** \n\n";
		cout << "1. Procesar un compra\n2. Navegacion de Facturas\n3. Listar Facturas \n4. Eliminar Facturas \n5. Volver al Menu Anterior";

		cout << "\nIngrese una opcion: ";
		cin >> producto;

		switch (producto)
		{
		case 1:
			tienda.RegistrarCompra();
			break;

		case 2:
			tienda.navegacionFacturas();
			break;

		case 3:
			
			break;

		case 4: {
			cout << "\n\n*** ELIMINAR FACTURAS***\n\n1. Elimiar Facturas por codigo\n2.Eliminar Faturas de un Cliente\n3.Volver al menu anterior";
			int opcElimi;
			cout << "\nIngrese una opcion: ";
			cin >> opcElimi;

			switch (opcElimi) {
			case 1:
				tienda.eliminarFactura();
				break;
			case 2: {
				cout << "\n\n*** ELIMINAR FACTURAS DE UN CLIENTE***\n\n";
				int id;
				cout << "\nIngrese el codigo del cliente: ";
				cin >> id;

				buscador.eliminarFacturasCliente(id);
				break;
			}
			case 5:
				cout << "\nVOLVIENDO AL MENU ANTERIOR";
				break;

			default:
				cout << "\nOPCION NO VALIDA";
				break;
			}
			break;
		}
		case 6:
			cout << "\nVOLVIENDO AL MENU ANTERIOR";
			break;

		default:
			cout << "\nOPCION NO VALIDA";
			break;
		}
	}
}


void generadores() {
	int opcionMenu = 0;
	while (opcionMenu != 4) {
		cout << "\n\n**** GENERADORES DE DATOS **** \n\n";

		cout << "1. Generador de Clientes\n2. Generador de Productos\n3. Generador de Facturas\n4. Volver al Menu Anteriore";
		cout << "\nIngrese una opcion: ";
		cin >> opcionMenu;

		switch (opcionMenu){
		case 1: {
			int opc = 0;
			while (opc != 3) {
				cout << "\n\n**** GENERADOR DE CLIENTES **** \n\n";
				cout << "1. Generar Archivo Con Datos de Clientes\n2. Generar Clientes \n3. Volver al Menu Anteriore";

				cout << "\nIngrese una opcion: ";
				cin >> opc;

				switch (opc)
				{
				case 1:
					buscador.generarArchivoNombres();
					buscador.generarArchivoApellidos();
					buscador.generarArchivoUbicaciones();
					buscador.generarArchivoCoordenadas();
					cout << "\n\nSE GENERARON LOS ARCHIVOS";
					break;

				case 2: {
					cout << "\n\n**** GENERADOR DE CLIENTES **** \n\n";

					cout << "\n\nIngrese cantidad de usuarios a generar: ";
					int cantidad;
					cin >> cantidad;

					buscador.generarClientes(cantidad);

					cout << "\n\nGENERACION DE CLIENTES COMPLETADA";
					break;
				}
				case 3:
					cout << "\nVOLVIENDO AL MENU ANTERIOR";
					break;

				default:
					cout << "\nOPCION NO VALIDA";
					break;
				}
			}
			break;
		}case 2: {
			int opc = 0;
			while (opc != 3) {
				cout << "\n\n**** GENERADOR DE PRODUCTOS **** \n\n";
				cout << "1. Generar Archivo Con Datos de Productos\n2. Generar Productos \n3. Volver al Menu Anteriore";

				cout << "\nIngrese una opcion: ";
				cin >> opc;

				switch (opc)
				{
				case 1:
					buscador.generarArchivoCategorias();
					buscador.generarArchivoSubCategoria();
					buscador.generarArchivoProducto();
					buscador.generarArchivoDescripcion();

					cout << "\n\nSE GENERARON LOS ARCHIVOS";
					break;

				case 2: {
					cout << "\n\n**** GENERADOR DE PRODUCTOS **** \n\n";

					cout << "\n\nIngrese cantidad de productos a generar: ";
					int cantidad;
					cin >> cantidad;

					buscador.generarProductos(cantidad);

					cout << "\n\nGENERACION DE PRODUCTOS COMPLETADA";
					break;
				}
				case 3:
					cout << "\nVOLVIENDO AL MENU ANTERIOR";
					break;

				default:
					cout << "\nOPCION NO VALIDA";
					break;
				}
			}
			break;
		}case 3: {
			int opc = 0;
			while (opc != 2) {
				cout << "\n\n**** GENERADOR DE PRODUCTOS **** \n\n";
				cout << "1. Generar Facturas \n2. Volver al Menu Anteriore";

				cout << "\nIngrese una opcion: ";
				cin >> opc;

				switch (opc)
				{
				case 1: {
					cout << "\n\n**** GENERADOR DE FACTURAS **** \n\n";

					cout << "\n\nIngrese cantidad de facturas a generar: ";
					int cantidad;
					cin >> cantidad;

					buscador.generarFacturas(cantidad);

					cout << "\n\nGENERACION DE FACTURAS COMPLETADA";
					break;
				}
				case 2:
					cout << "\nVOLVIENDO AL MENU ANTERIOR";
					break;

				default:
					cout << "\nOPCION NO VALIDA";
					break;
				}
			}
			break;
		}case 4: {
			cout << "\nVOLVIENDO AL MENU ANTERIOR";
			break;
		}case 5: {
			cout << "\nOPCION NO VALIDA";
			break;
		}
		}
	}
}