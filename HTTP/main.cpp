#include <stdio.h>
#include "iostream"
#include <stdlib.h>
#include <curl/curl.h>

using namespace std;
/* Nombre del archivo donde guardar */
char archivo[] = "archivo.txt";
/* Función de análisis del resultado */
size_t funcion_lectura(char *datos, size_t size, size_t nmemb, void *param)
{
    /* Se abre el archivo para añadir contenido puesto que
       el contenido puede llegar en varias llamadas */
    FILE *f = fopen(archivo, "a+");
    fwrite(datos, size, nmemb, f);
    fclose(f);
    cout<<datos;
    // Devolvemos lo escrito
    return size*nmemb;
}
/* Función que realiza la petición */
void funcion_peticion_http()
{
    CURL *handler = curl_easy_init();
    /* Nos aseguramos que el objeto se haya creado correctamente,
       y si es así, continuamos */
    if ( handler )
    {
        // Preparamos la variable donde almacenar la respuesta
        CURLcode res;

        // A continuación se configura la petición
        curl_easy_setopt(handler, CURLOPT_URL, "http://www.google.es");
        curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, funcion_lectura);
        // Luego se ejecuta la petición
        res = curl_easy_perform( handler );
        // Se comenta el resultado...
        if ( res == CURLE_OK )
            printf("Petición realizada exitosamente\n");
        else
            printf("Ha habido algun tipo de error :(\n");
        // Y por último se limpia
        curl_easy_cleanup(handler);
    }
}
int main(int argc, char* argv[] )
{
    // Borramos el archivo si ya existe
    FILE *file = fopen(archivo, "r");
    if ( file )
    {
        fclose(file);
        remove(archivo);
    }
    funcion_peticion_http();
    return 0;
}