#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <functional>
#include "pair.hpp"
#include "RBT.hpp"
#include "Iterator.hpp"
#include "stack.hpp"

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
            typedef typename RBT<value_type, key_compare>::reverse_iterator     reverse_iterator;




            typedef  typename    RBT<value_type, key_compare>::const_iterator   const_iterator;
            typedef  typename    RBT<value_type, key_compare>::const_reverse_iterator   const_reverse_iterator;
            typedef  typename    RBT<value_type, key_compare>::node             node_type;

            /*----------------------------CONSTRUCTORS----------------------------*/
            // map();

            explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc),
				_comp(comp),
				rbt()
			{
            }

           map& operator=( const map& other )
           {
                if (this == &other)
                    return (*this);
                this->rbt = other.rbt;
                return (*this);
           }

            map(const map &x) : _alloc(x._alloc), _comp(x._comp), rbt()
            {
                insert(x.begin(), x.end());
            }


            template <class InputIterator>
            map (InputIterator first, InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
            {
                insert(first, last);
            }

            /*----------------------------ITERATORS----------------------------*/

            iterator begin()
            {
                return (rbt.begin());
            }

            const_iterator begin() const
            {
                return (rbt.begin());
            }

            iterator end()
            {
                return (rbt.end());
            }

            const_iterator end() const
            {
                return (rbt.end());
            }

            reverse_iterator rbegin()
            {
                return (rbt.rbegin());
            }

            const_reverse_iterator rbegin() const
            {
                return (rbt.rbegin());
            }

            reverse_iterator rend()
            {
                return (rbt.rend());
            }

            const_reverse_iterator rend() const
            {
                return (rbt.rend());
            }

            /*----------------------------CAPACITY----------------------------*/
            bool empty() const
            {
                return (rbt.empty());
            }

            size_type size() const
            {
                return (rbt.count);
            }

            size_type max_size() const
            {
                return (get_allocator().max_size());
            }


            /*----------------------------ELEMENT-ACCESS----------------------------*/
            mapped_type& operator[] (const key_type& k)
            {
                int flag = 0;
                value_type  tmp_pair = ft::make_pair(k, mapped_type());
                node_type*  searched = this->rbt.search(tmp_pair, &flag);
                
                
                if (!flag)
                {
                    insert(tmp_pair);
                    return rbt.search(tmp_pair, &flag)->val.second;
                }
                return searched->val.second;
            }

            mapped_type& at( const key_type& key )
            {
                int flag = 0;
                node_type* searched = this->rbt.search(ft::make_pair(key, 0), &flag);
                if (!flag)
                    throw std::out_of_range("range error");
                return (searched->val.second);
            }
            const mapped_type& at( const key_type& key ) const
            {
                int flag = 0;
                const node_type* searched = this->rbt.search(ft::make_pair(key, mapped_type()), &flag);
                if (!flag)
                    throw std::out_of_range("range error");
                return (searched->val.second);
            }
            /*----------------------------MODIFIERS----------------------------*/
            void insert (const value_type& val)
            {
                rbt.insert(val);
                return ;
            }
	
           iterator insert (iterator position, const value_type& val)
           {
               
           }
	
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last)
            {
                while (first != last)
                {
                    rbt.insert(*first);
                    first++;
                }
            }
            pair<iterator,bool> insert (const value_type& val)
            {

            }



            void erase (iterator position)
            {
                rbt.deleteNode(position.base());
            }

            size_type erase (const key_type& k)
            {
                int flag = 0;
                node_type *tmp = rbt.search(ft::make_pair(k, mapped_type()), &flag);
                size_type deleted = rbt.count;

                if (flag)
                {
                    rbt.deleteNode(tmp);
                }
                if (deleted > rbt.count)
                    return 1;
                return (0);
            }

            void erase (iterator ft, iterator lt)
            {
                ft::stack<node_type *> storage;
                while (ft != lt)
                {
                    storage.push(ft.base());
                    ++ft;   
                }
			    while (!storage.empty())
                {
				    rbt.deleteNode(storage.top());
				    storage.pop();
			    }
        

            }
            // void swap (map& x);

            void clear()
            {
                erase(begin(),end());
            }

            /*----------------------------OBSERVERS----------------------------*/

            // key_ key_comp() const;
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

            allocator_type get_allocator() const
            {
                return(Allocator());
            }

        public:
            RBT<value_type, Compare> rbt;
            allocator_type  _alloc;
            Compare         _comp;
    };

    template <class init>
    size_t  distance(init __first, init __last)
    {
        size_t i = 0;

        while (__first != __last)
        {
            i++;
            __first++;
        }
        return i;
    }
}


#endif