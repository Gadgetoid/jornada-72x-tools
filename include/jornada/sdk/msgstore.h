#ifndef JORNADA_SDK_MSGSTORE_H
#define JORNADA_SDK_MSGSTORE_H


#ifdef __cplusplus
extern "C" {
#endif

BOOL MailClose(HANDLE hMail);
struct MailMsg_s;
typedef struct MailMsg_s MailMsg;
BOOL MailDelete(HANDLE hMail, MailMsg *pmm);
struct MailAtt_s;
typedef struct MailAtt_s MailAtt;
BOOL MailDeleteAttachment(HANDLE hMail, MailMsg *pmm, MailAtt *pma, BOOL fFullDelete);
int MailError(HANDLE hMail);
int MailErrorMsg(HANDLE hMail, LPWSTR szBuf, int iBufLen, int *piSrcLine);
BOOL MailFirst(HANDLE hMail, MailMsg *pmm);
BOOL MailFree(MailMsg *pmm);
BOOL MailGet(HANDLE hMail, MailMsg *pmm);
INT MailGetAttachment(HANDLE hMail, MailMsg *pmm, MailAtt *pma);
LPWSTR MailGetField(MailMsg *pmm, LPWSTR szName, BOOL fGetName);
BOOL MailGetFolderId(HANDLE hMail, BYTE *pbId, LPWSTR szName);
BOOL MailGetFolderName(HANDLE hMail, int *piId, int *piLen, LPWSTR szName);
struct _MAILSORTINFO;
typedef struct _MAILSORTINFO *PMAILSORTINFO;
BOOL MailGetSort(HANDLE hMail, PMAILSORTINFO pInfo);
BOOL MailGetSvcId(HANDLE hMail, MailMsg *pmm);
DWORD MailHeaderLen(MailMsg *pmm);
DWORD MailLocalAttachmentLen(HANDLE hMail, MailMsg *pmm);
BOOL MailNext(HANDLE hMail, MailMsg *pmm);
BOOL MailOpen(HANDLE *phMail, BOOL fAllowCreate);
BOOL MailOpenNotify(HANDLE *phMail, BOOL fAllowCreate, HWND hwndNotify);
BOOL MailPut(HANDLE hMail, MailMsg *pmm);
BOOL MailPutAttachment(HANDLE hMail, MailMsg *pmm, MailAtt *pma);
BOOL MailPutFolder(HANDLE hMail, BYTE bId, LPWSTR szName);
BOOL MailReadNonIPMProperties(HANDLE hMail, MailMsg *pmm, CEPROPVAL **ppPropVal, WORD *pcPropVal);
LONG MailRegCloseKey(HKEY hKey);
LONG MailRegEnumKeyExW(HKEY hKey, DWORD dwIndex, LPWSTR lpName, LPDWORD lpcbName, LPDWORD lpReserved, LPWSTR lpClass, LPDWORD lpcbClass, PFILETIME lpftLastWriteTime);
LONG MailRegOpenKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult);
BOOL MailRequestAttachment(HANDLE hMail, MailMsg *pmm, MailAtt *pma, BOOL bRetrieve);
BOOL MailSetAttachmentOptions(HANDLE hMail, MailMsg *pmm, DWORD dwFlags);
BOOL MailSetField(MailMsg *pmm, LPWSTR szName, LPCWSTR szVal);
typedef enum {
    MAIL_SORT_FROM,
    MAIL_SORT_SUBJ,
    MAIL_SORT_DATE,
    MAIL_SORT_SIZE
} MAILSORTFIELD;

BOOL MailSetSort(HANDLE hMail, MAILSORTFIELD iSort, BOOL fAscending);
BOOL MailUpdate(HANDLE hMail, MailMsg *pmm, BOOL fDoAll);
BOOL MailWriteNonIPMProperties(HANDLE hMail, MailMsg *pmm, CEPROPVAL *pPropVal, UINT cPropVal);
struct MailNonIpmInfo_s;
typedef struct MailNonIpmInfo_s MailNonIpmInfo;
struct MailAttArray_s;
typedef struct MailAttArray_s MailAttArray;
typedef struct _MAILSORTINFO MAILSORTINFO;
typedef DWORD (*PMAILATTACHMENTLEN)(HANDLE, MailMsg *);
typedef BOOL (*PMAILCLOSE)(HANDLE);
typedef BOOL (*PMAILDELETE)(HANDLE, MailMsg *);
typedef BOOL (*PMAILDELETEATTACHMENT)(HANDLE, MailMsg *, MailAtt *, BOOL);
typedef int (*PMAILERROR)(HANDLE);
typedef int (*PMAILERRORMSG)(HANDLE, LPWSTR, int, int *);
typedef BOOL (*PMAILFIRST)(HANDLE, MailMsg *);
typedef BOOL (*PMAILFREE)(MailMsg *);
typedef BOOL (*PMAILGET)(HANDLE, MailMsg *);
typedef UINT (*PMAILGETATTACHMENT)(HANDLE, MailMsg *, MailAtt *);
typedef LPWSTR (*PMAILGETFIELD)(MailMsg *, LPWSTR, BOOL);
typedef BOOL (*PMAILGETFOLDERID)(HANDLE, BYTE *, LPWSTR);
typedef BOOL (*PMAILGETFOLDERNAME)(HANDLE, int *, int *, LPWSTR);
typedef BOOL (*PMAILGETSORT)(HANDLE, MAILSORTFIELD *, BOOL *);
typedef BOOL (*PMAILGETSVCID)(HANDLE, MailMsg *);
typedef DWORD (*PMAILHEADERLEN)(MailMsg *);
typedef BOOL (*PMAILNEXT)(HANDLE, MailMsg *);
typedef BOOL (*PMAILOPEN)(HANDLE *, BOOL);
typedef BOOL (*PMAILPUT)(HANDLE, MailMsg *);
typedef BOOL (*PMAILPUTATTACHMENT)(HANDLE, MailMsg *, MailAtt *);
typedef BOOL (*PMAILPUTFOLDER)(HANDLE, BYTE, LPWSTR);
typedef BOOL (*PMAILREADNONIPMPROPERTIES)(HANDLE, MailMsg *, CEPROPVAL **, WORD *);
typedef LONG (*PMAILREGCLOSEKEY)(HKEY);
typedef LONG (*PMAILREGENUMKEYEXW)(HKEY, DWORD, LPWSTR, LPDWORD, LPDWORD, LPWSTR, LPDWORD, PFILETIME);
typedef LONG (*PMAILREGOPENKEYEXW)(HKEY, LPCWSTR, DWORD, REGSAM, PHKEY);
typedef BOOL (*PMAILREQUESTATTACHMENT)(HANDLE, MailMsg *, MailAtt *, BOOL);
typedef BOOL (*PMAILSETATTACHMENTOPTIONS)(HANDLE, MailMsg *, DWORD);
typedef BOOL (*PMAILSETFIELD)(MailMsg *, LPWSTR, LPCWSTR);
typedef BOOL (*PMAILSETSORT)(HANDLE, MAILSORTFIELD, BOOL);
typedef BOOL (*PMAILUPDATE)(HANDLE, MailMsg *, BOOL);
typedef BOOL (*PMAILWRITENONIPMPROPERTIES)(HANDLE, MailMsg *, CEPROPVAL *, UINT);
typedef struct MailAtt_s *lpMailAtt;
typedef struct MailAttArray_s *lpMailAttArray;
typedef struct MailNonIpmInfo_s *lpMailNonIpmInfo;
struct MailAttArray_s {
    DWORD dwFlags;
    UINT uiAttCount;
    lpMailAtt AttArray[];
};

struct MailAtt_s {
    UINT uiAttachmentNumber;
    DWORD dwFlags;
    ULONG ulCharacterPosition;
    ULONG ulSize;
    LPWSTR szOriginalName;
    LPWSTR szLocalName;
};

struct MailMsg_s {
    DWORD dwMsgId;
    DWORD dwFlags;
    DWORD dwMsgLen;
    WORD wBodyLen;
    FILETIME ftDate;
    LPWSTR szSvcId;
    LPWSTR szSvcNam;
    WCHAR *pwcHeaders;
    LPWSTR szBody;
    CEOID oid;
    HANDLE hHeap;
};

struct MailNonIpmInfo_s {
    LPWSTR szMessageClass;
    UINT uiPropCount;
    CEPROPVAL propArray[];
};

struct _MAILSORTINFO {
    MAILSORTFIELD iSort;
    BOOL fAscending;
    int cMsgs;
};


#ifdef __cplusplus
}
#endif

#endif
