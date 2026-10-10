#ifndef JORNADA_SDK_OLECTL_H
#define JORNADA_SDK_OLECTL_H

#include <jornada/sdk/oaidl.h>
#include <jornada/sdk/unknwn.h>
#include <jornada/sdk/wtypes.h>

#ifdef __cplusplus
extern "C" {
#endif

HRESULT DllRegisterServer(void);
HRESULT DllUnregisterServer(void);
struct tagFONTDESC;
typedef struct tagFONTDESC FONTDESC;
typedef struct tagFONTDESC *LPFONTDESC;
struct tagOCPFIPARAMS;
typedef struct tagOCPFIPARAMS *LPOCPFIPARAMS;
struct tagPICTDESC;
typedef struct tagPICTDESC *LPPICTDESC;
typedef struct tagOCPFIPARAMS OCPFIPARAMS;
typedef VARIANT_BOOL OLE_CANCELBOOL;
typedef VARIANT_BOOL OLE_ENABLEDEFAULTBOOL;
typedef VARIANT_BOOL OLE_OPTEXCLUSIVE;
typedef enum {
    triUnchecked = 0,
    triChecked = 1,
    triGray = 2
} OLE_TRISTATE;

typedef float OLE_XPOS_CONTAINER;
typedef long OLE_XPOS_PIXELS;
typedef float OLE_XSIZE_CONTAINER;
typedef long OLE_XSIZE_PIXELS;
typedef float OLE_YPOS_CONTAINER;
typedef long OLE_YPOS_PIXELS;
typedef float OLE_YSIZE_CONTAINER;
typedef long OLE_YSIZE_PIXELS;
typedef struct tagPICTDESC PICTDESC;
struct tagFONTDESC {
    UINT cbSizeofstruct;
    LPOLESTR lpstrName;
    CY cySize;
    SHORT sWeight;
    SHORT sCharset;
    BOOL fItalic;
    BOOL fUnderline;
    BOOL fStrikethrough;
} __attribute__((packed, aligned(8)));

struct tagOCPFIPARAMS {
    ULONG cbStructSize;
    HWND hWndOwner;
    int x;
    int y;
    LPCOLESTR lpszCaption;
    ULONG cObjects;
    LPUNKNOWN *lplpUnk;
    ULONG cPages;
    CLSID *lpPages;
    LCID lcid;
    DISPID dispidInitialProperty;
} __attribute__((packed, aligned(4)));

struct tagPICTDESC {
    UINT cbSizeofstruct;
    UINT picType;
    union {
        struct {
            HBITMAP hbitmap;
            HPALETTE hpal;
        } bmp;
        struct {
            HMETAFILE hmeta;
            int xExt;
            int yExt;
        } wmf;
        struct {
            HICON hicon;
        } icon;
        struct {
            HENHMETAFILE hemf;
        } emf;
    };
} __attribute__((packed, aligned(4)));


#ifdef __cplusplus
}
#endif

#endif
