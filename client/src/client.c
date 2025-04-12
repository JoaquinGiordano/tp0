#include "client.h"
#include <commons/log.h>
#include <readline/readline.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	if (logger == NULL) abort();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	log_info(logger,"Soy un Log");



	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	if (config == NULL) abort();
	
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	
	// Loggeamos el valor de config
	ip = config_get_string_value(config,"IP");
	valor = config_get_string_value(config,"CLAVE");
	puerto = config_get_string_value(config,"PUERTO");

	log_info(logger,ip);
	log_info(logger,valor);
	log_info(logger,puerto);

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	enviar_mensaje(valor,conexion);
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	nuevo_logger = log_create("tp0.log","TP0 LOGS",true, LOG_LEVEL_INFO);
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	nuevo_config = config_create("../cliente.config");
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	do{
		if(leido[0] == '\0') continue;
		leido = readline("> ");
		log_info(logger,leido);
	}while (leido[0] != '\0');

	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete


	do{
		if(leido[0] == '\0') continue;
		leido = readline("> ");
		agregar_a_paquete(paquete,leido,strlen(leido) + 1);
	}while (leido[0] != '\0');


	enviar_paquete(paquete,conexion);

	
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	free(leido);
	eliminar_paquete(paquete);
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
