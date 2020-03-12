#ifdef WIN32
	#include <windows.h>
#else
	#include "compiler.h"
	#include <errno.h>
#endif

#include <iostream>
#include <iomanip>
using namespace std;


#include "utility.h"
#include "JniIspDemo.h"
#include "AtJniIsp.h"




// Selected communication interface.
int intrfce = RS232;

// ISP done through CAN bootloader?
bool canItfce;

// CAN node number.
char *nnb = "FF";

// Function pointers.
DECLARE_FUNCTION_POINTER(ispInit);
DECLARE_FUNCTION_POINTER(ispSetLogEnabled);
DECLARE_FUNCTION_POINTER(ispSelectDevice);
DECLARE_FUNCTION_POINTER(ispSelectCommHardware);
DECLARE_FUNCTION_POINTER(ispOpenRs232Port);
DECLARE_FUNCTION_POINTER(ispSyncTarget);
DECLARE_FUNCTION_POINTER(ispParseHexFile);
DECLARE_FUNCTION_POINTER(ispBlankCheckMemory);
DECLARE_FUNCTION_POINTER(ispProgramDevice);
DECLARE_FUNCTION_POINTER(ispProgramAddrRange);
DECLARE_FUNCTION_POINTER(ispReadDevice);
DECLARE_FUNCTION_POINTER(ispReadAddrRange);
DECLARE_FUNCTION_POINTER(ispVerifyDevice);
DECLARE_FUNCTION_POINTER(ispGetLastError);
DECLARE_FUNCTION_POINTER(ispExit);
DECLARE_FUNCTION_POINTER(ispUpdateCmdsIds);
DECLARE_FUNCTION_POINTER(ispOpenCanPort);
DECLARE_FUNCTION_POINTER(ispOpenUsbPort);
DECLARE_FUNCTION_POINTER(ispSelectCanNode);
DECLARE_FUNCTION_POINTER(ispSelectMemory);
DECLARE_FUNCTION_POINTER(ispEraseDevice);
DECLARE_FUNCTION_POINTER(ispGetDeviceIndex);
DECLARE_FUNCTION_POINTER(ispDataLog);
DECLARE_FUNCTION_POINTER(ispSetDebugMode);
DECLARE_FUNCTION_POINTER(ispOpenLogFile);
DECLARE_FUNCTION_POINTER(ispExecCmd);
DECLARE_FUNCTION_POINTER(ispGetLastResult);
DECLARE_FUNCTION_POINTER(ispGetMemorySize);
DECLARE_FUNCTION_POINTER(ispReadSignatureBytes);
DECLARE_FUNCTION_POINTER(ispReadSpecialByte);
DECLARE_FUNCTION_POINTER(ispBlankCheckAddrRange);
DECLARE_FUNCTION_POINTER(ispFillBufferAddrRange);
DECLARE_FUNCTION_POINTER(ispSetSecurityLevel);
DECLARE_FUNCTION_POINTER(ispGetErrorVecPtr);
DECLARE_FUNCTION_POINTER(ispGetBufferAddrHi);
DECLARE_FUNCTION_POINTER(ispGetBufferAddrLo);
DECLARE_FUNCTION_POINTER(ispSerialize);
DECLARE_FUNCTION_POINTER(ispWriteSpecialByte);
DECLARE_FUNCTION_POINTER(ispGetLastErrorMssg);
DECLARE_FUNCTION_POINTER(ispGetErrorMssgFromIdx);
DECLARE_FUNCTION_POINTER(ispSetTimeout);
DECLARE_FUNCTION_POINTER(ispSetAutoIsp);
DECLARE_FUNCTION_POINTER(ispWriteHexFile);
DECLARE_FUNCTION_POINTER(ispSetDtrLow);
DECLARE_FUNCTION_POINTER(ispSetDtrHigh);
DECLARE_FUNCTION_POINTER(ispSetRtsLow);
DECLARE_FUNCTION_POINTER(ispSetRtsHigh);
DECLARE_FUNCTION_POINTER(ispEnterAppliMode);
DECLARE_FUNCTION_POINTER(ispEnterIspMode);






void display(int status, bool newLine) {
  if (status == PASS) {
    if (newLine)
      cout << "PASS" << endl;
    else
      cout << "PASS" << TAB << flush;
  } else {
    if (newLine)
      cout << "FAIL" << endl;
    else
      cout << "FAIL" << TAB << flush;
  }
}


void setOperationTitle(string str) {
  cout << str << setfill('.') << setw(TABDOTWIDTH - str.length()) << flush;
}


int loadLibFuncs(HINSTANCE h) {
  LOAD_FUNCTION_POINTER(h, ispInit); 
  ADDR_CHECK(ispInit);
  LOAD_FUNCTION_POINTER(h, ispSetLogEnabled); 
  ADDR_CHECK(ispSetLogEnabled);
  LOAD_FUNCTION_POINTER(h, ispSelectDevice);
  ADDR_CHECK(ispSelectDevice);
  LOAD_FUNCTION_POINTER(h, ispSelectCommHardware);
  ADDR_CHECK(ispSelectCommHardware);
  LOAD_FUNCTION_POINTER(h, ispOpenRs232Port);
  ADDR_CHECK(ispOpenRs232Port);
  LOAD_FUNCTION_POINTER(h, ispSyncTarget);
  ADDR_CHECK(ispSyncTarget);
  LOAD_FUNCTION_POINTER(h, ispParseHexFile);
  ADDR_CHECK(ispParseHexFile);
  LOAD_FUNCTION_POINTER(h, ispBlankCheckMemory);
  ADDR_CHECK(ispBlankCheckMemory);
  LOAD_FUNCTION_POINTER(h, ispProgramDevice);
  ADDR_CHECK(ispProgramDevice);
  LOAD_FUNCTION_POINTER(h, ispProgramAddrRange);
  ADDR_CHECK(ispProgramAddrRange);
  LOAD_FUNCTION_POINTER(h, ispReadDevice);
  ADDR_CHECK(ispReadDevice);
  LOAD_FUNCTION_POINTER(h, ispReadAddrRange);
  ADDR_CHECK(ispReadAddrRange);
  LOAD_FUNCTION_POINTER(h, ispVerifyDevice);
  ADDR_CHECK(ispVerifyDevice);
  LOAD_FUNCTION_POINTER(h, ispGetLastError);
  ADDR_CHECK(ispGetLastError);
  LOAD_FUNCTION_POINTER(h, ispExit);
  ADDR_CHECK(ispExit);
  LOAD_FUNCTION_POINTER(h, ispUpdateCmdsIds);
  ADDR_CHECK(ispUpdateCmdsIds);
  LOAD_FUNCTION_POINTER(h, ispOpenCanPort);
  ADDR_CHECK(ispOpenCanPort);
  LOAD_FUNCTION_POINTER(h, ispOpenUsbPort);
  ADDR_CHECK(ispOpenUsbPort);
  LOAD_FUNCTION_POINTER(h, ispSelectCanNode);
  ADDR_CHECK(ispSelectCanNode);
  LOAD_FUNCTION_POINTER(h, ispSelectMemory);
  ADDR_CHECK(ispSelectMemory);
  LOAD_FUNCTION_POINTER(h, ispEraseDevice);
  ADDR_CHECK(ispEraseDevice);
  LOAD_FUNCTION_POINTER(h, ispGetDeviceIndex);
  ADDR_CHECK(ispGetDeviceIndex);
  LOAD_FUNCTION_POINTER(h, ispDataLog);
  ADDR_CHECK(ispDataLog);    
  LOAD_FUNCTION_POINTER(h, ispSetDebugMode);
  ADDR_CHECK(ispSetDebugMode);
  LOAD_FUNCTION_POINTER(h, ispOpenLogFile);
  ADDR_CHECK(ispOpenLogFile);
  LOAD_FUNCTION_POINTER(h, ispExecCmd);
  ADDR_CHECK(ispExecCmd);
  LOAD_FUNCTION_POINTER(h, ispGetLastResult);
  ADDR_CHECK(ispGetLastResult);
  LOAD_FUNCTION_POINTER(h, ispGetMemorySize);
  ADDR_CHECK(ispGetMemorySize);
  LOAD_FUNCTION_POINTER(h, ispReadSignatureBytes);
  ADDR_CHECK(ispReadSignatureBytes);
  LOAD_FUNCTION_POINTER(h, ispReadSpecialByte);
  ADDR_CHECK(ispReadSpecialByte);
  LOAD_FUNCTION_POINTER(h, ispBlankCheckAddrRange);
  ADDR_CHECK(ispBlankCheckAddrRange);
  LOAD_FUNCTION_POINTER(h, ispFillBufferAddrRange);
  ADDR_CHECK(ispFillBufferAddrRange);
  LOAD_FUNCTION_POINTER(h, ispSetSecurityLevel);
  ADDR_CHECK(ispSetSecurityLevel);
  LOAD_FUNCTION_POINTER(h, ispGetErrorVecPtr);
  ADDR_CHECK(ispGetErrorVecPtr);
  LOAD_FUNCTION_POINTER(h, ispGetBufferAddrHi);
  ADDR_CHECK(ispGetBufferAddrHi);
  LOAD_FUNCTION_POINTER(h, ispGetBufferAddrLo);
  ADDR_CHECK(ispGetBufferAddrLo);
  LOAD_FUNCTION_POINTER(h, ispSerialize);
  ADDR_CHECK(ispSerialize);
  LOAD_FUNCTION_POINTER(h, ispWriteSpecialByte);
  ADDR_CHECK(ispWriteSpecialByte);
  LOAD_FUNCTION_POINTER(h, ispGetLastErrorMssg);
  ADDR_CHECK(ispGetLastErrorMssg);
  LOAD_FUNCTION_POINTER(h, ispGetErrorMssgFromIdx);
  ADDR_CHECK(ispGetErrorMssgFromIdx);
  LOAD_FUNCTION_POINTER(h, ispSetTimeout);
  ADDR_CHECK(ispSetTimeout);
  LOAD_FUNCTION_POINTER(h, ispSetAutoIsp);
  ADDR_CHECK(ispSetAutoIsp);
  LOAD_FUNCTION_POINTER(h, ispWriteHexFile);
  ADDR_CHECK(ispWriteHexFile);
  LOAD_FUNCTION_POINTER(h, ispSetDtrLow);
  ADDR_CHECK(ispSetDtrLow);
  LOAD_FUNCTION_POINTER(h, ispSetDtrHigh);
  ADDR_CHECK(ispSetDtrHigh);
  LOAD_FUNCTION_POINTER(h, ispSetRtsLow);
  ADDR_CHECK(ispSetRtsLow);
  LOAD_FUNCTION_POINTER(h, ispSetRtsHigh);
  ADDR_CHECK(ispSetRtsHigh);
  LOAD_FUNCTION_POINTER(h, ispEnterAppliMode);
  ADDR_CHECK(ispEnterAppliMode);
  LOAD_FUNCTION_POINTER(h, ispEnterIspMode);
  ADDR_CHECK(ispEnterIspMode);

  return PASS;
}



/*!
******************************************************************************
\fn         int main()
\brief	    ISP test main function.
******************************************************************************
*/
int main(int argc, char* argv[]) {

  int status = 0;

#ifdef WIN32
  HINSTANCE h;
  if ((h = LoadLibrary("AtJniIsp.dll")) == NULL) {
    return STATUS_CANNOT_LOAD_DLL;
  } else {
    loadLibFuncs(h);
  }
#else
  void* h = NULL;
  if ((h = dlopen("libatjniisp.so", RTLD_NOW)) == NULL) {
    perror(dlerror());
    return STATUS_CANNOT_LOAD_DLL;
  } else {
    loadLibFuncs(h);
  }
#endif

  // **********************************************************
  // ************** ISP software initialization ***************
  // **********************************************************

  setOperationTitle("Initializing");

  if (DYNCALL(ispInit()) == PASS) {
    display(PASS, NEWLINE);
    //    DYNCALL(ispSetDebugMode(1));
  } else {
    display(FAIL, NO_NEWLINE);
    return DYNCALL(ispGetLastError());
  }
	
  // **********************************************************
  // ***************** Enable Flip Logging ********************
  // **********************************************************

  DYNCALL(ispSetLogEnabled(0));

  // ********************************************************
  // ************** Microcontroller selection ***************
  // ********************************************************

  setOperationTitle("Device selection");

  if (DYNCALL(ispSelectDevice("AT89C51RD2")) == PASS) {
    display(PASS, NEWLINE);
  } else {
    display(FAIL, NO_NEWLINE);
    return DYNCALL(ispGetLastError());
  }

  // *************************************************
  // ************** Hardware selection ***************
  // *************************************************

  setOperationTitle("Hardware selection");

  if (DYNCALL(ispSelectCommHardware)(intrfce) == PASS) {
    display(PASS, NEWLINE);
  } else {
    display(FAIL, NO_NEWLINE);
    return DYNCALL(ispGetLastError());
  }

  // *************************************************
  // ************** Open communication ***************
  // *************************************************

  setOperationTitle("Opening port");

  switch (intrfce) {
  case RS232:
#ifdef WIN32
    status = DYNCALL(ispOpenRs232Port("COM1", 38400));
#else
    status = DYNCALL(ispOpenRs232Port("/dev/ttyS0", 38400));
#endif
    canItfce = false;
    break;
  case USB_PORT:
    status = DYNCALL(ispOpenUsbPort());
    canItfce = false;
    break;
  case VECTOR:
  case IXXAT:
  case PEAK:
  case SYSTEC_USB_CAN:
    status = DYNCALL(ispOpenCanPort(500, 0, 115200));
    canItfce = true;
    break;
  default:
    cout << "Invalid interface selection" << endl;
  }

  if (status == PASS) {
    display(PASS, NEWLINE);
  } else {
    display(FAIL, NO_NEWLINE);
    return DYNCALL(ispGetLastError());
  }

  // ***********************************************************
  // ************** Synchronize the RS232 target ***************
  // ***********************************************************

  if (SYNCHRO) {
    if (intrfce == RS232) {
      setOperationTitle("Synchronizing target");
      if (DYNCALL(ispSyncTarget())) {
	display(PASS, NEWLINE);
      } else {
	display(FAIL, NO_NEWLINE);
	status = DYNCALL(ispGetLastError());
	DYNCALL(ispExit());
	return status;
      }
    }
  }

  // ************************************************************
  // ************** Activate the CAN node for ISP ***************
  // ************************************************************

  // For CAN devices only.
  // In ISP mode, the ATMEL's bootloader accepts 0xFF as node number
  // for the 'select CAN node' command, whatever the actual node number is.

  if (canItfce) {
    setOperationTitle("Selecting CAN node");

    if (DYNCALL(ispSelectCanNode(0xFF))) {
      display(PASS, NEWLINE);
    } else {
      display(FAIL, NO_NEWLINE);
      status = DYNCALL(ispGetLastError());
      DYNCALL(ispExit());
      return status;
    }

    // We need to get the actual device node number to be able
    // to go back to ISP mode from appli mode.

    if (DYNCALL(ispReadSpecialByte(NNB))) {
      nnb = DYNCALL(ispGetLastResult());
    }

    setOperationTitle("Setting the CRIS");

    if (DYNCALL(ispWriteSpecialByte(CRIS, 0x00))) {
      display(PASS, NEWLINE);
    } else {
      display(FAIL, NO_NEWLINE);
      status = DYNCALL(ispGetLastError());
      DYNCALL(ispExit());
      return status;
    }
  }

  // ******************************************************
  // ************ Read the bootloader version *************
  // ******************************************************

  // Demonstrates how to read a device special byte.
  // The bootloader version byte always exists.
  // See ispdll.h for the enumeration of special bytes.

  if (READ_BLV) {
    setOperationTitle("Reading the bootloader version");

    if (DYNCALL(ispReadSpecialByte(BOOTLOADER_VERSION))) {
      display(PASS, NO_NEWLINE);
      string s = DYNCALL(ispGetLastResult());
      cout << "1." << s.substr(0, 1) << "." << s.substr(1, 1) << endl;
    } else {
      display(FAIL, NO_NEWLINE);
      status = DYNCALL(ispGetLastError());
      DYNCALL(ispExit());
      return status;
    }
  }

  // ******************************************************
  // *************** Erase the FLASH memory ***************
  // ******************************************************

  // Show block erasing for demo purpose.
  // Block erasing is not supported by all devices.

  if (FULL_ERASE) {
    setOperationTitle("Erasing FLASH");

    if (DYNCALL(ispEraseDevice())) {
      display(PASS, NEWLINE);
    } else {
      display(FAIL, NO_NEWLINE);
      status = DYNCALL(ispGetLastError());
      DYNCALL(ispExit());
      return status;
    }
  }

  // *****************************************************
  // *********** Blank check the FLASH memory ************
  // *****************************************************

  if (BLANK_CHECK) {
    setOperationTitle("Blank checking FLASH memory");

    if (DYNCALL(ispBlankCheckMemory())) {
      display(PASS, NEWLINE);
    } else {
      display(FAIL, NO_NEWLINE);
      status = DYNCALL(ispGetLastError());
      if (DYNCALL(ispGetLastError()) == STATUS_BLANK_CHECK_ERROR) {
	string s = DYNCALL(ispGetLastResult());
	cout << "at 0x" << s << endl;
      }
      DYNCALL(ispExit());
      return status;
    }
  }

  // **************************************************************
  // ************** Fill internal buffer with zeros ***************
  // **************************************************************

  // This is for demo about the way to fill the ISP internal buffer.

  if (FILL_ZEROS) {
    setOperationTitle("Filling buffer with 00");

    if (DYNCALL(ispFillBufferAddrRange(0, 0x3FF, "00"))) {
      display(PASS, NEWLINE);
    } else {
      display(FAIL, NO_NEWLINE);
      status = DYNCALL(ispGetLastError());
      DYNCALL(ispExit());
      return status;
    }
  }

  // *************************************************
  // ************** Parse the HEX file ***************
  // *************************************************

  if (PARSE_HEX) {
    setOperationTitle("Parsing HEX file");

    if (DYNCALL(ispParseHexFile("appli1.hex"))) {
      display(PASS, NEWLINE);
    } else {
      display(FAIL, NO_NEWLINE);
      status = DYNCALL(ispGetLastError());
      DYNCALL(ispExit());
      return status;
    }
  }

  // *************************************************
  // ************** Program the FLASH ****************
  // *************************************************

  if (PROGRAM_FLASH) {
    setOperationTitle("Programming FLASH");

    /*
      The address programming range is defined by the last HEX file parsing operation.
    */
    if (DYNCALL(ispProgramDevice())) {
      display(PASS, NEWLINE);
    } else {
      display(FAIL, NO_NEWLINE);
      status = DYNCALL(ispGetLastError());
      DYNCALL(ispExit());
      return status;
    }
  }

  // ************************************************
  // ************** Verify the FLASH ****************
  // ************************************************

  if (VERIFY_FLASH) {
    setOperationTitle("Verifying FLASH");

    string sAddrLo;
    string sAddrHi;

    /*
      The address programming range is defined by the last HEX file parsing operation.
      We can get the address min/max values by calling the ispGetBufferAddrLo/Hi functions.
    */
    if (DYNCALL(ispGetBufferAddrLo()) == PASS) {
      sAddrLo = DYNCALL(ispGetLastResult());
    } else {
      return 1;
    }

    if (DYNCALL(ispGetBufferAddrHi()) == PASS) {
      sAddrHi = DYNCALL(ispGetLastResult());
    } else {
      return 1;
    }

    ULONG nAddrLo = strtoul(sAddrLo.c_str(), NULL, 16);
    ULONG nAddrHi = strtoul(sAddrHi.c_str(), NULL, 16);

    if (DYNCALL(ispVerifyDevice(nAddrLo, nAddrHi))) {
      display(PASS, NEWLINE);
    } else {
      display(FAIL, NO_NEWLINE);
      status = DYNCALL(ispGetLastError());
      DYNCALL(ispExit());
      return status;
    }
  }

  // ************************************************
  // *************** Read the FLASH *****************
  // ************************************************

  // We read the FLASH memory and produce a HEX file from its content.
  // Call the ispReadDevice function to read the whole memory.

  if (READ_FLASH) {
    setOperationTitle("Reading FLASH");

    if (DYNCALL(ispReadAddrRange(0x00, 0x02000, "read.hex", HEX386))) {
      display(PASS, NEWLINE);
    } else {
      display(FAIL, NO_NEWLINE);
      status = DYNCALL(ispGetLastError());
      DYNCALL(ispExit());
      return status;
    }
  }

  // ************************************************
  // **************** Select EEPROM *****************
  // ************************************************

  if (SELECT_EEPROM) {
    setOperationTitle("Selecting EEPROM");

    if (DYNCALL(ispSelectMemory(EEPROM)) == PASS) {
      display(PASS, NEWLINE);
    } else {
      display(FAIL, NO_NEWLINE);
      status = DYNCALL(ispGetLastError());
      DYNCALL(ispExit());
      return status;
    }
  }

  // **************************************************************
  // **************** Fill EEPROM buffer with 0x55 ****************
  // **************************************************************

  // This is for demo about the way to fill the ISP internal buffer.
  if (FILL_EEPROM_BUFFER) {
    setOperationTitle("Filling EEPROM buffer with 55");

    if (DYNCALL(ispFillBufferAddrRange(0, 0x3FF, "55"))) {
      display(PASS, NEWLINE);
    } else {
      display(FAIL, NO_NEWLINE);
      status = DYNCALL(ispGetLastError());
      DYNCALL(ispExit());
      return status;
    }
  }

  // ************************************************
  // ***************** Program EEPROM ***************
  // ************************************************

  if (PROGRAM_EEPROM) {
    setOperationTitle("Programming EEPROM");

    if (DYNCALL(ispProgramDevice())) {
      display(PASS, NEWLINE);
    } else {
      display(FAIL, NO_NEWLINE);
      status = DYNCALL(ispGetLastError());
      DYNCALL(ispExit());
      return status;
    }
  }

  // ************************************************
  // ************** Verify the EEPROM ***************
  // ************************************************

  if (VERIFY_EEPROM) {
    setOperationTitle("Verifying EEPROM");

    if (DYNCALL(ispVerifyDevice(0, 0x3FF))) {
      display(PASS, NEWLINE);
    } else {
      display(FAIL, NO_NEWLINE);
      status = DYNCALL(ispGetLastError());
      DYNCALL(ispExit());
      return status;
    }
  }

  // ***************************************************
  // ************** Switch to appli mode ***************
  // ***************************************************
  /*
    The purpose of the following code is to show how to switch
    between ISP and application modes. If the embedded bootloader
    supports switching to application mode, you may uncomment this
    code to try it.
  */
  if (SWITCH_TO_APPLI) {
    setOperationTitle("Switching to appli mode");

    if (DYNCALL(ispEnterAppliMode(false, 0))) {
      display(PASS, NEWLINE);
    } else {
      display(FAIL, NO_NEWLINE);
      status = DYNCALL(ispGetLastError());
      DYNCALL(ispExit());
      return status;
    }
  }


  if (canItfce) {
    // Try to enter back ISP mode. Will probably fail until
    // we implement the proper mechanism in the firmware.

    if (GOBACKTO_ISP) {
      setOperationTitle("Switching to ISP mode");
      BYTE nnbByte = strtoul(nnb, NULL, 16);

      if (DYNCALL(ispEnterIspMode(nnbByte, 0xFF00))) {
	display(PASS, NEWLINE);
      } else {
	display(FAIL, NO_NEWLINE);
	status = DYNCALL(ispGetLastError());
	DYNCALL(ispExit());
	return status;
      }
    }


    if (VERIFY_POST_BACKTO_ISP) {
      // Try a verify device which should pass since we are
      // back in ISP mode.
      setOperationTitle("Verifying device");
      if (DYNCALL(ispVerifyDevice(0, 0x3FF))) {
	display(PASS, NEWLINE);
      } else {
	display(FAIL, NO_NEWLINE);
	status = DYNCALL(ispGetLastError());
	DYNCALL(ispExit());
	return status;
      }
    }
  }

  // ********************************************
  // **** Toggle DTR signal for demo purpose ****
  // ********************************************

  if (TOGGLE_DTR) {
    DYNCALL(ispSetDtrLow());
#ifdef WIN32
    Sleep(100);
#else
    usleep(100000);
#endif
    DYNCALL(ispSetDtrHigh());
#ifdef WIN32
    Sleep(100);
#else
    usleep(100000);
#endif
    DYNCALL(ispSetDtrLow());
  }

  // ********************************************
  // ************** Terminate ISP ***************
  // ********************************************

  // Always call the ispExit() function before exiting; it closes
  // any open port and frees dynamically allocated memory for internal
  // data buffer and objects.

  DYNCALL(ispExit());

#ifdef WIN32
  FreeLibrary(h);
#else
  dlclose(h);
#endif

  return 0;
}
