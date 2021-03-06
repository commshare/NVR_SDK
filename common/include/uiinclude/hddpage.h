#ifndef _HDDPAGE_H_
#define _HDDPAGE_H_

#include "ui.h"

#define IDC_STATIC_HDD_SELECT			IDD_DIALOG_HDD+1
#define IDC_COMBO_HDD_SELECT			IDD_DIALOG_HDD+2
#define IDC_STATIC_HDD_CONTENT			IDD_DIALOG_HDD+3
#define IDC_STATIC_HDD_REMAIN			IDD_DIALOG_HDD+4
#define IDC_STATIC_HDD_SLEEP			IDD_DIALOG_HDD+5
#define IDC_STATIC_HDD_STATE			IDD_DIALOG_HDD+6
#define IDC_STATIC_HDD_INFO				IDD_DIALOG_HDD+7
#define IDC_STATIC_HDD_CONTENT_VALUE	IDD_DIALOG_HDD+8
#define IDC_STATIC_HDD_REMAIN_VALUE		IDD_DIALOG_HDD+9
#define IDC_STATIC_HDD_SLEEP_VALUE		IDD_DIALOG_HDD+10
#define IDC_STATIC_HDD_STATE_VALUE		IDD_DIALOG_HDD+11
#define IDC_BUTTON_HDD_FORMAT			IDD_DIALOG_HDD+12
#define IDC_BUTTON_HDD_CANCEL			IDD_DIALOG_HDD+13

BOOL CreateHddPage();
BOOL ShowHddPage();

#endif
