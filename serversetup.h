//
// Created by Platon on 5/27/2020.
//

#ifndef UNTITLED3_SERVERSETUP_H
#define UNTITLED3_SERVERSETUP_H

#include <netinet/in.h>
#include <pthread.h>
#include "list.h"

static const char *menu =
        "Welcome to my server! You will be presented with a choice below:\n"
        "1. Enter text\n"
        "2. Translate entered text\n"
        "3. Capitalize text properly\n"
        "4. View last 10 changes\n"
        "5. Exit\n";
static const char * noText = "No text has been entered. Enter text using option 1.";
static const wchar_t * LnoText = (const wchar_t *) L"No text has been entered. Enter text using option 1.";
static const char * errSend = "Error occurred while attempting to send text. Closing the connection.";
static const char * errRecv = "Error occurred while attempting to receive text. Closing the connection.";

void * setUpServer(int * sockfd, int * connfd, int * len, struct sockaddr_in * servaddr, struct sockaddr_in * cli);
void die(void);
int overwrite(int connfd, wchar_t * text);
void * enterText(int connfd, wchar_t * string, Node ** localChanges);
void * translateText(int connfd, wchar_t * string, Node ** localChanges);
void * capitalizeText(int connfd, wchar_t * string, Node ** localChanges);
void * viewChanges(int connfd, wchar_t * string, Node ** localChanges);
void * cleanUp(int connfd, wchar_t * string, Node ** localChanges);
int handleClient(int connfd);

static void * (*functions[])() = {enterText, translateText, capitalizeText, viewChanges};

#endif //UNTITLED3_SERVERSETUP_H
