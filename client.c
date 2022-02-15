#include<stdio.h>
#include<winsock2.h>
#include <windows.h>


#pragma comment(lib, "ws2_32.lib")


#define DEFAULT_BUFLEN 512


int main(){
    char recvbuf[DEFAULT_BUFLEN] = "";
    int recvbuflen = DEFAULT_BUFLEN;
    SOCKET ConnectSocket = INVALID_SOCKET;
    WSADATA wsaData;
    char *mesage_send = "exit";
    int iResult = 0;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        printf("WSA ne c'est pas lance correctement %u\n", WSAGetLastError());
        return 1;
    }



    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(ConnectSocket == INVALID_SOCKET){
        printf("Une erreur c'est produite lors du chargement du socket %u\n", WSAGetLastError());
        WSACleanup();
        return 1;       
    }



    char IP[17] = "255.255.255.255";
    unsigned short port;
    struct sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(IP);
    clientService.sin_port = htons(80);
    
    
    iResult = connect(ConnectSocket, (SOCKADDR *) &clientService, sizeof(clientService));




    if(iResult == SOCKET_ERROR){
        printf("erreur dans la fonction connect: %ld\n", WSAGetLastError());
        iResult = closesocket(ConnectSocket);
        if (iResult == SOCKET_ERROR)
            printf("erreur dans la fonction CloseSocket: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;        
    }
    printf("\nArret de la connexion");
    WSACleanup();
    return 1;    

}


