/*! \file utility.h

  \brief This file implements utility functions prototypes.

*/


#ifndef UTILITY_H
#define UTILITY_H


#ifdef WIN32
	// Tell the compiler to shut up.
	#pragma warning(disable:4786)
#else
	#include <unistd.h>
#endif //LINUX

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

enum { CLOSED, OPEN };

enum { FAIL, PASS };

#define DYNCALL(FUNC) lp##FUNC
#define DECLARE_FUNCTION_POINTER(FUNC)  PF_##FUNC lp##FUNC=NULL;  
#define EXTERN_FUNCTION_POINTER(FUNC)  extern PF_##FUNC lp##FUNC;

#ifdef WIN32
#define LOAD_FUNCTION_POINTER(DLL,FUNC) lp##FUNC = (PF_##FUNC)GetProcAddress(DLL, #FUNC);
#define ADDR_CHECK(FUNC) if (lp##FUNC == NULL) {MessageBox(NULL, "Missing function in DLL", "DLL Message", MB_OK);}
#define UPPERCASE std::uppercase
#else
#include <dlfcn.h>
#define LOAD_FUNCTION_POINTER(DLL,FUNC) lp##FUNC = (PF_##FUNC)dlsym(DLL, #FUNC);
#define ADDR_CHECK(FUNC) if (lp##FUNC == NULL) {printf("%s\n", "Could not get a pointer on this function.");}
	
#define UPPERCASE ios::uppercase
#endif



enum {
    T_500  = 500,
    T_1SEC = 1000,
    T_2SEC = 2000,
    T_3SEC = 3000,
    T_4SEC = 4000,
    T_5SEC = 5000,
    T_10SEC = 10000,
    T_20SEC = 20000
};



/*!
******************************************************************************
\fn         void stringHexFmt(string & s, const T & t)
\brief	    Accepts a value of any type and writes it into a user-supplied
			string s in hexadecimal format without any leading 0X.
\param		s		User-supplied string which gets the result
\param		width	Number of chars of the output string
\param		t		Value to be converted
\par        Example of use:
\c          string s;
\c			stringHexFmt( s, 4, 128 );		// s = 0080
******************************************************************************
*/
/*
template <typename T> void stringHexFmt(string & s, int width, const T & t) {
  ostringstream oss;
  oss << hex << UPPERCASE << setfill('0') << setw(width) << static_cast<unsigned long>(t);
  s = oss.str();
}
*/
void stringHexFmt(string & s, int width, int value);

/*!
******************************************************************************
\fn         void stringDecFmt(string & s, const T & t)
\brief	    Accepts a value of any type and writes it into a user-supplied
			string s in decimal format.
\param		s		User-supplied string which gets the result
\param		t		Value to be converted
\par        Example of use:
\c          string s;
\c			stringDecFmt( s, 128 );		// s = 128
******************************************************************************
*/
template <typename T> void stringDecFmt(string & s, const T & t) {
  ostringstream oss;
  oss << t;
  s = oss.str();
}

/*
The castStream function template converts a variable of type
in_value to a variable of type out_type.
In the following example, castStream converts a string to a double:

string s = �18.67�;
double d = castStream < double > (s); // assign 18.67 to d
*/
template <typename Tout, typename Tin> Tout castStream(const Tin & t) {
  std::stringstream ss;
  ss << t;
  Tout ret;
  ss >> ret;
  return ret;
}


/* String bytes swapping.
   aabbccdd -> ddccbbaa
*/
string& reverseEndian(string* toStr, const string& fromStr);


#endif // UTILITY_H
