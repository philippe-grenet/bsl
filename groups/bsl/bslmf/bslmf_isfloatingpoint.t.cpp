// bslmf_isfloatingpoint.t.cpp                                        -*-C++-*-
#include <bslmf_isfloatingpoint.h>

#include <bsls_bsltestutil.h>

#include <cstdlib>
#include <cstdio>

using namespace std;
using namespace bsl;
using namespace BloombergLP;

//=============================================================================
//                                TEST PLAN
//-----------------------------------------------------------------------------
//                                Overview
//                                --------
// The component under test defines a meta-functions, 'bsl::is_floating_point',
// that determine whether a template parameter type is a floating-point type.
// Thus, we need to ensure that the values returned by the meta-functions is
// correct for each possible category of types.
//
// ----------------------------------------------------------------------------
// PUBLIC CLASS DATA
// [ 1] bsl::is_floating_point::value
//
// ----------------------------------------------------------------------------
// [ 2] USAGE EXAMPLE

//=============================================================================
//                       STANDARD BDE ASSERT TEST MACRO
//-----------------------------------------------------------------------------
// NOTE: THIS IS A LOW-LEVEL COMPONENT AND MAY NOT USE ANY C++ LIBRARY
// FUNCTIONS, INCLUDING IOSTREAMS.
static int testStatus = 0;

void aSsErT(bool b, const char *s, int i)
{
    if (b) {
        printf("Error " __FILE__ "(%d): %s    (failed)\n", i, s);
        if (testStatus >= 0 && testStatus <= 100) ++testStatus;
    }
}

# define ASSERT(X) { aSsErT(!(X), #X, __LINE__); }

//=============================================================================
//                       STANDARD BDE TEST DRIVER MACROS
//-----------------------------------------------------------------------------
#define LOOP_ASSERT  BSLS_BSLTESTUTIL_LOOP_ASSERT
#define LOOP2_ASSERT BSLS_BSLTESTUTIL_LOOP2_ASSERT
#define LOOP3_ASSERT BSLS_BSLTESTUTIL_LOOP3_ASSERT
#define LOOP4_ASSERT BSLS_BSLTESTUTIL_LOOP4_ASSERT
#define LOOP5_ASSERT BSLS_BSLTESTUTIL_LOOP5_ASSERT
#define LOOP6_ASSERT BSLS_BSLTESTUTIL_LOOP6_ASSERT

#define Q   BSLS_BSLTESTUTIL_Q   // Quote identifier literally.
#define P   BSLS_BSLTESTUTIL_P   // Print identifier and value.
#define P_  BSLS_BSLTESTUTIL_P_  // P(X) without '\n'.
#define T_  BSLS_BSLTESTUTIL_T_  // Print a tab (w/o newline).
#define L_  BSLS_BSLTESTUTIL_L_  // current Line number

//=============================================================================
//                  GLOBAL TYPEDEFS/CONSTANTS FOR TESTING
//-----------------------------------------------------------------------------

namespace {

struct TestType {
    // This user-defined type is used for testing.
};

typedef int (TestType::*MethodPtrTestType) ();
    // This pointer to non-static function member type is used for testing.

typedef void (*FunctionPtrTestType) ();
    // This function pointer type is used for testing.

}  // close unnamed namespace

#define TYPE_ASSERT_CVQ(metaFunc, member, type, result)                      \
    ASSERT(result == metaFunc<type>::member);                                 \
    ASSERT(result == metaFunc<type const>::member);                           \
    ASSERT(result == metaFunc<type volatile>::member);                        \
    ASSERT(result == metaFunc<type const volatile>::member);

#define TYPE_ASSERT_CVQ_REF(metaFunc, member, type, result)                   \
    ASSERT(result == metaFunc<type&>::member);                                \
    ASSERT(result == metaFunc<type const&>::member);                          \
    ASSERT(result == metaFunc<type volatile&>::member);                       \
    ASSERT(result == metaFunc<type const volatile&>::member);

//=============================================================================
//                              MAIN PROGRAM
//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    int test = argc > 1 ? atoi(argv[1]) : 0;
    int verbose = argc > 2;
    int veryVerbose = argc > 3;

    (void) verbose;
    (void) veryVerbose;

    printf("TEST " __FILE__ " CASE %d\n", test);

    switch (test) { case 0:
      case 2: {
        // --------------------------------------------------------------------
        // USAGE EXAMPLE
        //
        // Concerns:
        //: 1 The usage example provided in the component header file compiles,
        //:   links, and runs as shown.
        //
        // Plan:
        //: 1 Incorporate usage example from header into test driver, remove
        //:   leading comment characters, and replace 'assert' with 'ASSERT'.
        //:   (C-1)
        //
        // Testing:
        //   USAGE EXAMPLE
        // --------------------------------------------------------------------

        if (verbose) printf("\nUSAGE EXAMPLE\n"
                            "\n=============\n");

///Usage
///-----
// In this section we show intended use of this component.
//
///Example 1: Verify Floating-Point Types
///- - - - - - - - - - - - - - - -
// Suppose that we want to assert whether a particular type is a floating-point
// type.
//
// First, we create two 'typedef's -- a floating-point type and a
// non-floating-point type:
//..
        typedef void MyType;
        typedef float  MyFloatingPointType;
//..
// Now, we instantiate the 'bsl::is_floating_point' template for each of the
// 'typedef's and assert the 'value' static data member of each instantiation:
//..
        ASSERT(false == bsl::is_floating_point<MyType>::value);
        ASSERT(true == bsl::is_floating_point<MyFloatingPointType>::value);
//..

      } break;
      case 1: {
        // --------------------------------------------------------------------
        // 'bsl::is_floating_point::value'
        //   Ensure that 'bsl::is_floating_point' returns the correct values
        //   for a variety of a variety of template parameter types.
        //
        // Concerns:
        //: 1 'is_floating_point::value' is 'false' when 'TYPE' is a (possibly
        //:   cv-qualified) non-integral primitve type.
        //
        //: 2 'is_floating_point::value' is 'false' when 'TYPE' is a (possibly
        //:   cv-qualified) user-defined type.
        //:
        //: 3 'is_floating_point::value' is 'true' when 'TYPE' is a (possibly
        //:   cv-qualified) floating-point type.
        //
        // Plan:
        //   Verify that 'bsl::is_floating_point::value' has the correct value
        //   for each concern.
        //
        // Testing:
        //   bsl::is_floating_point::value
        // --------------------------------------------------------------------

        if (verbose) printf("\nbsl::is_floating_point::value\n"
                            "\n=============================\n");

        // C-1
        TYPE_ASSERT_CVQ(bsl::is_floating_point, value, int, false);
        TYPE_ASSERT_CVQ(bsl::is_floating_point, value, long int, false);

        // C-2
        TYPE_ASSERT_CVQ(bsl::is_floating_point, value, TestType, false);

        // C-3
        TYPE_ASSERT_CVQ(bsl::is_floating_point, value, float, true);
        TYPE_ASSERT_CVQ(bsl::is_floating_point, value, double, true);
        TYPE_ASSERT_CVQ(bsl::is_floating_point, value, long double, true);

      } break;
      default: {
        fprintf(stderr, "WARNING: CASE `%d' NOT FOUND.\n", test);
        testStatus = -1;
      }
    }

    if (testStatus > 0) {
        fprintf(stderr, "Error, non-zero test status = %d.\n", testStatus);
    }

    return testStatus;
}

// ----------------------------------------------------------------------------
// Copyright (C) 2012 Bloomberg L.P.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------- END-OF-FILE ----------------------------------
