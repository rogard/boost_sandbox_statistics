// Boost.Range library
//
//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_DETAIL_CHAIN_ITERATOR_HPP_INCLUDED
#define BOOST_RANGE_DETAIL_CHAIN_ITERATOR_HPP_INCLUDED

#include <boost/iterator/iterator_facade.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/detail/demote_iterator_traversal_tag.hpp>
#include <boost/range/value_type.hpp>
#include <boost/utility.hpp>

namespace boost
{
    namespace range_detail
    {

template<typename Iterator1, typename Iterator2>
struct chain_iterator_link
{
private:
    class reference_count_t
    {
    public:
        reference_count_t() : m_count(0u) {}
        reference_count_t(const reference_count_t&) : m_count(0u) {}
        reference_count_t& operator=(const reference_count_t&) { return *this; }

        void increment() { ++m_count; }
        bool decrement() { return --m_count ? false : true; }

    private:
        unsigned int m_count;
    };

public:
    chain_iterator_link(Iterator1 last1, Iterator2 first2)
        :    last1(last1)
        ,    first2(first2)
    {
    }

    void add_reference() const
    {
        count.increment();
    }

    bool release_reference() const
    {
        return count.decrement();
    }

    Iterator1 last1;
    Iterator2 first2;

private:
    chain_iterator_link() /* = delete */ ;

    mutable reference_count_t count;
};
} // range_detail

template<typename Iterator1, typename Iterator2>
inline void intrusive_ptr_add_ref(const range_detail::chain_iterator_link<Iterator1,Iterator2>* p)
{
    p->add_reference();
}

template<typename Iterator1, typename Iterator2>
inline void intrusive_ptr_release(const range_detail::chain_iterator_link<Iterator1,Iterator2>* p)
{
    if (p->release_reference())
        delete p;
}

namespace range_detail
{

class chain_iterator_begin_tag {};
class chain_iterator_end_tag {};

template<typename Iterator1
       , typename Iterator2
       , typename Reference
>
class chain_iterator_union
{
public:
    typedef Iterator1 iterator1_t;
    typedef Iterator2 iterator2_t;

    chain_iterator_union() {}
    chain_iterator_union(unsigned int /*selected*/, const iterator1_t& it1, const iterator2_t& it2) : m_it1(it1), m_it2(it2) {}

    iterator1_t& it1() { return m_it1; }
    const iterator1_t& it1() const { return m_it1; }

    iterator2_t& it2() { return m_it2; }
    const iterator2_t& it2() const { return m_it2; }

    Reference dereference(unsigned int selected) const
    {
        return selected ? *m_it2 : *m_it1;
    }

    bool equal(const chain_iterator_union& other, unsigned int selected) const
    {
        return selected
            ? m_it2 == other.m_it2
            : m_it1 == other.m_it1;
    }

private:
    iterator1_t m_it1;
    iterator2_t m_it2;
};

template<class Iterator, class Reference>
class chain_iterator_union<Iterator, Iterator, Reference>
{
public:
    typedef Iterator iterator1_t;
    typedef Iterator iterator2_t;

    chain_iterator_union() {}
    
    chain_iterator_union(unsigned int selected, const iterator1_t& it1, const iterator2_t& it2)
        : m_it(selected ? it2 : it1)
    {
    }

    iterator1_t& it1() { return m_it; }
    const iterator1_t& it1() const { return m_it; }

    iterator2_t& it2() { return m_it; }
    const iterator2_t& it2() const { return m_it; }

    Reference dereference(unsigned int) const
    {
        return *m_it;
    }

    bool equal(const chain_iterator_union& other, unsigned int selected) const
    {
        return m_it == other.m_it;
    }

private:
    iterator1_t m_it;
};

template<typename Iterator1
       , typename Iterator2
       , typename ValueType = typename iterator_value<Iterator1>::type
       , typename Reference = typename iterator_reference<Iterator1>::type
       , typename Traversal = typename demote_iterator_traversal_tag<
                                  typename iterator_traversal<Iterator1>::type
                                , typename iterator_traversal<Iterator2>::type>::type
>
class chain_iterator
    : public iterator_facade<chain_iterator<Iterator1,Iterator2,ValueType,Reference,Traversal>, ValueType, Traversal, Reference>
{
    typedef chain_iterator_link<Iterator1, Iterator2> link_t;
    typedef chain_iterator_union<Iterator1, Iterator2, Reference> iterator_union;
public:
    typedef Iterator1 iterator1_t;
    typedef Iterator2 iterator2_t;

    chain_iterator() : m_section(0u) {}

    chain_iterator(unsigned int section, Iterator1 current1, Iterator1 last1, Iterator2 first2, Iterator2 current2)
        : m_section(section)
        , m_it(section, current1, current2)
        , m_link(new link_t(last1, first2))
        {
        }

    template<typename Range1, typename Range2>
    chain_iterator(Range1& r1, Range2& r2, chain_iterator_begin_tag)
        : m_section(boost::empty(r1) ? 1u : 0u)
        , m_it(boost::empty(r1) ? 1u : 0u, boost::begin(r1), boost::begin(r2))
        , m_link(new link_t(boost::end(r1), boost::begin(r2)))
    {
    }

    template<typename Range1, typename Range2>
    chain_iterator(const Range1& r1, const Range2& r2, chain_iterator_begin_tag)
        : m_section(boost::empty(r1) ? 1u : 0u)
        , m_it(boost::empty(r1) ? 1u : 0u, boost::const_begin(r1), boost::const_begin(r2))
        , m_link(new link_t(boost::const_end(r1), boost::const_begin(r2)))
    {
    }

    template<typename Range1, typename Range2>
    chain_iterator(Range1& r1, Range2& r2, chain_iterator_end_tag)
        : m_section(1u)
        , m_it(1u, boost::end(r1), boost::end(r2))
        , m_link(new link_t(boost::end(r1), boost::begin(r2)))
    {
    }

    template<typename Range1, typename Range2>
    chain_iterator(const Range1& r1, const Range2& r2, chain_iterator_end_tag)
        : m_section(1u)
        , m_it(1u, boost::end(r1), boost::end(r2))
//        , m_it(1u, boost::const_end(r1), boost::const_end(r2))
        , m_link(new link_t(boost::end(r1), boost::begin(r2)))
//        , m_link(new link_t(boost::const_end(r1), boost::const_begin(r2)))
    {
    }

private:
    void increment()
    {
        if (m_section)
            ++m_it.it2();
        else
        {
            ++m_it.it1();
            if (m_it.it1() == m_link->last1)
            {
                m_it.it2() = m_link->first2;
                m_section = 1u;
            }
        }
    }

    void decrement()
    {
        if (m_section)
        {
            if (m_it.it2() == m_link->first2)
            {
                m_it.it1() = boost::prior(m_link->last1);
                m_section = 0u;
            }
            else
                --m_it.it2();
        }
        else
            --m_it.it1();
    }

    typename chain_iterator::reference dereference() const
    {
        return m_it.dereference(m_section);
    }

    bool equal(const chain_iterator& other) const
    {
        return m_section == other.m_section
            && m_it.equal(other.m_it, m_section);
    }

    void advance(typename chain_iterator::difference_type offset)
    {
        if (m_section)
            advance_from_range2(offset);
        else
            advance_from_range1(offset);
    }

    typename chain_iterator::difference_type distance_to(const chain_iterator& other) const
    {
        typename chain_iterator::difference_type result;
        if (m_section)
        {
            if (other.m_section)
                result = other.m_it.it2() - m_it.it2();
            else
            {
                result = (m_link->first2 - m_it.it2())
                       + (other.m_it.it1() - m_link->last1);

                BOOST_ASSERT( result <= 0 );
            }
        }
        else
        {
            if (other.m_section)
            {
                result = (m_link->last1 - m_it.it1())
                       + (other.m_it.it2() - m_link->first2);
            }
            else
                result = other.m_it.it1() - m_it.it1();
        }
        return result;
    }

    void advance_from_range2(typename chain_iterator::difference_type offset)
    {
        typedef typename chain_iterator::difference_type difference_t;
        BOOST_ASSERT( m_section == 1u );
        if (offset < 0)
        {
            difference_t r2_dist = m_link->first2 - m_it.it2();
            BOOST_ASSERT( r2_dist <= 0 );
            if (offset >= r2_dist)
                std::advance(m_it.it2(), offset);
            else
            {
                difference_t r1_dist = offset - r2_dist;
                BOOST_ASSERT( r1_dist <= 0 );
                m_it.it1() = m_link->last1 + r1_dist;
                m_section = 0u;
            }
        }
        else
            std::advance(m_it.it2(), offset);
    }

    void advance_from_range1(typename chain_iterator::difference_type offset)
    {
        typedef typename chain_iterator::difference_type difference_t;
        BOOST_ASSERT( m_section == 0u );
        if (offset > 0)
        {
            difference_t r1_dist = m_link->last1 - m_it.it1();
            BOOST_ASSERT( r1_dist >= 0 );
            if (offset < r1_dist)
                std::advance(m_it.it1(), offset);
            else
            {
                difference_t r2_dist = offset - r1_dist;
                BOOST_ASSERT( r2_dist >= 0 );
                m_it.it2() = m_link->first2 + r2_dist;
                m_section = 1u;
            }
        }
        else
            std::advance(m_it.it1(), offset);
    }

    unsigned int m_section;
    iterator_union m_it;
    intrusive_ptr<const link_t> m_link;

    friend class ::boost::iterator_core_access;
};

    } // namespace range_detail

} // namespace boost
#endif // include guard


