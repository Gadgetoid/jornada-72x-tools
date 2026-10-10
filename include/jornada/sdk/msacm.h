#ifndef JORNADA_SDK_MSACM_H
#define JORNADA_SDK_MSACM_H


#ifdef __cplusplus
extern "C" {
#endif

struct tACMFILTERCHOOSE;
typedef struct tACMFILTERCHOOSE *LPACMFILTERCHOOSE;
MMRESULT acmFilterChoose(LPACMFILTERCHOOSE pafltrc);
struct tACMFILTERDETAILS;
typedef struct tACMFILTERDETAILS *LPACMFILTERDETAILS;
MMRESULT acmFilterDetails(HACMDRIVER had, LPACMFILTERDETAILS pafd, DWORD fdwDetails);
typedef BOOL (*ACMFILTERENUMCB)(HACMDRIVERID, LPACMFILTERDETAILS, DWORD, DWORD);
MMRESULT acmFilterEnum(HACMDRIVER had, LPACMFILTERDETAILS pafd, ACMFILTERENUMCB fnCallback, DWORD dwInstance, DWORD fdwEnum);
struct tACMFILTERTAGDETAILS;
typedef struct tACMFILTERTAGDETAILS *LPACMFILTERTAGDETAILS;
MMRESULT acmFilterTagDetails(HACMDRIVER had, LPACMFILTERTAGDETAILS paftd, DWORD fdwDetails);
typedef BOOL (*ACMFILTERTAGENUMCB)(HACMDRIVERID, LPACMFILTERTAGDETAILS, DWORD, DWORD);
MMRESULT acmFilterTagEnum(HACMDRIVER had, LPACMFILTERTAGDETAILS paftd, ACMFILTERTAGENUMCB fnCallback, DWORD dwInstance, DWORD fdwEnum);
struct tACMFORMATCHOOSE;
typedef struct tACMFORMATCHOOSE *LPACMFORMATCHOOSE;
MMRESULT acmFormatChoose(LPACMFORMATCHOOSE pafmtc);
typedef LRESULT (*ACMDRIVERPROC)(DWORD, HACMDRIVERID, UINT, LPARAM, LPARAM);
typedef struct tACMFILTERCHOOSE ACMFILTERCHOOSE;
typedef UINT (*ACMFILTERCHOOSEHOOKPROC)(HWND, UINT, WPARAM, LPARAM);
typedef struct tACMFILTERDETAILS ACMFILTERDETAILS;
typedef struct tACMFILTERTAGDETAILS ACMFILTERTAGDETAILS;
typedef struct tACMFORMATCHOOSE ACMFORMATCHOOSE;
typedef UINT (*ACMFORMATCHOOSEHOOKPROC)(HWND, UINT, WPARAM, LPARAM);
typedef ACMDRIVERPROC *LPACMDRIVERPROC;
struct tACMDRIVERDETAILS;
typedef struct tACMDRIVERDETAILS *PACMDRIVERDETAILS;
typedef struct tACMFILTERCHOOSE *PACMFILTERCHOOSE;
typedef struct tACMFILTERDETAILS *PACMFILTERDETAILS;
typedef struct tACMFILTERTAGDETAILS *PACMFILTERTAGDETAILS;
typedef struct tACMFORMATCHOOSE *PACMFORMATCHOOSE;
struct tACMFORMATDETAILS;
typedef struct tACMFORMATDETAILS *PACMFORMATDETAILS;
struct tACMFORMATTAGDETAILSW;
typedef struct tACMFORMATTAGDETAILSW *PACMFORMATTAGDETAILS;
struct tACMSTREAMHEADER;
typedef struct tACMSTREAMHEADER *PACMSTREAMHEADER;
struct tACMDRIVERDETAILS {
    DWORD cbStruct;
    FOURCC fccType;
    FOURCC fccComp;
    WORD wMid;
    WORD wPid;
    DWORD vdwACM;
    DWORD vdwDriver;
    DWORD fdwSupport;
    DWORD cFormatTags;
    DWORD cFilterTags;
    HICON hicon;
    WCHAR szShortName[32];
    WCHAR szLongName[128];
    WCHAR szCopyright[80];
    WCHAR szLicensing[128];
    WCHAR szFeatures[512];
} __attribute__((packed, aligned(1)));

struct tACMFILTERCHOOSE {
    DWORD cbStruct;
    DWORD fdwStyle;
    HWND hwndOwner;
    LPWAVEFILTER pwfltr;
    DWORD cbwfltr;
    LPCWSTR pszTitle;
    WCHAR szFilterTag[48];
    WCHAR szFilter[128];
    LPWSTR pszName;
    DWORD cchName;
    DWORD fdwEnum;
    LPWAVEFILTER pwfltrEnum;
    HINSTANCE hInstance;
    LPCWSTR pszTemplateName;
    LPARAM lCustData;
    ACMFILTERCHOOSEHOOKPROC pfnHook;
} __attribute__((packed, aligned(1)));

struct tACMFILTERDETAILS {
    DWORD cbStruct;
    DWORD dwFilterIndex;
    DWORD dwFilterTag;
    DWORD fdwSupport;
    LPWAVEFILTER pwfltr;
    DWORD cbwfltr;
    WCHAR szFilter[128];
} __attribute__((packed, aligned(1)));

struct tACMFILTERTAGDETAILS {
    DWORD cbStruct;
    DWORD dwFilterTagIndex;
    DWORD dwFilterTag;
    DWORD cbFilterSize;
    DWORD fdwSupport;
    DWORD cStandardFilters;
    WCHAR szFilterTag[48];
} __attribute__((packed, aligned(1)));

struct tACMFORMATCHOOSE {
    DWORD cbStruct;
    DWORD fdwStyle;
    HWND hwndOwner;
    LPWAVEFORMATEX pwfx;
    DWORD cbwfx;
    LPCWSTR pszTitle;
    WCHAR szFormatTag[48];
    WCHAR szFormat[128];
    LPWSTR pszName;
    DWORD cchName;
    DWORD fdwEnum;
    LPWAVEFORMATEX pwfxEnum;
    HINSTANCE hInstance;
    LPCWSTR pszTemplateName;
    LPARAM lCustData;
    ACMFORMATCHOOSEHOOKPROC pfnHook;
} __attribute__((packed, aligned(1)));

struct tACMFORMATDETAILS {
    DWORD cbStruct;
    DWORD dwFormatIndex;
    DWORD dwFormatTag;
    DWORD fdwSupport;
    LPWAVEFORMATEX pwfx;
    DWORD cbwfx;
    WCHAR szFormat[128];
} __attribute__((packed, aligned(1)));

struct tACMFORMATTAGDETAILSW {
    DWORD cbStruct;
    DWORD dwFormatTagIndex;
    DWORD dwFormatTag;
    DWORD cbFormatSize;
    DWORD fdwSupport;
    DWORD cStandardFormats;
    WCHAR szFormatTag[48];
} __attribute__((packed, aligned(1)));

struct tACMSTREAMHEADER {
    DWORD cbStruct;
    DWORD fdwStatus;
    DWORD dwUser;
    LPBYTE pbSrc;
    DWORD cbSrcLength;
    DWORD cbSrcLengthUsed;
    DWORD dwSrcUser;
    LPBYTE pbDst;
    DWORD cbDstLength;
    DWORD cbDstLengthUsed;
    DWORD dwDstUser;
    DWORD dwReservedDriver[10];
} __attribute__((packed, aligned(1)));


#ifdef __cplusplus
}
#endif

#endif
