/*
*   ESERCIZIO : compilare ed eseguire il sorgente presente
*   poi modificarlo in modo che stampi l'ip del client
*
*   SOLUZIONE v0.3
*/
#include <stdio.h>
#include <string.h>

#include "UDP.H"
#include "sequence.h"

#include <netinet/in.h>
#include <arpa/inet.h>


int main(void)
{
    unsigned char buffer[1024]; // buffer per ricezione
    unsigned long ip_address;
    unsigned short port_number;
    unsigned int num; // variabile per numero da generare
    int n;

// inizializzazione socket con porta UDP numero 23365
    if (UDP_init(23365) < 0)
    {
        printf("Errore inizializzazione socket!\r\n");
        return -1;
    }
    printf("Servizio attivo…\r\n");
    while (1)
    {
        if ((n = UDP_receive( &ip_address, &port_number, buffer, sizeof(buffer))) > 0)
        {
            // ricezione di un datagram e verifica del messaggio
            buffer[n] = '\0'; // terminatore di stringa
            if (strcmp((char*)buffer, "REQ") == 0)
            {
                // richiesta di generazione di un nuovo numero
                num = sequence();
                UDP_send(ip_address, port_number, (void*)&num, sizeof(unsigned int));
                printf("…inviato numero %u.\r\n", num);
                //soluzione
                printf("... all'indirizzo %lu \r\n", ip_address);
                //
                // ma invece del consueto indirizzo ip es. 127.0.0.1
                // stampa un numero intero es.2130706433
                // che ne è la rappresentazione binaria a 32 bit :
                // 01111111 00000000 00000000 00000001
                // 127      0        0        1
                // occorre convertire l'integer in una stringa
                // di numeri separati dai punti
                // vedi soluzione v.02
                // abbiamo a disposizione la funzione
                //
                //      char *inet_ntoa(struct in_addr addr)
                //
                // che prende in input l'indirizzo strutturato
                // e restituisce la stringa (puntatore ad una ..)
                //
                // Internet address (a structure for historical reasons)
                //  struct in_addr {
                //      uint32_t s_addr; // that's a 32-bit int (4 bytes)
                //    };

                struct in_addr add;


                // ma stampa l'indirizzo ad ordine invertito ...
                // vedi soluzione v0.3
                // occorre usare la funzione
                //      htonl( );
                // riferimenti
                //      http://beej.us/guide/bgnet/output/html/multipage/ipstructsdata.html#byteorder

                add.s_addr=htonl( ip_address );

                char *ip_address_string;
                ip_address_string=inet_ntoa(add);
                printf("... all'indirizzo %s \r\n", ip_address_string);
            }
        }
    }
    UDP_close();
    return 0;
}
