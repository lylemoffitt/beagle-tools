//
//  formatting.h
//
//  Created by Lyle Moffitt on 6/1/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#ifndef CNC_formatting_h
#define CNC_formatting_h

#include <string>
#include <cstring>

template<class ... var_t> 
inline 
std::string
stringf( const char * format, var_t ... f_args )
{
    using namespace std;
    size_t _sz = (sizeof...(f_args)) * sizeof(size_t) * string(format).size();
    char buf [_sz];
    memset(&buf, 0, _sz);
    sprintf(buf, format, f_args... );
    return std::string( buf );
}


#include <vector>
template<typename _type>
struct init_ls : public std::vector<_type>
{
    init_ls( std::initializer_list<_type> _ls):     
    std::vector<_type>(_ls)
    {
    }
};


#include "macros.h"
struct coordinate
{
    pos_type    X, Y, Z;
};


struct burn_pt : coordinate
{
    const bool init;
    burn_pt():init(false){}
    burn_pt(coordinate c, pix_type p):val(p),coordinate(c),init(true){}
    /// Position reltive to start.
    pix_type         val;
};

#include <list>
#include <atomic>
struct burn_list : std::list<burn_pt>
{
    std::atomic_size_t _size ;
};




std::string         str_low(const std::string& _s);

 
std::string         str_uppr(const std::string& _s);


std::string&        mk_lower(std::string& _s);


std::string&        mk_upper(std::string& _s);

#include <deque>
std::deque<std::string>
str_tokenize(std::string & _src, std::string _tok);

inline  
std::string         
operator ""_str(long double val){           return std::to_string(val);
}

inline
std::string         
operator ""_str(unsigned long long val){    return std::to_string(val);
}

inline
std::string         
operator ""_str(const char * val){          return std::string(val);
}

#include <cstdlib>
inline 
double              
operator ""_lf(const char * val){           return std::atof(val);
}

inline 
int                 
operator ""_int(const char * val){          return std::atoi(val);
}

inline 
size_t                 
operator ""_len(const char * val){          return std::strlen(val);
}

#include <chrono>
using sec_float=std::chrono::duration<double,std::chrono::seconds::period>;
static_assert(std::chrono::treat_as_floating_point<sec_float::rep>::value,
              "Custom duration not evaluated properly.");

inline
sec_float
operator ""_sec(long double val){          return sec_float(val);
}








#endif //CNC_formatting_h
