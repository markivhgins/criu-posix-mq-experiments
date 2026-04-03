#include <mqueue.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    mqd_t mq;
    struct mq_attr attr;

    // Configure queue
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
    attr.mq_curmsgs = 0;

    mq = mq_open("/testqueue", O_CREAT | O_RDWR, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return 1;
    }

    printf("Queue created. PID: %d\n", getpid());

    char msg[100];
    for (int i = 0; i < 5; i++) {
        sprintf(msg, "message-%d", i);
        if (mq_send(mq, msg, strlen(msg) + 1, i) == -1) {
            perror("mq_send");
        } else {
            printf("Sent: %s (priority %d)\n", msg, i);
        }
    }

    printf("Sleeping... attach CRIU now\n");

    sleep(1000);

    mq_close(mq);
    mq_unlink("/testqueue");

    return 0;
}
