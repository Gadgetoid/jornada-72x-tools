#ifndef JORNADA_SDK_IMM_H
#define JORNADA_SDK_IMM_H


#ifdef __cplusplus
extern "C" {
#endif

BOOL ImmAssociateContextEx(HWND, HIMC, DWORD);
HIMCC ImmCreateIMCC(DWORD);
HIMCC ImmDestroyIMCC(HIMCC);
BOOL ImmGenerateMessage(HIMC);
BOOL ImmGetHotKey(DWORD, LPUINT lpuModifiers, LPUINT lpuVKey, LPHKL);
DWORD ImmGetIMCCLockCount(HIMCC);
DWORD ImmGetIMCCSize(HIMCC);
DWORD ImmGetIMCLockCount(HIMC);
struct tagINPUTCONTEXT;
typedef struct tagINPUTCONTEXT *LPINPUTCONTEXT;
LPINPUTCONTEXT ImmLockIMC(HIMC);
LPVOID ImmLockIMCC(HIMCC);
HIMCC ImmReSizeIMCC(HIMCC, DWORD);
LRESULT ImmRequestMessageW(HIMC, WPARAM, LPARAM);
BOOL ImmSIPanelState(UINT dwCmd, LPVOID pValue);
BOOL ImmSetHotKey(DWORD, UINT, UINT, HKL);
BOOL ImmUnlockIMC(HIMC);
BOOL ImmUnlockIMCC(HIMCC);
struct tagCANDIDATEINFO;
typedef struct tagCANDIDATEINFO CANDIDATEINFO;
struct tagCOMPOSITIONSTRING;
typedef struct tagCOMPOSITIONSTRING COMPOSITIONSTRING;
struct tagGUIDELINE;
typedef struct tagGUIDELINE GUIDELINE;
struct _tagHWXRESULT;
typedef struct _tagHWXRESULT HWXRESULT;
struct tagIMEINFO;
typedef struct tagIMEINFO IMEINFO;
typedef struct tagINPUTCONTEXT INPUTCONTEXT;
typedef struct tagCANDIDATEINFO *LPCANDIDATEINFO;
typedef struct tagCOMPOSITIONSTRING *LPCOMPOSITIONSTRING;
typedef struct tagGUIDELINE *LPGUIDELINE;
typedef struct tagIMECHARPOSITION *LPIMECHARPOSITION;
typedef struct tagIMEINFO *LPIMEINFO;
typedef struct tagRECONVERTSTRING *LPRECONVERTSTRING;
struct tagSOFTKBDDATA;
typedef struct tagSOFTKBDDATA *LPSOFTKBDDATA;
struct _MYCANDLIST;
typedef struct _MYCANDLIST MYCANDLIST;
typedef struct tagCANDIDATEFORM *NPCANDIDATEFORM;
typedef struct tagCANDIDATEINFO *NPCANDIDATEINFO;
typedef struct tagCANDIDATELIST *NPCANDIDATELIST;
typedef struct tagCOMPOSITIONFORM *NPCOMPOSITIONFORM;
typedef struct tagCOMPOSITIONSTRING *NPCOMPOSITIONSTRING;
typedef struct tagGUIDELINE *NPGUIDELINE;
typedef struct tagIMECHARPOSITION *NPIMECHARPOSITION;
typedef struct tagIMEINFO *NPIMEINFO;
typedef struct tagIMEMENUITEMINFOW *NPIMEMENUITEMINFOW;
typedef NPIMEMENUITEMINFOW NPIMEMENUITEMINFO;
typedef struct tagIMEMENUITEMINFOA *NPIMEMENUITEMINFOA;
typedef struct tagINPUTCONTEXT *NPINPUTCONTEXT;
typedef struct tagRECONVERTSTRING *NPRECONVERTSTRING;
typedef struct tagREGISTERWORDW *NPREGISTERWORDW;
typedef NPREGISTERWORDW NPREGISTERWORD;
typedef struct tagREGISTERWORDA *NPREGISTERWORDA;
typedef struct tagSOFTKBDDATA *NPSOFTKBDDATA;
typedef struct tagSTYLEBUFW *NPSTYLEBUFW;
typedef NPSTYLEBUFW NPSTYLEBUF;
typedef struct tagSTYLEBUFA *NPSTYLEBUFA;
typedef struct tagCANDIDATEINFO *PCANDIDATEINFO;
typedef struct tagCOMPOSITIONSTRING *PCOMPOSITIONSTRING;
typedef struct tagGUIDELINE *PGUIDELINE;
typedef struct _tagHWXRESULT *PHWXRESULT;
typedef struct tagIMEINFO *PIMEINFO;
typedef struct tagINPUTCONTEXT *PINPUTCONTEXT;
typedef struct tagSOFTKBDDATA *PSOFTKBDDATA;
typedef struct tagSOFTKBDDATA SOFTKBDDATA;
struct _MYCANDLIST {
    HWND ParentWnd;
    LPCANDIDATELIST CandList;
};

struct _tagHWXRESULT {
    WORD cbCount;
    WORD iSelection;
    WORD iPosition;
    TCHAR chCandidate[1];
};

struct tagCANDIDATEINFO {
    DWORD dwSize;
    DWORD dwCount;
    DWORD dwOffset[32];
    DWORD dwPrivateSize;
    DWORD dwPrivateOffset;
};

struct tagCOMPOSITIONSTRING {
    DWORD dwSize;
    DWORD dwCompReadAttrLen;
    DWORD dwCompReadAttrOffset;
    DWORD dwCompReadClauseLen;
    DWORD dwCompReadClauseOffset;
    DWORD dwCompReadStrLen;
    DWORD dwCompReadStrOffset;
    DWORD dwCompAttrLen;
    DWORD dwCompAttrOffset;
    DWORD dwCompClauseLen;
    DWORD dwCompClauseOffset;
    DWORD dwCompStrLen;
    DWORD dwCompStrOffset;
    DWORD dwCursorPos;
    DWORD dwDeltaStart;
    DWORD dwResultReadClauseLen;
    DWORD dwResultReadClauseOffset;
    DWORD dwResultReadStrLen;
    DWORD dwResultReadStrOffset;
    DWORD dwResultClauseLen;
    DWORD dwResultClauseOffset;
    DWORD dwResultStrLen;
    DWORD dwResultStrOffset;
    DWORD dwPrivateSize;
    DWORD dwPrivateOffset;
};

struct tagGUIDELINE {
    DWORD dwSize;
    DWORD dwLevel;
    DWORD dwIndex;
    DWORD dwStrLen;
    DWORD dwStrOffset;
    DWORD dwPrivateSize;
    DWORD dwPrivateOffset;
};

struct tagIMEINFO {
    DWORD dwPrivateDataSize;
    DWORD fdwProperty;
    DWORD fdwConversionCaps;
    DWORD fdwSentenceCaps;
    DWORD fdwUICaps;
    DWORD fdwSCSCaps;
    DWORD fdwSelectCaps;
};

struct tagINPUTCONTEXT {
    HWND hWnd;
    BOOL fOpen;
    DWORD fdwClient;
    HWND hwndImeInUse;
    POINT ptStatusWndPos;
    POINT ptSoftKbdPos;
    DWORD fdwConversion;
    DWORD fdwSentence;
    union {
        LOGFONTA A;
        LOGFONTW W;
    } lfFont;
    COMPOSITIONFORM cfCompForm;
    CANDIDATEFORM cfCandForm[4];
    HIMCC hCompStr;
    HIMCC hCandInfo;
    HIMCC hGuideLine;
    HIMCC hPrivate;
    DWORD dwNumMsgBuf;
    HIMCC hMsgBuf;
    DWORD fdwInit;
    DWORD dwReserve[3];
    UINT uSavedVKey;
    BOOL fChgMsg;
    DWORD fdwFlags;
    DWORD fdw31Compat;
    DWORD dwRefCount;
};

struct tagSOFTKBDDATA {
    UINT uCount;
    WORD wCode[1][256];
};


#ifdef __cplusplus
}
#endif

#endif
