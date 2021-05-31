#include <conio.h>
#include <iostream>
#include "Amazon.h"


void clientes();
void productos();
void facturas();

using namespace std;
int main()
{
	Amazon tienda;
	Cliente aux;
	int opcion;
	//int cliente;
	int producto;

	cout << "\n\t**** TIENDA VIRTUAL DE AMAZON *********\n\n";
	
	cout << "1.Clientes \n2.Productos\n3.Facturas\n4.Salir\n ";
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
		break;

	default:
		cout << "...Saliendo ....";
		break;

	}
	
	_getch();
}


void clientes()
{
	Amazon tienda;
	int cliente;
	cout << "\n\t*** SECCION CLIENTE  *****\n\n";
	cout << "1.Agregar Cliente\n2.Consultar Clientes \n3.Navegacion de Clientes \n4.Modificar Clientes\n5.Listar Clientes\n6.Eliminar Cliente \n7. Salir";

	cout << "Ingrese una opcion:";
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
		tienda.listarClientes();
		break;

	case 6:
		tienda.eliminarClientes();
		break;

	default:
		break;



	}

	
}

void productos()
{
	Amazon tienda;
	int producto;
	cout << "\n\t*** SECCION PRODUCTO *** \n\n";
	cout << "1.Agregar Producto\n2.Consultar Producto \n3. Modificar Producto \n4.Navegacion Producto \n5.Eliminar Producto 6.Salir";

	cout << "Ingrese una opcion: ";
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
		tienda.listarProductos();
		break;

	case 5:
		tienda.eliminarProducto();
		break;


	default:
		
		break;

	}

}