#define ROUTER_IP "192.168.0.1"
#define ROUTER_PORT 80

#include <stdio.h>
#include <string.h>

#include <curl/curl.h>

// referencia: http://osvdb.org/show/osvdb/102605

CURL *curl;
CURLcode res;

char hostport[40];

int testAuth( const char* username, const char* password ) {

  struct curl_httppost *formpost = NULL;
  struct curl_httppost *lastptr = NULL;
  struct curl_slist *headerlist = NULL;

  curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "loginUsername", CURLFORM_COPYCONTENTS, username, CURLFORM_END );
  curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "loginPassword", CURLFORM_COPYCONTENTS, password, CURLFORM_END );

  curl_easy_setopt( curl, CURLOPT_URL, hostport );

  curl_easy_setopt( curl, CURLOPT_HTTPHEADER, headerlist );
  curl_easy_setopt( curl, CURLOPT_HTTPPOST, formpost );

  curl_easy_setopt( curl, CURLOPT_TIMEOUT, 10L ); // esperar al menos 10 segundos

  res = curl_easy_perform( curl );

  if(res == CURLE_OPERATION_TIMEDOUT ) {
    printf("El router se colgo:)\n\n");
  };

  return 0;
};

int main() {

  snprintf( hostport, sizeof(hostport), "http://%s:%d/goform/login", ROUTER_IP, ROUTER_PORT );

  curl = curl_easy_init();

  printf("-> URL: %s\n", hostport );
  printf("-> Probar la autenticacion con credenciales en blanco.\n\t- Usuario: , Password: \n");

  testAuth( "", "" );
  return 0;
};
