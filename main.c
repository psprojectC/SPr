#include <locale.h>
#include <unistd.h>
#include <cygwin/in.h>

#include "change.h"
#include "serversetup.h"

#define PORT 8101
#define SA struct sockaddr

int main()
{
    //pid - getpid() <unistd.h>
    setlocale(LC_ALL, "");
    int sockfd, connfd, len;
    struct sockaddr_in cli, servaddr =
            {.sin_family = AF_INET,
                    .sin_addr.s_addr = htonl(INADDR_ANY),
                    .sin_port = htons(PORT)
            };
    setUpServer(&sockfd, &connfd, &len, &servaddr, &cli);
    size_t i = 0;
    while(1)
    {
        connfd = accept(sockfd, (SA *) &cli, &len);
        if (connfd < 0) die();
        handleClient(connfd);
        close(connfd);
    }
}




