#pragma once
#include <windef.h>

struct GDIBitmap
{
    HBITMAP handle;
    int width;
    int height;

    GDIBitmap()
        : handle(0)
    {
    }
};