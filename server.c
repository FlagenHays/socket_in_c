#include<stdio.h>
#include<winsock2.h>
#include <windows.h>
#include <string.h>
#pragma comment (lib,"ws2_32.lib") 
#define DEFAULT_BUFLEN 512
int main(){
    SOCKET ListenSocket = INVALID_SOCKET;
    struct sockaddr_in service;
    FILE *fp = NULL;
    WSADATA wsaData;
    int resultat = 0;
    char return_char[] = "";
    char recvbuf[DEFAULT_BUFLEN] = "";
    int recvbuflen = DEFAULT_BUFLEN;
    int caractere = 0;
    int i = 0;
    resultat = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (resultat != NO_ERROR) {
        printf("WSA ne c'est pas lance correctement \n");
        return 1;
    }




    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSocket == INVALID_SOCKET) {
        printf("La fonction a echoue avec le code erreur: %u\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }




    service.sin_family = AF_INET; //type
    service.sin_addr.s_addr = inet_addr("127.0.0.1"); //ip
    service.sin_port = htons(4242); //port
    resultat = bind(ListenSocket, (SOCKADDR*) &service, sizeof (service));



    if(resultat == SOCKET_ERROR){
        wprintf(L"Impossible de bind le socket %u\n", WSAGetLastError());
        closesocket(ListenSocket);
        resultat = closesocket(ListenSocket);
        if(resultat == SOCKET_ERROR){
            wprintf(L"Erreur à la fermture du socket %u\n", WSAGetLastError());
        }
        WSACleanup();
        return 1;
    }


    else{
        printf("Le socket a bien ete bind\n");
    }



    listen(ListenSocket, SOMAXCONN);
    if(resultat == SOCKET_ERROR){
        wprintf(L"Erreur au listen du socket %u\n", WSAGetLastError());
        WSACleanup();
        return 1;        
        }
    else{printf("Le socket a bien ete ecoute\n");}
        
    wprintf(L"En attente de connexion...\n");
    SOCKET AcceptSocket;
    AcceptSocket = accept(ListenSocket, NULL, NULL);
    if(AcceptSocket == INVALID_SOCKET){
        printf("Erreur dans la lecture du socket %u\n", WSAGetLastError());
        resultat = closesocket(ListenSocket);
        if(resultat == SOCKET_ERROR){
            wprintf(L"Erreur à la fermture du socket %u\n", WSAGetLastError());
        }
        WSACleanup();
        return 1;
    }
    else{
        wprintf(L"Client connecte.\n");
    }
    
    do {

        resultat = recv(AcceptSocket, recvbuf, recvbuflen, 0);
        if ( resultat > 0 ){
            system(recvbuf);
        }
    } while(1);
    pclose(fp);
    printf("Le client a stope la connextion");
    resultat = closesocket(ListenSocket);
    if(resultat == SOCKET_ERROR){
        wprintf(L"Erreur à la fermture du socket %u\n", WSAGetLastError());
    }


    WSACleanup();
    return 1;    
    
    return 0;
}
