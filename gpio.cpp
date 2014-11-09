//
//  GPIO.cpp
//
//  Created by Lyle Moffitt on 6/1/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "GPIO.h"

#include "formatting.h"
#include "macros.h"

#include <unistd.h>
#include <fcntl.h>

#include <iostream>
#include <string>
#include <fstream>

 #include <cassert>
#include <sys/stat.h>
#include <errno.h>
#include <chrono>


#include <thread>

using namespace std;

/* ***********************          gpio             ************************ */

gpio::gpio(u_int _number):
    path( stringf("%s%u/",BASE_PATH,_number) ),
    val(path , "value"),
    dir(path , "direction"),
    low(path , "active_low"),
    state(false)
{
    if (!mtex.try_lock()) {return;}
    dir.set( "out"  ); //Set direction outwards
    val.set( "0"    ); //Set output value to logical zero
    low.set( "1"    ); //Set gpio to active-LOW
    LOG3 LOUT "GPIO("<<to_string(_number)<<") constructed.\n";
    mtex.unlock();
}

gpio::gpio(gpio & _g):
    path(_g.path), val(_g.val), dir(_g.dir), low(_g.low)
{
}


gpio::~gpio()
{
    if (!mtex.try_lock()) {this_thread::yield(); return;}
    dir.set( "out" );
    val.set( "0"   );
    low.set( "0"   );
    mtex.unlock();
}

using sec_float=chrono::duration<double,chrono::seconds::period>;
static_assert(chrono::treat_as_floating_point<sec_float::rep>::value,
              "Custom duration not evaluated properly.");

void    
gpio::toggle(double  delay)
{
    mtex.lock();
    val.set( (state=!state)? "1":"0" ); //Flip and print
#ifndef EMULATION_ONLY
    this_thread::sleep_for(sec_float(delay));
#endif
    val.set( (state=!state)? "1":"0" );   
    mtex.unlock();
}

bool 
gpio::operator=(bool _val)
{
    mtex.lock();
    state=_val;
    val.set( _val? "1":"0" );
    mtex.unlock();
    return state;
}

bool 
gpio::eval()
{
    if (!mtex.try_lock()) {this_thread::yield(); return state;}
    switch( val.get()[0] )
    {
        case '1': state = true; break;
        case '0': state = false; break;
        default:
            assert( (val.get()[0]=='1' || val.get()[0]=='0') && 
                   "GPIO value read incorrectly.");
    }
    mtex.unlock();
    return state;
}




