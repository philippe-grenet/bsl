// bslstl_unorderedmultiset.h                                         -*-C++-*-
#ifndef INCLUDED_BSLSTL_UNORDEREDMULTISET
#define INCLUDED_BSLSTL_UNORDEREDMULTISET

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide an STL-compliant unordered_multiset class.
//
//@CLASSES:
//   bsl::unordered_multiset : hashed-map container
//
//@SEE_ALSO: bsl+stdhdrs
//
//@DESCRIPTION: This component defines a single class template
// 'unordered_multiset', implementing the standard container holding a
// collection of multiple keys with no guarantees on ordering.
//
// An instantiation of 'unordered_multiset' is an allocator-aware,
// value-semantic type whose salient attributes are its size (number of keys)
// and the set of keys the 'unordered_multiset' contains, without regard to
// their order.  If 'unordered_multiset' is instantiated with a key type that
// is not itself value-semantic, then it will not retain all of its
// value-semantic qualities.  In particular, if the key type cannot be tested
// for equality, then an 'unordered_multiset' containing that type cannot be
// tested for equality.  It is even possible to instantiate
// 'unordered_multiset' with a key type that does not have an accessible
// copy-constructor, in which case the 'unordered_multiset' will not be
// copyable.  Note that the equality operator 'operator==' for each element is
// used to determine when two 'unordered_multiset' objects have the same value,
// and not the equality comparator supplied at construction.
//
// An 'unordered_multiset' meets the requirements of an unordered associative
// container with forward iterators in the C++11 standard [unord].  The
// 'unordered_multiset' implemented here adheres to the C++11 standard, except
// that it does not have interfaces that take rvalue references,
// 'initializer_list', 'emplace', or operations taking a variadic number of
// template parameters.  Note that excluded C++11 features are those that
// require (or are greatly simplified by) C++11 compiler support.
//
///Requirements on 'KEY'
///---------------------
// An 'unordered_multiset' instantiation is a fully "Value-Semantic Type" (see
// {'bsldoc_glossary'}) only if the supplied 'KEY' template parameters is
// fully value-semantic.  It is possible to instantiate an 'unordered_multiset'
// with 'KEY' parameter arguments that do not provide a full set of
// value-semantic operations, but then some methods of the container may not be
// instantiable.  The following terminology, adopted from the C++11 standard,
// is used in the function documentation of 'unordered_multiset' to describe a
// function's requirements for the 'KEY' template parameter.  These terms are
// also defined in section [utility.arg.requirements] of the C++11 standard.
// Note that, in the context of an 'unordered_multiset' instantiation, the
// requirements apply specifically to the 'unordered_multiset's entry type,
// 'value_type', which is an alias for 'KEY'.
//
//: "default-constructible": The type provides an accessible default
//:                          constructor.
//:
//: "copy-constructible": The type provides an accessible copy constructor.
//:
//: "equality-comparable": The type provides an equality-comparison operator
//:     that defines an equivalence relationship and is both reflexive and
//:     transitive.
//
///Memory Allocation
///-----------------
// The type supplied as a set's 'ALLOCATOR' template parameter determines how
// that set will allocate memory.  The 'unordered_multiset' template supports
// allocators meeting the requirements of the C++11 standard
// [allocator.requirements], and in addition it supports scoped-allocators
// derived from the 'bslma::Allocator' memory allocation protocol.  Clients
// intending to use 'bslma' style allocators should use the template's default
// 'ALLOCATOR' type: The default type for the 'ALLOCATOR' template parameter,
// 'bsl::allocator', provides a C++11 standard-compatible adapter for a
// 'bslma::Allocator' object.
//
///'bslma'-Style Allocators
/// - - - - - - - - - - - -
// If the parameterized 'ALLOCATOR' type of an 'unordered_multiset'
// instantiation is 'bsl::allocator', then objects of that set type will
// conform to the standard behavior of a 'bslma'-allocator-enabled type.  Such
// a set accepts an optional 'bslma::Allocator' argument at construction.  If
// the address of a 'bslma::Allocator' object is explicitly supplied at
// construction, it will be used to supply memory for the 'unordered_multiset'
// throughout its lifetime; otherwise, the 'unordered_multiset' will use the
// default allocator installed at the time of the 'unordered_multiset's
// construction (see 'bslma_default').  In addition to directly allocating
// memory from the indicated 'bslma::Allocator', an 'unordered_multiset'
// supplies that allocator's address to the constructors of contained objects
// of the parameterized 'KEY' types with the
// 'bslalg::TypeTraitUsesBslmaAllocator' trait.
//
///Operations
///----------
// This section describes the run-time complexity of operations on instances
// of 'unordered_multiset':
//..
//  Legend
//  ------
//  'K'             - parameterized 'KEY' type of the unordered multiset
//  'a', 'b'        - two distinct objects of type 'unordered_multiset<K>'
//  'n', 'm'        - number of elements in 'a' and 'b' respectively
//  'w'             - number of buckets of 'a'
//  'value_type'    - unoredered_multiset<K>::value_type
//  'c'             - comparator providing an ordering for objects of type 'K'
//  'al             - an STL-style memory allocator
//  'i1', 'i2'      - two iterators defining a sequence of 'value_type' objects
//  'k'             - an object of type 'K'
//  'v'             - an object of type 'value_type'
//  'p1', 'p2'      - two iterators belonging to 'a'
//  distance(i1,i2) - the number of elements in the range [i1, i2)
//  distance(p1,p2) - the number of elements in the range [p1, p2)
//
//  +----------------------------------------------------+--------------------+
//  | Operation                                          | Complexity         |
//  +====================================================+====================+
//  | unordered_multiset<K> a; (default construction)    | O[1]               |
//  | unordered_multiset<K> a(al);                       |                    |
//  +----------------------------------------------------+--------------------+
//  | unordered_multiset<K> a(b); (copy construction)    | Average: O[n]      |
//  | unordered_multiset<K> a(b, al);                    | Worst:   O[n^2]    |
//  +----------------------------------------------------+--------------------+
//  | unordered_multiset<K> a(w);                        | O[n]               |
//  | unordered_multiset<K> a(w, hf);                    |                    |
//  | unordered_multiset<K> a(w, hf, eq);                |                    |
//  | unordered_multiset<K> a(w, hf, eq, al);            |                    |
//  +----------------------------------------------------+--------------------+
//  | unordered_multiset<K> a(i1, i2);                   | Average: O[        |
//  | unordered_multiset<K> a(i1, i2, w)                 |   distance(i1, i2)]|
//  | unordered_multiset<K> a(i1, i2, w, hf);            | Worst:   O[n^2]    |
//  | unordered_multiset<K> a(i1, i2, w, hf, eq);        |                    |
//  | unordered_multiset<K> a(i1, i2, w, hf, eq, al);    |                    |
//  +----------------------------------------------------+--------------------+
//  | a.~unordered_multiset<K>(); (destruction)          | O[n]               |
//  +----------------------------------------------------+--------------------+
//  | a = b;          (assignment)                       | Average: O[n]      |
//  |                                                    | Worst:   O[n^2]    |
//  +----------------------------------------------------+--------------------+
//  | a.begin(), a.end(), a.cbegin(), a.cend(),          | O[1]               |
//  +----------------------------------------------------+--------------------+
//  | a == b, a != b                                     | Best:  O[n]        |
//  |                                                    | Worst: O[n^2]      |
//  +----------------------------------------------------+--------------------+
//  | a.swap(b), swap(a,b)                               | O[1] if 'a' and    |
//  |                                                    | 'b' use the same   |
//  |                                                    | allocator,         |
//  |                                                    | O[n + m] otherwise |
//  +----------------------------------------------------+--------------------+
//  | a.key_eq()                                         | O[1]               |
//  +----------------------------------------------------+--------------------+
//  | a.hash_function()                                  | O[1]               |
//  +----------------------------------------------------+--------------------+
//  | a.size()                                           | O[1]               |
//  +----------------------------------------------------+--------------------+
//  | a.max_size()                                       | O[1]               |
//  +----------------------------------------------------+--------------------+
//  | a.empty()                                          | O[1]               |
//  +----------------------------------------------------+--------------------+
//  | get_allocator()                                    | O[1]               |
//  +----------------------------------------------------+--------------------+
//  | a.insert(v)                                        | Average: O[1]      |
//  |                                                    | Worst:   O[n]      |
//  +----------------------------------------------------+--------------------+
//  | a.insert(p1, v)                                    | Average: O[1]      |
//  |                                                    | Worst:   O[n]      |
//  +----------------------------------------------------+--------------------+
//  | a.insert(i1, i2)                                   | Average O[         |
//  |                                                    |   distance(i1, i2)]|
//  |                                                    | Worst:  O[ n *     |
//  |                                                    |   distance(i1, i2)]|
//  +----------------------------------------------------+--------------------+
//  | a.erase(p1)                                        | Average: O[1]      |
//  |                                                    | Worst:   O[n]      |
//  +----------------------------------------------------+--------------------+
//  | a.erase(k)                                         | Average: O[        |
//  |                                                    |         a.count(k)]|
//  |                                                    | Worst:   O[n]      |
//  +----------------------------------------------------+--------------------+
//  | a.erase(p1, p2)                                    | Average: O[        |
//  |                                                    |   distance(p1, p2)]|
//  |                                                    | Worst:   O[n]      |
//  +----------------------------------------------------+--------------------+
//  | a.clear()                                          | O[n]               |
//  +----------------------------------------------------+--------------------+
//  | a.find(k)                                          | Average: O[1]      |
//  |                                                    | Worst:   O[n]      |
//  +----------------------------------------------------+--------------------+
//  | a.count(k)                                         | Average: O[1]      |
//  |                                                    | Worst:   O[n]      |
//  +----------------------------------------------------+--------------------+
//  | a.equal_range(k)                                   | Average: O[        |
//  |                                                    |         a.count(k)]|
//  |                                                    | Worst:   O[n]      |
//  +----------------------------------------------------+--------------------+
//  | a.bucket_count()                                   | O[1]               |
//  +----------------------------------------------------+--------------------+
//  | a.max_bucket_count()                               | O[1]               |
//  +----------------------------------------------------+--------------------+
//  | a.bucket(k)                                        | O[1]               |
//  +----------------------------------------------------+--------------------+
//  | a.bucket_size(k)                                   | O[a.bucket_size(k)]|
//  +----------------------------------------------------+--------------------+
//  | a.load_factor()                                    | O[1]               |
//  +----------------------------------------------------+--------------------+
//  | a.max_load_factor()                                | O[1]               |
//  | a.max_load_factor(z)                               | O[1]               |
//  +----------------------------------------------------+--------------------+
//  | a.rehash(k)                                        | Average: O[n]      |
//  |                                                    | Worst:   O[n^2]    |
//  +----------------------------------------------------+--------------------+
//  | a.resize(k)                                        | Average: O[n]      |
//  |                                                    | Worst:   O[n^2]    |
//  +----------------------------------------------------+--------------------+
//..
//
///Usage
///-----

// Prevent 'bslstl' headers from being included directly in 'BSL_OVERRIDES_STD'
// mode.  Doing so is unsupported, and is likely to cause compilation errors.
#if defined(BSL_OVERRIDES_STD) && !defined(BSL_STDHDRS_PROLOGUE_IN_EFFECT)
#error "<bslstl_unorderedmultiset.h> header can't be included directly in \
BSL_OVERRIDES_STD mode"
#endif

#ifndef INCLUDED_BSLSCM_VERSION
#include <bslscm_version.h>
#endif

#ifndef INCLUDED_BSLSTL_ALLOCATOR
#include <bslstl_allocator.h>  // Can probably escape with a fwd-decl, but not
#endif                         // very user friendly

#ifndef INCLUDED_BSLSTL_ALLOCATORTRAITS
#include <bslstl_allocatortraits.h>
#endif

#ifndef INCLUDED_BSLSTL_EQUALTO
#include <bslstl_equalto.h>
#endif

#ifndef INCLUDED_BSLSTL_HASH
#include <bslstl_hash.h>
#endif

#ifndef INCLUDED_BSLSTL_HASHTABLE
#include <bslstl_hashtable.h>
#endif

#ifndef INCLUDED_BSLSTL_HASHTABLEBUCKETITERATOR
#include <bslstl_hashtablebucketiterator.h>
#endif

#ifndef INCLUDED_BSLSTL_HASHTABLEITERATOR
#include <bslstl_hashtableiterator.h>
#endif

#ifndef INCLUDED_BSLSTL_ITERATORUTIL
#include <bslstl_iteratorutil.h>
#endif

#ifndef INCLUDED_BSLSTL_PAIR
#include <bslstl_pair.h>  // result type of 'equal_range' method
#endif

#ifndef INCLUDED_BSLSTL_UNORDEREDSETKEYCONFIGURATION
#include <bslstl_unorderedsetkeyconfiguration.h>
#endif

#ifndef INCLUDED_BSLALG_BIDIRECTIONALLINK
#include <bslalg_bidirectionallink.h>
#endif

#ifndef INCLUDED_BSLALG_BIDIRECTIONALNODE
#include <bslalg_bidirectionalnode.h>
#endif

#ifndef INCLUDED_BSLALG_TYPETRAITHASSTLITERATORS
#include <bslalg_typetraithasstliterators.h>
#endif

#ifndef INCLUDED_BSLMA_USESBSLMAALLOCATOR
#include <bslma_usesbslmaallocator.h>
#endif

#ifndef INCLUDED_BSLMF_ISBITWISEMOVEABLE
#include <bslmf_isbitwisemoveable.h>
#endif

#ifndef INCLUDED_BSLMF_NESTEDTRAITDECLARATION
#include <bslmf_nestedtraitdeclaration.h>
#endif

#ifndef INCLUDED_CSTDDEF
#include <cstddef>  // for 'std::size_t'
#define INCLUDED_CSTDDEF
#endif

#ifndef INCLUDED_ITERATOR
#include <iterator>  // for 'std::iterator_traits'
#define INCLUDED_ITERATOR
#endif

namespace bsl {

                        // ========================
                        // class unordered_multiset
                        // ========================

template <class KEY,
          class HASH  = bsl::hash<KEY>,
          class EQUAL = bsl::equal_to<KEY>,
          class ALLOCATOR = bsl::allocator<KEY> >
class unordered_multiset
{
    // This class template implements a value-semantic container type holding
    // an unordered multi set of values (of template parameter type 'KEY').
    //
    // This class:
    //: o supports a complete set of *value-semantic* operations
    //:   o except for 'bdex' serialization
    //: o is *exception-neutral* (agnostic except for the 'at' method)
    //: o is *alias-safe*
    //: o is 'const' *thread-safe*
    // For terminology see {'bsldoc_glossary'}.

  private:

      // PRIVATE TYPE
    typedef bsl::allocator_traits<ALLOCATOR> AllocatorTraits;
        // This typedef is an alias for the allocator traits type associated
        // with this container.

    typedef KEY ValueType;
        // This typedef is an alias for the type of values maintained by this
        // set.

    typedef ::BloombergLP::bslstl::UnorderedSetKeyConfiguration<ValueType>
                                                             ListConfiguration;
        // This typedef is an alias for the policy used internally by this
        // container to extract the 'KEY' value from the values maintained by
        // this multi-set.

    typedef ::BloombergLP::bslstl::HashTable<ListConfiguration,
                                             HASH,
                                             EQUAL,
                                             ALLOCATOR> HashTable;
        // This typedef is an alias for the template instantiation of the
        // underlying 'bslstl::HashTable' used to implement this multi-set.

    typedef ::BloombergLP::bslalg::BidirectionalLink HashTableLink;
        // This typedef is an alias for the type of links maintained by the
        // linked list of elements held by the underlying 'bslstl::HashTable'.

    // FRIEND
    template <class KEY2,
              class HASH2,
              class EQUAL2,
              class ALLOCATOR2>
    friend bool operator==(
                const unordered_multiset<KEY2, HASH2, EQUAL2, ALLOCATOR2>&,
                const unordered_multiset<KEY2, HASH2, EQUAL2, ALLOCATOR2>&);

  public:
    // PUBLIC TYPES
    typedef KEY                                        key_type;
    typedef KEY                                        value_type;
    typedef HASH                                       hasher;
    typedef EQUAL                                      key_equal;
    typedef ALLOCATOR                                  allocator_type;

    typedef typename allocator_type::reference         reference;
    typedef typename allocator_type::const_reference   const_reference;

    typedef typename AllocatorTraits::size_type        size_type;
    typedef typename AllocatorTraits::difference_type  difference_type;
    typedef typename AllocatorTraits::pointer          pointer;
    typedef typename AllocatorTraits::const_pointer    const_pointer;

  public:
    // TRAITS
    BSLMF_NESTED_TRAIT_DECLARATION_IF(
                    unordered_multiset,
                    ::BloombergLP::bslmf::IsBitwiseMoveable,
                    ::BloombergLP::bslmf::IsBitwiseMoveable<HashTable>::value);

    typedef ::BloombergLP::bslstl::HashTableIterator<
                                   const value_type, difference_type> iterator;
    typedef ::BloombergLP::bslstl::HashTableBucketIterator<
                             const value_type, difference_type> local_iterator;

    typedef iterator                                            const_iterator;
    typedef local_iterator                                const_local_iterator;

  private:
    // DATA
    HashTable d_impl;

  public:
    // CREATORS
    explicit unordered_multiset(
                           size_type             initialNumBuckets = 0,
                           const hasher&         hash = hasher(),
                           const key_equal&      keyEqual = key_equal(),
                           const allocator_type& allocator = allocator_type());
        // Construct an empty unordered multi-set.  Optionally specify an
        // 'initialNumBuckets' indicating the initial size of the array of
        // buckets of this container.  If 'initialNumBuckets' is not supplied,
        // an implementation defined value is used.  Optionally specify a
        // 'hasher' used to generate the hash values associated to the
        // keys extracted from the values contained in this object.  If 'hash'
        // is not supplied, a default-constructed object of type 'hasher' is
        // used.  Optionally specify a key-equality functor 'keyEqual' used to
        // verify that two key values are the same.  If 'keyEqual' is not
        // supplied, a default-constructed object of type 'key_equal' is used.
        // Optionally specify an 'allocator' used to supply memory.  If
        // 'allocator' is not supplied, a default-constructed object of the
        // (template parameter) type 'allocator_type' is used.  If the
        // 'allocator_type' is 'bsl::allocator' (the default), then 'allocator'
        // shall be convertible to 'bslma::Allocator *'.  If the 'ALLOCATOR' is
        // 'bsl::allocator' and 'allocator' is not supplied, the currently
        // installed default allocator will be used to supply memory.

    explicit unordered_multiset(const allocator_type& allocator);
        // Construct an empty unordered multi-set that uses the specified
        // 'allocator' to supply memory.  Use a default-constructed object of
        // type 'hasher' to generate hash values for the key extracted from the
        // values contained in this object.  Also, use a default-constructed
        // object of type 'key_equal' to verify that two key values are the
        // same.  If the 'allocator_type' is 'bsl::allocator' (the default),
        // then 'allocator' shall be convertible to 'bslma::Allocator *'.

    unordered_multiset(const unordered_multiset& original);
    unordered_multiset(const unordered_multiset& original,
                       const allocator_type&     allocator);
        // Construct an unordered set having the same value as that of the
        // specified 'original'.  Use a default-constructed object of type
        // 'hasher' to generate hash values for the key extracted from the
        // values contained in this object.  Also, use a default-constructed
        // object of type 'key_equal' to verify that two key values are the
        // same.  Optionally specify an 'allocator' used to supply memory.  If
        // 'allocator' is not supplied, a default-constructed object of type
        // 'allocator_type' is used.  If the 'allocator_type' is
        // 'bsl::allocator' (the default), then 'allocator' shall be
        // convertible to 'bslma::Allocator *'.

    template <class INPUT_ITERATOR>
    unordered_multiset(INPUT_ITERATOR        first,
                       INPUT_ITERATOR        last,
                       size_type             initialNumBuckets = 0,
                       const hasher&         hash = hasher(),
                       const key_equal&      keyEqual = key_equal(),
                       const allocator_type& allocator = allocator_type());
        // Construct an empty unordered multi-set and insert each 'value_type'
        // object in the sequence starting at the specified 'first' element,
        // and ending immediately before the specified 'last' element, ignoring
        // those pairs having a key that appears earlier in the sequence.
        // Optionally specify an 'initialNumBuckets' indicating the initial
        // size of the array of buckets of this container.  If
        // 'initialNumBuckets' is not supplied, an implementation defined value
        // is used.  Optionally specify a 'hasher' used to generate hash values
        // for the keys extracted from the values contained in this object.  If
        // 'hash' is not supplied, a default-constructed object of type
        // 'hasher' is used.  Optionally specify a key-equality functor
        // 'keyEqual' used to verify that two key values are the same.  If
        // 'keyEqual' is not supplied, a default-constructed object of type
        // 'key_equal' is used.  Optionally specify an 'allocator' used to
        // supply memory.  If 'allocator' is not supplied, a
        // default-constructed object of the (template parameter) type
        // 'allocator_type' is used.  If the 'allocator_type' is
        // 'bsl::allocator' (the default), then 'allocator' shall be
        // convertible to 'bslma::Allocator *'.  If the 'allocator_type' is
        // 'bsl::allocator' and 'allocator' is not supplied, the currently
        // installed default allocator will be used to supply memory.  The
        // (template parameter) type 'INPUT_ITERATOR' shall meet the
        // requirements of an input iterator defined in the C++11 standard
        // [24.2.3] providing access to values of a type convertible to
        // 'value_type'.  The behavior is undefined unless 'first' and 'last'
        // refer to a sequence of valid values where 'first' is at a position
        // at or before 'last'.  This method requires that the (template
        // parameter) type 'KEY' be "copy-constructible" (see {Requirements on
        // 'KEY'}).

    ~unordered_multiset();
        // Destroy this object.

    // MANIPULATORS
    unordered_multiset& operator=(const unordered_multiset& rhs);
        // Assign to this object the value, hasher, and key-equality functor of
        // the specified 'rhs' object, propagate to this object the allocator
        // of 'rhs' if the 'ALLOCATOR' type has trait
        // 'propagate_on_container_copy_assignment', and return a reference
        // providing modifiable access to this object.  This method requires
        // that the (template parameter) type 'KEY' be "copy-constructible"
        // (see {Requirements on 'KEY'}).

    iterator begin();
        // Return an iterator providing modifiable access to the first
        // 'value_type' object (in the sequence of 'value_type' objects)
        // maintained by this multi-set, or the 'end' iterator if this
        // multi-set is empty.

    iterator end();
        // Return an iterator providing modifiable access to the past-the-end
        // element in the sequence of 'value_type' objects maintained by this
        // set.

    local_iterator begin(size_type index);
        // Return a local iterator providing modifiable access to the first
        // 'value_type' object in the sequence of 'value_type' objects of the
        // bucket having the specified 'index', in the array of buckets
        // maintained by this multi-set, or the 'end(index)' otherwise.

    local_iterator end(size_type index);
        // Return a local iterator providing modifiable access to the
        // past-the-end element in the sequence of 'value_type' objects of the
        // bucket having the specified 'index's, in the array of buckets
        // maintained by this multi-set.

    void clear();
        // Remove all entries from this multi-set.  Note that the container is
        // empty after this call, but allocated memory may be retained for
        // future use.

    pair<iterator, iterator> equal_range(const key_type& key);
        // Return a pair of iterators providing modifiable access to the
        // sequence of 'value_type' objects in this multi-set having the
        // specified 'key', where the the first iterator is positioned at the
        // start of the sequence, and the second is positioned one past the
        // end of the sequence.  If this multi-set contains no 'value_type'
        // objects having 'key', then the two returned iterators will have the
        // same value.

    size_type erase(const key_type& key);
        // Remove from this multi-set all 'value_type' objects having the
        // specified 'key', if they exist, and return the number of
        // object erased; otherwise, if there is no 'value_type' object having
        // 'key', return 0 with no other effect.

    iterator erase(const_iterator position);
        // Remove from this multi-set the 'value_type' object at the
        // specified 'position', and return an iterator referring to the
        // element immediately following the removed element, or to the
        // past-the-end position if the removed element was the last element in
        // the sequence of elements maintained by this multi-set.  The behavior
        // is undefined unless 'position' refers to a 'value_type' object in
        // this multi-set.

    iterator erase(const_iterator first, const_iterator last);
        // Remove from multi-set the 'value_type' objects starting at the
        // specified 'first' position up to, but including the specified 'last'
        // position, and return 'last'.  The behavior is undefined unless
        // 'first' and 'last' either refer to elements in multi-set or are the
        // 'end' iterator, and the 'first' position is at or before the 'last'
        // position in the ordered sequence provided by this container.

    iterator find(const key_type& key);
        // Return an iterator providing modifiable access to the first
        // 'value_type' objects in the sequence of all the value-elements of
        // this multi-set having the specified 'key', if such value-elements
        // exist, and the past-the-end ('end') iterator otherwise.

    iterator insert(const value_type& value);
        // Insert the specified 'value' into multi-set;  if a 'value_type'
        // object having the same key (according to 'key_equal') as 'value'
        // already exists in multi-set, the operation is guaranteed to insert
        // 'value' in a position contiguous to another value having the same
        // key.  Return an iterator referring to the 'value_type' object
        // inserted.  This method requires that the (template parameter) type
        // 'KEY' be "copy-constructible" (see {Requirements on 'KEY'}).

    iterator insert(const_iterator hint, const value_type& value);
        // Insert the specified 'value' into multi-set (in constant
        // time if the specified 'hint' is a valid element in the bucket to
        // which 'value' belongs);  if a 'value_type' object having the same
        // key (according to 'key_equal') as 'value' already exists in this
        // set, this method is guaranteed to insert 'value' in a position
        // contiguous to another value in the set having the same key.  Return
        // an iterator referring to the newly inserted 'value_type' object.  If
        // 'hint' is not a position in the bucket of the key of 'value', this
        // operation will have worst case O[N] and average case constant time
        // complexity, where 'N' is the size of multi-set.  The behavior is
        // undefined unless 'hint' is a valid iterator into this unordered
        // multi set.  This method requires that the (template parameter) type
        // 'KEY' be "copy-constructible" (see {Requirements on 'KEY'}).

    template <class INPUT_ITERATOR>
    void insert(INPUT_ITERATOR first, INPUT_ITERATOR last);
        // Insert into multi-set the value of each 'value_type' object in the
        // range starting at the specified 'first' iterator and ending
        // immediately before the specified 'last' iterator.  The (template
        // parameter) type 'INPUT_ITERATOR' shall meet the requirements of an
        // input iterator defined in the C++11 standard [24.2.3] providing
        // access to values of a type convertible to 'value_type'.  This method
        // requires that the (template parameter) type 'KEY' be
        // "copy-constructible" (see {Requirements on 'KEY'}).

    void  max_load_factor(float newLoadFactor);
        // Set the maximum load factor of this container to the specified
        // 'newLoadFactor'.

    void rehash(size_type numBuckets);
        // Change the size of the array of buckets maintained by this container
        // to the specified 'numBuckets', and redistribute all the contained
        // elements into the new sequence of buckets, according to their hash
        // values.  Note that this operation has no effect if rehashing the
        // elements into 'numBuckets' would cause multi-set to exceed its
        // 'max_load_factor'.

    void reserve(size_type numElements);
        // Increase the number of buckets of multi-set to a quantity such that
        // the ratio between the specified 'numElements' and this quantity does
        // not exceed 'max_load_factor'.

    void swap(unordered_multiset& other);
        // Exchange the value of this object as well as its hasher and
        // key-equality functor with those of the specified 'other' object.
        // Additionally if
        // 'bslstl::AllocatorTraits<ALLOCATOR>::propagate_on_container_swap' is
        // 'true' then exchange the allocator of this object with that of the
        // 'other' object, and do not modify either allocator otherwise.  This
        // method provides the no-throw exception-safety guarantee and
        // guarantees O[1] complexity.  The behavior is undefined is unless
        // either this object was created with the same allocator as 'other' or
        // 'propagate_on_container_swap' is 'true'.

    // ACCESSORS
    const_iterator begin() const;
        // Return an iterator providing non-modifiable access to the first
        // 'value_type' object (in the sequence of 'value_type' objects)
        // maintained by this multi-set, or the 'end' iterator if this
        // multi-set is empty.

    const_iterator end() const;
        // Return an iterator providing non-modifiable access to the
        // past-the-end element (in the sequence of 'value_type' objects)
        // maintained by this multi-set.

    const_iterator cbegin() const;
        // Return an iterator providing non-modifiable access to the first
        // 'value_type' object (in the sequence of 'value_type' objects)
        // maintained by this multi-set, or the 'end' iterator if this
        // multi-set is empty.

    const_iterator cend() const;
        // Return an iterator providing non-modifiable access to the
        // past-the-end element (in the sequence of 'value_type' objects)
        // maintained by this multi-set.

    const_local_iterator begin(size_type index) const;
        // Return a local iterator providing non-modifiable access to the first
        // 'value_type' object (in the sequence of 'value_type' objects) of the
        // bucket having the specified 'index' in the array of buckets
        // maintained by this multi-set, or the 'end(index)' otherwise.

    const_local_iterator end(size_type index) const;
        // Return a local iterator providing non-modifiable access to the
        // past-the-end element (in the sequence of 'value_type' objects) of
        // the bucket having the specified 'index' in the array of buckets
        // maintained by this multi-set.

    const_local_iterator cbegin(size_type index) const;
        // Return a local iterator providing non-modifiable access to the first
        // 'value_type' object (in the sequence of 'value_type' objects) of the
        // bucket having the specified 'index' in the array of buckets
        // maintained by multi-set, or the 'end(index)' otherwise.

    const_local_iterator cend(size_type index) const;
        // Return a local iterator providing non-modifiable access to the
        // past-the-end element (in the sequence of 'value_type' objects) of
        // the bucket having the specified 'index' in the array of buckets
        // maintained by multi-set.

    size_type bucket(const key_type& key) const;
        // Return the index of the bucket, in the array of buckets of this
        // container, where values having the specified 'key' would be
        // inserted.

    size_type bucket_count() const;
        // Return the number of buckets in the array of buckets maintained by
        // multi-set.

    size_type bucket_size(size_type index) const;
        // Return the number of elements contained in the bucket at the
        // specified 'index' in the array of buckets maintained by this
        // container.

    size_type count(const key_type& key) const;
        // Return the number of 'value_type' objects within this map having the
        // specified 'key'.  Note that since an unordered set maintains unique
        // keys, the returned value will be either 0 or 1.

    bool empty() const;
        // Return 'true' if multi-set contains no elements, and 'false'
        // otherwise.

    pair<const_iterator, const_iterator> equal_range(
                                                    const key_type& key) const;
        // Return a pair of iterators providing non-modifiable access to the
        // sequence of 'value_type' objects in this container having the
        // specified 'key', where the the first iterator is positioned at the
        // start of the sequence and the second iterator is positioned one past
        // the end of the sequence.  If multi-set contains no 'value_type'
        // objects having 'key' then the two returned iterators will have the
        // same value.  Note that since a set maintains unique keys, the range
        // will contain at most one element.

    const_iterator find(const key_type& key) const;
        // Return an iterator providing non-modifiable access to the first
        // 'value_type' objects in the sequence of value-elements of this
        // multi-set having the specified 'key', if such value-elements exist,
        // and the past-the-end ('end') iterator otherwise.

    allocator_type get_allocator() const;
        // Return (a copy of) the allocator used for memory allocation by this
        // set.

    key_equal key_eq() const;
        // Return (a copy of) the key-equality binary functor that returns
        // 'true' if the value of two 'key_type' objects is the same, and
        // 'false' otherwise.

    hasher hash_function() const;
        // Return (a copy of) the hash unary functor used by multi-set to
        // generate a hash value (of type 'size_t') for a 'key_type' object.

    float load_factor() const;
        // Return the current ratio between the 'size' of this container and
        // the number of buckets.  The 'load_factor' is a measure of how full
        // the container is, and a higher load factor leads to an increased
        // number of collisions, thus resulting in a loss performance.

    size_type max_bucket_count() const;
        // Return a theoretical upper bound on the largest number of buckets
        // that this container could possibly manage.  Note that there is no
        // guarantee that the set can successfully grow to the returned size,
        // or even close to that size without running out of resources.

    float max_load_factor() const;
        // Return the maximum load factor allowed for this container.  If
        // an insert operation would cause 'load_factor' to exceed
        // the 'max_load_factor', that same insert operation will increase the
        // number of buckets and rehash the elements of the container into
        // those buckets the (see rehash).

    size_type max_size() const;
        // Return a theoretical upper bound on the largest number of elements
        // that multi-set could possibly hold.  Note that there is no guarantee
        // that the set can successfully grow to the returned size, or even
        // close to that size without running out of resources.

    size_type size() const;
        // Return the number of elements in multi-set.

    // FRIEND
    template <class KEY2,
              class HASH2,
              class EQUAL2,
              class ALLOCATOR2>
    friend bool operator==(
                const unordered_multiset<KEY2, HASH2, EQUAL2, ALLOCATOR2>&,
                const unordered_multiset<KEY2, HASH2, EQUAL2, ALLOCATOR2>&);

};

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
bool operator==(const unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>& lhs,
                const unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>& rhs);
    // Return 'true' if the specified 'lhs' and 'rhs' objects have the same
    // value, and 'false' otherwise.  Two 'unordered_multiset' objects have the
    // same value if they have the same number of value-elements, and for each
    // value-element that is contained in 'lhs' there is a value-element
    // contained in 'rhs' having the same value, and vice-versa.  This method
    // requires that the (template parameter) type 'KEY' be
    // "equality-comparable" (see {Requirements on 'KEY'}).

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
bool operator!=(const unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>& lhs,
                const unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>& rhs);
    // Return 'true' if the specified 'lhs' and 'rhs' objects do not have the
    // same value, and 'false' otherwise.  Two 'unordered_multiset' objects do
    // not have the same value if they do not have the same number of
    // value-elements, or that for some value-element contained in 'lhs' there
    // is not a value-element in 'rhs' having the same value, and vice-versa.
    // This method requires that the (template parameter) type 'KEY' and be
    // "equality-comparable" (see {Requirements on 'KEY'}).

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
void swap(unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>& x,
          unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>& y);
    // Swap both the value and the comparator of the specified 'a' object with
    // the value and comparator of the specified 'b' object.  The behavior is
    // undefined is unless this object was created with the same allocator as
    // 'other'.  Additionally if
    // 'bslstl::AllocatorTraits<ALLOCATOR>::propagate_on_container_swap' is
    // 'true' then exchange the allocator of 'a' with that of 'b', and do not
    // modify either allocator otherwise.  This method provides the no-throw
    // exception-safety guarantee and guarantees O[1] complexity.  The behavior
    // is undefined is unless either this object was created with the same
    // allocator as 'other' or 'propagate_on_container_swap' is 'true'.

}  // close namespace bsl

// ============================================================================
//                                TYPE TRAITS
// ============================================================================

// Type traits for STL *unordered* *associative* containers:
//: o An unordered associative container defines STL iterators.
//: o An unordered associative container is bitwise moveable if the both
//:      functors and the allocator are bitwise moveable.
//: o An unordered associative container uses 'bslma' allocators if the
//:      parameterized 'ALLOCATOR' is convertible from 'bslma::Allocator*'.

namespace BloombergLP {
namespace bslalg {

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
struct HasStlIterators<bsl::unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR> >
     : bsl::true_type
{};

}  // close namespace bslalg

namespace bslma {

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
struct UsesBslmaAllocator<bsl::unordered_multiset<KEY,
                                                  HASH,
                                                  EQUAL,
                                                  ALLOCATOR> >
    : bsl::is_convertible<Allocator*, ALLOCATOR>::type
{};

}  // close namespace bslma
}  // close namespace BloombergLP

// ===========================================================================
//                  TEMPLATE AND INLINE FUNCTION DEFINITIONS
// ===========================================================================

namespace bsl
{

                        //-------------------------
                        // class unordered_multiset
                        //-------------------------

// CREATORS
template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::
unordered_multiset(size_type             initialNumBuckets,
                   const hasher&         hash,
                   const key_equal&      keyEqual,
                   const allocator_type& allocator)
: d_impl(hash, keyEqual, initialNumBuckets, allocator)
{
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
template <class INPUT_ITERATOR>
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::unordered_multiset(
                                       INPUT_ITERATOR        first,
                                       INPUT_ITERATOR        last,
                                       size_type             initialNumBuckets,
                                       const hasher&         hash,
                                       const key_equal&      keyEqual,
                                       const allocator_type& allocator)
: d_impl(hash, keyEqual, initialNumBuckets, allocator)
{
    this->insert(first, last);
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::unordered_multiset(
                                               const allocator_type& allocator)
: d_impl(HASH(), EQUAL(), 0, allocator)
{
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::unordered_multiset(
                                           const unordered_multiset& original,
                                           const allocator_type&     allocator)
: d_impl(original.d_impl, allocator)
{
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::unordered_multiset(
                                            const unordered_multiset& original)
: d_impl(original.d_impl,
         AllocatorTraits::select_on_container_copy_construction(
                                                     original.get_allocator()))
{
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::~unordered_multiset()
{
    // All memory management is handled by the base 'd_impl' member.
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>&
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::operator=(
                                               const unordered_multiset& rhs)
{
    // Actually, need to check propagate_on_copy_assign trait
    unordered_multiset(rhs, get_allocator()).swap(*this);
    return *this;

}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
ALLOCATOR
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::get_allocator() const
{
    return d_impl.allocator();
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
bool
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::empty() const
{
    return 0 == d_impl.size();
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::size_type
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::size() const
{
    return d_impl.size();
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::size_type
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::max_size() const
{
    return d_impl.maxSize();
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::begin()
{
    return iterator(d_impl.elementListRoot());
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::end()
{
    return iterator();
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::local_iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::begin(size_type index)
{
    BSLS_ASSERT_SAFE(index < this->bucket_count());

    return local_iterator(&d_impl.bucketAtIndex(index));
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::local_iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::end(size_type index)
{
    BSLS_ASSERT_SAFE(index < this->bucket_count());

    return local_iterator(0, &d_impl.bucketAtIndex(index));
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
void
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::clear()
{
    d_impl.removeAll();
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::find(const key_type& key)
{
    return iterator(d_impl.find(key));
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
bsl::pair<typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::iterator,
          typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::iterator>
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::equal_range(
                                                           const key_type& key)
{
    HashTableLink *first;
    HashTableLink *last;
    d_impl.findRange(&first, &last, key);
    return bsl::pair<iterator, iterator>(iterator(first), iterator(last));
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::size_type
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::erase(const key_type& key)
{
    typedef ::BloombergLP::bslalg::BidirectionalNode<value_type> BNode;

    if (HashTableLink *target = d_impl.find(key)) {
        target = d_impl.remove(target);
        size_type result = 1;
        while (target && this->key_eq()(
       key,
       ListConfiguration::extractKey(static_cast<BNode *>(target)->value()))) {
            target = d_impl.remove(target);
            ++result;
        }
        return result;                                                // RETURN
    }

    return 0;
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::erase(const_iterator position)
{
    BSLS_ASSERT(position != this->end());

    return iterator(d_impl.remove(position.node()));
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::erase(const_iterator first,
                                                       const_iterator last)
{

#if defined BDE_BUILD_TARGET_SAFE_2
    if (first != last) {
        iterator it        = this->begin();
        const iterator end = this->end();
        for (; it != first; ++it) {
            BSLS_ASSERT(last != it);
            BSLS_ASSERT(end  != it);
        }
        for (; it != last; ++it) {
            BSLS_ASSERT(end  != it);
        }
    }
#endif

    while (first != last) {
        first = this->erase(first);
    }

    return iterator(first.node()); // convert from const_iterator
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::insert(
                                                       const value_type& value)
{
    return iterator(d_impl.insert(value));
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::insert(
                                                    const_iterator    hint,
                                                    const value_type& value)
{
    return iterator(d_impl.insert(value, hint.node()));
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
template <class INPUT_ITERATOR>
void
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::insert(INPUT_ITERATOR first,
                                                        INPUT_ITERATOR last)
{
    if (size_t maxInsertions =
            ::BloombergLP::bslstl::IteratorUtil::insertDistance(first, last)) {
        this->reserve(this->size() + maxInsertions);
    }

    while (first != last) {
        d_impl.insert(*first++);
    }
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
void unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::max_load_factor(
                                                           float newLoadFactor)
{
    d_impl.maxLoadFactor(newLoadFactor);
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
void
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::rehash(size_type numBuckets)
{
    return d_impl.rehash(numBuckets);
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
void
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::reserve(size_type numElements)
{
    return d_impl.rehashForNumElements(numElements);
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
void
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::swap(
                                                     unordered_multiset& other)
{
    d_impl.swap(other.d_impl);
}

// ACCESSORS
template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::const_iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::begin() const
{
    return const_iterator(d_impl.elementListRoot());
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::const_iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::end() const
{
    return const_iterator();
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::const_iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::cbegin() const
{
    return const_iterator(d_impl.elementListRoot());
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::const_iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::cend() const
{
    return const_iterator();
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::const_local_iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::begin(size_type index) const
{
    BSLS_ASSERT_SAFE(index < this->bucket_count());

    return const_local_iterator(&d_impl.bucketAtIndex(index));
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
typename
 unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::const_local_iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::end(size_type index) const
{
    BSLS_ASSERT_SAFE(index < this->bucket_count());

    return const_local_iterator(0, &d_impl.bucketAtIndex(index));
}


template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
typename
 unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::const_local_iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::cbegin(size_type index) const
{
    BSLS_ASSERT_SAFE(index < this->bucket_count());

    return const_local_iterator(&d_impl.bucketAtIndex(index));
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::const_local_iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::cend(size_type index) const
{
    BSLS_ASSERT_SAFE(index < this->bucket_count());

    return const_local_iterator(0, &d_impl.bucketAtIndex(index));
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::size_type
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::bucket(
                                                     const key_type& key) const
{
    return d_impl.bucketIndexForKey(key);
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::size_type
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::bucket_count() const
{
    return d_impl.numBuckets();
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::size_type
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::bucket_size(
                                                         size_type index) const
{
    BSLS_ASSERT_SAFE(index < this->bucket_count());

    return d_impl.countElementsInBucket(index);
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::size_type
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::count(
                                                     const key_type& key) const
{
    typedef ::BloombergLP::bslalg::BidirectionalNode<value_type> BNode;

    size_type result = 0;
    for (HashTableLink *cursor = d_impl.find(key);
         cursor;
         ++result, cursor = cursor->nextLink()) {

        BNode *cursorNode = static_cast<BNode *>(cursor);
        if (!this->key_eq()(
                         key,
                         ListConfiguration::extractKey(cursorNode->value()))) {
            break;
        }
    }
    return result;
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::const_iterator
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::find(
                                                     const key_type& key) const
{
    return const_iterator(d_impl.find(key));
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::hasher
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::hash_function() const
{
    return d_impl.hasher();
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::key_equal
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::key_eq() const
{
    return d_impl.comparator();
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
bsl::pair<
      typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::const_iterator,
      typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::const_iterator>
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::equal_range(
                                                     const key_type& key) const
{
    HashTableLink *first;
    HashTableLink *last;
    d_impl.findRange(&first, &last, key);
    return bsl::pair<const_iterator, const_iterator>(const_iterator(first),
                                                     const_iterator(last));
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
typename unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::size_type
unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::max_bucket_count() const
{
    return d_impl.maxNumOfBuckets();
}


template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
float unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::load_factor() const
{
    return d_impl.loadFactor();
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
float unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>::max_load_factor() const
{
    return d_impl.maxLoadFactor();
}

}  // close namespace bsl

// FREE FUNCTIONS
template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
bool bsl::operator==(
              const bsl::unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>& lhs,
              const bsl::unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>& rhs)
{
    return lhs.d_impl == rhs.d_impl;
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
bool bsl::operator!=(
              const bsl::unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>& lhs,
              const bsl::unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>& rhs)
{
    return !(lhs == rhs);
}

template <class KEY, class HASH, class EQUAL, class ALLOCATOR>
inline
void
bsl::swap(bsl::unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>& x,
          bsl::unordered_multiset<KEY, HASH, EQUAL, ALLOCATOR>& y)
{
    x.swap(y);
}

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
