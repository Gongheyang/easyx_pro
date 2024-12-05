#include "public_fun.h" 
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <direct.h>     
#include <string.h>
#include <codecvt>



int create_random(int x1, int x2) {
    if (x2 > x1)
        return rand() % (x2 - x1 + 1) + x1;
    else
        return 0;
}

void get_current_directory(IN OUT char* root)
{
    char rootPath[256] = { 0 };
    char *buffer = NULL;
    if ((buffer = _getcwd(NULL, 0)) == NULL)
    {
        printf_s(" _getcwd function get current working directory failed! \n");
    }
    else
    {
        sprintf_s(rootPath, "%s", buffer);
        free(buffer);
    }
    for (int i = 0; i < sizeof(rootPath); i++)
    {
        if (rootPath[i] == '\\')
        {
            rootPath[i] = '/';
        }
    }
    memcpy(root, rootPath, sizeof(rootPath));
}

void get_parent_directory(IN OUT char* root)
{
    char parPath[256] = { 0 };
    get_current_directory(parPath);
    int index = 0;
    char * result = strrchr(parPath, '/');  // search from back to front
    if (result != NULL) {
        index = result - parPath;
    }
    char rootPath[256] = { 0 };
    strncpy_s(rootPath, parPath, index);
    memcpy(root, rootPath, sizeof(rootPath));
}

void getFileFullPath(IN char* root, IN char* file, OUT char* fullpath)
{
    static char tmp[256] = { 0 };
    sprintf_s(tmp, "%s%s", root, file);
    memcpy(fullpath, tmp, strlen(tmp));
}


const char* wctoch(IN wchar_t * wstr) {

    static char retTmp[256] = { 0 };
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    // Convert to string
    std::string str = conv.to_bytes(wstr);

    sprintf_s(retTmp, str.c_str(), str.length());
    return  retTmp;
}

const wchar_t* chtowc(IN char * ch) {

    static wchar_t retTmp[256] = { 0 };
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    // Convert to wide string
    std::wstring wstr = converter.from_bytes(ch);
    swprintf_s(retTmp, wstr.c_str(), wstr.length());
    return retTmp;
}
