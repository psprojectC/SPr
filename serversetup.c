//
// Created by Platon on 5/27/2020.
//

#include "serversetup.h"
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include <wchar.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <locale.h>

#include "textManipulation.h"
#include "list.h"

#define SA struct sockaddr
#define SERVER_BACKLOG 20

void * setUpServer(int * sockfd, int * connfd, int * len, struct sockaddr_in * servaddr, struct sockaddr_in * cli)
{
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (*sockfd == -1) die();
    if (bind(*sockfd, (SA *) servaddr, sizeof(*servaddr)) != 0) die();
    if (listen(*sockfd, SERVER_BACKLOG) != 0) die();
    *len = sizeof(*cli);
    return NULL;
}

void die(void)
{
    fprintf(stderr, "%s", strerror(errno)), exit(errno);
}

void * enterText(int connfd, wchar_t * string, Node ** localChanges)
{
    //puts("enter text");
    char temp[2000];
    if (recv(connfd, temp, 2000, 0) < 0)
    {
        fputs(errRecv, stderr);
        close(connfd);
        return (void *) -1;
    }
    swprintf(string, strlen(temp), L"%hs", temp);
    overwrite(connfd, string);
    return NULL;
}

void * translateText(int connfd, wchar_t * string, Node ** localChanges)
{
    if (!wcslen(string))
    {
        if (send(connfd, LnoText, wcslen(noText) * sizeof(wchar_t), 0) < 0)
        {
            fputs(errSend, stdout);
            close(connfd);
            return (void *) -1;
        }
    }
    else
    {
        string = translate(string, localChanges);
        overwrite(connfd, string);
        if (send(connfd, string, sizeof(wchar_t) * wcslen(string), 0) < 0) puts(strerror(errno));
    }
    return NULL;
}

void * capitalizeText(int connfd, wchar_t * string, Node ** localChanges)
{
    if (!wcslen(string))
    {
        if (send(connfd, LnoText, wcslen(noText) * sizeof(wchar_t), 0) < 0)
        {
            fputs(errSend, stdout);
            close(connfd);
            return (void *) -1;
        }
    }
    else
    {
        string = capitalize(string, localChanges);
        overwrite(connfd, string);
        if (send(connfd, string, sizeof(wchar_t) * wcslen(string), 0) < 0) puts(strerror(errno));
    }
    return NULL;
}

void * viewChanges(int connfd, wchar_t * string, Node ** localChanges)
{
    if (!wcslen(string))
    {
        if (send(connfd, L"No text has been entered. Enter text using option 1.", 53, 0) < 0)
        {
            fputs(errSend, stdout);
            close(connfd);
            return (void *) -1;
        }
        if (send(connfd, L"end", 4, 0) < 0)
        {
            fputs(errSend, stdout);
            close(connfd);
            return (void *) -1;
        }
    }
    else
    {
        const wchar_t * tbs = additivePrint(*localChanges);
        if (send(connfd, tbs, wcslen(tbs) * sizeof(wchar_t), 0) < 0) puts(strerror(errno));
        free(tbs);
    }
    return NULL;
}
int overwrite(int connfd, wchar_t * text)
{
    char fileName[30];
    snprintf(fileName, 30, "User%d-%d.txt", getpid(), connfd);
    int fdButShouldHaveBeenfp = open(fileName, O_CREAT|O_RDWR|O_TRUNC, 0644);
    if (fdButShouldHaveBeenfp < 0) die();
    int status = write(fdButShouldHaveBeenfp, text, wcslen(text) * sizeof(wchar_t));
    if (status < 0) puts(strerror(errno));
    else write(STDOUT_FILENO, fileName, strlen(fileName));
    close(fdButShouldHaveBeenfp);
    return 0;
}

int handleClient(int connfd)
{
    Node * localChanges = NULL;
    wchar_t * string = calloc(sizeof(wchar_t), 2000);
    if (send(connfd, menu, strlen(menu), 0) < 0)
    {
        fprintf(stderr, "Error sending the menu to client.");
        puts(strerror(errno));
        return errno;
    }
    int8_t choice;
    while(1)
    {
        if (recv(connfd, &choice, sizeof(int8_t), 0) < 0)
        {
            fprintf(stderr, "Error receiving from client.");
            return errno;
        }
        if (choice == '5') break;
        choice -= '0';
        if (choice >= 0 && choice < 5) functions[choice](connfd, string, &localChanges);
    }
    printf("\nconnection %d closed\n", connfd);
    setlocale(LC_ALL, "");
    free(string);
    return 0;
}