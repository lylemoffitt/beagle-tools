//
//  pwm.cpp
//
//  Created by Lyle Moffitt on 11/3/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "pwm.h"
#include <chrono>
#include <thread>

//using attr = pwm_config::attribute;

using namespace pwm_config;
using namespace std;

pwm::pwm(std::string _name, std::string _base):
path(       _base+_name         ),
period(     path+"/","period"   ),
polarity(   path+"/","polarity" ),
duty(       path+"/","duty"     ),
run(        path+"/","run"      ),
std::unordered_map<std::string,dev&>  
({
    {   "period"  ,period       },
    {   "polarity",polarity     },
    {   "duty"    ,duty         },
    {   "run"     ,run          },
})
{ 
}


pwm::pwm(const pwm & _p):
path(       _p.path     ),
period(     _p.period   ),
polarity(   _p.polarity ),
duty(       _p.duty     ),
run(        _p.run      ),
std::unordered_map<std::string,dev&>(_p)
{
}



using sec_float=chrono::duration<double,chrono::seconds::period>;
static_assert(chrono::treat_as_floating_point<sec_float::rep>::value,
              "Custom duration not evaluated properly.");

void    
pwm::toggle(double  delay)
{
    run( !(run) );
#ifndef EMULATION_ONLY
    this_thread::sleep_for(sec_float(delay));
#endif
    run( !(run) );
}




void 
pwm::operator= (std::pair<size_t,size_t> _ratio)
{
    duty(_ratio.first);
    period(_ratio.second);
}

void 
pwm::operator= (double _duty)
{
    assert(_duty>=0&&_duty<=1 && "Duty ratio must be between 0-1");
    duty(_duty * period);
}






