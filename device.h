//
//  device.h
//
//  Created by Lyle Moffitt on 11/3/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#ifndef __CNC__device__
#define __CNC__device__

#include "formatting.h"

#include <fstream>
#include <string>
#include <mutex>

#include <sstream>
#include <cassert>
#include <mutex>
#include <utility>

template <typename _t>
class device;

/// A single file within a device
struct dev
{
    /// The name (full path) of the device
    const std::string       name;

    /// The actual device
    std::fstream            f_dev;
    
    std::mutex              hold;
    std::string             state;
    
    /// Constructor
    dev(std::string     _full_path);
    /// Constructor
    dev(std::string     _path, std::string      _name);
    /// Copy constructor
    dev(const dev & _d);
    /// Copy constructor
//    dev(dev && _d);
    /// Default constructor
    dev();
    
    /// Write to the device
    void                    set(std::string  _s);
    /// Read from the device
    std::string             get();
};

template <typename _t>
struct device : dev 
{
    /// Constructor
    device(std::string     _full_path):
    dev(_full_path)
    {}
    /// Constructor
    device(std::string     _path, std::string      _name):
    dev(_path,_name)
    {}
    /// Copy constructor
    device(const dev & _d):
    dev(_d)
    {}
    /// Copy constructor
    //    dev(dev && _d);
    /// Default constructor
    device():dev()
    {}
    
    /// Read any \e default-constructable type
    _t  operator() (void)
    {
        std::lock_guard<std::mutex> lock(hold);
        assert( !name.empty() ); 
        assert( !f_dev.is_open() );
        f_dev.open(name, std::fstream::in );
        assert(f_dev.good() && "Error opening file.");
        _t ret;
        state.clear();
        f_dev >> ret;
        state=std::to_string(ret);
        f_dev.close();
        return  ret;
    }
    
    void  operator() (_t _val)
    {
        std::lock_guard<std::mutex> lock(hold);
        assert( !name.empty() ); 
        assert( !f_dev.is_open() );
        f_dev.open(name, std::fstream::out);
        assert(f_dev.good() && "Error opening file.");
        std::stringstream tmp_ss;
        tmp_ss << _val;
        state = tmp_ss.str();
        f_dev << tmp_ss.str();
        f_dev.close();
    }
    
    /** Read last state
     \note Type _t must be default construtable.
     \note Type _t must implement \c operator>>()
     */
    operator _t()
    {
        if(state.empty()){  this->get();  }
        _t ret;
        std::stringstream tmp_ss(state);
        tmp_ss >> ret;
        return ret;
    }
    
};




#endif /* defined(__CNC__device__) */
