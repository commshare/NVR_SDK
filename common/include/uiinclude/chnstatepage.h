#ifndef _CHNSTATEPAGE_H_
#define _CHNSTATEPAGE_H_

#include "ui.h"

#define IDC_STATIC_CHNSTATE_CHNINDEX			IDD_DIALOG_CHNSTATE+1

#define IDC_STATIC_CHNSTATE_CHN1				IDD_DIALOG_CHNSTATE+2
#define IDC_STATIC_CHNSTATE_CHN2				IDD_DIALOG_CHNSTATE+3
#define IDC_STATIC_CHNSTATE_CHN3				IDD_DIALOG_CHNSTATE+4
#define IDC_STATIC_CHNSTATE_CHN4				IDD_DIALOG_CHNSTATE+5

#define IDC_STATIC_CHNSTATE_STATE				IDD_DIALOG_CHNSTATE+6

#define IDC_LIGHT_CHNSTATE_STATE1				IDD_DIALOG_CHNSTATE+7
#define IDC_LIGHT_CHNSTATE_STATE2				IDD_DIALOG_CHNSTATE+8
#define IDC_LIGHT_CHNSTATE_STATE3				IDD_DIALOG_CHNSTATE+9
#define IDC_LIGHT_CHNSTATE_STATE4				IDD_DIALOG_CHNSTATE+10

#define IDC_STATIC_CHNSTATE_ENABLE				IDD_DIALOG_CHNSTATE+11

#define IDC_CHECK_CHNSTATE_ENABLE1				IDD_DIALOG_CHNSTATE+12
#define IDC_CHECK_CHNSTATE_ENABLE2				IDD_DIALOG_CHNSTATE+13
#define IDC_CHECK_CHNSTATE_ENABLE3				IDD_DIALOG_CHNSTATE+14
#define IDC_CHECK_CHNSTATE_ENABLE4				IDD_DIALOG_CHNSTATE+15

#define IDC_BUTTON_CHNSTATE_ALLSTARTUP			IDD_DIALOG_CHNSTATE+16
#define IDC_BUTTON_CHNSTATE_ALLSTOP				IDD_DIALOG_CHNSTATE+17

#define IDC_BUTTON_CHNSTATE_BACK				IDD_DIALOG_CHNSTATE+18

BOOL CreateChnstatePage();
BOOL ShowChnstatePage();

#endif

