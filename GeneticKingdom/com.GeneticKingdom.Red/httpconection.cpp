#include <iostream>
#include <string>
#include <json/value.h>
#include <json/json.h>
#include <curl/curl.h>
#include "../com.GeneticKingdom.EstructurasDatos/Array.h"
#include "../com.GeneticKingdom.EstructurasDatos/Array.cpp"

string datosLeidos;
Array<Array<int>> datosParseados;

/**
 * Funcion a llamar cuando se lee los datos del service web
 * @param buf parametro por defecto
 * @param size parametro por defecto
 * @param nmemb parametro por defecto
 * @param up parametro por defecto
 * @return bytes leidos
 */
size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{
    for (int c = 0; c<size*nmemb; c++){datosLeidos.push_back(buf[c]);}
    return size*nmemb;
}

/**
 * Interpreta el json recibido que contiene la poblacion
 * @param pStr string que contiene el json recibido
 */
void interpretar(string pStr){
    datosLeidos="";
    datosParseados = * new Array<Array<int>>();
    Json::Value root;
    Json::Reader reader;
    reader.parse( pStr, root );
    Json::Value data = root.get ("poblacionGeneral",0);
    for (int i = 0; i < data.size(); i++){
        Json::Value dat1 = data[i];
        Array<int> individuo;
        individuo = * new Array<int>();
        for(int j=0; j< dat1.size(); j++){
            individuo.insert(dat1[j].asInt());
        }
        datosParseados.insert(individuo);
    }
}

/**
 * Metdo que utiliza curl para realizar la peticion HTTP
 */
void solicitarPoblacion(){
    CURL* curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, "localhost:9080/EvolucionadorUniversal/rest/Genetico/Poblacion");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_perform(curl);

    interpretar(datosLeidos);

    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

/**
 * Metdo que utiliza curl para realizar la peticion HTTP
 */
void cambiarTamanoP(int tamano){
    CURL* curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    string url="localhost:9080/EvolucionadorUniversal/rest/Genetico/tamanoP/";
    url.append(to_string(tamano));
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_perform(curl);

    interpretar(datosLeidos);

    curl_easy_cleanup(curl);
    curl_global_cleanup();
}