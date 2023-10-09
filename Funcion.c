#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int PartidasGanadas;
	char Jugador [80];
	
	//Creamos una conexion al servidor MySQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//Inicializamos la conexión al servidor MySQL
	
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "Juego",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//Creamos el string para poder hacer la consulta a MYSQL
	//con una variable, que es el nombre del jugador que buscamos
	
	char Consulta [80];
	printf("Dame el nombre: ");
	scanf("%s", Jugador);
	sprintf (Consulta,"SELECT Partida.Identificador FROM Partida, Jugador WHERE Jugador.Nombre ='%s' AND Jugador.Identificador = Partida.Ganador", Jugador);
	
	//Consulta SQL para obtener una tabla con
	//los datos solicitados de la base de datos
	
	err=mysql_query (conn, Consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//Recogemos el resultado de la consulta en una
	//tabla virtual MySQL
	
	resultado = mysql_store_result (conn);