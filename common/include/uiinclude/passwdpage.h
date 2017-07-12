#ifndef _PASSWDPAGE_H_
#define _PASSWDPAGE_H_

#include "ui.h"

#define IDC_STATIC_PASSWD_USER		IDD_DIALOG_PASSWD+1
#define IDC_STATIC_PASSWD_OLD		IDD_DIALOG_PASSWD+2
#define IDC_STATIC_PASSWD_NEW		IDD_DIALOG_PASSWD+3
#define IDC_STATIC_PASSWD_SURE		IDD_DIALOG_PASSWD+4

#define IDC_EDIT_PASSWD_USER		IDD_DIALOG_PASSWD+5
#define IDC_EDIT_PASSWD_OLD			IDD_DIALOG_PASSWD+6
#define IDC_EDIT_PASSWD_NEW			IDD_DIALOG_PASSWD+7
#define IDC_EDIT_PASSWD_SURE		IDD_DIALOG_PASSWD+8

#define IDC_BUTTON_PASSWD_OK		IDD_DIALOG_PASSWD+9
#define IDC_BUTTON_PASSWD_CANCEL	IDD_DIALOG_PASSWD+10

BOOL CreatePasswdPage();
BOOL ShowPasswdPage();

void OnPasswdOK(s32 param);
void OnPasswdCancel(s32 param);

#endif
