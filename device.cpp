//
//  device.cpp
//
//  Created by Lyle Moffitt on 11/3/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "device.h"
#include "macros.h"

#include <unistd.h>
#include <fcntl.h>

#include <iostream>
#include <string>
#include <fstream>

#include <cassert>
#include <sys/stat.h>
#include <errno.h>

#include <thread>



using namespace std;
/* ***********************          dev             ************************* */

dev::dev():
name( "")   
{
}

dev::dev(std::string     _full_path):
name( _full_path )   
{
    assert(!_full_path.empty() && "Device constructed with empty path string!");
}

dev::dev(std::string     _path, std::string      _name):
name( (_path+_name) )   
{
    assert(!name.empty() && "Device constructed with empty path string!");
    LOG3 LOUT "\tDevice ("<<name<<") constructed.\n";
}

dev::dev(const dev & _d):
name(_d.name)
{
    assert(!name.empty() && "Device constructed with empty path string!");
}


void 
dev::set(std::string  _s)
{   
    lock_guard<mutex> lock(hold);
    LOG8 cerr<<"\nSET : ";
    LOG8 cerr<<"\t"<<_s<<" =>"<<name<<endl;
    assert( !_s.empty() && "Attempting to set with an empty string.");
    assert( !name.empty() ); 
    f_dev.open(name, fstream::out);
    //    assert(f_dev.good() && "Error opening file.");
    f_dev << _s;
    state=_s;
    f_dev.close();
}

std::string 
dev::get()
{ 
    lock_guard<mutex> lock(hold);
    LOG8 cerr<<"\nGET : ";
    LOG8 ECHO(name);
    assert( !name.empty() ); 
    assert( !f_dev.is_open() );
    f_dev.open(name, fstream::in );
    assert(f_dev.good() && "Error opening file.");
    f_dev >> state;
    f_dev.close();
    assert( !state.empty() && "Nothing read from file."); 
    return  state.c_str();
}


