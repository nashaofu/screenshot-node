#ifndef PRTSCN_OSX_H_
#define PRTSCN_OSX_H_
#include <Foundation/Foundation.h>
#include <CoreServices/CoreServices.h>

struct IData
{
  unsigned int length;
  char * byte;
};

IData getScreen(const int, const int, const int, const int);

#endif
