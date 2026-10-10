/*
 * The notify component supports the Windows CE event notification system.
 */
#ifndef _NOTIFY_H_
#define _NOTIFY_H_

#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef	_WIN32_WCE	/* Valid from Windows CE 1.01 and later */

typedef struct UserNotificationType {
	DWORD		ActionFlags;
	wchar_t		*pwszDialogTitle;
	wchar_t		*pwszDialogText;
	wchar_t		*pwszSound;
	DWORD		nMaxSound;
	DWORD		dwReserved;
} CE_USER_NOTIFICATION, *PCE_USER_NOTIFICATION;

typedef struct UserNotificationTrigger {
	DWORD		dwSize;
	DWORD		dwType;
	DWORD		dwEvent;
	WCHAR		*lpszApplication;
	WCHAR		*lpszArguments;
	SYSTEMTIME	stStartTime;
	SYSTEMTIME	stEndTime;
} CE_NOTIFICATION_TRIGGER, *PCE_NOTIFICATION_TRIGGER;

/* Flags for ActionFlags. Values from forums.microsoft.com. */
#define	PUN_LED		1	/* ? */
#define	PUN_VIBRATE	2	/* ? */
#define	PUN_DIALOG	4	/* ? */
#define	PUN_SOUND	8	/* ? */
#define	PUN_REPEAT	16	/* ? */
#define	PUN_PRIVATE	32	/* ? */

/* Values for lWhichEvent in CeRunAppAtEvent */
#define	NOTIFICATION_EVENT_NONE			0	/* ? */
#define	NOTIFICATION_EVENT_TIME_CHANGE		1	/* ? */
#define	NOTIFICATION_EVENT_SYNC_END		2	/* ? */
#define	NOTIFICATION_EVENT_ON_AC_POWER		3	/* ? */
#define	NOTIFICATION_EVENT_OFF_AC_POWER		4	/* ? */
#define	NOTIFICATION_EVENT_NET_CONNECT		5	/* ? */
#define	NOTIFICATION_EVENT_NET_DISCONNECT	6	/* ? */
#define	NOTIFICATION_EVENT_DEVICE_CHANGE	7	/* ? */
#define	NOTIFICATION_EVENT_IR_DISCOVERED	8	/* ? */
#define	NOTIFICATION_EVENT_RS232_DETECTED	9	/* ? */
#define	NOTIFICATION_EVENT_RESTORE_END		10	/* ? */
#define	NOTIFICATION_EVENT_WAKEUP		11	/* ? */
#define	NOTIFICATION_EVENT_TZ_CHANGE		12	/* ? */
#define	NOTIFICATION_EVENT_MACHINE_NAME_CHANGE	13	/* ? */

/* Command line values */
#define APP_RUN_AFTER_EXTENDED_EVENT	L"AppRunAfterExtendedEvent"
#define APP_RUN_AFTER_SYNC		L"AppRunAfterSync"
#define APP_RUN_AFTER_TZ_CHANGE		L"AppRunAfterTzChange"
#define APP_RUN_AFTER_WAKEUP		L"AppRunAfterWakeup"
#define APP_RUN_AT_AC_POWER_ON		L"AppRunAtAcPowerOn"
#define APP_RUN_AT_AC_POWER_OFF		L"AppRunAtAcPowerOff"
#define APP_RUN_AT_NET_CONNECT		L"AppRunAtNetConnect"
#define APP_RUN_AT_NET_DISCONNECT	L"AppRunAtNetDisconnect"
#define APP_RUN_AT_DEVICE_CHANGE	L"AppRunDeviceChange"
#define APP_RUN_AT_IR_DISCOVERY		L"AppRunAtIrDiscovery"
#define APP_RUN_AT_RS232_DETECT		L"AppRunAtRs232Detect"
#define APP_RUN_AFTER_RESTORE		L"AppRunAfterRestore"

/**
 * Deletes a pending user notification set with CeSetUserNotification.
 *
 * Has no effect on notifications that have already fired: use
 * CeHandleAppNotifications for those. Windows CE 1.0 has
 * PegClearUserNotification instead.
 *
 * @param hNotification Handle from CeSetUserNotification.
 * @return TRUE on success, FALSE on failure.
 */
BOOL CeClearUserNotification (HANDLE hNotification); 
BOOL CeGetUserNotification (HANDLE hNotification,
		DWORD cBufferSize,
		LPDWORD pcBytesNeeded,
		LPBYTE pBuffer);
BOOL CeGetUserNotificationHandles (HANDLE* rghNotifications,
		DWORD cHandles,
		LPDWORD pcHandlesNeeded);
/**
 * Shows the notification options dialog and returns the user's choices.
 *
 * The dialog only offers options the hardware supports. Store the result
 * and pass it to CeSetUserNotification. Windows CE 1.0 has
 * PegGetUserNotificationPreferences instead.
 *
 * @param hWndParent Owner window for the dialog.
 * @param lpNotification CE_USER_NOTIFICATION with the initial settings.
 *        Receives the user's settings.
 * @return TRUE if the user changed the settings, FALSE if not or on
 *         failure.
 */
BOOL CeGetUserNotificationPreferences (HWND hWndParent,
		PCE_USER_NOTIFICATION lpNotification); 
/**
 * Marks all fired notifications owned by an application as handled.
 *
 * Stops the sound, LED and vibration and removes the taskbar annunciator.
 * Windows CE 1.0 has PegHandleAppNotifications instead.
 *
 * @param pwszAppName The owner name passed to CeSetUserNotification.
 * @return TRUE on success, FALSE on failure.
 */
BOOL CeHandleAppNotifications (wchar_t *pwszAppName); 
/**
 * Registers an application to be started when a system event occurs.
 *
 * The application is started with a command line beginning with an
 * APP_RUN_* string matching the event, such as APP_RUN_AFTER_SYNC, and
 * sometimes followed by a parameter. If an instance is already running,
 * the new one should hand over to it and exit. Windows CE 1.0 has
 * PegRunAppAtEvent instead.
 *
 * @param pwszAppName Path of the application to start.
 * @param lWhichEvent NOTIFICATION_EVENT_SYNC_END, _DEVICE_CHANGE,
 *        _RS232_DETECTED, _TIME_CHANGE or _RESTORE_END, or
 *        NOTIFICATION_EVENT_NONE to remove all of the application's
 *        registrations. NOTIFICATION_EVENT_ON_AC_POWER, _OFF_AC_POWER,
 *        _NET_CONNECT, _NET_DISCONNECT and _IR_DISCOVERED are not
 *        supported.
 * @return TRUE on success, FALSE on failure.
 */
BOOL CeRunAppAtEvent (wchar_t *pwszAppName, LONG lWhichEvent); 
/**
 * Registers an application to be started at a given time.
 *
 * Replaces any earlier request for the same application. The application
 * gets APP_RUN_AT_TIME as its command line. If an instance is already
 * running, the new one should hand over to it and exit. Windows CE 1.0
 * has PegRunAppAtTime instead.
 *
 * @param pwszAppName Path of the application to start.
 * @param lpTime Local time to start it, or NULL to cancel the request.
 * @return TRUE on success, FALSE on failure.
 */
BOOL CeRunAppAtTime (wchar_t *pwszAppName, SYSTEMTIME* lpTime); 
/**
 * Creates or replaces a user notification (sound, LED, dialog and so on)
 * due at a given time.
 *
 * The application isn't started when the notification fires. If the user
 * picks the annunciator, a new instance starts with a command line of
 * APP_RUN_TO_HANDLE_NOTIFICATION followed by the notification handle. Get
 * the options from the user with CeGetUserNotificationPreferences.
 * Windows CE 1.0 has PegSetUserNotification instead.
 *
 * @param hNotification Notification to replace, or 0 to create one.
 * @param pwszAppName Owning application. Its icon is used as the taskbar
 *        annunciator.
 * @param lpTime Local time the notification fires.
 * @param lpUserNotification CE_USER_NOTIFICATION with the actions (PUN_*
 *        flags), dialog text and sound.
 * @return The notification handle, or 0 on failure.
 */
HANDLE CeSetUserNotification (HANDLE hNotification,
		wchar_t *pwszAppName,
		SYSTEMTIME* lpTime,
		PCE_USER_NOTIFICATION lpUserNotification); 
HANDLE CeSetUserNotificationEx (HANDLE hNotification,
		CE_NOTIFICATION_TRIGGER *pcnt,
		CE_USER_NOTIFICATION* pceun);

#endif	/* _WIN32_WCE */

#ifdef  __cplusplus
}
#endif

#endif	/* _NOTIFY_H_ */
