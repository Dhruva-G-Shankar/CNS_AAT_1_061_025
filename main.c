#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")

#define PORT 9000

const char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const char* key      = "QWERTYUIOPASDFGHJKLZXCVBNMlkjhgfdsamnbvcxzpoiuytrewq";

void encrypt(const char* text, char* result) {
    int i;
    for (i = 0; text[i]; i++) {
        char* ptr = strchr(alphabet, text[i]);
        if (ptr) {
            int idx = ptr - alphabet;
            result[i] = key[idx];
        } else {
            result[i] = text[i];
        }
    }
    result[i] = '\0';
}

void decrypt(const char* cipher, char* result) {
    int i;
    for (i = 0; cipher[i]; i++) {
        char* ptr = strchr(key, cipher[i]);
        if (ptr) {
            int idx = ptr - key;
            result[i] = alphabet[idx];
        } else {
            result[i] = cipher[i];
        }
    }
    result[i] = '\0';
}

DWORD WINAPI server_thread(LPVOID lpParam) {
    SOCKET server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char decrypted[1024], ack[1024], encrypted_ack[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 1);
    printf("Server listening on port %d...\n", PORT);

    client_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    recv(client_socket, buffer, sizeof(buffer), 0);

    decrypt(buffer, decrypted);
    printf("Received (decrypted): %s\n", decrypted);

    sprintf(ack, "Acknowledged: %s", decrypted);
    encrypt(ack, encrypted_ack);
    send(client_socket, encrypted_ack, strlen(encrypted_ack), 0);

    closesocket(client_socket);
    closesocket(server_fd);

    return 0;
}

DWORD WINAPI client_thread(LPVOID lpParam) {
    Sleep(1000); // Ensure server starts first
    SOCKET sock;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char message[1024] = "Hello Server";
    char encrypted[1024], decrypted_ack[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    encrypt(message, encrypted);
    send(sock, encrypted, strlen(encrypted), 0);

    recv(sock, buffer, sizeof(buffer), 0);
    decrypt(buffer, decrypted_ack);
    printf("Server response (decrypted): %s\n", decrypted_ack);

    closesocket(sock);
    return 0;
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    HANDLE hServer, hClient;

    hServer = CreateThread(NULL, 0, server_thread, NULL, 0, NULL);
    Sleep(500); // Let server start before client
    hClient = CreateThread(NULL, 0, client_thread, NULL, 0, NULL);

    WaitForSingleObject(hServer, INFINITE);
    WaitForSingleObject(hClient, INFINITE);

    WSACleanup();
    return 0;
}
