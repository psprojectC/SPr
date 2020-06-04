//
// Created by Platon on 5/5/2020.
//

#include "textManipulation.h"
#include "change.h"
#include <stdlib.h>
#include <wctype.h>

void computeLPSArray(const wchar_t *pat, const size_t patternLen, size_t *lps)
{
    lps[0] = 0;
    for (size_t len = 0, i = 1; i < patternLen;)
    {
        if (pat[i] == pat[len]) lps[i++] = ++len;
        else
        {
            if (len) len = lps[len - 1];
            else lps[i++] = 0;
        }
    }
}

void KMPSearch(wchar_t *text, const wchar_t *pattern, const wchar_t *replace, Node ** localChanges)
{
    const size_t patternLen = wcslen(pattern);
    const size_t textLen = wcslen(text);
    size_t lps[patternLen];
    computeLPSArray(pattern, patternLen, lps);
    for (size_t i = 0, j = 0; i < textLen;)
    {
        if (pattern[j] == text[i]) i++, j++;
        else
        {
            if (j) j = lps[j - 1];
            else i++;
        }
        if (j == patternLen)
        {
            const size_t idx = i - j;
            const size_t repLen = wcslen(replace);
            //wprintf((const wchar_t *) L"Found pattern at: %zu.\n", idx);
            wchar_t * description = malloc(sizeof(wchar_t[40]));
            Change * ch = malloc(sizeof(Change));
            swprintf(description, 40, (const wchar_t *) L"%ls changed to %ls at index %d", pattern, replace, idx);
            ch->description = description, ch->pToString = toString;
            if (len(*localChanges) == 10)  del1st(localChanges);
            stack(localChanges, ch);
            size_t i_;
            for (i_ = 0; i_ < repLen; i_++) text[i_ + idx] = replace[i_];
            for (size_t j_ = i_; j_ < patternLen; j_++) text[j_ + idx] = throwaway;
            j = lps[j - 1];
        }
        else if (i < textLen && pattern[j] != text[i])
        {
            if (j) j = lps[j - 1];
            else i++;
        }
    }
}

void changeScalarChars(wchar_t* ch, const size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        switch (ch[i])
        {
            case L'A': { ch[i] = L'А'; break; }
            case L'B': { ch[i] = L'Б'; break; }
            case L'D': { ch[i] = L'Д'; break; }
            case L'E': { ch[i] = L'Е'; break; }
            case L'F': { ch[i] = L'Ф'; break; }
            case L'G': { ch[i] = L'Г'; break; }
            case L'H': { ch[i] = L'Х'; break; }
            case L'I': { ch[i] = L'И'; break; }
            case L'K': { ch[i] = L'К'; break; }
            case L'L': { ch[i] = L'Л'; break; }
            case L'M': { ch[i] = L'М'; break; }
            case L'N': { ch[i] = L'Н'; break; }
            case L'O': { ch[i] = L'О'; break; }
            case L'P': { ch[i] = L'П'; break; }
            case L'R': { ch[i] = L'Р'; break; }
            case L'S': { ch[i] = L'С'; break; }
            case L'T': { ch[i] = L'Т'; break; }
            case L'U': { ch[i] = L'У'; break; }
            case L'V': { ch[i] = L'В'; break; }
            case L'Y': { ch[i] = L'Ь'; break; }
            case L'Z': { ch[i] = L'З'; break; }
            case L'a': { ch[i] = L'а'; break; }
            case L'b': { ch[i] = L'б'; break; }
            case L'd': { ch[i] = L'д'; break; }
            case L'e': { ch[i] = L'е'; break; }
            case L'f': { ch[i] = L'ф'; break; }
            case L'g': { ch[i] = L'г'; break; }
            case L'h': { ch[i] = L'х'; break; }
            case L'i': { ch[i] = L'и'; break; }
            case L'k': { ch[i] = L'к'; break; }
            case L'l': { ch[i] = L'л'; break; }
            case L'm': { ch[i] = L'м'; break; }
            case L'n': { ch[i] = L'н'; break; }
            case L'o': { ch[i] = L'о'; break; }
            case L'p': { ch[i] = L'п'; break; }
            case L'r': { ch[i] = L'р'; break; }
            case L's': { ch[i] = L'с'; break; }
            case L't': { ch[i] = L'т'; break; }
            case L'u': { ch[i] = L'у'; break; }
            case L'v': { ch[i] = L'в'; break; }
            case L'y': { ch[i] = L'ь'; break; }
            case L'z': { ch[i] = L'з'; break; }
        }
    }
}

const wchar_t *translate(const wchar_t *text, Node ** localChanges)
{
    const size_t len = wcslen(text);
    for (size_t i = 0; i < sizeof(multiToUpper) / sizeof(*multiToUpper); ++i) KMPSearch(text, multiToUpper[i], replaceUpper[i], localChanges);
    for (size_t i = 0; i < sizeof(multiToLower) / sizeof(*multiToLower); ++i) KMPSearch(text, multiToLower[i], replaceLower[i], localChanges);
    changeScalarChars(text, len);
    size_t count = 0;
    for (size_t j = 0; j < len; ++j) if (text[j] == throwaway) count++;
    const size_t newStringLen = len - count;
    wchar_t * newString = malloc(sizeof(wchar_t) * newStringLen + 1);
    for (size_t k = 0, l = 0; k < len; ++k) if (text[k] != throwaway) newString[l++] = text[k];
    newString[newStringLen] = L'\0';
    return newString;
}

const wchar_t * capitalize(wchar_t *text, Node ** localChanges)
{
    //make sure to pass a non const wchar_t string
    const size_t len = wcslen(text);
    if (!len) return NULL;
    for (size_t i = 0; i < len; ++i)
    {
        if (text[i] == L'.')
        {
            size_t j = i + 1;
            while (j < len - 1 && !iswupper(text[j]) && iswlower(text[j++]));
            text[j] = towupper(text[j]);
            i = j;
        }
    }
    return text;
}
