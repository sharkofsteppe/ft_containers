#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "Iterator.hpp"
#include <iostream>
#include <numeric>
#include <stdexcept>

namespace   ft
{
    template <bool, typename T = void>
    struct enable_if{};

    template <typename T>
    struct enable_if<true, T> {
    typedef T type;
    };

    template< class T, class Alloc = std::allocator<T> > 
    class vector
    {
        public:
            typedef             T                                               value_type;
            typedef             Alloc                                           allocator_type;
            typedef typename    allocator_type::reference                       reference;
            typedef typename    allocator_type::const_reference                 const_reference;
            typedef typename    allocator_type::pointer                         pointer;
            typedef typename    allocator_type::const_pointer                   const_pointer;
            typedef typename    allocator_type::difference_type                 difference_type;
            typedef typename    allocator_type::size_type                       size_type;
            typedef             ft::Ptrit<value_type, difference_type,
                                pointer, reference>                             iterator;
            typedef             ft::Ptrit<value_type, difference_type,
                                const_pointer, const_reference>                 const_iterator;
            typedef             ft::reverse_iterator<iterator>                  reverse_iterator;
            typedef             ft::reverse_iterator<const_iterator>            const_reverse_iterator;
            


        /*Constructors-------------------------------------------------------------------------------*/
        explicit vector (const allocator_type& alloc = allocator_type()) :  _N_(0), _alloc(alloc), First(0), Last(0), End(0){};// default
        explicit vector (size_type n, const value_type& val = value_type(), 
                        const allocator_type& alloc = allocator_type()) : _N_(n), _alloc(alloc)
        {
            First = _alloc.allocate(_N_);
            Last = First;
            End = First + _N_;
            while (Last != End)
            {
                _alloc.construct(Last, val);
                Last++;
            }
        }; // to fill with n elements. Each element is a copy of val 

        vector(const vector& x) : _N_(0), _alloc(x._alloc),  First(0), Last(0), End(0)
        {
            this->insert(this->begin(), x.begin(), x.end());
        } // copy constructor

   
       

        template <class InputIterator>
        vector (typename enable_if<!std::numeric_limits<InputIterator>::is_integer , InputIterator>::type first , InputIterator last,
                 const allocator_type& alloc = allocator_type()) : _alloc(alloc)
        {
            _N_ = last - first;
            First = _alloc.allocate(_N_);
            Last = First;
            End = First + _N_;
            while (Last != End)
            {
                _alloc.construct(Last, *first);
                first++;
                Last++; 
            }
        } // to fill range

	    vector &operator=(const vector& x)
		{
			if (x == *this)
				return (*this);

			this->clear();

			this->insert(this->end(), x.begin(), x.end());

			return (*this);
		}

        ~vector()
        {
            this->clear();
            _alloc.deallocate(First, _N_);
        }


        /*Iterators-----------------------------------------------------------------------------------*/

            iterator begin() 
            { return (iterator(First));}
            iterator end() 
            { return (iterator(Last));}
            const_iterator begin() const 
            { return (const_iterator(First)); }
            const_iterator end() const 
            { return (const_iterator(Last)); }

            reverse_iterator rbegin() 
            { return (reverse_iterator(end()));}
            reverse_iterator rend() 
            { return (reverse_iterator(begin()));}
            const_reverse_iterator rbegin() const 
            { return (const_reverse_iterator(end())); }
            const_reverse_iterator rend() const 
            { return (const_reverse_iterator(begin())); }



        /*Capacity-------------------------------------------------------------------------------*/
            size_type size() const
            { 
                return (Last - First); }

            size_type	max_size() const
            { return (allocator_type().max_size()); }

            void resize (size_type n, value_type val = value_type())
            {
                if (size() < n)
                    insert(end(), n - size(), val);
                if(n < size())
                    erase (begin() + n, end());
            }

            size_type capacity() const
            {
                return (First == 0 ? 0 : End - First);
            }

            bool empty() const
            { return (size() == 0); }

            void    reserve(size_type N)
            {
                _N_ = N;
                if (max_size() < N)
                    throw std::out_of_range("too big number");
                else if (capacity() < N)
                {
                    pointer Q = _alloc.allocate(N, (void *)0);
                    pointer Qcopy = Q;
                    iterator tmp = begin();
                    iterator tmpen = end();
                    while (tmp != tmpen)
                    {
                        *Qcopy = *tmp;
                        tmp++;
                        Qcopy++;
                    }
                    End = Q + N;
                    Last = Q + size();
                    _alloc.deallocate(First, Last - First);
                    First = Q;
                    
                }
            }

        /*Element access---------------------------------------------------------------------------*/

            reference operator[] (size_type P)
            {
                return(*(begin() + P));
            }

            const_reference operator[](size_type P) const
            {
                return (*(begin() + P));
            }

            const_reference at(size_type P) const
            {
                if (size() <= P)
                    throw std::out_of_range("Out of range");
                return (*(begin() + P));
            }

            reference at(size_type P)
            {
                if (size() <= P)
                    throw std::out_of_range("Out of range");
                return (*(begin() + P));
            }

            reference front()
            {return (*begin());}
            const_reference front() const
            { return (*begin());}
            reference back()
            { return (*(end() - 1));}
            const_reference back() const
            { return (*(end() - 1));}

        /*-------------------------------------Modifiers-------------------------------------------*/

           
            iterator erase(iterator first, iterator last)
            {
                
                size_type dif = last - first;
                difference_type diff = first - begin();
                iterator itb = begin() + diff;
                iterator ite = end();
                while (itb != ite)
                {
                    _alloc.destroy(itb.base());
                    if (itb < ite - dif)
                        _alloc.construct(itb.base(),*((itb + dif).base()));
                    itb++;
                }
                Last -= dif;
                End -= dif;
               
                return (first);
            }

            iterator erase (iterator position)
            { return (erase(position, position + 1)); }

            iterator insert(iterator position, const value_type& val)
            {
                difference_type dif = end() - position;
                if (capacity() == 0)
                {
                    this->reserve(1);
                }
                if (size() == capacity())
                    this->reserve(capacity() * 2);

                iterator ipt = begin() + size();
                iterator pt = end() - dif;
                while (ipt > pt)
                {
                    *(ipt) = *(ipt - 1);
                    ipt--;
                }
                *(ipt) = val;
                Last++;
                return (ipt);
            }

            void insert (iterator position, size_type n, const value_type& val)
            {
                difference_type diff = position - begin();
                if (capacity() == 0)
                {
                    this->reserve(n * 2);
                }
                if (size() == capacity())
                    this->reserve((capacity() + n) * 2);

                iterator ipt = begin() + size() + n;
                size_type i = n;
                while (ipt > (begin() + diff))
                {
                    *(ipt) = *(ipt - n);
                    ipt--;
                }
                ipt = begin() + diff;
                while (i > 0)
                {
                    *ipt = val;
                    ipt++;
                    i--;
                }
                Last += n;
            }

            template <class InputIterator>
            void insert (iterator position, InputIterator first, typename
                        ft::enable_if< !std::numeric_limits<InputIterator>::is_integer,
                        InputIterator >::type last)
            {
                difference_type diff = position - begin();
                difference_type n = last - first;

                if (capacity() == 0)
                    this->reserve(n);
                if (size() == capacity())
                    this->reserve((capacity() + n));
                if (capacity() - size() < (unsigned long)n)
                    this->reserve(n * 2);
                iterator ipt = begin() + size() + n;
                if (size() >= (unsigned long)n)
                {
                    while (ipt > (begin() + diff))
                    {
                        _alloc.construct(ipt.base(),*(ipt - n) );
                        _alloc.destroy((ipt - n).base());
                        ipt--;
                    }
                }
                ipt = begin() + diff;
                while (first != last)
                {
                    _alloc.construct(ipt.base(), *first);
                    ipt++;
                    first++;
                }
                Last += n;
            }

            void push_back (const value_type& val)
            { insert(end() , val); }

            void pop_back()
            { erase(end() - 1); }
	
            template <class InputIterator>
            void assign (InputIterator first, InputIterator last)
            {
                erase(begin(), end());
                insert(begin(), first, last);
            }
	
            void assign (size_type n, const value_type& val)
            {
                value_type nval = val;
                erase(begin(), end());
                insert(begin(), n, nval);
            }



            void clear()
            { erase(begin(), end()); }

            void swap (vector& x)
            {
                if (_alloc == x._alloc)
                {
                    std::swap(First, x.First);
                    std::swap(Last, x.Last);
                    std::swap(End, x.End);
                }
                else
                {
                    vector Ts = *this;
                    *this = x;
                    x = Ts;
                }
            }
        /*--------------------------------------------------------------------------------------------*/
        /*-------------------------------------ELEMENT ACCESS-------------------------------------------*/


        allocator_type  get_allocator() const
        { return (_alloc); }

        private:
            size_type           _N_;
            allocator_type      _alloc;
            pointer             First;
            pointer             Last;
            pointer             End;

    };
    
    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                        InputIterator2 first2, InputIterator2 last2)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1) return false;
            else if (*first1 < *first2) return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }
    template <class T, class Alloc>
    bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        typename ft::vector<T>::const_iterator first1 = lhs.begin();
		typename ft::vector<T>::const_iterator first2 = rhs.begin();
		while (first1 != lhs.end())
		{
			if (first2 == rhs.end() || *first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return (true);
    }

    template <class T, class Alloc>
    bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    { return (!(lhs == rhs));}

    template <class T, class Alloc>
    bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}

    template <class T, class Alloc>
    bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    { return (!(rhs < lhs)); }


    template <class T, class Alloc>
    bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(lhs < rhs));
    }
    template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>&y)
	{
		x.swap(y);
	}

}

#endif