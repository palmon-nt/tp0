#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char *ip;
	char *puerto;
	char *valor;
	t_log *logger;
	t_config *config;
	
	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger("tp0.log", "MiPrograma", true, LOG_LEVEL_INFO);
	
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
 log_info(logger,"holaaaa");
 
	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
		

	// Usando el config creado previamente, leemos los valores del config y los
	// dejamos en las variables 'ip', 'puerto' y 'valor'
   valor=config_get_string_value(config,"CLAVE");
	ip=config_get_string_value(config,"IP");
	puerto=config_get_string_value(config,"PUERTO");
	// Loggeamos el valor de config
	log_info(logger,"%s",valor);
	log_info(logger,"%s",ip);
	log_info(logger,"%s",puerto);
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

t_log *iniciar_logger(char *file, char *process_name, bool is_active_console, t_log_level level)
{
	t_log *nuevo_logger=log_create(file,process_name,is_active_console,level);

	return nuevo_logger;
}

t_config *iniciar_config(void)
{
	t_config *nuevo_config=config_create("cliente.config");

	return nuevo_config;
}

void leer_consola(t_log *logger)
{
	char *leido;

	// La primera te la dejo de yapa
	leido = readline("> ");
	while(strcmp("",leido)){
		printf("ingresaste: %s\n",leido);
		free(leido);
		leido=readline("> ");
	}
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío

	// ¡No te olvides de liberar las lineas antes de regresar!
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!

	char *leido;
	t_paquete *paquete=crear_paquete();
	while(strcmp(leido=readline("> "),"")){
		agregar_a_paquete(paquete,leido,strlen(leido)+1);
		free(leido);
	}
	// Leemos y esta vez agregamos las lineas al paquete
	enviar_paquete(paquete,conexion);
	eliminar_paquete(paquete);
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
}

void terminar_programa(int conexion, t_log *logger, t_config *config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config)
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	  log_destroy(logger);
	  config_destroy(config);
	  liberar_conexion(conexion);
}
