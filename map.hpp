#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <functional>
#include "pair.hpp"
#include "RBT.hpp"
#include "Iterator.hpp"

namespace       ft
{
    template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {   
        
        public:
            typedef Key                                                         key_type;
            typedef T                                                           mapped_type;
            typedef Compare                                                     key_compare;
            typedef Allocator                                                   allocator_type;
            typedef ft::pair<const Key, T>                                      value_type;
            class                                                               value_compare;
            typedef typename Allocator::pointer                                 pointer;
            typedef typename Allocator::const_pointer                           const_pointer;
            typedef typename Allocator::reference                               reference;
            typedef typename Allocator::const_reference                         const_reference;
            typedef typename Allocator::size_type                               size_type;
            typedef typename Allocator::difference_type                         difference_type;

            typedef typename RBT<value_type, key_compare>::iterator             iterator;
            // typedef typename RBT<value_type, key_compare>::reverse_iterator     reverse_iterator;




            // typedef  typename           RBT<value_type, key_compare>::const_iterator                 const_iterator;

            // typedef reverse_iterator<const_iterator>                            const_reverse_iterator;
            // typedef reverse_iterator<iterator>                                  reverse_iterator;

            /*----------------------------CONSTRUCTORS----------------------------*/
            // map();

            explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc),
				_comp(comp),
				rbt()
			{}

            // map(const key_compare &comp, const allocator_type &al);

            map(const map &x);

            template<class InIt>
            map(InIt first, InIt last);

            template <class InputIterator>
            map (InputIterator first, InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type());

            /*----------------------------ITERATORS----------------------------*/

            iterator begin()
            {
                return (rbt.begin());
            } 
            // const_iterator begin() const ;

            iterator end()
            {
                return (rbt.end());
            }
            // const_iterator end() const ;

            // reverse_iterator rbegin()
            // {
            //     return (rbt.rbegin());
            // }
            // const_reverse_iterator rbegin() const ;

            // reverse_iterator rend()
            // {
            //     return (rbt.rend());
            // }
            // const_reverse_iterator rend() const ;

            /*----------------------------CAPACITY----------------------------*/
            bool empty() const;
            size_type size() const;
            size_type max_size() const;

            /*----------------------------ELEMENT-ACCESS----------------------------*/
            mapped_type& operator[] (const key_type& k);

            /*----------------------------MODIFIERS----------------------------*/
            void insert (const value_type& val)
            {
                rbt.insert(val);
                
                return ;
            }
	
            // iterator insert (iterator position, const value_type& val);
	
            // template <class InputIterator>
            // void insert (InputIterator first, InputIterator last);

            // void erase (iterator position);

            // size_type erase (const key_type& k);

            // void erase (iterator first, iterator last);
            // void swap (map& x);
            void clear();

            /*----------------------------OBSERVERS----------------------------*/

            // key_compare key_comp() const;
            // value_compare value_comp() const;

            /*----------------------------OPERATIONS----------------------------*/
            // iterator find (const key_type& k);
            // const_iterator find (const key_type& k) const;
            // size_type count (const key_type& k) const;
            // iterator lower_bound (const key_type& k);
            // const_iterator lower_bound (const key_type& k) const;
            // iterator upper_bound (const key_type& k);
            // const_iterator upper_bound (const key_type& k) const;
            // ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
            // ft::pair<iterator,iterator>             equal_range (const key_type& k);

            // allocator_type get_allocator() const;
        public:
            RBT<value_type, Compare> rbt;
            allocator_type  _alloc;
            Compare         _comp;
    };
}


#endif