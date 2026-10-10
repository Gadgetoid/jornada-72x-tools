#ifndef JORNADA_SDK_IMGDECMP_H
#define JORNADA_SDK_IMGDECMP_H

#include <jornada/sdk/imgrendr.h>

#ifdef __cplusplus
extern "C" {
#endif

struct tagDecompressImageInfo;
typedef struct tagDecompressImageInfo DecompressImageInfo;
HRESULT DecompressImageIndirect(DecompressImageInfo *pParams);
COLORREF * Get332Palette(void);
COLORREF * GetHalftonePalette(void);
COLORREF GetTransparentColor(void);
typedef DWORD (*GETDATAFUNC)(LPSTR, DWORD, LPARAM);
typedef void (*PROGRESSFUNC)(IImageRender *, BOOL, LPARAM);
struct tagDecompressImageInfo {
    DWORD dwSize;
    LPBYTE pbBuffer;
    DWORD dwBufferMax;
    DWORD dwBufferCurrent;
    HBITMAP *phBM;
    IImageRender **ppImageRender;
    int iBitDepth;
    LPARAM lParam;
    HDC hdc;
    int iScale;
    int iMaxWidth;
    int iMaxHeight;
    GETDATAFUNC pfnGetData;
    PROGRESSFUNC pfnImageProgress;
    COLORREF crTransparentOverride;
};


#ifdef __cplusplus
}
#endif

#endif
