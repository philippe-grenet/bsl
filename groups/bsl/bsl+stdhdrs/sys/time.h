/* sys/time.h                                                        -*-C-*- */
#ifndef INCLUDED_NATIVE_C_SYS_TIME
#define INCLUDED_NATIVE_C_SYS_TIME

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

/*
//@PURPOSE: Provide functionality of the corresponding C++ Standard header
//
//@SEE_ALSO: package bsl+stdhdrs
//
//@DESCRIPTION: Provide functionality of the corresponding C++ standard header.
// This file includes the compiler provided native standard header.  In
// addition, in 'bde-stl' mode (used by Bloomberg managed code, see
// 'bsl+stdhdrs.txt' for more information) include the corresponding header in
// 'bsl+bslhdrs' as well as 'bsl_stdhdrs_prologue.h' and
// 'bsl_stdhdrs_epilogue.h'.  This includes the respective 'bsl' types and
// places them in the 'std' namespace.
*/

#if !defined(BSL_OVERRIDES_STD) || !defined(__cplusplus)

#   ifndef INCLUDED_BSL_STDHDRS_INCPATH
#   include <bsl_stdhdrs_incpaths.h>
#   endif

#   include BSL_NATIVE_SYS_TIME_HEADER(sys/time.h)

#else  /* defined(BSL_OVERRIDES_STD) */

#   ifndef BSL_STDHDRS_PROLOGUE_IN_EFFECT
#   include <bsl_stdhdrs_prologue.h>
#   endif

#   ifndef BSL_STDHDRS_RUN_EPILOGUE
#   define BSL_STDHDRS_RUN_EPILOGUE
#   define BSL_STDHDRS_EPILOGUE_RUN_BY_c_sys_time
#   endif

#   ifndef INCLUDED_BSL_STDHDRS_INCPATH
#   include <bsl_stdhdrs_incpaths.h>
#   endif

#   include BSL_NATIVE_SYS_TIME_HEADER(sys/time.h)

// This native header does not define any symbols in namespace 'std' to import,
// so the following include is not necessary:
// #include <bsl_c_sys_time.h>

#   ifdef BSL_STDHDRS_EPILOGUE_RUN_BY_c_sys_time
#   undef BSL_STDHDRS_EPILOGUE_RUN_BY_c_sys_time
#   include <bsl_stdhdrs_epilogue.h>
#   endif

#endif  /* BSL_OVERRIDES_STD */

#endif  /* INCLUDED_NATIVE_C_SYS_TIME */

/*
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
*/