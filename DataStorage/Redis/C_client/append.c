#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <hiredis/hiredis.h>

int main(int argc, char *argv[]) {
    if (argc != 3)
        errx(EXIT_FAILURE, "expected password and value to push");
    char password[80], value_str[1024];
    strncpy(password, argv[1], 80);
    strncpy(value_str, argv[2], 1024);
    char list_name[80] = "append_test";
    char host[80] = "localhost";
    const int port = 6379;
    struct timeval timeout = {2, 0};
    redisContext *redis = redisConnectWithTimeout(host, port, timeout);
    if (redis == NULL || redis->err) {
        if (redis)
            errx(redis->err, "connection failed: %s", redis->errstr);
        else
            errx(EXIT_FAILURE, "can't allocate context");
    }
    redisReply *reply = redisCommand(redis, "AUTH %b",
                                     password, strlen(password));
    printf("reply: '%s'\n", reply->str);
    freeReplyObject(reply);
    reply = redisCommand(redis, "RPUSH %b %b",
                         list_name, strlen(list_name),
                         value_str, strlen(value_str));
    printf("reply: '%s'\n", reply->str);
    freeReplyObject(reply);
    redisFree(redis);
    return EXIT_SUCCESS;
}
