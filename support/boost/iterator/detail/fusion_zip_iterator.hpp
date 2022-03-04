///////////////////////////////////////////////////////////////////////////////
// fusion_zip_iterator.hpp                                                   //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ITERATOR_FUSION_ZIP_ITERATOR_HPP_ER_2010
#define BOOST_ITERATOR_FUSION_ZIP_ITERATOR_HPP_ER_2010
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/detail/tuple_basic.hpp>
#include <boost/mpl/detail/sequence_to_unpack_variadic.hpp>

#include <boost/mpl/accumulate.hpp>

namespace boost{
namespace fusion{
namespace detail{
namespace zip_iterator_aux{

    template<typename vec_It>
    class traits
    {

        template<typename It>
        struct wrapper
        {
            typedef boost::assign::v2::reference_wrapper::assign::v2::ref::assign_tag::copy tag_;
            typedef typename boost::iterator_reference<It>::type ref_;
            typedef typename boost::remove_reference<ref_>::type value_;
            typedef boost::assign::v2::reference_wrapper<tag_,value_> type;
        };
             
        template<typename It>
        struct deduce_value{
            typedef typename boost::iterator_reference<It>::type from_;
            typedef typename reference_traits::convert_to<from_>::type ref_to_;
            typedef typename boost::remove_reference<ref_to_>::type type;
        };

        typedef typename boost::fusion::unpack_vector<vec_It>::type vec_it_;
        typedef typename boost::mpl::transform<
            vec_it_, wrapper<boost::mpl::_1> 
        >::type vec_wrapper_;
        
        typedef typename boost::mpl::transform<
            vec_it_, boost::iterator_difference<boost::mpl::_1> 
                >::type vec_diff_;

        typedef typename boost::mpl::transform<
            vec_it_, boost::pure_traversal_tag<boost::iterator_traversal<> 
                >::type vec_traversal_;

        typedef typename boost::fusion::unpack_vector<vec_wrapper_>::type 
           storage_;

        public:

        typedef typename boost::mpl::max_element<
            vec_diff_,
            boost::numeric::is_subranged<boost::mpl::_1,boost::mpl::_2>
        >::type difference_type;

        

        typedef typename boost::mpl::accumulate<
            vec_traversal_,
            random_access_traversal_tag,
            boost::detail::minimum_category
        >::type traversal_category;

                    
    };

    template<typename D,typename vec_It>
    struct facade
    {
        typedef zip_iterator_aux::traits<vec_It> traits_
            typedef boost::iterator_facade<
                D,
                typename traits_::value_type,  
                typename traits_::traversal_category,
                typename traits_::reference,
                typename traits_::difference_type
            > type;
        };


}// fusion_zip_iterator_aux


    template<typename vec_It>
    class zip_iterator : public fusion_zip_iterator_aux::facade<
        zip_iterator<vec_It>,vec_It>::type
    {

        typedef zip_iterator_aux::traits<vec_It> traits_;
        friend class iterator_core_access;
        private:

        typedef typename traits_::reference reference;
        typedef typename traits_::difference_type difference_type;
        typedef typename tratts_::traversal_category traversal_category;

        typedef typename fusion_zip_iterator_aux::facade<
        zip_iterator<vec_It>,vec_It>::type super_t;

        zip_iterator(){}
        zip_iterator(  ){}

        private:
        reference dereference()
        {
            return vec_ref_();           
        }     

    };


    template<typename IteratorTuple>
    struct zip_iterator_base
    {
     private:
      
      
        // Traversal catetgory is the minimum traversal category in the 
        // iterator tuple.
        typedef typename 
        detail::minimum_traversal_category_in_iterator_tuple<
            IteratorTuple
        >::type traversal_category;
     public:
      
        // The iterator facade type from which the zip iterator will
        // be derived.
        typedef iterator_facade<
            zip_iterator<IteratorTuple>,
            value_type,  
            traversal_category,
            reference,
            difference_type
        > type;
    };

    template <>
    struct zip_iterator_base<int>
    {
        typedef int type;
    };
  }
  
  /////////////////////////////////////////////////////////////////////
  //
  // zip_iterator class definition
  //
  template<typename IteratorTuple>
  class zip_iterator : 
    public detail::zip_iterator_base<IteratorTuple>::type
  {  

   // Typedef super_t as our base class. 
   typedef typename 
     detail::zip_iterator_base<IteratorTuple>::type super_t;

   // iterator_core_access is the iterator's best friend.
   friend class iterator_core_access;

  public:
    
    // Construction
    // ============
    
    // Default constructor
    zip_iterator() { }

    // Constructor from iterator tuple
    zip_iterator(IteratorTuple iterator_tuple) 
      : m_iterator_tuple(iterator_tuple) 
    { }

    // Copy constructor
    template<typename OtherIteratorTuple>
    zip_iterator(
       const zip_iterator<OtherIteratorTuple>& other,
       typename enable_if_convertible<
         OtherIteratorTuple,
         IteratorTuple
         >::type* = 0
    ) : m_iterator_tuple(other.get_iterator_tuple())
    {}

    // Get method for the iterator tuple.
    const IteratorTuple& get_iterator_tuple() const
    { return m_iterator_tuple; }

  private:
    
    // Implementation of Iterator Operations
    // =====================================
    
    // Dereferencing returns a tuple built from the dereferenced
    // iterators in the iterator tuple.
    typename super_t::reference dereference() const
    { 
      return detail::tuple_impl_specific::tuple_transform( 
        get_iterator_tuple(),
        detail::dereference_iterator()
       );
    }

    // Two zip iterators are equal if all iterators in the iterator
    // tuple are equal. NOTE: It should be possible to implement this
    // as
    //
    // return get_iterator_tuple() == other.get_iterator_tuple();
    //
    // but equality of tuples currently (7/2003) does not compile
    // under several compilers. No point in bringing in a bunch
    // of #ifdefs here.
    //
    template<typename OtherIteratorTuple>   
    bool equal(const zip_iterator<OtherIteratorTuple>& other) const
    {
      return detail::tuple_impl_specific::tuple_equal(
        get_iterator_tuple(),
        other.get_iterator_tuple()
        );
    }

    // Advancing a zip iterator means to advance all iterators in the
    // iterator tuple.
    void advance(typename super_t::difference_type n)
    { 
      detail::tuple_impl_specific::tuple_for_each(
          m_iterator_tuple,
          detail::advance_iterator<BOOST_DEDUCED_TYPENAME super_t::difference_type>(n)
          );
    }
    // Incrementing a zip iterator means to increment all iterators in
    // the iterator tuple.
    void increment()
    { 
      detail::tuple_impl_specific::tuple_for_each(
        m_iterator_tuple,
        detail::increment_iterator()
        );
    }
    
    // Decrementing a zip iterator means to decrement all iterators in
    // the iterator tuple.
    void decrement()
    { 
      detail::tuple_impl_specific::tuple_for_each(
        m_iterator_tuple,
        detail::decrement_iterator()
        );
    }
    
    // Distance is calculated using the first iterator in the tuple.
    template<typename OtherIteratorTuple>
      typename super_t::difference_type distance_to(
        const zip_iterator<OtherIteratorTuple>& other
        ) const
    { 
        return boost::tuples::get<0>(other.get_iterator_tuple()) - 
            boost::tuples::get<0>(this->get_iterator_tuple());
    }
  
    // Data Members
    // ============
    
    // The iterator tuple.
    IteratorTuple m_iterator_tuple;
 
  };

}// detail
}// fusion
}// boost

#endif