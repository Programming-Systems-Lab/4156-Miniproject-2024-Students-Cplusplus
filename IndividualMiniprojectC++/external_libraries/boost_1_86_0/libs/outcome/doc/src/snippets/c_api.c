/* Example of Outcome used with C APIs
(C) 2017-2024 Niall Douglas <http://www.nedproductions.biz/> (4 commits)


Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#define _CRT_SECURE_NO_WARNINGS 1

#include <errno.h>

#include <stdio.h>
#include <string.h>  // for strerror
// This header in Experimental Outcome is pure C, it provides a suite of C helper macros
#include "../../../include/outcome/experimental/result.h"

//! [preamble]
// Declare our C++ function's returning result type. Only needs to be done once.
// This declares an `status_result<size_t, system_code>` which is an alias to
// `basic_result<size_t, status_code<erased<intptr_t>>>`.
//
// The first parameter is some unique identifier for this type which will be used
// whenever we reference this type in the future.
CXX_DECLARE_RESULT_SYSTEM(to_string_rettype, size_t);

// Tell C about our extern C++ function `to_string()`
extern CXX_RESULT_SYSTEM(to_string_rettype) _Z9to_stringPcmi(char *buffer, size_t bufferlen, int v);
//! [preamble]

//! [example]
void print(int v)
{
  char buffer[4];
  CXX_RESULT_SYSTEM(to_string_rettype) res;

  res = _Z9to_stringPcmi(buffer, sizeof(buffer), v);
  if(CXX_RESULT_HAS_VALUE(res))
  {
    printf("to_string(%d) fills buffer with '%s' of %zu characters\n", v, buffer, res.value);
    return;
  }
  // Is the error returned in the POSIX domain and thus an errno?
  if(CXX_RESULT_ERROR_IS_ERRNO(res))
  {
    fprintf(stderr, "to_string(%d) failed with error code %d (%s)\n", v, (int) res.error.value, strerror((int) res.error.value));
    return;
  }
  fprintf(stderr, "to_string(%d) failed with unknown error code %lld\n", v, (long long) res.error.value);
}

int main(void)
{
  print(9);
  print(99);
  print(999);
  print(9999);
  return 0;
}
//! [example]

extern CXX_RESULT_SYSTEM(to_string_rettype) _Z9to_stringPcmi(char *buffer, size_t bufferlen, int v)
{
  // Fake a C++ function so it'll compile and run
  CXX_RESULT_SYSTEM(to_string_rettype) ret;
  memset(&ret, 0, sizeof(ret));
  char temp[256];
  sprintf(temp, "%d", v);
  size_t len = strlen(temp);
  if(len > bufferlen - 1)
  {
    ret.flags |= 18U;
    ret.error.value = ENOBUFS;
    return ret;
  }
  memcpy(buffer, temp, len + 1);
  ret.flags |= 1U;
  ret.value = len;
  return ret;
}