#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define MAX_QUEUE_SIZE 256

typedef struct {
    char data[MAX_QUEUE_SIZE];
    size_t front;
    size_t rear;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
} Queue;

void initializeQueue(Queue *queue)
{
    queue->front = 0;
    queue->rear = 0;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->not_empty, NULL);
}

void enqueue(Queue *queue, char item)
{
    pthread_mutex_lock(&queue->mutex);

    while ((queue->rear + 1) % MAX_QUEUE_SIZE == queue->front) {
        pthread_cond_wait(&queue->not_empty, &queue->mutex);
    }

    queue->data[queue->rear] = item;
    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;

    pthread_cond_signal(&queue->not_empty);
    pthread_mutex_unlock(&queue->mutex);
}

char dequeue(Queue *queue)
{
    pthread_mutex_lock(&queue->mutex);

    while (queue->front == queue->rear) {
        pthread_cond_wait(&queue->not_empty, &queue->mutex);
    }

    char item = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;

    pthread_cond_signal(&queue->not_empty);
    pthread_mutex_unlock(&queue->mutex);

    return item;
}

int openSerialPort(const char *portName)
{
    int serialPort = open(portName, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (serialPort == -1) {
        perror("Error opening serial port");
        exit(EXIT_FAILURE);
    }
    return serialPort;
}

void configureSerialPort(int serialPort, speed_t baudRate)
{
    struct termios tty;
    if (tcgetattr(serialPort, &tty) != 0) {
        perror("Error getting serial port attributes");
        close(serialPort);
        exit(EXIT_FAILURE);
    }

    cfsetospeed(&tty, baudRate);
    cfsetispeed(&tty, baudRate);

    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;

    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(serialPort, TCSANOW, &tty) != 0) {
        perror("Error setting serial port attributes");
        close(serialPort);
        exit(EXIT_FAILURE);
    }
}

void *senderTask(void *arg)
{
    printf("%s task started!\r\n", __func__);

    Queue *sendQueue = (Queue *)arg;

    int serialPort = openSerialPort("/dev/tty.usbmodemmeplight1");  // Replace with your serial port
    configureSerialPort(serialPort, B230400);

    while (1) {
        //char dataToSend = dequeue(sendQueue);
        char *test_write_buff = "test_write_ buffer hamza test. 1 2 3 4 5 6 7 8 9 0\r\n";

        write(serialPort, test_write_buff, strlen(test_write_buff));
        usleep(1000000);  // Adjust sleep time to 1 second
        printf("aaa\r\n");
    }
}

void *receiverTask(void *arg)
{

    printf("%s task started!\r\n", __func__);

    Queue *receiveQueue = (Queue *)arg;

    int serialPort = openSerialPort("/dev/tty.usbmodemmeplight1");  // Replace with your serial port
    configureSerialPort(serialPort, B230400);

    while (1) {
        char receivedData;
        ssize_t bytesRead = read(serialPort, &receivedData, 1);
        if (bytesRead > 0) {
            enqueue(receiveQueue, receivedData);
        }
    }
}

void *readProcessTask(void *arg)
{

    printf("%s task started!\r\n", __func__);

    Queue *readQueue = (Queue *)arg;

    while (1) {
        char processedData = dequeue(readQueue);
        // Process the received data (replace this with your processing logic)
        printf("%c", processedData);
    }
}

int main()
{
    Queue sendQueue, receiveQueue, readQueue;
    initializeQueue(&sendQueue);
    initializeQueue(&receiveQueue);
    initializeQueue(&readQueue);

    pthread_t senderThread, receiverThread, readProcessThread;

    pthread_create(&senderThread, NULL, senderTask, (void *)&sendQueue);
    pthread_create(&receiverThread, NULL, receiverTask, (void *)&receiveQueue);
    pthread_create(&readProcessThread, NULL, readProcessTask, (void *)&receiveQueue);

    pthread_join(senderThread, NULL);
    pthread_join(receiverThread, NULL);
    pthread_join(readProcessThread, NULL);
    printf("aaa");

    while (1) {
        printf("aaa");
        sleep(1);
    }

    // Cleanup: Destroy mutex and condition variables
    pthread_mutex_destroy(&sendQueue.mutex);
    pthread_cond_destroy(&sendQueue.not_empty);
    pthread_mutex_destroy(&receiveQueue.mutex);
    pthread_cond_destroy(&receiveQueue.not_empty);
    pthread_mutex_destroy(&readQueue.mutex);
    pthread_cond_destroy(&readQueue.not_empty);

    return 0;
}