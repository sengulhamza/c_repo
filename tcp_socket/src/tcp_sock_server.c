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

#define TCP_SOCK_SERVER_PORT 1234
#define TCP_SOCK_SERVER_BUFFER_SIZE 1024

static void *tcp_sock_thread_send(void *cfd)
{
    char tmp[516] = {"A"};
    int c = *((int *)cfd);
    while (1) {
        send(c, tmp, 516, 0);
        printf("send ok\n");
        sleep(2);
    }
}

static void *tcp_sock_thread_recv(void *cfd)
{
    char tmp[516];
    int d = *((int *)cfd);
    while (1) {
        int idata = 0;
        idata = recv(d, tmp, 516, 0);
        if (idata > 0) {
            printf("%s \r\n", tmp);
        }
    }
}

int main()
{
    struct sockaddr_in serv, cli;
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("socket");
        return -1;
    }
    //初始化结构体serv
    serv.sin_family = AF_INET;
    serv.sin_port = htons(TCP_SOCK_SERVER_PORT);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
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
    socklen_t cli_len;
    cli_len = sizeof(cli);
    while (1) {
        int cfd = accept(sfd, (struct sockaddr *)&cli, &cli_len);
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