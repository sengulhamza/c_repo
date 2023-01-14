#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "hex_dump.h"
#include "tcp_msg.h"

#define TCP_SOCK_SERVER_PORT 1234
#define TCP_SOCK_SERVER_BUFFER_SIZE 1024

#define TCP_SOCK_SERVER_TEST_PAYLOAD "Follow the white rabbit."

static void *tcp_sock_thread_send(void *cfd)
{
    int c = *((int *)cfd);
    while (1) {
        send(c, &(tcp_msg_t) {
            0x1, TCP_SOCK_SERVER_TEST_PAYLOAD, strlen(TCP_SOCK_SERVER_TEST_PAYLOAD)
        }, sizeof(tcp_msg_t), 0);
        printf("Message sent.\r\n");
        sleep(2);
    }
}

static void *tcp_sock_thread_recv(void *cfd)
{
    tcp_msg_t tcp_msg_rec = {0};
    int d = *((int *)cfd);
    while (1) {
        int idata = 0;
        idata = recv(d, &tcp_msg_rec, sizeof(tcp_msg_t), 0);
        if (idata > 0) {
            printf("\r\nMessage received:\r\n");
            hex_dump(VARIABLE_PTR_STRGFY((uint8_t *)&tcp_msg_rec), sizeof(tcp_msg_rec));
        }
    }
}

int main()
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("socket");
        return -1;
    }

    struct sockaddr_in serv = {
        .sin_family = AF_INET,
        .sin_port = htons(TCP_SOCK_SERVER_PORT),
        .sin_addr.s_addr = htonl(INADDR_ANY),
    };
    int bd = bind(sfd, (struct sockaddr *)&serv, sizeof(serv));
    if (bd == -1) {
        perror("bind");
        return -1;
    }
    int ln = listen(sfd, 2); //监听
    if (ln == -1) {
        perror("listen");
        return -1;
    }
    socklen_t sock_len = sizeof(struct sockaddr_in);
    while (1) {
        int cfd = accept(sfd, (struct sockaddr *) & (struct sockaddr_in) {}, &sock_len);
        if (cfd == -1) {
            perror("accept");
            return -1;
        }
        pthread_t tid1, tid2;
        pthread_create(&tid1, NULL, tcp_sock_thread_send, &cfd);
        pthread_create(&tid2, NULL, tcp_sock_thread_recv, &cfd);
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
    }
    return 0;
}
