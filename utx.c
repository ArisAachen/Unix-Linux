//
// Created by aris on 2021/6/27.
//
#include <utmpx.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void utx_test() {
    printf("utx_test \n");
    // peek to head
    setutxent();
    struct utmpx tmp = {
            .ut_type = LOGIN_PROCESS,
            .ut_id = ":0",
    };
    // get uid
    struct utmpx* result = NULL;
    result = getutxid(&tmp);
    if ( result != NULL)
        printf("auto id: %s, user: %s pid: %d  \n", result->ut_id, result->ut_user, result->ut_pid);
    setutxent();
    result = NULL;
    while ( (result = getutxent()) ) {
        printf("id: %s, user: %s pid: %d  \n", result->ut_id, result->ut_user, result->ut_pid);
    }

    char* login = getlogin();
    printf("login: %s  \n", login);
}

// last login
#include <lastlog.h>
void last_login_test() {
    printf("last_login_test \n");
    int fd = open(_PATH_LASTLOG,O_RDONLY);
    if (fd == -1) {
        printf("last login failed, err: %s \n", strerror(errno));
        return;
    }
    uid_t id = getuid();
    if ( !lseek(fd,id * sizeof(struct lastlog),SEEK_SET) ) {
        printf("seek failed, err: %s \n", strerror(errno));
        return;
    }
    struct lastlog last;
    if ( !read(fd, &last, sizeof(struct lastlog)) ) {
        printf("read failed, err: %s \n", strerror(errno));
        return;
    }
    printf("last login success. id: %d, time: %d \n", id,last.ll_time);
}


int main() {
    utx_test();
    last_login_test();


    return 1;
}