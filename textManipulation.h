//
// Created by Platon on 5/5/2020.
//

#ifndef UNTITLED3_TEXTMANIPULATION_H
#define UNTITLED3_TEXTMANIPULATION_H

#include <wchar.h>

#include "list.h"

static const wchar_t *multiToUpper[] = {L"Sht", L"SHT", L"Zh", L"ZH", L"Ts", L"TS", L"Ch", L"CH", L"Sh", L"SH", L"Yu",
                                        L"YU", L"Ya", L"YA"};
static const wchar_t *replaceUpper[] = {L"Щ", L"Щ", L"Ж", L"Ж", L"Ц", L"Ц", L"Ч", L"Ч", L"Ш", L"Ш", L"Ю", L"Ю", L"Я",
                                        L"Я"};
static const wchar_t *multiToLower[] = {L"sht", L"zh", L"ts", L"ch", L"sh", L"yu", L"ya"};
static const wchar_t *replaceLower[] = {L"щ", L"ж", L"ц", L"ч", L"ш", L"ю", L"я"};

static const wchar_t throwaway = L'\a';

void changeScalarChars(wchar_t *ch, const size_t len);
void KMPSearch(wchar_t *text, const wchar_t *pattern, const wchar_t *replace, Node ** localChanges);
void computeLPSArray(const wchar_t *pat, const size_t patternLen, size_t *lps);
const wchar_t * capitalize(wchar_t *text, Node ** localChanges);
const wchar_t * translate(const wchar_t *text, Node ** localChanges);

#endif //UNTITLED3_TEXTMANIPULATION_H
