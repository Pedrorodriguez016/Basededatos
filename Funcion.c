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
	//Recogemos el resultado de la primera fila
	
	row = mysql_fetch_row (resultado);
	//Analizamos para empezar la primera fila para saber
	//si hemos obtenido resultados con la consulta
	
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	
	//En caso de obtener resultados, se analiza cada fila hasta llegar
	//a la primera fila con un valor nulo
	
	else
		
		while (row !=NULL) {
			
			//Mientras la fila no sea nula se sumara una Partida Ganada
			PartidasGanadas++;
			//Obtenemos la siguiente fila para el siguiente loop
			row = mysql_fetch_row (resultado);
	}
		
		//Cerrar la conexion con el servidor MySQL 
		mysql_close (conn);
		//Imprimimos en pantalla el resultado deseado,
		//aunque esto se puede modificar para que solamente
		printf("%d\n",PartidasGanadas);
		
		exit(0);
}