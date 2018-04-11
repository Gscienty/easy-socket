#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>

int main() {

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    bind(fd, (sockaddr *) &addr, sizeof(sockaddr_in));
    char buf[10];

    sockaddr_in caddr;
    socklen_t len = sizeof(sockaddr_in);
    int n = recvfrom(fd, buf, 10, 0, (sockaddr *) &caddr, &len);

    std::cout << buf[0] << std::endl;

    close(fd);

    return 0;
}