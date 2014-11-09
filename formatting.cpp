//
//  formatting.cpp
//
//  Created by Lyle Moffitt on 7/22/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "formatting.h"


#include <string>

std::string str_low(const std::string& _s)
{
    std::string _d;
    for (auto& i : _s ) { _d += std::tolower(i) ;}
    return _d;
}


std::string str_uppr(const std::string& _s)
{
    std::string _d;
    for (auto& i : _s ) { _d += std::toupper(i) ;}
    return _d;
}


std::string& mk_upper(std::string& _s)
{
    for (auto& i : _s ) { i = std::toupper(i) ;}
    return _s;
}

std::string& mk_lower(std::string& _s)
{
    for (auto& i : _s ) { i = std::tolower(i) ;}
    return _s;
}


#include <string>
#include <deque>
using namespace std;

std::deque<std::string>
str_tokenize(std::string & _src, std::string _tok)
{
    deque<string> ds;
    for(size_t _b(0),_e(0);;){
        _b = _src.find_first_not_of(_tok,_e);
        _e = _src.find_first_of(_tok,_b);
        if(_b==string::npos){break;}
        ds.push_back(_src.substr(_b,_e-_b));
    }
    return ds;
}














