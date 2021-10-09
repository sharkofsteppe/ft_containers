#include <iostream>
#include <vector>
#include "vector.hpp"
#include <map>
#include "map.hpp"
// #include "tests.hpp"

# define B_CYAN "\x1b[46;1m" <<
# define B_RED  "\x1b[41;1m" <<
# define YELLOW "\x1b[33;1m" <<
# define RED    "\x1b[31;1m" <<
# define GREEN  "\x1b[32;1m" <<
# define DEFAULT << "\x1b[m"

# define STRESS_PUSH    5
# define STRESS_POP     5

template< class T>
void    print_map(T& map)
{
    int a = 0;
    std::cout << "[ ";
    for (typename T::const_iterator i = map.begin();
         i != map.end(); ++i, ++a)
    {
        std::cout << i->second << " ";
        if (a == 5)
            break ;
    }
    std::cout << "]" << std::endl;
}

void    compare_maps(std::map<int, long>& lhs, ft::map<int, long>& rhs)
{
    print_map(lhs);
    print_map(rhs);
    
    std::map<int, long>::const_iterator i = lhs.begin();
    ft::map<int, long>::const_iterator j = rhs.begin();
    for ( ; i != lhs.end() && j != rhs.end(); ++i, ++j)
        if ((i->first != j->first) || (i->second != j->second))
        {

            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
            return;
        }
    if (i != lhs.end() || j != rhs.end())
    {
        std::cout << RED "KO" DEFAULT << std::endl;
        return;
    }
    std::cout << GREEN "OK" DEFAULT << " | ";

    // size
    if (lhs.size() != rhs.size())
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;

    // begin iterators
    if (lhs.size() && lhs.begin()->second != rhs.begin()->second)
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;

    // last element

    // ft::map<int, long>::const_iterator o = rhs.end();
    // --o;
    // std::cout <<(--rhs.end())->second << " GAPE " << (--lhs.end())->second << '\n';

    if (lhs.size() && (--lhs.end())->second != (--rhs.end())->second)
    {

        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    }
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;

    std::cout << '\n' << std::endl;
}

void    stress_test(std::map<int, long>& lhs, ft::map<int, long>& rhs)
{

    for (int i = -100; i < -100 + STRESS_PUSH; i++)
        { lhs[i] = i * 123; rhs[i] = i * 123; }


    size_t tmp1, tmp2;
    for (int i = -100; i < -100 + STRESS_POP; i++)
        {

            tmp1 = lhs.erase(i);
            tmp2 = rhs.erase(i);


            if (tmp1 != tmp2)
            {

                std::cout << RED "Stress test: KO" DEFAULT << '\n' << std::endl;
                return;
            }
        }
}



void    value_generator(int count, std::vector<std::pair<int, long> >& sv,
                       ft::vector<ft::pair<int, long> >& fv)
{
    sv.clear();
    fv.clear();
    for (int i = 0; i < count; i++)
    {
        sv.push_back(std::make_pair(i, i * 2));
        fv.push_back(ft::make_pair(i, i * 2));
    }
}




void    test_map_rev_iterators_1_1(void)
{
    std::cout << YELLOW "1.1) reverse iterators [empty]:" DEFAULT << std::endl;

    std::map<int, long>    smap;
    ft::map<int, long>     fmap;

    
    for (std::map<int, long>::reverse_iterator i = smap.rbegin(); i != smap.rend(); ++i)
        i->second = 0;

    for (ft::map<int, long>::reverse_iterator i = fmap.rbegin(); i != fmap.rend(); ++i)
        i->second = 0;

    std::map<int, long>::reverse_iterator  s_it = smap.rbegin();
    // s_it++; ++s_it; s_it--; --s_it; // SEGV
    std::cout << "std: ";
    if (s_it != smap.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::map<int, long>::reverse_iterator  f_it = fmap.rbegin();
    f_it++; ++f_it; f_it--; --f_it;
    std::cout << "ft:  ";
    if (f_it != fmap.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_maps(smap, fmap);
}

void    test_map_rev_iterators_1_2(void)
{
    std::cout << YELLOW "1.2) reverse iterators [non-empty]:" DEFAULT << std::endl;

    std::vector<std::pair<int, long> >  svec;
    ft::vector<ft::pair<int, long> >    fvec;
    value_generator(5, svec, fvec);

    std::map<int, long>    smap(svec.begin(), svec.end());
    ft::map<int, long>     fmap(fvec.begin(), fvec.end());

    for (std::map<int, long>::reverse_iterator i = smap.rbegin(); i != smap.rend(); ++i)
        i->second = 0;

    for (ft::map<int, long>::reverse_iterator i = fmap.rbegin(); i != fmap.rend(); ++i)
        i->second = 0;

    std::map<int, long>::reverse_iterator  s_it = smap.rbegin();
    s_it++; ++s_it; s_it--; --s_it;
    std::cout << "std: ";
    if (s_it != smap.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::map<int, long>::reverse_iterator  f_it = fmap.rbegin();
    f_it++; ++f_it; f_it--; --f_it;
    std::cout << "ft:  ";
    if (f_it != fmap.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;


    compare_maps(smap, fmap);
}

void    test_map_rev_iterators_2_1(void)
{
    std::cout << YELLOW "2.1) const_reverse_iterators [empty]:" DEFAULT << std::endl;

    std::map<int, long>    smap;
    ft::map<int, long>     fmap;

    for (std::map<int, long>::const_reverse_iterator i = smap.rbegin(); i != smap.rend(); ++i)
        *i;

    for (ft::map<int, long>::const_reverse_iterator i = fmap.rbegin(); i != fmap.rend(); ++i)
        *i;

    std::map<int, long>::const_reverse_iterator  s_it = smap.rbegin();
    // s_it++; ++s_it; s_it--; --s_it; // SEGV
    std::cout << "std: ";
    if (s_it != smap.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::map<int, long>::const_reverse_iterator  f_it = fmap.rbegin();
    f_it++; ++f_it; f_it--; --f_it;
    std::cout << "ft:  ";
    if (f_it != fmap.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_maps(smap, fmap);
}

void    test_map_rev_iterators_2_2(void)
{
    std::cout << YELLOW "2.2) const_reverse_iterators [non-empty]:" DEFAULT << std::endl;

    std::vector<std::pair<int, long> >  svec;
    ft::vector<ft::pair<int, long> >    fvec;
    value_generator(5, svec, fvec);

    std::map<int, long>    smap(svec.begin(), svec.end());
    ft::map<int, long>     fmap(fvec.begin(), fvec.end());

    for (std::map<int, long>::const_reverse_iterator i = smap.rbegin(); i != smap.rend(); ++i)
        *i;

    for (ft::map<int, long>::const_reverse_iterator i = fmap.rbegin(); i != fmap.rend(); ++i)
        *i;

    std::map<int, long>::const_reverse_iterator  s_it = smap.rbegin();
    s_it++; ++s_it; s_it--; --s_it;
    std::cout << "std: ";
    if (s_it != smap.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::map<int, long>::const_reverse_iterator  f_it = fmap.rbegin();
    f_it++; ++f_it; f_it--; --f_it;
    std::cout << "ft:  ";
    if (f_it != fmap.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;


    compare_maps(smap, fmap);
}

void    test_map_rev_iterators_3(void)
{
    std::cout << YELLOW "3) reverse_iterators order:" DEFAULT << std::endl;

    std::vector<std::pair<int, long> >  svec;
    ft::vector<ft::pair<int, long> >    fvec;
    value_generator(5, svec, fvec);

    std::map<int, long>    smap(svec.begin(), svec.end());
    ft::map<int, long>     fmap(fvec.begin(), fvec.end());

    for (std::map<int, long>::reverse_iterator i = smap.rbegin(); i != smap.rend(); ++i)
        i->second = (int)std::distance(smap.rbegin(), i);

    for (ft::map<int, long>::reverse_iterator i = fmap.rbegin(); i != fmap.rend(); ++i)
        i->second = (int)ft::distance(fmap.rbegin(), i);

    compare_maps(smap, fmap);
}

void    test_map_iterators_1_1(void)
{
    std::cout << YELLOW "1.1) iterators [empty]:" DEFAULT << std::endl;

    std::map<int, long>    smap;
    ft::map<int, long>     fmap;

    for (std::map<int, long>::iterator i = smap.begin(); i != smap.end(); ++i)
        i->second = 0;


    for (ft::map<int, long>::iterator i = fmap.begin(); i != fmap.end(); ++i)
        i->second = 0;

    std::map<int, long>::iterator  s_it = smap.begin();
    // s_it++; ++s_it; s_it--; --s_it;  // infinite
    std::cout << "std: ";
    if (s_it != smap.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::map<int, long>::iterator  f_it = fmap.begin();
    f_it++; ++f_it; f_it--; --f_it;
    std::cout << "ft:  ";
    if (f_it != fmap.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_maps(smap, fmap);
}

void    test_map_iterators_1_2(void)
{
    std::cout << YELLOW "1.2) iterators [non-empty]:" DEFAULT << std::endl;

    std::vector<std::pair<int, long> >  svec;
    ft::vector<ft::pair<int, long> >    fvec;
    value_generator(5, svec, fvec);

    std::map<int, long>    smap(svec.begin(), svec.end());
    ft::map<int, long>     fmap(fvec.begin(), fvec.end());

    for (std::map<int, long>::iterator i = smap.begin(); i != smap.end(); ++i)
        i->second = 0;

    for (ft::map<int, long>::iterator i = fmap.begin(); i != fmap.end(); ++i)
        i->second = 0;

    std::map<int, long>::iterator  s_it = smap.begin();
    s_it++; ++s_it; s_it--; --s_it;
    std::cout << "std: ";
    if (s_it != smap.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::map<int, long>::iterator  f_it = fmap.begin();
    f_it++; ++f_it; f_it--; --f_it;
    std::cout << "ft:  ";
    if (f_it != fmap.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_maps(smap, fmap);
}

void    test_map_iterators_2_1(void)
{
    std::cout << YELLOW "2.1) const_iterators [empty]:" DEFAULT << std::endl;

    std::map<int, long>    smap;
    ft::map<int, long>     fmap;

    for (std::map<int, long>::const_iterator i = smap.begin(); i != smap.end(); ++i)
        *i;

    for (ft::map<int, long>::const_iterator i = fmap.begin(); i != fmap.end(); ++i)
        *i;

    std::map<int, long>::const_iterator  s_it = smap.begin();
    // s_it++; ++s_it; s_it--; --s_it; // infinite
    std::cout << "std: ";
    if (s_it != smap.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::map<int, long>::const_iterator  f_it = fmap.begin();
    f_it++; ++f_it; f_it--; --f_it;
    std::cout << "ft:  ";
    if (f_it != fmap.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_maps(smap, fmap);
}

void    test_map_iterators_2_2(void)
{
    std::cout << YELLOW "2.2) const_iterators [non-empty]:" DEFAULT << std::endl;

    std::vector<std::pair<int, long> >  svec;
    ft::vector<ft::pair<int, long> >    fvec;
    value_generator(5, svec, fvec);

    std::map<int, long>    smap(svec.begin(), svec.end());
    ft::map<int, long>     fmap(fvec.begin(), fvec.end());

    for (std::map<int, long>::const_iterator i = smap.begin(); i != smap.end(); ++i)
        *i;

    for (ft::map<int, long>::const_iterator i = fmap.begin(); i != fmap.end(); ++i)
        *i;

    std::map<int, long>::const_iterator  s_it = smap.begin();
    s_it++; ++s_it; s_it--; --s_it;
    std::cout << "std: ";
    if (s_it != smap.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::map<int, long>::const_iterator  f_it = fmap.begin();
    f_it++; ++f_it; f_it--; --f_it;
    std::cout << "ft:  ";
    if (f_it != fmap.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_maps(smap, fmap);
}

void    test_map_iterators_3(void)
{
    std::cout << YELLOW "3) iterators order: " DEFAULT << std::endl;

    std::vector<std::pair<int, long> >  svec;
    ft::vector<ft::pair<int, long> >    fvec;
    value_generator(5, svec, fvec);

    std::map<int, long>    smap(svec.begin(), svec.end());
    ft::map<int, long>     fmap(fvec.begin(), fvec.end());

    for (std::map<int, long>::iterator i = smap.begin(); i != smap.end(); ++i)
        i->second = (int)std::distance(smap.begin(), i);

    for (ft::map<int, long>::iterator i = fmap.begin(); i != fmap.end(); ++i)
        i->second = (int)ft::distance(fmap.begin(), i);

    compare_maps(smap, fmap);
}

void    test_map_constructor_1_1(void)
{
    std::cout << YELLOW "1.1) Default constructor:" DEFAULT << std::endl;
    std::map<int, long>    smap;
    ft::map<int, long>     fmap;

    compare_maps(smap, fmap);
}

void    test_map_constructor_1_2(void)
{
    std::cout << YELLOW "1.2) Default constructor [+ add + erase]:" DEFAULT << std::endl;
    std::map<int, long>    smap;
    ft::map<int, long>     fmap;

    stress_test(smap, fmap);

    compare_maps(smap, fmap);
}

void    test_map_constructor_2_1(void)
{
    std::cout << YELLOW "2.1) Default constructor with compare + allocator :" DEFAULT << std::endl;

    std::allocator<int>  alloc;

    std::map<int, long>    smap(std::less<int>(), alloc);
    ft::map<int, long>     fmap(std::less<int>(), alloc);

    compare_maps(smap, fmap);
}

void    test_map_constructor_2_2(void)
{
    std::cout << YELLOW "2.2) Default constructor with allocator [+ add + erase]:" DEFAULT << std::endl;

    std::allocator<int>  alloc;

    std::map<int, long>    smap(std::less<int>(), alloc);
    ft::map<int, long>     fmap(std::less<int>(), alloc);

    stress_test(smap, fmap);

    compare_maps(smap, fmap);
}

void    test_map_constructor_3_1(void)
{
    std::cout << YELLOW "3.1) Range based constructor:" DEFAULT << std::endl;

    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;

        std::map<int, long>    smap(svec.begin(), svec.end());
        ft::map<int, long>     fmap(fvec.begin(), fvec.end());

        compare_maps(smap, fmap);
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(1, svec, fvec);

        std::map<int, long>    smap(svec.begin(), svec.end());
        ft::map<int, long>     fmap(fvec.begin(), fvec.end());

        compare_maps(smap, fmap);
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(5, svec, fvec);

        std::map<int, long>    smap(svec.begin(), svec.end());
        ft::map<int, long>     fmap(fvec.begin(), fvec.end());

        compare_maps(smap, fmap);
    }
}

void    test_map_constructor_3_2(void)
{
    std::cout << YELLOW "3.2) Range based constructor [+ push + pop]:" DEFAULT << std::endl;

    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(0, svec, fvec);
        std::map<int, long>    smap(svec.begin(), svec.end());
        ft::map<int, long>     fmap(fvec.begin(), fvec.end());

      




        stress_test(smap, fmap);
        compare_maps(smap, fmap);

    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(1, svec, fvec);
     

        std::map<int, long>    smap(svec.begin(), svec.end());
        ft::map<int, long>     fmap(fvec.begin(), fvec.end());
    
        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(5, svec, fvec);

        std::map<int, long>    smap(svec.begin(), svec.end());
        ft::map<int, long>     fmap(fvec.begin(), fvec.end());

        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
}

void    test_map_constructor_5_1(void)
{
    std::cout << YELLOW "5.1) Copy constructor [empty]:" DEFAULT << std::endl;

    {
        std::map<int, long>    ssample;
        ft::map<int, long>     fsample;

        std::map<int, long>    smap(ssample);
        ft::map<int, long>     fmap(fsample);

        compare_maps(smap, fmap);
    }
}

void    test_map_constructor_5_2(void)
{
    std::cout << YELLOW "5.2) Copy constructor [empty + push + pop]:" DEFAULT << std::endl;

    {
        std::map<int, long>    ssample;
        ft::map<int, long>     fsample;

        std::map<int, long>    smap(ssample);
        ft::map<int, long>     fmap(fsample);

        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
}

void    test_map_constructor_5_3(void)
{
    std::cout << YELLOW "5.3) Copy constructor [non-empty]:" DEFAULT << std::endl;

    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(1, svec, fvec);

        std::map<int, long>    ssample(svec.begin(), svec.end());
        ft::map<int, long>     fsample(fvec.begin(), fvec.end());

        std::map<int, long>    smap(ssample);
        ft::map<int, long>     fmap(fsample);

        compare_maps(smap, fmap);
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(5, svec, fvec);

        std::map<int, long>    ssample(svec.begin(), svec.end());
        ft::map<int, long>     fsample(fvec.begin(), fvec.end());

        std::map<int, long>    smap(ssample);
        ft::map<int, long>     fmap(fsample);

        compare_maps(smap, fmap);
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(15, svec, fvec);

        std::map<int, long>    ssample(svec.begin(), svec.end());
        ft::map<int, long>     fsample(fvec.begin(), fvec.end());

        std::map<int, long>    smap(ssample);
        ft::map<int, long>     fmap(fsample);

        compare_maps(smap, fmap);
    }
}

void    test_map_constructor_5_4(void)
{
    std::cout << YELLOW "5.4) Copy constructor [+ non-empty + push + pop]:" DEFAULT << std::endl;

    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(1, svec, fvec);

        std::map<int, long>    ssample(svec.begin(), svec.end());
        ft::map<int, long>     fsample(fvec.begin(), fvec.end());

        std::map<int, long>    smap(ssample);
        ft::map<int, long>     fmap(fsample);

        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(5, svec, fvec);

        std::map<int, long>    ssample(svec.begin(), svec.end());
        ft::map<int, long>     fsample(fvec.begin(), fvec.end());

        std::map<int, long>    smap(ssample);
        ft::map<int, long>     fmap(fsample);

        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(15, svec, fvec);

        std::map<int, long>    ssample(svec.begin(), svec.end());
        ft::map<int, long>     fsample(fvec.begin(), fvec.end());

        std::map<int, long>    smap(ssample);
        ft::map<int, long>     fmap(fsample);

        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
}

void    test_map_capacity_1(void)
{
    std::cout << YELLOW "1) Empty:" DEFAULT << std::endl;

    {
        std::map<int, long>    smap;
        ft::map<int, long>     fmap;

        if (smap.empty() == fmap.empty())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(1, svec, fvec);

        std::map<int, long>    smap(svec.begin(), svec.end());
        ft::map<int, long>     fmap(fvec.begin(), fvec.end());

        if (smap.empty() == fmap.empty())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(5, svec, fvec);

        std::map<int, long>    smap(svec.begin(), svec.end());
        ft::map<int, long>     fmap(fvec.begin(), fvec.end());

        if (smap.empty() == fmap.empty())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(15, svec, fvec);

        std::map<int, long>    smap(svec.begin(), svec.end());
        ft::map<int, long>     fmap(fvec.begin(), fvec.end());

        if (smap.empty() == fmap.empty())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    std::cout << '\n' << std::endl;
}

void    test_map_capacity_2(void)
{
    std::cout << YELLOW "2) Size:" DEFAULT << std::endl;

    {
        std::map<int, long>    smap;
        ft::map<int, long>     fmap;

        if (smap.size() == fmap.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(1, svec, fvec);

        std::map<int, long>    smap(svec.begin(), svec.end());
        ft::map<int, long>     fmap(fvec.begin(), fvec.end());

        if (smap.size() == fmap.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(5, svec, fvec);

        std::map<int, long>    smap(svec.begin(), svec.end());
        ft::map<int, long>     fmap(fvec.begin(), fvec.end());

        if (smap.size() == fmap.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(15, svec, fvec);

        std::map<int, long>    smap(svec.begin(), svec.end());
        ft::map<int, long>     fmap(fvec.begin(), fvec.end());

        if (smap.size() == fmap.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    std::cout << '\n' << std::endl;
}


void    test_map_get_allocator(void)
{
    std::cout << YELLOW "get_allocator: " DEFAULT << std::endl;

    std::vector<std::pair<int, long> >  svec;
    ft::vector<ft::pair<int, long> >    fvec;
    value_generator(5, svec, fvec);

    std::map<int, long>    smap(svec.begin(), svec.end());
    ft::map<int, long>     fmap(fvec.begin(), fvec.end());

    if (smap.get_allocator() != fmap.get_allocator())
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    std::cout << '\n' << std::endl;
}

void    test_map_assignment_1_1(void)
{
    std::cout << YELLOW "1.1) operator= [to empty]:" DEFAULT << std::endl;

    {
        std::map<int, long>    ssample;
        ft::map<int, long>     fsample;

        std::map<int, long>    smap;
        ft::map<int, long>     fmap;

        smap = ssample;
        fmap = fsample;

        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(1, svec, fvec);

        std::map<int, long>    ssample(svec.begin(), svec.end());
        ft::map<int, long>     fsample(fvec.begin(), fvec.end());

        std::map<int, long>    smap;
        ft::map<int, long>     fmap;

        smap = ssample;
        fmap = fsample;

        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(5, svec, fvec);

        std::map<int, long>    ssample(svec.begin(), svec.end());
        ft::map<int, long>     fsample(fvec.begin(), fvec.end());

        std::map<int, long>    smap;
        ft::map<int, long>     fmap;

        smap = ssample;
        fmap = fsample;

        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(15, svec, fvec);

        std::map<int, long>    ssample(svec.begin(), svec.end());
        ft::map<int, long>     fsample(fvec.begin(), fvec.end());

        std::map<int, long>    smap;
        ft::map<int, long>     fmap;

        smap = ssample;
        fmap = fsample;

        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
}

void    test_map_assignment_1_2(void)
{
    std::cout << YELLOW "1.2) operator= [to non-empty]:" DEFAULT << std::endl;

    {
        std::vector<std::pair<int, long> >  svec1;
        ft::vector<ft::pair<int, long> >    fvec1;
        value_generator(0, svec1, fvec1);
        std::vector<std::pair<int, long> >  svec2;
        ft::vector<ft::pair<int, long> >    fvec2;
        value_generator(15, svec2, fvec2);

        std::map<int, long>    ssample(svec1.begin(), svec1.end());
        ft::map<int, long>     fsample(fvec1.begin(), fvec1.end());

        std::map<int, long>    smap(svec2.begin(), svec2.end());
        ft::map<int, long>     fmap(fvec2.begin(), fvec2.end());

        smap = ssample;
        fmap = fsample;

        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
    {
        std::vector<std::pair<int, long> >  svec1;
        ft::vector<ft::pair<int, long> >    fvec1;
        value_generator(1, svec1, fvec1);
        std::vector<std::pair<int, long> >  svec2;
        ft::vector<ft::pair<int, long> >    fvec2;
        value_generator(15, svec2, fvec2);

        std::map<int, long>    ssample(svec1.begin(), svec1.end());
        ft::map<int, long>     fsample(fvec1.begin(), fvec1.end());

        std::map<int, long>    smap(svec2.begin(), svec2.end());
        ft::map<int, long>     fmap(fvec2.begin(), fvec2.end());

        smap = ssample;
        fmap = fsample;

        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
    {
        std::vector<std::pair<int, long> >  svec1;
        ft::vector<ft::pair<int, long> >    fvec1;
        value_generator(5, svec1, fvec1);
        std::vector<std::pair<int, long> >  svec2;
        ft::vector<ft::pair<int, long> >    fvec2;
        value_generator(15, svec2, fvec2);

        std::map<int, long>    ssample(svec1.begin(), svec1.end());
        ft::map<int, long>     fsample(fvec1.begin(), fvec1.end());

        std::map<int, long>    smap(svec2.begin(), svec2.end());
        ft::map<int, long>     fmap(fvec2.begin(), fvec2.end());

        smap = ssample;
        fmap = fsample;

        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
    {
        std::vector<std::pair<int, long> >  svec1;
        ft::vector<ft::pair<int, long> >    fvec1;
        value_generator(15, svec1, fvec1);
        std::vector<std::pair<int, long> >  svec2;
        ft::vector<ft::pair<int, long> >    fvec2;
        value_generator(5, svec2, fvec2);

        std::map<int, long>    ssample(svec1.begin(), svec1.end());
        ft::map<int, long>     fsample(fvec1.begin(), fvec1.end());

        std::map<int, long>    smap(svec2.begin(), svec2.end());
        ft::map<int, long>     fmap(fvec2.begin(), fvec2.end());

        smap = ssample;
        fmap = fsample;

        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
}

void    test_map_access_1_1(void)
{
    std::cout << YELLOW "1.1) at [non-empty]:" DEFAULT << std::endl;

    std::vector<std::pair<int, long> >  svec;
    ft::vector<ft::pair<int, long> >    fvec;
    value_generator(5, svec, fvec);

    std::map<int, long>    smap(svec.begin(), svec.end());
    ft::map<int, long>     fmap(fvec.begin(), fvec.end());

    for (ft::map<int, long>::size_type i = 0; i < fmap.size(); i++)
        if (smap.at(i) != fmap.at(i))
        {
            std::cout << "const ref:\t" << RED "KO" DEFAULT << std::endl;
            return;
        }
    std::cout << "const ref:\t" << GREEN "OK" DEFAULT << std::endl;

    for (ft::map<int, long>::size_type i = 0; i < fmap.size(); i++)
    {
        smap.at(i) = 7;
        fmap.at(i) = 7;
        if (smap.at(i) != fmap.at(i))
        {
            std::cout << "ref:\t\t" << RED "KO" DEFAULT << std::endl;
            return;
        }
    }
    std::cout << "ref:\t\t" << GREEN "OK" DEFAULT << std::endl;

    stress_test(smap, fmap);
    compare_maps(smap, fmap);
}

void    test_map_access_1_2(void)
{
    std::cout << YELLOW "1.2) at [empty]:" DEFAULT << std::endl;

    std::map<int, long>    smap;
    ft::map<int, long>     fmap;

    try
    {
        fmap.at(0);
        std::cout << "const ref:\t" << RED "KO" DEFAULT << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "exception : " << e.what() << '\n';
        std::cout << "const ref:\t" << GREEN "OK" DEFAULT << std::endl;
    }

    try
    {
        fmap.at(0) = 5;
        std::cout << "const ref:\t" << RED "KO" DEFAULT << std::endl;

    }
    catch(const std::exception& e)
    {
        std::cerr << "exception : " << e.what() << '\n';
        std::cout << "const ref:\t" << GREEN "OK" DEFAULT << std::endl;
    }
    stress_test(smap, fmap);
    compare_maps(smap, fmap);
}

void    test_map_access_2(void)
{
    std::cout << YELLOW "2) operator[] [non-empty]:" DEFAULT << '\n' << std::endl;

    std::vector<std::pair<int, long> >  svec;
    ft::vector<ft::pair<int, long> >    fvec;
    value_generator(5, svec, fvec);

    std::map<int, long>    smap(svec.begin(), svec.end());
    ft::map<int, long>     fmap(fvec.begin(), fvec.end());

    for (ft::map<int, long>::size_type i = 0; i < smap.size(); i++)
        if (smap[i] != fmap[i])
        {

            std::cout << "const ref:\t" << RED "KO" DEFAULT << std::endl;
            return;
        }

    std::cout << "const ref:\t" << GREEN "OK" DEFAULT << std::endl;

    std::cout << fmap.size() << std::endl;
    for (ft::map<int, long>::size_type i = 0; i < smap.size(); i++)
    {
        smap[i] = 7;
        fmap[i] = 7;
        if (smap[i] != fmap[i])
        {

            std::cout << "ref:\t\t" << RED "KO" DEFAULT << '\n' << std::endl;
            return;
        }
    }
    std::cout << "ref:\t\t" << GREEN "OK" DEFAULT << std::endl;

    stress_test(smap, fmap);
    compare_maps(smap, fmap);
}


void    test_map_clear(void)
{
    std::cout << YELLOW "1) clear:" DEFAULT << std::endl;

    {
        std::map<int, long>    smap;
        ft::map<int, long>     fmap;

        smap.clear();
        fmap.clear();

        if (smap.size() == fmap.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        std::cout << std::endl;
        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(1, svec, fvec);

        std::map<int, long>    smap(svec.begin(), svec.end());
        ft::map<int, long>     fmap(fvec.begin(), fvec.end());


        smap.clear();
        fmap.clear();
        std::cout << "hello \n";

        if (smap.size() == fmap.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        std::cout << std::endl;
        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
    {
        std::vector<std::pair<int, long> >  svec;
        ft::vector<ft::pair<int, long> >    fvec;
        value_generator(5, svec, fvec);

        std::map<int, long>    smap(svec.begin(), svec.end());
        ft::map<int, long>     fmap(fvec.begin(), fvec.end());

        print_map(smap);
        print_map(fmap);
        smap.clear();
        fmap.clear();

        if (smap.size() == fmap.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        std::cout << std::endl;
        stress_test(smap, fmap);
        compare_maps(smap, fmap);
    }
    // {
    //     std::vector<std::pair<int, long> >  svec;
    //     ft::vector<ft::pair<int, long> >    fvec;
    //     value_generator(15, svec, fvec);

    //     std::map<int, long>    smap(svec.begin(), svec.end());
    //     ft::map<int, long>     fmap(fvec.begin(), fvec.end());

    //     smap.clear();
    //     fmap.clear();

    //     if (smap.size() == fmap.size())
    //         std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    //     else
    //         std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    //     std::cout << std::endl;
    //     stress_test(smap, fmap);
    //     compare_maps(smap, fmap);
    // }
}
void    test_map_erase_1(void)
{
    std::cout << YELLOW "3.1) erase [by iterator]:" DEFAULT << std::endl;

    std::vector<std::pair<int, long> >  svec;
    ft::vector<ft::pair<int, long> >    fvec;
    value_generator(10, svec, fvec);

    std::map<int, long>    smap(svec.begin(), svec.end());
    ft::map<int, long>     fmap(fvec.begin(), fvec.end());

    compare_maps(smap, fmap);

    smap.erase(smap.begin());
    fmap.erase(fmap.begin());

    compare_maps(smap, fmap);
    smap.erase(++smap.begin());
    fmap.erase(++fmap.begin());

    compare_maps(smap, fmap);

    // smap.erase(++smap.end());
    // fmap.erase(++fmap.end());

    compare_maps(smap, fmap);

    smap.erase(++(++(++smap.begin())));
    fmap.erase(++(++(++fmap.begin())));

    stress_test(smap, fmap);
    compare_maps(smap, fmap);
}

void    test_map_erase_2(void)
{
    std::cout << YELLOW "3.2) erase [by range]:" DEFAULT << std::endl;

    std::vector<std::pair<int, long> >  svec;
    ft::vector<ft::pair<int, long> >    fvec;
    value_generator(10, svec, fvec);

    std::map<int, long>    smap(svec.begin(), svec.end());
    ft::map<int, long>     fmap(fvec.begin(), fvec.end());

    compare_maps(smap, fmap);

    smap.erase(++(++(++smap.begin())), (--(--(--smap.end()))));

    fmap.erase(++(++(++fmap.begin())), (--(--(--fmap.end()))));


    compare_maps(smap, fmap);

    smap.erase(++smap.begin(), smap.end());
    fmap.erase(++fmap.begin(), fmap.end());

    print_map(smap);
    print_map(fmap);

    compare_maps(smap, fmap);

    smap.erase(smap.begin(), smap.end());
    fmap.erase(fmap.begin(), fmap.end());

    stress_test(smap, fmap);
    compare_maps(smap, fmap);
}

void    test_map_erase_3(void)
{
    std::cout << YELLOW "3.3) erase [by key]:" DEFAULT << std::endl;

    std::vector<std::pair<int, long> >  svec;
    ft::vector<ft::pair<int, long> >    fvec;
    value_generator(10, svec, fvec);

    std::map<int, long>    smap(svec.begin(), svec.end());
    ft::map<int, long>     fmap(fvec.begin(), fvec.end());

    compare_maps(smap, fmap);

    smap.erase(6);
    fmap.erase(6);
    compare_maps(smap, fmap);

    smap.erase(0);
    fmap.erase(0);
    compare_maps(smap, fmap);

    smap.erase(4);
    fmap.erase(4);
    compare_maps(smap, fmap);

    smap.erase(8);
    fmap.erase(8);

    stress_test(smap, fmap);
    compare_maps(smap, fmap);
}


int main()
{
    std::cout << B_RED "[   FT_MAP   ]" DEFAULT << '\n' << std::endl;
    // std::cout << B_CYAN "   Constructors   " DEFAULT << std::endl;

    // test_map_constructor_1_1();
    // test_map_constructor_1_2();

    // test_map_constructor_2_1();
    // test_map_constructor_2_2();

    // test_map_constructor_3_1();
    // test_map_constructor_3_2();

    // test_map_constructor_5_1();
    // test_map_constructor_5_2();
    // test_map_constructor_5_3();
    // test_map_constructor_5_4();

    //  std::cout << B_CYAN "   Capacity   " DEFAULT << std::endl;
    // test_map_capacity_1();
    // test_map_capacity_2();

    // std::cout << B_CYAN "   Iterators   " DEFAULT << std::endl;
    // test_map_iterators_1_1();
    // test_map_iterators_1_2();
    // test_map_iterators_2_1();
    // test_map_iterators_2_2();
    // test_map_iterators_3();

    // std::cout << B_CYAN "   Reverse iterators   " DEFAULT << std::endl;
    // test_map_rev_iterators_1_1();
    // test_map_rev_iterators_1_2();
    // test_map_rev_iterators_2_1();
    // test_map_rev_iterators_2_2();
    // test_map_rev_iterators_3();

    //     std::cout << B_CYAN "   Assignments   " DEFAULT << std::endl;
    // test_map_assignment_1_1();
    // test_map_assignment_1_2();

    // std::cout << B_CYAN "   Get allocator   " DEFAULT << std::endl;
    // test_map_get_allocator();

    // std::cout << B_CYAN "   Element access   " DEFAULT << std::endl;
    // test_map_access_1_1();
    // test_map_access_1_2();
    // test_map_access_2();


        std::cout << B_CYAN "   Modifiers   " DEFAULT << std::endl;
    test_map_clear();
    // test_map_erase_1();
    // test_map_erase_2();
    // test_map_erase_3();
    // test_map_insert_1();
    // test_map_insert_2();
    // test_map_insert_3();
    return (0);
}