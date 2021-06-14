#include <iostream>
#include <functional>
#include <unistd.h>
#include <sys/wait.h>

std::string myreadline(int fp, int max) {
    char buf[max+1];
    int i = 0;
    do {
        read(fp, buf + i, 1);
    } while (++i<max && buf[i-1] != '\n');
    buf[i] = 0;
    return buf;
}

template <typename T>
T runInChild(std::function<T(void)> fun){

    std::string message;
    char buf[1024];

    // crea pipe
    int c2p[2]; // [0]: read, [1]: write
    if(pipe(c2p)==-1) {
        std::cerr << "can't open pipe" << std::endl;
        exit(EXIT_FAILURE);
    }

    pid_t child_pid = fork();
    int wstatus;

    if(child_pid == -1) {
        std::cerr<<"for error";
        exit(EXIT_FAILURE);
    } else if(child_pid > 0) {
        std::cout<<"[F] "<<getpid()<<" start"<<std::endl;
        close(c2p[1]);
        T res;
        read(c2p[0], &res, sizeof(T));
        std::cout<<"[F] read "<<res<<std::endl;
        wait(nullptr);
        return res;
    } else {
        std::cout<<"[K] "<<getpid()<<" start"<< std::endl;
        close(c2p[0]);
        T res = fun();
        write(c2p[1], &res, sizeof(res));
        std::cout<<"[K] write "<<res<<std::endl;
        exit(EXIT_SUCCESS);
    }
}



void es1(){
    int x = 2;
    runInChild<std::string>([x]() -> std::string {
        for(int i=0; i<x; i++) {
            sleep(1);
            std::cout << getpid() << " YEET!" << std::endl;
        }
        return "YAY";
    });
}

int main() {
    es1();


    return 0;
}





