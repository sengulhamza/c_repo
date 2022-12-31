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

#define TCP_SOCK_CLIENT_ADDR "127.0.0.1"
#define TCP_SOCK_CLIENT_PORT 1234

#define TCP_SOCK_CLIENT_TEST_PAYLOAD "I am following the red rabbit."

static void *tcp_sock_thread_send(void *cfd)
{
    int c = *((int *)cfd);
    while (1) {
        send(c, &(tcp_msg_t) {
            0x2, TCP_SOCK_CLIENT_TEST_PAYLOAD, strlen(TCP_SOCK_CLIENT_TEST_PAYLOAD)
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
        .sin_port = htons(TCP_SOCK_CLIENT_PORT),
    };
    inet_pton(AF_INET, TCP_SOCK_CLIENT_ADDR, &serv.sin_addr);
    int ct = connect(sfd, (struct sockaddr *)&serv, sizeof(serv));
    if (ct == -1) {
        perror("connect");
        return -1;
    }
    while (1) {
        pthread_t tid1, tid2;
        pthread_create(&tid1, NULL, tcp_sock_thread_send, &sfd);
        pthread_create(&tid2, NULL, tcp_sock_thread_recv, &sfd);
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
    }
    return 0;
}
