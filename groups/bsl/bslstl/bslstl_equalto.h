// bslstl_equalto.h                                                   -*-C++-*-
#ifndef INCLUDED_BSLSTL_EQUALTO
#define INCLUDED_BSLSTL_EQUALTO

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide a binary functor conforming to the C++11 'equal_to' spec.
//
//@CLASSES:
//  equal_to: C++11-compliant binary functor applying 'operator=='
//
//@SEE_ALSO: bslstl_unorderedmap, bslstl_unorderedset
//
//@DESCRIPTION: This component provides the C+11 standard binary comparison
// functor, 'bsl::equal_to', that evaluates equality of two 'VALUE_TYPE'
// objects through the 'operator=='.  The application of the functor to two
// different objects 'o1' and 'o2' returns true if 'o1 == o2'.  Note that this
// the for use as keys in the standard unordered associative containers such as
// 'bsl::unordered_map' and 'bsl::unordered_set'.  Also note that this class is
// an empty POD type.
//
///Usage
///-----

// Prevent 'bslstl' headers from being included directly in 'BSL_OVERRIDES_STD'
// mode.  Doing so is unsupported, and is likely to cause compilation errors.
#if defined(BSL_OVERRIDES_STD) && !defined(BSL_STDHDRS_PROLOGUE_IN_EFFECT)
#error "<bslstl_equalto.h> header can't be included directly in \
BSL_OVERRIDES_STD mode"
#endif

#ifndef INCLUDED_BSLSCM_VERSION
#include <bslscm_version.h>
#endif

#ifndef INCLUDED_BSLMF_ISBITWISEMOVEABLE
#include <bslmf_isbitwisemoveable.h>
#endif

#ifndef INCLUDED_BSLMF_ISTRIVIALLYCOPYABLE
#include <bslmf_istriviallycopyable.h>
#endif

#ifndef INCLUDED_BSLMF_ISTRIVIALLYDEFAULTCONSTRUCTIBLE
#include <bslmf_istriviallydefaultconstructible.h>
#endif

#ifndef INCLUDED_BSLMF_NESTEDTRAITDECLARATION
#include <bslmf_nestedtraitdeclaration.h>
#endif

namespace bsl
{

                       // ===============
                       // struct equal_to
                       // ===============

template<class VALUE_TYPE>
struct equal_to {
    // This 'struct' defines a binary comparison functor applying 'operator=='
    // to two 'VALUE_TYPE' objects.  This class conforms to the C++11 standard
    // specification of 'std::equal_to' that does not require inheriting from
    // 'std::binary_function'.  Note that this class is an empty POD type.

    // TRAITS
    BSLMF_NESTED_TRAIT_DECLARATION(equal_to, is_trivially_copyable);

    // STANDARD TYPEDEFS
    typedef VALUE_TYPE first_argument_type;
    typedef VALUE_TYPE second_argument_type;
    typedef bool       result_type;

    //! equal_to() = default;
        // Create a 'equal_to' object.

    //! equal_to(const equal_to& original) = default;
        // Create a 'equal_to' object.  Note that as
        // 'equal_to' is an empty (stateless) type, this operation
        // will have no observable effect.

    //! ~equal_to() = default;
        // Destroy this object.

    // MANIPULATORS
    //! equal_to& operator=(const equal_to&) = default;
        // Assign to this object the value of the specified 'rhs' object, and
        // a return a reference providing modifiable access to this object.
        // Note that as 'equal_to' is an empty (stateless) type,
        // this operation will have no observable effect.

    // ACCESSORS
    bool operator()(const VALUE_TYPE& lhs, const VALUE_TYPE& rhs) const;
        // Return 'true' if the specified 'lhs' compares equal to the specified
        // 'rhs' using the equality-comparison operator, 'lhs == rhs'.
};

}  // namespace bsl

// ============================================================================
//                                TYPE TRAITS
// ============================================================================

// Type traits for STL *sequence* containers:
//: o A sequence container defines STL iterators.
//: o A sequence container is bitwise moveable if the allocator is bitwise
//:     moveable.
//: o A sequence container uses 'bslma' allocators if the parameterized
//:     'ALLOCATOR' is convertible from 'bslma::Allocator*'.

namespace bsl {

template<class VALUE_TYPE>
struct is_trivially_default_constructible<equal_to<VALUE_TYPE> >
: bsl::true_type
{};

template<class VALUE_TYPE>
struct is_trivially_copyable<equal_to<VALUE_TYPE> >
: bsl::true_type
{};

}

namespace BloombergLP {
namespace bslmf {

template<class VALUE_TYPE>
struct IsBitwiseMoveable<bsl::equal_to<VALUE_TYPE> >
: bsl::true_type
{};

}
}  // namespace BloombergLP

namespace bsl {

// ============================================================================
//                      INLINE FUNCTION DEFINITIONS
// ============================================================================

                       // --------------------
                       // struct bsl::equal_to
                       // --------------------

// ACCESSORS
template<class VALUE_TYPE>
inline
bool equal_to<VALUE_TYPE>::operator()(const VALUE_TYPE& lhs,
                                      const VALUE_TYPE& rhs) const
{
    return lhs == rhs;
}

}  // close namespace bsl

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