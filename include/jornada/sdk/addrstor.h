#ifndef JORNADA_SDK_ADDRSTOR_H
#define JORNADA_SDK_ADDRSTOR_H

#include <jornada/sdk/addrmapi.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _AddressCard;
typedef struct _AddressCard AddressCard;
BOOL AddAddressCard(AddressCard *pac, CEOID *poidCard, int *pindex);
void CloseAddressBook(void);
BOOL CreateAddressBook(HHPRTAG *rghhProps, int numProps);
BOOL DeleteAddressCard(CEOID oidCard);
CEOID FindFirstEntry(TCHAR *szFind, HHPRTAG hhProp, int *pindex, DWORD dwFlags);
void FreeAddressCard(AddressCard *pac);
int GetAddressCardIndex(CEOID oidCard);
CEOID GetAddressCardOid(int nCard);
BOOL GetAddressCardProperties(CEOID oidCard, AddressCard *pac, int numRequestedProps, HHPRTAG *rghhProp);
BOOL GetColumnProperties(HHPRTAG *propList, int *pColumns);
BOOL GetMatchingEntry(TCHAR *szMatch, int *pBufSize, TCHAR *szField, CEOID *poidMatch, HHPRTAG *phhMatch);
int GetNumberOfAddressCards(void);
struct _PropertyDataStruct;
typedef struct _PropertyDataStruct PropertyDataStruct;
int GetPropertyDataStruct(int fFlag, ULONG uValue, PropertyDataStruct *ppds);
HHPRTAG GetSortOrder(BOOL fDatabaseSort);
BOOL ModifyAddressCard(AddressCard *pac, CEOID oidCard, int *pindex);
BOOL OpenAddressBook(HWND hwnd, HHPRTAG hhProp);
BOOL OpenAddressCard(CEOID oidCard, AddressCard *pac, ULONG uFlags);
void RecountCards(void);
BOOL SetColumnProperties(HHPRTAG *propList, int nColumns);
void SetMask(AddressCard *pac, HHPRTAG hhProp);
BOOL SetSortOrder(HHPRTAG hhProp);
struct _AddressCard {
    SYSTEMTIME stBirthday;
    SYSTEMTIME stAnniversary;
    TCHAR *pszBusinessFax;
    TCHAR *pszCompany;
    TCHAR *pszDepartment;
    TCHAR *pszEmail;
    TCHAR *pszMobilePhone;
    TCHAR *pszOfficeLocation;
    TCHAR *pszPager;
    TCHAR *pszWorkPhone;
    TCHAR *pszTitle;
    TCHAR *pszHomePhone;
    TCHAR *pszEmail2;
    TCHAR *pszSpouse;
    TCHAR *pszNotes;
    TCHAR *pszEmail3;
    TCHAR *pszHomePhone2;
    TCHAR *pszHomeFax;
    TCHAR *pszCarPhone;
    TCHAR *pszAssistant;
    TCHAR *pszAssistantPhone;
    TCHAR *pszChildren;
    TCHAR *pszCategory;
    TCHAR *pszWebPage;
    TCHAR *pszWorkPhone2;
    TCHAR *pszNamePrefix;
    TCHAR *pszGivenName;
    TCHAR *pszMiddleName;
    TCHAR *pszSurname;
    TCHAR *pszGeneration;
    TCHAR *pszHomeAddrStreet;
    TCHAR *pszHomeAddrCity;
    TCHAR *pszHomeAddrState;
    TCHAR *pszHomeAddrPostalCode;
    TCHAR *pszHomeAddrCountry;
    TCHAR *pszOtherAddrStreet;
    TCHAR *pszOtherAddrCity;
    TCHAR *pszOtherAddrState;
    TCHAR *pszOtherAddrPostalCode;
    TCHAR *pszOtherAddrCountry;
    TCHAR *pszOfficeAddrStreet;
    TCHAR *pszOfficeAddrCity;
    TCHAR *pszOfficeAddrState;
    TCHAR *pszOfficeAddrPostalCode;
    TCHAR *pszOfficeAddrCountry;
    BYTE rgbReserved[84];
};

struct _PropertyDataStruct {
    TCHAR *pszReserved;
    TCHAR *pszPropertyName;
    ULONG uPropType;
    HHPRTAG hhProp;
};


#ifdef __cplusplus
}
#endif

#endif
