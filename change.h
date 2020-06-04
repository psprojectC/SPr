//
// Created by Platon on 5/3/2020.
//

#ifndef UNTITLED3_CHANGE_H
#define UNTITLED3_CHANGE_H

#include <stddef.h>

typedef struct Change
{
    const wchar_t * description;
    const wchar_t * (*pToString)(const struct Change * item);
}Change;

const wchar_t * toString(const Change * item);

#endif //UNTITLED3_CHANGE_H
