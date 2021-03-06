#include <stdlib.h>

#include <string>
#include <iostream>

using namespace std;

#include "pluton/service.h"

//////////////////////////////////////////////////////////////////////
// This is a sample pluton service that demonstrates the common parts
// of the interface and uses them in various different ways for
// demonstration purposes. This program compiles and runs as a service
// which simply echos the request back to the client with some leading
// text to show that the request was exchanged.
//
// Generally speaking, this is a well-coded pluton service from the
// perspective that it assiduously checks all return codes and logs
// all unexpected results.
//////////////////////////////////////////////////////////////////////

int
main(int argc, char** argv)
{
  pluton::service S("sampleService");

  if (!S.initialize()) {
    clog << S.getFault().getMessage("Fatal: initialize() failed in sampleService")  << endl;
    exit(1);
  }

  // Simply iterate on requests

  while (S.getRequest()) {

    string request;			// Be in-efficient and slurp the request
    S.getRequestData(request);		// into a string.

    string response = "testService got: ";
    response += request;

    if (!S.sendResponse(response)) {
      clog << S.getFault().getMessage("Fatal: sendResponse() failed in sampleService") << endl;
      exit(1);
    }
  }

  //////////////////////////////////////////////////////////////////////
  // Check to see if getRequest faulted or we're just being
  // told terminated.
  //////////////////////////////////////////////////////////////////////

  if (S.hasFault()) {
    clog << S.getFault().getMessage("Fatal: getRequest() failed in sampleService") << endl;
    exit(2);
  }

  return 0;		// Cause destructor to be called
}
