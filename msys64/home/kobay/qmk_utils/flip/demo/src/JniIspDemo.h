#ifndef _JNIISPDEMO_H_
#define _JNIISPDEMO_H_


#ifdef WIN32

	#include <windows.h>

	// Allow applications not built with Microsoft Visual C++ to link with our DLL.
	#define STDCALL __stdcall
#else

	// Linux specific
	#define STDCALL

#endif//WIN32


#define NO_NEWLINE	false
#define NEWLINE		true
#define TAB "\t"

// ============================ Flow control =================================

#define SYNCHRO                1
#define READ_BLV               1
#define FULL_ERASE             1
#define BLANK_CHECK            1
#define FILL_ZEROS             1
#define PARSE_HEX              1
#define PROGRAM_FLASH          1
#define VERIFY_FLASH           1
#define READ_FLASH             1
#define SELECT_EEPROM          0
#define FILL_EEPROM_BUFFER     0
#define PROGRAM_EEPROM         0
#define VERIFY_EEPROM          0
#define SWITCH_TO_APPLI        0
#define VERIFY_IN_APPLI_MODE   0
#define GOBACKTO_ISP           0
#define VERIFY_POST_BACKTO_ISP 0
#define TOGGLE_DTR				1  // Activates DTR signal toggling test.

const int TABDOTWIDTH = 40;
const int TABFAIL     =  4;




#endif // _JNIISPDEMO_H_



