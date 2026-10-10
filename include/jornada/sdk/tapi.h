#ifndef JORNADA_SDK_TAPI_H
#define JORNADA_SDK_TAPI_H

#include <ras.h>

#ifdef __cplusplus
extern "C" {
#endif

struct HCALL__;
typedef const struct HCALL__ *HCALL;
LONG lineAccept(HCALL hCall, LPCSTR lpsUserUserInfo, DWORD dwSize);
/**
 * Installs a telephony service provider.
 *
 * TAPI calls the provider's TSPI_lineGetProcTable export to retrieve its
 * function table; the provider need export only that entry point.
 *
 * @param lpszProviderFilename Path to the provider.
 * @param hwndOwner Owner window for installation dialogs, or NULL.
 * @param lpdwPermanentProviderID Receives the provider ID, or NULL.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineAddProvider(LPCWSTR lpszProviderFilename, HWND hwndOwner, LPDWORD lpdwPermanentProviderID);
LONG lineAddToConference(HCALL hConfCall, HCALL hConsultCall);
LONG lineAnswer(HCALL hCall, LPCSTR lpsUserUserInfo, DWORD dwSize);
LONG lineBlindTransfer(HCALL hCall, LPCWSTR lpszDestAddressW, DWORD dwCountryCode);
struct HLINE__;
typedef const struct HLINE__ *HLINE;
/**
 * Closes an open line device and invalidates its handle.
 *
 * Close or drop calls owned on the line first. Closing can revoke
 * ownership and drop calls that the application owns.
 *
 * @param hLine Open line handle to close.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineClose(HLINE hLine);
typedef HCALL *LPHCALL;
LONG lineCompleteTransfer(HCALL hCall, HCALL hConsultCall, LPHCALL lphConfCall, DWORD dwTransferMode);
/**
 * Displays the provider's configuration dialog and returns edited settings.
 *
 * The opaque output can be passed to lineSetDevConfig. Set dwTotalSize in
 * lpDeviceConfigOut before the call; on LINEERR_STRUCTURETOOSMALL,
 * dwNeededSize reports the required size. Editing does not affect active
 * connections by itself.
 *
 * @param dwDeviceID Line device to configure.
 * @param hwndOwner Owner window for the dialog, or NULL.
 * @param lpszDeviceClass Device class to configure, or NULL for the top level.
 * @param lpDeviceConfigIn Existing opaque configuration data.
 * @param dwSize Size of lpDeviceConfigIn in bytes.
 * @param lpDeviceConfigOut Receives the edited configuration.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineConfigDialogEdit(DWORD dwDeviceID, HWND hwndOwner, LPCWSTR lpszDeviceClass, const LPVOID lpDeviceConfigIn, DWORD dwSize, LPVARSTRING lpDeviceConfigOut);
/**
 * Releases the application's handle and resources for a call.
 *
 * This does not change the physical call state. Deallocating the handle
 * also stops further LINE_REPLY processing for that call.
 *
 * @param hCall Call handle to release.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineDeallocateCall(HCALL hCall);
LONG lineDevSpecific(HLINE hLine, DWORD dwAddressID, HCALL hCall, LPVOID lpParams, DWORD dwSize);
LONG lineDial(HCALL hCall, LPCWSTR lpszDestAddress, DWORD dwCountryCode);
/**
 * Drops or rejects a call owned by the application.
 *
 * Optionally sends user-to-user data during disconnect. The network is
 * not guaranteed to deliver that data. Dropping a conference call can
 * also affect its related calls.
 *
 * @param hCall Call to drop; it cannot be idle.
 * @param lpsUserUserInfo Optional data to send, or NULL.
 * @param dwSize Size of the user-user data in bytes.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineDrop(HCALL hCall, LPCSTR lpsUserUserInfo, DWORD dwSize);
struct lineforwardlist_tag;
typedef struct lineforwardlist_tag *LPLINEFORWARDLIST;
struct linecallparams_tag;
typedef struct linecallparams_tag *LPLINECALLPARAMS;
LONG lineForward(HLINE hLine, DWORD bAllAddresses, DWORD dwAddressID, const LPLINEFORWARDLIST lpForwardList, DWORD dwNumRingsNoAnswer, LPHCALL lphConsultCall, const LPLINECALLPARAMS lpCallParams);
LONG lineGenerateDigits(HCALL hCall, DWORD dwDigitMode, LPCWSTR lpszDigits, DWORD dwDuration);
struct linegeneratetone_tag;
typedef struct linegeneratetone_tag *LPLINEGENERATETONE;
LONG lineGenerateTone(HCALL hCall, DWORD dwToneMode, DWORD dwDuration, DWORD dwNumTones, const LPLINEGENERATETONE lpTones);
struct HLINEAPP__;
typedef const struct HLINEAPP__ *HLINEAPP;
struct lineaddresscaps_tag;
typedef struct lineaddresscaps_tag *LPLINEADDRESSCAPS;
LONG lineGetAddressCaps(HLINEAPP hLineApp, DWORD dwDeviceID, DWORD dwAddressID, DWORD dwAPIVersion, DWORD dwExtVersion, LPLINEADDRESSCAPS lpAddressCaps);
LONG lineGetAddressID(HLINE hLine, LPDWORD lpdwAddressID, DWORD dwAddressMode, LPCWSTR lpsAddress, DWORD dwSize);
struct lineaddressstatus_tag;
typedef struct lineaddressstatus_tag *LPLINEADDRESSSTATUS;
LONG lineGetAddressStatus(HLINE hLine, DWORD dwAddressID, LPLINEADDRESSSTATUS lpAddressStatus);
struct lineextensionid_tag;
typedef struct lineextensionid_tag *LPLINEEXTENSIONID;
LONG lineGetAppPriority(LPCWSTR lpszAppFilename, DWORD dwMediaMode, LPLINEEXTENSIONID lpExtensionID, DWORD dwRequestMode, LPVARSTRING lpExtensionName, LPDWORD lpdwPriority);
struct linecallinfo_tag;
typedef struct linecallinfo_tag *LPLINECALLINFO;
LONG lineGetCallInfo(HCALL hCall, LPLINECALLINFO lpCallInfo);
struct linecallstatus_tag;
typedef struct linecallstatus_tag *LPLINECALLSTATUS;
LONG lineGetCallStatus(HCALL hCall, LPLINECALLSTATUS lpCallStatus);
struct linecalllist_tag;
typedef struct linecalllist_tag *LPLINECALLLIST;
LONG lineGetConfRelatedCalls(HCALL hCall, LPLINECALLLIST lpCallList);
struct linedevcaps_tag;
typedef struct linedevcaps_tag *LPLINEDEVCAPS;
/**
 * Retrieves the capabilities of a line device.
 *
 * Negotiate the TAPI version first. dwExtVersion is unsupported and must
 * be zero. Set dwTotalSize in lpLineDevCaps before calling; use the
 * returned address count to query each address with lineGetAddressCaps.
 *
 * @param hLineApp TAPI application handle.
 * @param dwDeviceID Line device identifier.
 * @param dwAPIVersion Negotiated TAPI version.
 * @param dwExtVersion Set to zero.
 * @param lpLineDevCaps Receives capabilities; set dwTotalSize first.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineGetDevCaps(HLINEAPP hLineApp, DWORD dwDeviceID, DWORD dwAPIVersion, DWORD dwExtVersion, LPLINEDEVCAPS lpLineDevCaps);
/**
 * Retrieves the default opaque configuration for a line device.
 *
 * CE returns a default configuration. Treat the data as opaque: do not
 * modify it, and use lineSetDevConfig to restore it. Set dwTotalSize in
 * the VARSTRING before calling.
 *
 * @param dwDeviceID Line device identifier.
 * @param lpDeviceConfig Receives configuration in a VARSTRING.
 * @param lpszDeviceClass Device class whose configuration is requested.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineGetDevConfig(DWORD dwDeviceID, LPVARSTRING lpDeviceConfig, LPCWSTR lpszDeviceClass);
/**
 * Retrieves a line, address or call's device identifier for a device class.
 *
 * Set exactly one LINECALLSELECT_* flag in dwSelect and initialize the
 * output VARSTRING's dwTotalSize before calling.
 *
 * @param hLine Line handle when selecting a line or address.
 * @param dwAddressID Address identifier when selecting an address.
 * @param hCall Call handle when selecting a call.
 * @param dwSelect LINECALLSELECT_LINE, LINECALLSELECT_ADDRESS or LINECALLSELECT_CALL.
 * @param lpDeviceID Receives the device identifier in a VARSTRING.
 * @param lpszDeviceClass Device class name.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineGetID(HLINE hLine, DWORD dwAddressID, HCALL hCall, DWORD dwSelect, LPVARSTRING lpDeviceID, LPCWSTR lpszDeviceClass);
typedef HICON *LPHICON;
LONG lineGetIcon(DWORD dwDeviceID, LPCWSTR lpszDeviceClass, LPHICON lphIcon);
struct linedevstatus_tag;
typedef struct linedevstatus_tag *LPLINEDEVSTATUS;
LONG lineGetLineDevStatus(HLINE hLine, LPLINEDEVSTATUS lpLineDevStatus);
struct linemessage_tag;
typedef struct linemessage_tag *LPLINEMESSAGE;
LONG lineGetMessage(HLINEAPP hLineApp, LPLINEMESSAGE lpMessage, DWORD dwTimeout);
LONG lineGetNewCalls(HLINE hLine, DWORD dwAddressID, DWORD dwSelect, LPLINECALLLIST lpCallList);
LONG lineGetNumRings(HLINE hLine, DWORD dwAddressID, LPDWORD lpdwNumRings);
struct lineproviderlist_tag;
typedef struct lineproviderlist_tag *LPLINEPROVIDERLIST;
LONG lineGetProviderList(DWORD dwAPIVersion, LPLINEPROVIDERLIST lpProviderList);
LONG lineGetStatusMessages(HLINE hLine, LPDWORD lpdwLineStates, LPDWORD lpdwAddressStates);
struct linetranslatecaps_tag;
typedef struct linetranslatecaps_tag *LPLINETRANSLATECAPS;
LONG lineGetTranslateCaps(HLINEAPP hLineApp, DWORD dwAPIVersion, LPLINETRANSLATECAPS lpTranslateCaps);
LONG lineHandoff(HCALL hCall, LPCWSTR lpszFileName, DWORD dwMediaMode);
LONG lineHold(HCALL hCall);
typedef HLINEAPP *LPHLINEAPP;
typedef void (*LINECALLBACK)(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
/**
 * Initializes TAPI and registers the application's callback.
 *
 * The callback receives line, address and call events. TAPI messages go
 * directly to this callback, so a UI thread must not block in GetMessage
 * waiting for a TAPI message; use Sleep(50) followed by PeekMessage.
 * Call lineShutdown when the application no longer uses TAPI.
 *
 * @param lphLineApp Receives the TAPI application handle.
 * @param hInstance Application or DLL instance.
 * @param lpfnCallback Callback for TAPI events.
 * @param lpszAppName Optional displayable ASCII application name, or NULL.
 * @param lpdwNumDevs Receives the number of line devices.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineInitialize(LPHLINEAPP lphLineApp, HINSTANCE hInstance, LINECALLBACK lpfnCallback, LPCWSTR lpszAppName, LPDWORD lpdwNumDevs);
struct lineinitializeexparams_tag;
typedef struct lineinitializeexparams_tag *LPLINEINITIALIZEEXPARAMS;
LONG lineInitializeEx(LPHLINEAPP lphLineApp, HINSTANCE hInstance, LINECALLBACK lpfnCallback, LPCWSTR lpszFriendlyAppName, LPDWORD lpdwNumDevs, LPDWORD lpdwAPIVersion, LPLINEINITIALIZEEXPARAMS lpLineInitializeExParams);
/**
 * Starts a call on a line to a destination address.
 *
 * The request is asynchronous. The call handle is valid after a successful
 * LINE_REPLY. With NULL lpCallParams, TAPI uses default voice-call
 * parameters. The address may be NULL for a non-dialed line.
 *
 * @param hLine Open line on which to place the call.
 * @param lphCall Receives the call handle after successful completion.
 * @param lpszDestAddress Dialable destination, or NULL for a non-dialed address.
 * @param dwCountryCode Destination country code, or 0 for the default.
 * @param lpCallParams Optional call setup parameters, or NULL for defaults.
 * @return Positive request ID for asynchronous completion, or a negative
 *         LINEERR_* code.
 */
LONG lineMakeCall(HLINE hLine, LPHCALL lphCall, LPCWSTR lpszDestAddress, DWORD dwCountryCode, const LPLINECALLPARAMS lpCallParams);
LONG lineMonitorDigits(HCALL hCall, DWORD dwDigitModes);
LONG lineMonitorMedia(HCALL hCall, DWORD dwMediaModes);
/**
 * Negotiates a TAPI version supported by the application and line device.
 *
 * The selected version is within the requested range. Extensions are not
 * supported; set lpExtensionID to NULL.
 *
 * @param hLineApp TAPI application handle.
 * @param dwDeviceID Line device identifier.
 * @param dwAPILowVersion Lowest supported TAPI version.
 * @param dwAPIHighVersion Highest supported TAPI version.
 * @param lpdwAPIVersion Receives the negotiated version.
 * @param lpExtensionID Ignored; set to NULL.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineNegotiateAPIVersion(HLINEAPP hLineApp, DWORD dwDeviceID, DWORD dwAPILowVersion, DWORD dwAPIHighVersion, LPDWORD lpdwAPIVersion, LPLINEEXTENSIONID lpExtensionID);
LONG lineNegotiateExtVersion(HLINEAPP hLineApp, DWORD dwDeviceID, DWORD dwAPIVersion, DWORD dwExtLowVersion, DWORD dwExtHighVersion, LPDWORD lpdwExtVersion);
typedef HLINE *LPHLINE;
/**
 * Opens a line device and returns a handle for later line operations.
 *
 * Set dwExtVersion to zero. dwPrivileges selects outgoing-call-only,
 * monitor, owner, or monitor-and-owner access. dwMediaModes applies when
 * owner privilege is requested.
 *
 * @param hLineApp TAPI application handle.
 * @param dwDeviceID Line device identifier.
 * @param lphLine Receives the open line handle.
 * @param dwAPIVersion Version negotiated with lineNegotiateAPIVersion.
 * @param dwExtVersion Set to zero.
 * @param dwCallbackInstance Application data returned with TAPI messages.
 * @param dwPrivileges LINECALLPRIVILEGE_* access for calls.
 * @param dwMediaModes Media types the application can own.
 * @param lpCallParams Optional call parameters.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineOpen(HLINEAPP hLineApp, DWORD dwDeviceID, LPHLINE lphLine, DWORD dwAPIVersion, DWORD dwExtVersion, DWORD dwCallbackInstance, DWORD dwPrivileges, DWORD dwMediaModes, const LPLINECALLPARAMS lpCallParams);
LONG linePickup(HLINE hLine, DWORD dwAddressID, LPHCALL lphCall, LPCWSTR lpszDestAddress, LPCWSTR lpszGroupID);
LONG linePrepareAddToConference(HCALL hConfCall, LPHCALL lphConsultCall, const LPLINECALLPARAMS lpCallParams);
LONG lineRedirect(HCALL hCall, LPCWSTR lpszDestAddress, DWORD dwCountryCode);
LONG lineReleaseUserUserInfo(HCALL hCall);
LONG lineRemoveFromConference(HCALL hCall);
LONG lineSendUserUserInfo(HCALL hCall, LPCSTR lpsUserUserInfo, DWORD dwSize);
LONG lineSetAppPriority(LPCWSTR lpszAppFilename, DWORD dwMediaMode, LPLINEEXTENSIONID lpExtensionID, DWORD dwRequestMode, LPCWSTR lpszExtensionName, DWORD dwPriority);
struct linedialparams_tag;
typedef struct linedialparams_tag *LPLINEDIALPARAMS;
LONG lineSetCallParams(HCALL hCall, DWORD dwBearerMode, DWORD dwMinRate, DWORD dwMaxRate, const LPLINEDIALPARAMS lpDialParams);
LONG lineSetCallPrivilege(HCALL hCall, DWORD dwCallPrivilege);
/**
 * Sets the current location used for address translation.
 *
 * dwLocation must be a permanent location ID returned by
 * lineGetTranslateCaps.
 *
 * @param hLineApp TAPI application handle, or NULL before initialization.
 * @param dwLocation Permanent location ID.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineSetCurrentLocation(HLINEAPP hLineApp, DWORD dwLocation);
/**
 * Applies opaque line-device configuration obtained with lineGetDevConfig.
 *
 * Do not inspect or modify the configuration data. It is generally valid
 * only for the device from which it was obtained.
 *
 * @param dwDeviceID Line device identifier.
 * @param lpDeviceConfig Opaque configuration data.
 * @param dwSize Configuration size in bytes.
 * @param lpszDeviceClass Device class name.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineSetDevConfig(DWORD dwDeviceID, const LPVOID lpDeviceConfig, DWORD dwSize, LPCWSTR lpszDeviceClass);
LONG lineSetMediaMode(HCALL hCall, DWORD dwMediaModes);
LONG lineSetNumRings(HLINE hLine, DWORD dwAddressID, DWORD dwNumRings);
/**
 * Selects line and address status changes reported to the application.
 *
 * Reporting is disabled by default. LINEDEVSTATE_REINIT notifications
 * cannot be masked.
 *
 * @param hLine Line device handle.
 * @param dwLineStates LINEDEVSTATE_* notifications to enable.
 * @param dwAddressStates LINEADDRESSSTATE_* notifications to enable.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineSetStatusMessages(HLINE hLine, DWORD dwLineStates, DWORD dwAddressStates);
LONG lineSetTerminal(HLINE hLine, DWORD dwAddressID, HCALL hCall, DWORD dwSelect, DWORD dwTerminalModes, DWORD dwTerminalID, DWORD bEnable);
LONG lineSetTollList(HLINEAPP hLineApp, DWORD dwDeviceID, LPCWSTR lpszAddressIn, DWORD dwTollListOption);
LONG lineSetupConference(HCALL hCall, HLINE hLine, LPHCALL lphConfCall, LPHCALL lphConsultCall, DWORD dwNumParties, const LPLINECALLPARAMS lpCallParams);
LONG lineSetupTransfer(HCALL hCall, LPHCALL lphConsultCall, const LPLINECALLPARAMS lpCallParams);
/**
 * Shuts down an application's TAPI session.
 *
 * The call handles are deleted, open lines are closed and outstanding
 * asynchronous requests are canceled. Close lines explicitly first when
 * practical.
 *
 * @param hLineApp TAPI application handle.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineShutdown(HLINEAPP hLineApp);
LONG lineSwapHold(HCALL hActiveCall, HCALL hHeldCall);
struct linetranslateoutput_tag;
typedef struct linetranslateoutput_tag *LPLINETRANSLATEOUTPUT;
/**
 * Translates an address into a dialable string for a line device.
 *
 * dwCard is unsupported and must be zero. Set dwTotalSize in the output
 * LINETRANSLATEOUTPUT before calling. FORCELOCAL can override a toll-list
 * classification when translating a local number.
 *
 * @param hLineApp TAPI application handle, or NULL before initialization.
 * @param dwDeviceID Line device identifier.
 * @param dwAPIVersion Highest TAPI version supported by the application.
 * @param lpszAddressIn Canonical address or dialable digits.
 * @param dwCard Unsupported; set to zero.
 * @param dwTranslateOptions LINETRANSLATEOPTION_* flags.
 * @param lpTranslateOutput Receives the translated address; set dwTotalSize first.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineTranslateAddress(HLINEAPP hLineApp, DWORD dwDeviceID, DWORD dwAPIVersion, LPCWSTR lpszAddressIn, DWORD dwCard, DWORD dwTranslateOptions, LPLINETRANSLATEOUTPUT lpTranslateOutput);
/**
 * Displays a dialog for editing location and calling-card settings.
 *
 * After the dialog closes, call lineGetTranslateCaps to retrieve changes
 * and lineTranslateAddress to translate numbers with the new settings.
 *
 * @param hLineApp TAPI application handle.
 * @param dwDeviceID Line device identifier.
 * @param dwAPIVersion Highest TAPI version supported by the application.
 * @param hwndOwner Owner window for the dialog, or NULL.
 * @param lpszAddressIn Optional canonical number to preview, or NULL.
 * @return 0 on success, or a negative LINEERR_* code.
 */
LONG lineTranslateDialog(HLINEAPP hLineApp, DWORD dwDeviceID, DWORD dwAPIVersion, HWND hwndOwner, LPCWSTR lpszAddressIn);
LONG lineUnhold(HCALL hCall);
struct HPHONE__;
typedef const struct HPHONE__ *HPHONE;
LONG phoneClose(HPHONE hPhone);
LONG phoneConfigDialog(DWORD dwDeviceID, HWND hwndOwner, LPCWSTR lpszDeviceClass);
LONG phoneDevSpecific(HPHONE hPhone, LPVOID lpParams, DWORD dwSize);
struct HPHONEAPP__;
typedef const struct HPHONEAPP__ *HPHONEAPP;
struct phonecaps_tag;
typedef struct phonecaps_tag *LPPHONECAPS;
LONG phoneGetDevCaps(HPHONEAPP hPhoneApp, DWORD dwDeviceID, DWORD dwAPIVersion, DWORD dwExtVersion, LPPHONECAPS lpPhoneCaps);
LONG phoneGetGain(HPHONE hPhone, DWORD dwHookSwitchDev, LPDWORD lpdwGain);
LONG phoneGetHookSwitch(HPHONE hPhone, LPDWORD lpdwHookSwitchDevs);
LONG phoneGetID(HPHONE hPhone, LPVARSTRING lpDeviceID, LPCWSTR lpszDeviceClass);
LONG phoneGetIcon(DWORD dwDeviceID, LPCWSTR lpszDeviceClass, LPHICON lphIcon);
struct phonemessage_tag;
typedef struct phonemessage_tag *LPPHONEMESSAGE;
LONG phoneGetMessage(HPHONEAPP hPhoneApp, LPPHONEMESSAGE lpMessage, DWORD dwTimeout);
LONG phoneGetRing(HPHONE hPhone, LPDWORD lpdwRingMode, LPDWORD lpdwVolume);
struct phonestatus_tag;
typedef struct phonestatus_tag *LPPHONESTATUS;
LONG phoneGetStatus(HPHONE hPhone, LPPHONESTATUS lpPhoneStatus);
LONG phoneGetStatusMessages(HPHONE hPhone, LPDWORD lpdwPhoneStates, LPDWORD lpdwButtonModes, LPDWORD lpdwButtonStates);
LONG phoneGetVolume(HPHONE hPhone, DWORD dwHookSwitchDev, LPDWORD lpdwVolume);
typedef HPHONEAPP *LPHPHONEAPP;
typedef void (*PHONECALLBACK)(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
struct phoneinitializeexparams_tag;
typedef struct phoneinitializeexparams_tag *LPPHONEINITIALIZEEXPARAMS;
LONG phoneInitializeEx(LPHPHONEAPP lphPhoneApp, HINSTANCE hInstance, PHONECALLBACK lpfnCallback, LPCWSTR lpszFriendlyAppName, LPDWORD lpdwNumDevs, LPDWORD lpdwAPIVersion, LPPHONEINITIALIZEEXPARAMS lpPhoneInitializeExParams);
struct phoneextensionid_tag;
typedef struct phoneextensionid_tag *LPPHONEEXTENSIONID;
LONG phoneNegotiateAPIVersion(HPHONEAPP hPhoneApp, DWORD dwDeviceID, DWORD dwAPILowVersion, DWORD dwAPIHighVersion, LPDWORD lpdwAPIVersion, LPPHONEEXTENSIONID lpExtensionID);
LONG phoneNegotiateExtVersion(HPHONEAPP hPhoneApp, DWORD dwDeviceID, DWORD dwAPIVersion, DWORD dwExtLowVersion, DWORD dwExtHighVersion, LPDWORD lpdwExtVersion);
typedef HPHONE *LPHPHONE;
LONG phoneOpen(HPHONEAPP hPhoneApp, DWORD dwDeviceID, LPHPHONE lphPhone, DWORD dwAPIVersion, DWORD dwExtVersion, DWORD dwCallbackInstance, DWORD dwPrivilege);
LONG phoneSetGain(HPHONE hPhone, DWORD dwHookSwitchDev, DWORD dwGain);
LONG phoneSetHookSwitch(HPHONE hPhone, DWORD dwHookSwitchDevs, DWORD dwHookSwitchMode);
LONG phoneSetRing(HPHONE hPhone, DWORD dwRingMode, DWORD dwVolume);
LONG phoneSetStatusMessages(HPHONE hPhone, DWORD dwPhoneStates, DWORD dwButtonModes, DWORD dwButtonStates);
LONG phoneSetVolume(HPHONE hPhone, DWORD dwHookSwitchDev, DWORD dwVolume);
LONG phoneShutdown(HPHONEAPP hPhoneApp);
typedef struct lineaddresscaps_tag LINEADDRESSCAPS;
typedef struct lineaddressstatus_tag LINEADDRESSSTATUS;
typedef struct linecallinfo_tag LINECALLINFO;
typedef struct linecalllist_tag LINECALLLIST;
typedef struct linecallparams_tag LINECALLPARAMS;
typedef struct linecallstatus_tag LINECALLSTATUS;
struct linecalltreatmententry_tag;
typedef struct linecalltreatmententry_tag LINECALLTREATMENTENTRY;
struct linecardentry_tag;
typedef struct linecardentry_tag LINECARDENTRY;
struct linecountryentry_tag;
typedef struct linecountryentry_tag LINECOUNTRYENTRY;
struct linecountrylist_tag;
typedef struct linecountrylist_tag LINECOUNTRYLIST;
typedef struct linedevcaps_tag LINEDEVCAPS;
typedef struct linedevstatus_tag LINEDEVSTATUS;
typedef struct linedialparams_tag LINEDIALPARAMS;
typedef struct lineextensionid_tag LINEEXTENSIONID;
struct lineforward_tag;
typedef struct lineforward_tag LINEFORWARD;
typedef struct lineforwardlist_tag LINEFORWARDLIST;
typedef struct linegeneratetone_tag LINEGENERATETONE;
typedef struct lineinitializeexparams_tag LINEINITIALIZEEXPARAMS;
struct linelocationentry_tag;
typedef struct linelocationentry_tag LINELOCATIONENTRY;
struct linemediacontrolcallstate_tag;
typedef struct linemediacontrolcallstate_tag LINEMEDIACONTROLCALLSTATE;
struct linemediacontroldigit_tag;
typedef struct linemediacontroldigit_tag LINEMEDIACONTROLDIGIT;
struct linemediacontrolmedia_tag;
typedef struct linemediacontrolmedia_tag LINEMEDIACONTROLMEDIA;
struct linemediacontroltone_tag;
typedef struct linemediacontroltone_tag LINEMEDIACONTROLTONE;
typedef struct linemessage_tag LINEMESSAGE;
struct linemonitortone_tag;
typedef struct linemonitortone_tag LINEMONITORTONE;
struct lineproviderentry_tag;
typedef struct lineproviderentry_tag LINEPROVIDERENTRY;
typedef struct lineproviderlist_tag LINEPROVIDERLIST;
struct linetermcaps_tag;
typedef struct linetermcaps_tag LINETERMCAPS;
typedef struct linetranslatecaps_tag LINETRANSLATECAPS;
typedef struct linetranslateoutput_tag LINETRANSLATEOUTPUT;
typedef struct linecalltreatmententry_tag *LPLINECALLTREATMENTENTRY;
typedef struct linecardentry_tag *LPLINECARDENTRY;
typedef struct linecountryentry_tag *LPLINECOUNTRYENTRY;
typedef struct linecountrylist_tag *LPLINECOUNTRYLIST;
typedef struct lineforward_tag *LPLINEFORWARD;
typedef struct linelocationentry_tag *LPLINELOCATIONENTRY;
typedef struct linemediacontrolcallstate_tag *LPLINEMEDIACONTROLCALLSTATE;
typedef struct linemediacontroldigit_tag *LPLINEMEDIACONTROLDIGIT;
typedef struct linemediacontrolmedia_tag *LPLINEMEDIACONTROLMEDIA;
typedef struct linemediacontroltone_tag *LPLINEMEDIACONTROLTONE;
typedef struct linemonitortone_tag *LPLINEMONITORTONE;
typedef struct lineproviderentry_tag *LPLINEPROVIDERENTRY;
typedef struct linetermcaps_tag *LPLINETERMCAPS;
struct phonebuttoninfo_tag;
typedef struct phonebuttoninfo_tag *LPPHONEBUTTONINFO;
typedef struct phonebuttoninfo_tag PHONEBUTTONINFO;
typedef struct phonecaps_tag PHONECAPS;
typedef struct phoneextensionid_tag PHONEEXTENSIONID;
typedef struct phoneinitializeexparams_tag PHONEINITIALIZEEXPARAMS;
typedef struct phonemessage_tag PHONEMESSAGE;
typedef struct phonestatus_tag PHONESTATUS;
struct HCALL__ {
    int unused;
} __attribute__((packed, aligned(1)));

struct HLINEAPP__ {
    int unused;
} __attribute__((packed, aligned(1)));

struct HLINE__ {
    int unused;
} __attribute__((packed, aligned(1)));

struct HPHONEAPP__ {
    int unused;
} __attribute__((packed, aligned(1)));

struct HPHONE__ {
    int unused;
} __attribute__((packed, aligned(1)));

struct lineaddresscaps_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwLineDeviceID;
    DWORD dwAddressSize;
    DWORD dwAddressOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
    DWORD dwAddressSharing;
    DWORD dwAddressStates;
    DWORD dwCallInfoStates;
    DWORD dwCallerIDFlags;
    DWORD dwCalledIDFlags;
    DWORD dwConnectedIDFlags;
    DWORD dwRedirectionIDFlags;
    DWORD dwRedirectingIDFlags;
    DWORD dwCallStates;
    DWORD dwDialToneModes;
    DWORD dwBusyModes;
    DWORD dwSpecialInfo;
    DWORD dwDisconnectModes;
    DWORD dwMaxNumActiveCalls;
    DWORD dwMaxNumOnHoldCalls;
    DWORD dwMaxNumOnHoldPendingCalls;
    DWORD dwMaxNumConference;
    DWORD dwMaxNumTransConf;
    DWORD dwAddrCapFlags;
    DWORD dwCallFeatures;
    DWORD dwRemoveFromConfCaps;
    DWORD dwRemoveFromConfState;
    DWORD dwTransferModes;
    DWORD dwParkModes;
    DWORD dwForwardModes;
    DWORD dwMaxForwardEntries;
    DWORD dwMaxSpecificEntries;
    DWORD dwMinFwdNumRings;
    DWORD dwMaxFwdNumRings;
    DWORD dwMaxCallCompletions;
    DWORD dwCallCompletionConds;
    DWORD dwCallCompletionModes;
    DWORD dwNumCompletionMessages;
    DWORD dwCompletionMsgTextEntrySize;
    DWORD dwCompletionMsgTextSize;
    DWORD dwCompletionMsgTextOffset;
    DWORD dwAddressFeatures;
    DWORD dwPredictiveAutoTransferStates;
    DWORD dwNumCallTreatments;
    DWORD dwCallTreatmentListSize;
    DWORD dwCallTreatmentListOffset;
    DWORD dwDeviceClassesSize;
    DWORD dwDeviceClassesOffset;
    DWORD dwMaxCallDataSize;
    DWORD dwCallFeatures2;
    DWORD dwMaxNoAnswerTimeout;
    DWORD dwConnectedModes;
    DWORD dwOfferingModes;
    DWORD dwAvailableMediaModes;
} __attribute__((packed, aligned(1)));

struct lineaddressstatus_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwNumInUse;
    DWORD dwNumActiveCalls;
    DWORD dwNumOnHoldCalls;
    DWORD dwNumOnHoldPendCalls;
    DWORD dwAddressFeatures;
    DWORD dwNumRingsNoAnswer;
    DWORD dwForwardNumEntries;
    DWORD dwForwardSize;
    DWORD dwForwardOffset;
    DWORD dwTerminalModesSize;
    DWORD dwTerminalModesOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
} __attribute__((packed, aligned(1)));

struct linedialparams_tag {
    DWORD dwDialPause;
    DWORD dwDialSpeed;
    DWORD dwDigitDuration;
    DWORD dwWaitForDialtone;
} __attribute__((packed, aligned(1)));

struct linecallinfo_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    HLINE hLine;
    DWORD dwLineDeviceID;
    DWORD dwAddressID;
    DWORD dwBearerMode;
    DWORD dwRate;
    DWORD dwMediaMode;
    DWORD dwAppSpecific;
    DWORD dwCallID;
    DWORD dwRelatedCallID;
    DWORD dwCallParamFlags;
    DWORD dwCallStates;
    DWORD dwMonitorDigitModes;
    DWORD dwMonitorMediaModes;
    LINEDIALPARAMS DialParams;
    DWORD dwOrigin;
    DWORD dwReason;
    DWORD dwCompletionID;
    DWORD dwNumOwners;
    DWORD dwNumMonitors;
    DWORD dwCountryCode;
    DWORD dwTrunk;
    DWORD dwCallerIDFlags;
    DWORD dwCallerIDSize;
    DWORD dwCallerIDOffset;
    DWORD dwCallerIDNameSize;
    DWORD dwCallerIDNameOffset;
    DWORD dwCalledIDFlags;
    DWORD dwCalledIDSize;
    DWORD dwCalledIDOffset;
    DWORD dwCalledIDNameSize;
    DWORD dwCalledIDNameOffset;
    DWORD dwConnectedIDFlags;
    DWORD dwConnectedIDSize;
    DWORD dwConnectedIDOffset;
    DWORD dwConnectedIDNameSize;
    DWORD dwConnectedIDNameOffset;
    DWORD dwRedirectionIDFlags;
    DWORD dwRedirectionIDSize;
    DWORD dwRedirectionIDOffset;
    DWORD dwRedirectionIDNameSize;
    DWORD dwRedirectionIDNameOffset;
    DWORD dwRedirectingIDFlags;
    DWORD dwRedirectingIDSize;
    DWORD dwRedirectingIDOffset;
    DWORD dwRedirectingIDNameSize;
    DWORD dwRedirectingIDNameOffset;
    DWORD dwAppNameSize;
    DWORD dwAppNameOffset;
    DWORD dwDisplayableAddressSize;
    DWORD dwDisplayableAddressOffset;
    DWORD dwCalledPartySize;
    DWORD dwCalledPartyOffset;
    DWORD dwCommentSize;
    DWORD dwCommentOffset;
    DWORD dwDisplaySize;
    DWORD dwDisplayOffset;
    DWORD dwUserUserInfoSize;
    DWORD dwUserUserInfoOffset;
    DWORD dwHighLevelCompSize;
    DWORD dwHighLevelCompOffset;
    DWORD dwLowLevelCompSize;
    DWORD dwLowLevelCompOffset;
    DWORD dwChargingInfoSize;
    DWORD dwChargingInfoOffset;
    DWORD dwTerminalModesSize;
    DWORD dwTerminalModesOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
    DWORD dwCallTreatment;
    DWORD dwCallDataSize;
    DWORD dwCallDataOffset;
    DWORD dwSendingFlowspecSize;
    DWORD dwSendingFlowspecOffset;
    DWORD dwReceivingFlowspecSize;
    DWORD dwReceivingFlowspecOffset;
    DWORD dwAddressType;
} __attribute__((packed, aligned(1)));

struct linecalllist_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwCallsNumEntries;
    DWORD dwCallsSize;
    DWORD dwCallsOffset;
} __attribute__((packed, aligned(1)));

struct linecallparams_tag {
    DWORD dwTotalSize;
    DWORD dwBearerMode;
    DWORD dwMinRate;
    DWORD dwMaxRate;
    DWORD dwMediaMode;
    DWORD dwCallParamFlags;
    DWORD dwAddressMode;
    DWORD dwAddressID;
    LINEDIALPARAMS DialParams;
    DWORD dwOrigAddressSize;
    DWORD dwOrigAddressOffset;
    DWORD dwDisplayableAddressSize;
    DWORD dwDisplayableAddressOffset;
    DWORD dwCalledPartySize;
    DWORD dwCalledPartyOffset;
    DWORD dwCommentSize;
    DWORD dwCommentOffset;
    DWORD dwUserUserInfoSize;
    DWORD dwUserUserInfoOffset;
    DWORD dwHighLevelCompSize;
    DWORD dwHighLevelCompOffset;
    DWORD dwLowLevelCompSize;
    DWORD dwLowLevelCompOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
    DWORD dwPredictiveAutoTransferStates;
    DWORD dwTargetAddressSize;
    DWORD dwTargetAddressOffset;
    DWORD dwSendingFlowspecSize;
    DWORD dwSendingFlowspecOffset;
    DWORD dwReceivingFlowspecSize;
    DWORD dwReceivingFlowspecOffset;
    DWORD dwDeviceClassSize;
    DWORD dwDeviceClassOffset;
    DWORD dwDeviceConfigSize;
    DWORD dwDeviceConfigOffset;
    DWORD dwCallDataSize;
    DWORD dwCallDataOffset;
    DWORD dwNoAnswerTimeout;
    DWORD dwCallingPartyIDSize;
    DWORD dwCallingPartyIDOffset;
    DWORD dwAddressType;
} __attribute__((packed, aligned(1)));

struct linecallstatus_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwCallState;
    DWORD dwCallStateMode;
    DWORD dwCallPrivilege;
    DWORD dwCallFeatures;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
    DWORD dwCallFeatures2;
    SYSTEMTIME tStateEntryTime;
} __attribute__((packed, aligned(1)));

struct linecalltreatmententry_tag {
    DWORD dwCallTreatmentID;
    DWORD dwCallTreatmentNameSize;
    DWORD dwCallTreatmentNameOffset;
} __attribute__((packed, aligned(1)));

struct linecardentry_tag {
    DWORD dwPermanentCardID;
    DWORD dwCardNameSize;
    DWORD dwCardNameOffset;
    DWORD dwCardNumberDigits;
    DWORD dwSameAreaRuleSize;
    DWORD dwSameAreaRuleOffset;
    DWORD dwLongDistanceRuleSize;
    DWORD dwLongDistanceRuleOffset;
    DWORD dwInternationalRuleSize;
    DWORD dwInternationalRuleOffset;
    DWORD dwOptions;
} __attribute__((packed, aligned(1)));

struct linecountryentry_tag {
    DWORD dwCountryID;
    DWORD dwCountryCode;
    DWORD dwNextCountryID;
    DWORD dwCountryNameSize;
    DWORD dwCountryNameOffset;
    DWORD dwSameAreaRuleSize;
    DWORD dwSameAreaRuleOffset;
    DWORD dwLongDistanceRuleSize;
    DWORD dwLongDistanceRuleOffset;
    DWORD dwInternationalRuleSize;
    DWORD dwInternationalRuleOffset;
} __attribute__((packed, aligned(1)));

struct linecountrylist_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwNumCountries;
    DWORD dwCountryListSize;
    DWORD dwCountryListOffset;
} __attribute__((packed, aligned(1)));

struct linedevcaps_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwProviderInfoSize;
    DWORD dwProviderInfoOffset;
    DWORD dwSwitchInfoSize;
    DWORD dwSwitchInfoOffset;
    DWORD dwPermanentLineID;
    DWORD dwLineNameSize;
    DWORD dwLineNameOffset;
    DWORD dwStringFormat;
    DWORD dwAddressModes;
    DWORD dwNumAddresses;
    DWORD dwBearerModes;
    DWORD dwMaxRate;
    DWORD dwMediaModes;
    DWORD dwGenerateToneModes;
    DWORD dwGenerateToneMaxNumFreq;
    DWORD dwGenerateDigitModes;
    DWORD dwMonitorToneMaxNumFreq;
    DWORD dwMonitorToneMaxNumEntries;
    DWORD dwMonitorDigitModes;
    DWORD dwGatherDigitsMinTimeout;
    DWORD dwGatherDigitsMaxTimeout;
    DWORD dwMedCtlDigitMaxListSize;
    DWORD dwMedCtlMediaMaxListSize;
    DWORD dwMedCtlToneMaxListSize;
    DWORD dwMedCtlCallStateMaxListSize;
    DWORD dwDevCapFlags;
    DWORD dwMaxNumActiveCalls;
    DWORD dwAnswerMode;
    DWORD dwRingModes;
    DWORD dwLineStates;
    DWORD dwUUIAcceptSize;
    DWORD dwUUIAnswerSize;
    DWORD dwUUIMakeCallSize;
    DWORD dwUUIDropSize;
    DWORD dwUUISendUserUserInfoSize;
    DWORD dwUUICallInfoSize;
    LINEDIALPARAMS MinDialParams;
    LINEDIALPARAMS MaxDialParams;
    LINEDIALPARAMS DefaultDialParams;
    DWORD dwNumTerminals;
    DWORD dwTerminalCapsSize;
    DWORD dwTerminalCapsOffset;
    DWORD dwTerminalTextEntrySize;
    DWORD dwTerminalTextSize;
    DWORD dwTerminalTextOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
    DWORD dwLineFeatures;
    DWORD dwSettableDevStatus;
    DWORD dwDeviceClassesSize;
    DWORD dwDeviceClassesOffset;
    GUID PermanentLineGuid;
    DWORD dwAddressTypes;
    GUID ProtocolGuid;
    DWORD dwAvailableTracking;
} __attribute__((packed, aligned(1)));

struct linedevstatus_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwNumOpens;
    DWORD dwOpenMediaModes;
    DWORD dwNumActiveCalls;
    DWORD dwNumOnHoldCalls;
    DWORD dwNumOnHoldPendCalls;
    DWORD dwLineFeatures;
    DWORD dwNumCallCompletions;
    DWORD dwRingMode;
    DWORD dwSignalLevel;
    DWORD dwBatteryLevel;
    DWORD dwRoamMode;
    DWORD dwDevStatusFlags;
    DWORD dwTerminalModesSize;
    DWORD dwTerminalModesOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
    DWORD dwAvailableMediaModes;
    DWORD dwAppInfoSize;
    DWORD dwAppInfoOffset;
} __attribute__((packed, aligned(1)));

struct lineextensionid_tag {
    DWORD dwExtensionID0;
    DWORD dwExtensionID1;
    DWORD dwExtensionID2;
    DWORD dwExtensionID3;
} __attribute__((packed, aligned(1)));

struct lineforward_tag {
    DWORD dwForwardMode;
    DWORD dwCallerAddressSize;
    DWORD dwCallerAddressOffset;
    DWORD dwDestCountryCode;
    DWORD dwDestAddressSize;
    DWORD dwDestAddressOffset;
} __attribute__((packed, aligned(1)));

struct lineforwardlist_tag {
    DWORD dwTotalSize;
    DWORD dwNumEntries;
    LINEFORWARD ForwardList[1];
} __attribute__((packed, aligned(1)));

struct linegeneratetone_tag {
    DWORD dwFrequency;
    DWORD dwCadenceOn;
    DWORD dwCadenceOff;
    DWORD dwVolume;
} __attribute__((packed, aligned(1)));

struct lineinitializeexparams_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwOptions;
    union {
        HANDLE hEvent;
        HANDLE hCompletionPort;
    } Handles;
    DWORD dwCompletionKey;
} __attribute__((packed, aligned(1)));

struct linelocationentry_tag {
    DWORD dwPermanentLocationID;
    DWORD dwLocationNameSize;
    DWORD dwLocationNameOffset;
    DWORD dwCountryCode;
    DWORD dwCityCodeSize;
    DWORD dwCityCodeOffset;
    DWORD dwPreferredCardID;
    DWORD dwLocalAccessCodeSize;
    DWORD dwLocalAccessCodeOffset;
    DWORD dwLongDistanceAccessCodeSize;
    DWORD dwLongDistanceAccessCodeOffset;
    DWORD dwTollPrefixListSize;
    DWORD dwTollPrefixListOffset;
    DWORD dwCountryID;
    DWORD dwOptions;
    DWORD dwCancelCallWaitingSize;
    DWORD dwCancelCallWaitingOffset;
} __attribute__((packed, aligned(1)));

struct linemediacontrolcallstate_tag {
    DWORD dwCallStates;
    DWORD dwMediaControl;
} __attribute__((packed, aligned(1)));

struct linemediacontroldigit_tag {
    DWORD dwDigit;
    DWORD dwDigitModes;
    DWORD dwMediaControl;
} __attribute__((packed, aligned(1)));

struct linemediacontrolmedia_tag {
    DWORD dwMediaModes;
    DWORD dwDuration;
    DWORD dwMediaControl;
} __attribute__((packed, aligned(1)));

struct linemediacontroltone_tag {
    DWORD dwAppSpecific;
    DWORD dwDuration;
    DWORD dwFrequency1;
    DWORD dwFrequency2;
    DWORD dwFrequency3;
    DWORD dwMediaControl;
} __attribute__((packed, aligned(1)));

struct linemessage_tag {
    DWORD hDevice;
    DWORD dwMessageID;
    DWORD dwCallbackInstance;
    DWORD dwParam1;
    DWORD dwParam2;
    DWORD dwParam3;
} __attribute__((packed, aligned(1)));

struct linemonitortone_tag {
    DWORD dwAppSpecific;
    DWORD dwDuration;
    DWORD dwFrequency1;
    DWORD dwFrequency2;
    DWORD dwFrequency3;
} __attribute__((packed, aligned(1)));

struct lineproviderentry_tag {
    DWORD dwPermanentProviderID;
    DWORD dwProviderFilenameSize;
    DWORD dwProviderFilenameOffset;
} __attribute__((packed, aligned(1)));

struct lineproviderlist_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwNumProviders;
    DWORD dwProviderListSize;
    DWORD dwProviderListOffset;
} __attribute__((packed, aligned(1)));

struct linetermcaps_tag {
    DWORD dwTermDev;
    DWORD dwTermModes;
    DWORD dwTermSharing;
} __attribute__((packed, aligned(1)));

struct linetranslatecaps_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwNumLocations;
    DWORD dwLocationListSize;
    DWORD dwLocationListOffset;
    DWORD dwCurrentLocationID;
    DWORD dwNumCards;
    DWORD dwCardListSize;
    DWORD dwCardListOffset;
    DWORD dwCurrentPreferredCardID;
} __attribute__((packed, aligned(1)));

struct linetranslateoutput_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwDialableStringSize;
    DWORD dwDialableStringOffset;
    DWORD dwDisplayableStringSize;
    DWORD dwDisplayableStringOffset;
    DWORD dwCurrentCountry;
    DWORD dwDestCountry;
    DWORD dwTranslateResults;
} __attribute__((packed, aligned(1)));

struct phonebuttoninfo_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwButtonMode;
    DWORD dwButtonFunction;
    DWORD dwButtonTextSize;
    DWORD dwButtonTextOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
    DWORD dwButtonState;
} __attribute__((packed, aligned(1)));

struct phonecaps_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwProviderInfoSize;
    DWORD dwProviderInfoOffset;
    DWORD dwPhoneInfoSize;
    DWORD dwPhoneInfoOffset;
    DWORD dwPermanentPhoneID;
    DWORD dwPhoneNameSize;
    DWORD dwPhoneNameOffset;
    DWORD dwStringFormat;
    DWORD dwPhoneStates;
    DWORD dwHookSwitchDevs;
    DWORD dwHandsetHookSwitchModes;
    DWORD dwSpeakerHookSwitchModes;
    DWORD dwHeadsetHookSwitchModes;
    DWORD dwVolumeFlags;
    DWORD dwGainFlags;
    DWORD dwDisplayNumRows;
    DWORD dwDisplayNumColumns;
    DWORD dwNumRingModes;
    DWORD dwNumButtonLamps;
    DWORD dwButtonModesSize;
    DWORD dwButtonModesOffset;
    DWORD dwButtonFunctionsSize;
    DWORD dwButtonFunctionsOffset;
    DWORD dwLampModesSize;
    DWORD dwLampModesOffset;
    DWORD dwNumSetData;
    DWORD dwSetDataSize;
    DWORD dwSetDataOffset;
    DWORD dwNumGetData;
    DWORD dwGetDataSize;
    DWORD dwGetDataOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
    DWORD dwDeviceClassesSize;
    DWORD dwDeviceClassesOffset;
    DWORD dwPhoneFeatures;
    DWORD dwSettableHandsetHookSwitchModes;
    DWORD dwSettableSpeakerHookSwitchModes;
    DWORD dwSettableHeadsetHookSwitchModes;
    DWORD dwMonitoredHandsetHookSwitchModes;
    DWORD dwMonitoredSpeakerHookSwitchModes;
    DWORD dwMonitoredHeadsetHookSwitchModes;
    GUID PermanentPhoneGuid;
} __attribute__((packed, aligned(1)));

struct phoneextensionid_tag {
    DWORD dwExtensionID0;
    DWORD dwExtensionID1;
    DWORD dwExtensionID2;
    DWORD dwExtensionID3;
} __attribute__((packed, aligned(1)));

struct phoneinitializeexparams_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwOptions;
    union {
        HANDLE hEvent;
        HANDLE hCompletionPort;
    } Handles;
    DWORD dwCompletionKey;
} __attribute__((packed, aligned(1)));

struct phonemessage_tag {
    DWORD hDevice;
    DWORD dwMessageID;
    DWORD dwCallbackInstance;
    DWORD dwParam1;
    DWORD dwParam2;
    DWORD dwParam3;
} __attribute__((packed, aligned(1)));

struct phonestatus_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwStatusFlags;
    DWORD dwNumOwners;
    DWORD dwNumMonitors;
    DWORD dwRingMode;
    DWORD dwRingVolume;
    DWORD dwHandsetHookSwitchMode;
    DWORD dwHandsetVolume;
    DWORD dwHandsetGain;
    DWORD dwSpeakerHookSwitchMode;
    DWORD dwSpeakerVolume;
    DWORD dwSpeakerGain;
    DWORD dwHeadsetHookSwitchMode;
    DWORD dwHeadsetVolume;
    DWORD dwHeadsetGain;
    DWORD dwDisplaySize;
    DWORD dwDisplayOffset;
    DWORD dwLampModesSize;
    DWORD dwLampModesOffset;
    DWORD dwOwnerNameSize;
    DWORD dwOwnerNameOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
    DWORD dwPhoneFeatures;
} __attribute__((packed, aligned(1)));


#ifdef __cplusplus
}
#endif

#endif
