#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "RBT.hpp"
#include  <cstddef>
namespace ft
{

    struct input_iterator_tag  {};
    struct output_iterator_tag {};
    struct forward_iterator_tag       : public input_iterator_tag         {};
    struct bidirectional_iterator_tag : public forward_iterator_tag       {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template<class Category, class T, class Distance = ptrdiff_t,
            class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };

    template<class T, class D, class Pt, class Rt>
    struct Ranit : public iterator<random_access_iterator_tag,
    T, D, Pt, Rt>{};

    template<class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    template<class T>
    struct iterator_traits<T*>
    {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef random_access_iterator_tag iterator_category;
    };

    template<class T>
    struct iterator_traits<const T*>
    {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef random_access_iterator_tag iterator_category;
    };

    template<class T, class D, class Pt, class Rt>
    class Ptrit : public iterator<random_access_iterator_tag, T, D, Pt, Rt>
    {
        protected:
        Pt current;
        public:

        typedef Ptrit<T, D, Pt, Rt> Myt;


        Ptrit(){};
        explicit Ptrit(Pt P) : current(P) {};
        Ptrit(const Ptrit<T, D, Pt, Rt> & X) : current(X.base()) {};


        Pt      base() const {return (current);}
        Rt      operator*() const {return (*current);}
        Pt      operator->() const {return (&**this);}
        Myt     &operator++() { ++current; return (*this);}
        Myt     operator++(int) { Myt tmp = *this; ++current; return (tmp);}
        Myt     &operator--() { --current; return (*this);}
        Myt     operator--(int) { Myt tmp = *this; --current; return (tmp);}
        bool    operator==(int Y)  const { return (current == (Pt)Y);};
        bool    operator==(const Myt &Y) const {return (current == Y.current);};
        bool    operator!=(const Myt &Y) const {return (!(current == Y.current));};
        Myt     &operator+=(D N) {current += N; return (*this);};
        Myt     operator+(D N) const { return (Myt(current + N));};
        Myt     &operator-=(D N) { current -= N; return (*this);};
        Myt     operator-(D N) const { return (Myt(current - N));};
        Rt      operator[](D N) const { return (*(*this + N));};
        bool    operator<(const Myt &Y) const {return (current < Y.current);};
        bool    operator>(const Myt &Y) const {return (current > Y.current);};
        bool    operator<=(const Myt &Y) const {return (!(current < Y.current));};
        bool    operator>=(const Myt &Y) const {return (!(current > Y.current));};
        D       operator-(const Myt &Y) const {return (current  - Y.current);};

    };
    // template<class T, class D, class Pt, class Rt> inline
    // Ptrit<T, D, Pt, Rt>
    //     operator+(D N, const Ptrit<T, D, Pt, Rt>) {return (Y + N); };

    template<class RanIt>
    class reverse_iterator : public iterator<
    typename iterator_traits<RanIt>::iterator_category,
    typename iterator_traits<RanIt>::value_type,
    typename iterator_traits<RanIt>::difference_type,
    typename iterator_traits<RanIt>::pointer,
    typename iterator_traits<RanIt>::reference>
    {
        protected:
                             RanIt                                  current;
        public:
        typedef             reverse_iterator<RanIt>                 Myt;
        typedef typename    iterator_traits<RanIt>::difference_type D;
        typedef typename    iterator_traits<RanIt>::pointer         Pt;
        typedef typename    iterator_traits<RanIt>::reference       Rt;
        typedef             RanIt                                   iterator_type;

        reverse_iterator() {};
        explicit reverse_iterator(RanIt X) : current(X) {};
        template<class U> reverse_iterator(const reverse_iterator<U> &X) : current(X.base()) {};
        RanIt   base() const { return (current);};
        Rt      operator*() const { RanIt tmp = current; return (*--tmp);};
        Pt      operator->() const {return (&**this);}
        Myt     &operator++() { --current; return (*this);}
        Myt     operator++(int) { Myt tmp = *this; --current; return (tmp);}
        Myt     &operator--() { ++current; return (*this);}
        Myt     operator--(int) { Myt tmp = *this; ++current; return (tmp);}
        bool    Eq(const Myt& Y)  const { return (current == Y.current);};
        bool    operator==(int Y)  const { return (current == (Pt)Y);};
        bool    operator==(const Myt &Y) const {return (current == Y.current);};
        bool    operator!=(const Myt &Y) const {return (!(current == Y.current));};
        bool    operator<(const Myt &Y) const {return (current > Y.current);};
        bool    operator>(const Myt &Y) const {return (current < Y.current);};
        bool    operator<=(const Myt &Y) const {return (!(current < Y.current));};
        bool    operator>=(const Myt &Y) const {return (!(current > Y.current));};


        Myt     &operator+=(D N) {current -= N; return (*this);};
        Myt     operator+(D N) const { return (Myt(current - N));};
        Myt     &operator-=(D N) { current += N; return (*this);};
        Myt     operator-(D N) const { return (Myt(current + N));};
        Rt      operator[](D N) const { return (*(*this + N));};
        bool    Lt(const Myt &Y) const {return (Y.current < current);};
       
        D       Mi(const Myt &Y) const {return (Y.current - current);};
    };


    template<class T, class D, class Pt, class Rt>
    class TREEit : public iterator<bidirectional_iterator_tag, T, D, Pt, Rt>
    {
        protected:
        Node<T> *current;
        public:

        typedef TREEit<T, D, Pt, Rt> Myt;


        TREEit(){};

        TREEit(Node<T> *other) : current(other)
        {}

        // explicit TREEit(Node<T> P) : current(P)
        // {
        //     // std::cout << "fdsf\n";
        // };

        // TREEit(const TREEit<T, D, Pt, Rt> & X) : current(X.base()) {};


        // Pt      base() const {return (current);}
        // Rt      operator*() const {return (*current);}
        T *operator->() const {return &current->val;}
        // Myt     &operator++() { ++current; return (*this);}
        // Myt     operator++(int) { Myt tmp = *this; ++current; return (tmp);}
        // Myt     &operator--() { --current; return (*this);}
        // Myt     operator--(int) { Myt tmp = *this; --current; return (tmp);}
        // bool    operator==(int Y)  const { return (current == (Pt)Y);};
        // bool    operator==(const Myt &Y) const {return (current == Y.current);};
        // bool    operator!=(const Myt &Y) const {return (!(current == Y.current));};
        // Myt     &operator+=(D N) {current += N; return (*this);};
        // Myt     operator+(D N) const { return (Myt(current + N));};
        // Myt     &operator-=(D N) { current -= N; return (*this);};
        // Myt     operator-(D N) const { return (Myt(current - N));};
        // Rt      operator[](D N) const { return (*(*this + N));};
        // bool    operator<(const Myt &Y) const {return (current < Y.current);};
        // bool    operator>(const Myt &Y) const {return (current > Y.current);};
        // bool    operator<=(const Myt &Y) const {return (!(current < Y.current));};
        // bool    operator>=(const Myt &Y) const {return (!(current > Y.current));};
        // D       operator-(const Myt &Y) const {return (current  - Y.current);};

    };
    
} // namespace ft



 
#endif
