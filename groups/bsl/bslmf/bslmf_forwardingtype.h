// bslmf_forwardingtype.h                                             -*-C++-*-
#ifndef INCLUDED_BSLMF_FORWARDINGTYPE
#define INCLUDED_BSLMF_FORWARDINGTYPE

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide a meta-function for determining an optimal forwarding type.
//
//@CLASSES:
//  bslmf::ForwardingType: meta-function to determine optimal forwarding type
//
//@SEE_ALSO: bslmf_removecvq
//
//@DESCRIPTION: This component provides a meta function determining the most
// efficient forwarding type for a given template type 'TYPE'.
//
// For instance, on some platforms, non-modifiable references to user types
// should be taken by 'const&' to avoid a potentially expensive copy, but basic
// types (e.g., fundamental types, pointer types, function references and
// pointers) would be more efficiently taken by (non-reference) value, even
// though this involves making a copy.  This is because the copy can then be
// used internally by the function, whereas a 'const&' cannot and would have to
// be copied anyway (if used locally by the compiler), adding to the cost of
// passing the 'const&' argument.
//
// This component should not be used except when performance is of highest
// concern.
//
///Usage
///------
// The following example shows the result of instantiating
// 'bslmf::ForwardingType' on a number of different types.  First declare some
// types to compare:
//..
//  struct MyType {};
//  typedef int                    T1;
//  typedef int&                   T2;
//  typedef const volatile double& T3;
//  typedef const double &         T4;
//  typedef const float * &        T5;
//  typedef const float * const &  T6;
//  typedef MyType                 T7;
//  typedef const MyType&          T8;
//  typedef MyType&                T9;
//  typedef Mytype*                T10;
//..
// Next declare the expected result types:
//..
//  typedef int                    EXP1;
//  typedef int&                   EXP2;
//  typedef const volatile double& EXP3;
//  typedef double                 EXP4;
//  typedef const float * &        EXP5;
//  typedef const float *          EXP6;
//  typedef const MyType&          EXP7;
//  typedef const MyType&          EXP8;
//  typedef MyType&                EXP9;
//  typedef Mytype*                EXP10;
//..
// Finally, check that they match:
//..
//  assert(1 == (bsl::is_same<bslmf::ForwardingType<T1>::Type,
//                             EXP1>::value));
//  assert(1 == (bsl::is_same<bslmf::ForwardingType<T2>::Type,
//                             EXP2>::value));
//  assert(1 == (bsl::is_same<bslmf::ForwardingType<T3>::Type,
//                             EXP3>::value));
//  assert(1 == (bsl::is_same<bslmf::ForwardingType<T4>::Type,
//                             EXP4>::value));
//  assert(1 == (bsl::is_same<bslmf::ForwardingType<T5>::Type,
//                             EXP5>::value));
//  assert(1 == (bsl::is_same<bslmf::ForwardingType<T6>::Type,
//                             EXP6>::value));
//  assert(1 == (bsl::is_same<bslmf::ForwardingType<T7>::Type,
//                             EXP7>::value));
//  assert(1 == (bsl::is_same<bslmf::ForwardingType<T8>::Type,
//                             EXP8>::value));
//  assert(1 == (bsl::is_same<bslmf::ForwardingType<T9>::Type,
//                             EXP9>::value));
//  assert(1 == (bsl::is_same<bslmf::ForwardingType<T10>::Type,
//                             EXP10>::value));
//..

#ifndef INCLUDED_BSLSCM_VERSION
#include <bslscm_version.h>
#endif

#ifndef INCLUDED_BSLMF_FUNCTIONPOINTERTRAITS
#include <bslmf_functionpointertraits.h>
#endif

#ifndef INCLUDED_BSLMF_ISENUM
#include <bslmf_isenum.h>
#endif

#ifndef INCLUDED_BSLMF_ISFUNDAMENTAL
#include <bslmf_isfundamental.h>
#endif

#ifndef INCLUDED_BSLMF_ISPOINTERTOMEMBER
#include <bslmf_ispointertomember.h>
#endif

#ifndef INCLUDED_BSLMF_MEMBERFUNCTIONPOINTERTRAITS
#include <bslmf_memberfunctionpointertraits.h>
#endif

#ifndef INCLUDED_BSLMF_REMOVECVQ
#include <bslmf_removecvq.h>
#endif

#ifndef INCLUDED_CSTDDEF
#include <cstddef>       // 'std::size_t'
#define INCLUDED_CSTDDEF
#endif

namespace BloombergLP {


namespace bslmf {

template <typename TYPE, int IS_BASIC_TYPE, int IS_REFERENCE>
struct ForwardingType_Imp;

                        // ====================
                        // class ForwardingType
                        // ====================

template <typename TYPE>
struct ForwardingType {
    // This template is used to specialize 'TYPE' such that arguments of type
    // 'TYPE' can be efficiently forwarded by reference or pointer.

    enum { BSLMF_FORWARDING_TYPE_ID = 1 };  // For testing only.
    enum {
        IS_BASIC_TYPE = bsl::is_fundamental<TYPE>::value ||
                        bsl::is_member_pointer<TYPE>::value ||
                        IsFunctionPointer<TYPE>::value ||
                        IsFunctionPointer<TYPE*>::value ||
                        bsl::is_enum<TYPE>::value
    };

    typedef typename
        ForwardingType_Imp<TYPE, IS_BASIC_TYPE, 0 >::Type Type;
};

// PARTIAL SPECIALIZATIONS
template <typename TYPE>
struct ForwardingType<const TYPE&> {
    // This specialization is used when the template parameter of
    // 'ForwardingType' is a 'const T&' and 'T' is not a volatile type.  In
    // that case, it may be advantageous to pass an argument by value if 'T' is
    // a basic type, but not if it is a user-defined type.

    enum { BSLMF_FORWARDING_TYPE_ID = 2 };  // For testing only.
    enum {
        IS_BASIC_TYPE = bsl::is_fundamental<TYPE>::value ||
                        bsl::is_member_pointer<TYPE>::value ||
                        IsFunctionPointer<TYPE>::value ||
                        IsFunctionPointer<TYPE*>::value ||
                        bsl::is_enum<TYPE>::value
    };

    typedef typename
        ForwardingType_Imp<const TYPE, IS_BASIC_TYPE, 0 >::Type Type;
};

template <typename TYPE>
struct ForwardingType<const volatile TYPE&> {
    // This specialization is used when the template parameter of
    // 'ForwardingType' is a 'const volatile T&'.  In that case, this template
    // parameter cannot be forwarded as any other type.

    enum { BSLMF_FORWARDING_TYPE_ID = 3 };  // For testing only.

    typedef const volatile TYPE& Type;
};

template <typename TYPE>
struct ForwardingType<volatile TYPE&> {
    // This specialization is used when the template parameter of
    // 'ForwardingType' is a 'const volatile T&'.  In that case, this template
    // parameter cannot be forwarded as any other type.

    enum { BSLMF_FORWARDING_TYPE_ID = 4 };  // For testing only.

    typedef volatile TYPE* Type;
};

template <typename TYPE>
struct ForwardingType<TYPE&>
: public ForwardingType_Imp<TYPE, 0, 1> {
    // This specialization is used when the template parameter of
    // 'ForwardingType' is a 'T&' and 'T' is not cv-qualified.

    enum { BSLMF_FORWARDING_TYPE_ID = 5 };  // For testing only.
};

template <typename TYPE>
struct ForwardingType<TYPE*> {
    // Pointer rvalues should not be forwarded any other way.

    enum { BSLMF_FORWARDING_TYPE_ID = 6 };  // For testing only.
    typedef TYPE* Type;
};

template <typename TYPE>
struct ForwardingType<TYPE* const&> {
    // Pointer rvalues should not be forwarded any other way.

    enum { BSLMF_FORWARDING_TYPE_ID = 7 };  // For testing only.
    typedef TYPE* Type;
};

                        // =========================
                        // class ConstForwardingType
                        // =========================

template <typename TYPE>
struct ConstForwardingType : public ForwardingType<const TYPE>{
    // Use 'ConstForwardingType<TYPE>' for forwarding an rvalue of the given
    // 'TYPE'.  Note that for lvalues and pointer types,
    // 'ConstForwardingType<TYPE>' should produce the same type as the
    // 'ForwardingType<TYPE>'.
};

// PARTIAL SPECIALIZATIONS
template <typename TYPE>
struct ConstForwardingType<TYPE&> : public ForwardingType<TYPE&>{
};

template <typename TYPE>
struct ConstForwardingType<TYPE*> : public ForwardingType<TYPE*>{
};

                        // ========================
                        // class ForwardingType_Imp
                        // ========================

template <typename TYPE, int IS_BASIC_TYPE, int IS_REFERENCE>
struct ForwardingType_Imp {
    typedef TYPE& Type;
};

// PARTIAL SPECIALIZATIONS
template <typename TYPE>
struct ForwardingType_Imp<TYPE,0,0> {
    typedef const TYPE& Type;
};

template <typename TYPE, std::size_t NUM_ELEMENTS>
struct ForwardingType_Imp<TYPE [NUM_ELEMENTS], 0, 0> {
    typedef TYPE *Type;
};

template <typename TYPE, std::size_t NUM_ELEMENTS>
struct ForwardingType_Imp<TYPE [NUM_ELEMENTS], 0, 1> {
    typedef TYPE *Type;
};

template <typename TYPE>
struct ForwardingType_Imp<TYPE,1, 0> {
    typedef typename bsl::remove_cv<TYPE>::type Type;
};

}  // close package namespace


}  // close enterprise namespace

#endif

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
