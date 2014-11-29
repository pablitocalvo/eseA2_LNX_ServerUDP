/*
*   ESERCIZIO : compilare ed eseguire il sorgente presente
*   poi modificarlo in modo che stampi l'ip del client
*
*
*/
#include <stdio.h>
#include <string.h>

#include "UDP.H"
#include "sequence.h"


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
            }
        }
    }
    UDP_close();
    return 0;
}
