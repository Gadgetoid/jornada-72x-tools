#ifndef JORNADA_EXTRAS_COMMCTRL_H
#define JORNADA_EXTRAS_COMMCTRL_H

#ifndef RC_INVOKED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Checks whether a message is meant for a command bar and, if so, processes
 * it.
 *
 * Undocumented in the Windows CE SDK. The SDK samples call it in the message
 * loop, like IsDialogMessage, and skip TranslateMessage and DispatchMessage
 * when it returns TRUE.
 *
 * @param hwndCB The command bar.
 * @param lpMsg The message from GetMessage.
 * @return TRUE if the message was processed, FALSE otherwise.
 */
BOOL WINAPI IsCommandBarMessage(HWND hwndCB, LPMSG lpMsg);
/**
 * Copies an image from one image list into an image in another, dithering
 * it.
 *
 * Undocumented in the Windows CE SDK.
 *
 * @param himlDst Destination image list.
 * @param iDst Index of the destination image.
 * @param xDst Horizontal offset within the destination image.
 * @param yDst Vertical offset within the destination image.
 * @param himlSrc Source image list.
 * @param iSrc Index of the source image.
 * @param fStyle Drawing style, ILD_*.
 */
void WINAPI ImageList_CopyDitherImage(HIMAGELIST himlDst, WORD iDst, int xDst, int yDst, HIMAGELIST himlSrc, int iSrc, UINT fStyle);
/**
 * Creates a colour bitmap of the given size.
 *
 * Undocumented in the Windows CE SDK. Kept in the CE 2.0 headers for
 * compatibility with CE 1.0.
 *
 * @param cx Width, in pixels.
 * @param cy Height, in pixels.
 * @return The bitmap, or NULL on failure. Free with DeleteObject.
 */
HBITMAP WINAPI CreateColorBitmap(int cx, int cy);
/**
 * Creates a monochrome bitmap of the given size.
 *
 * Undocumented in the Windows CE SDK. Kept in the CE 2.0 headers for
 * compatibility with CE 1.0.
 *
 * @param cx Width, in pixels.
 * @param cy Height, in pixels.
 * @return The bitmap, or NULL on failure. Free with DeleteObject.
 */
HBITMAP WINAPI CreateMonoBitmap(int cx, int cy);

#if JORNADA_CE == 1
typedef LV_KEYDOWN NMLVKEYDOWN, *LPNMLVKEYDOWN;
#endif
typedef TV_KEYDOWN NMTVKEYDOWN, *LPNMTVKEYDOWN;
typedef TC_KEYDOWN NMTCKEYDOWN;

#if JORNADA_CE >= 2

typedef struct tagNMKEY {
    NMHDR hdr;
    WORD wVKey;
    UINT flags;
} NMKEY, *LPNMKEY;

typedef struct tagNMTTCUSTOMDRAW {
    NMCUSTOMDRAW nmcd;
    UINT uDrawFlags;
} NMTTCUSTOMDRAW, *LPNMTTCUSTOMDRAW;

typedef struct tagNMDATETIMESTRINGW {
    NMHDR nmhdr;
    LPCWSTR pszUserString;
    SYSTEMTIME st;
    DWORD dwFlags;
} NMDATETIMESTRINGW, *LPNMDATETIMESTRINGW;

typedef struct tagNMDATETIMESTRINGA {
    NMHDR nmhdr;
    LPCSTR pszUserString;
    SYSTEMTIME st;
    DWORD dwFlags;
} NMDATETIMESTRINGA, *LPNMDATETIMESTRINGA;

typedef struct tagNMDATETIMEWMKEYDOWNW {
    NMHDR nmhdr;
    int nVirtKey;
    LPCWSTR pszFormat;
    SYSTEMTIME st;
} NMDATETIMEWMKEYDOWNW, *LPNMDATETIMEWMKEYDOWNW;

typedef struct tagNMDATETIMEWMKEYDOWNA {
    NMHDR nmhdr;
    int nVirtKey;
    LPCSTR pszFormat;
    SYSTEMTIME st;
} NMDATETIMEWMKEYDOWNA, *LPNMDATETIMEWMKEYDOWNA;

typedef struct tagNMDATETIMEFORMATW {
    NMHDR nmhdr;
    LPCWSTR pszFormat;
    SYSTEMTIME st;
    LPCWSTR pszDisplay;
    WCHAR szDisplay[64];
} NMDATETIMEFORMATW, *LPNMDATETIMEFORMATW;

typedef struct tagNMDATETIMEFORMATA {
    NMHDR nmhdr;
    LPCSTR pszFormat;
    SYSTEMTIME st;
    LPCSTR pszDisplay;
    CHAR szDisplay[64];
} NMDATETIMEFORMATA, *LPNMDATETIMEFORMATA;

typedef struct tagNMDATETIMEFORMATQUERYW {
    NMHDR nmhdr;
    LPCWSTR pszFormat;
    SIZE szMax;
} NMDATETIMEFORMATQUERYW, *LPNMDATETIMEFORMATQUERYW;

typedef struct tagNMDATETIMEFORMATQUERYA {
    NMHDR nmhdr;
    LPCSTR pszFormat;
    SIZE szMax;
} NMDATETIMEFORMATQUERYA, *LPNMDATETIMEFORMATQUERYA;

#endif

#define CommandBar_AddToolTips(hwndCB, cbToolTips, lpToolTipsStrings) \
    SendMessage((hwndCB), TB_SETTOOLTIPS, (WPARAM)(cbToolTips), (LPARAM)(lpToolTipsStrings))
#define LPHDITEM LPHDITEMW
#define LPLVCOLUMN LPLVCOLUMNW
#define NM_FINDITEM NMLVFINDITEM
#define PNM_FINDITEM LPNMLVFINDITEM
#define LPNM_FINDITEM LPNMLVFINDITEM

#if JORNADA_CE == 1
#define OVERLAYMASKTOINDEX(i) ((((i) >> 8) & (ILD_OVERLAYMASK >> 8)) - 1)
#define STATEIMAGEMASKTOINDEX(i) (((i) & LVIS_STATEIMAGEMASK) >> 12)
#define TabCtrl_GetBkColor(hwnd) (COLORREF)SendMessage((hwnd), TCM_GETBKCOLOR, 0, 0L)
#define TabCtrl_SetBkColor(hwnd, clrBk) (BOOL)SendMessage((hwnd), TCM_SETBKCOLOR, 0, (LPARAM)(COLORREF)(clrBk))
#define PropSheet_SetWizButtonsNow(hDlg, dwFlags) PropSheet_SetWizButtons(hDlg, dwFlags)
#else
#define CommandBands_IsVisible(hwndCmdBands) IsWindowVisible((hwndCmdBands))
#define Header_SetHotDivider(hwnd, fPos, dw) (int)SendMessage((hwnd), HDM_SETHOTDIVIDER, (WPARAM)(fPos), (LPARAM)(dw))
#define LPLVITEM LPLVITEMW
#define NMDATETIMESTRING NMDATETIMESTRINGW
#define LPNMDATETIMESTRING LPNMDATETIMESTRINGW
#define NMDATETIMEWMKEYDOWN NMDATETIMEWMKEYDOWNW
#define LPNMDATETIMEWMKEYDOWN LPNMDATETIMEWMKEYDOWNW
#define NMDATETIMEFORMAT NMDATETIMEFORMATW
#define LPNMDATETIMEFORMAT LPNMDATETIMEFORMATW
#define NMDATETIMEFORMATQUERY NMDATETIMEFORMATQUERYW
#define LPNMDATETIMEFORMATQUERY LPNMDATETIMEFORMATQUERYW
#define NM_ODSTATECHANGE NMLVODSTATECHANGE
#define PNM_ODSTATECHANGE LPNMLVODSTATECHANGE
#define LPNM_ODSTATECHANGE LPNMLVODSTATECHANGE
#endif

#ifdef __cplusplus
}
#endif

#endif

#endif
