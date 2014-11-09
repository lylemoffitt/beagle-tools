//
//  GPIO.h
//
//  Created by Lyle Moffitt on 6/1/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#ifndef __CNC__GPIO__
#define __CNC__GPIO__



#include "macros.h"
#include "device.h"

#include <string>
#include <iostream>
#include <fstream>
#include <mutex>
#include <atomic>

//The usual system headers for read() and write()

#if defined(TESTING) && !defined(BEAGLEBONE) 
#define BASE_PATH "test_gpio/gpio"
#else
#define BASE_PATH "/sys/class/gpio/gpio"
#endif//TESTING



/// A collection of devices used to emulate a single GPIO pin
struct gpio
{
    /// The full path to the directory that contains the devices.
    const std::string       path;
    /// The associated devices.
    dev                     val, dir, low;
    /// The last value written to or read from the device.
    std::atomic_bool        state;
    
    std::mutex              mtex;

    /// Constructor
    gpio(u_int _number);
    /// Copy constructor
    gpio(gpio & _g);
    
    /// Destructor
    ~gpio();
    
    /** Flip pin state for specified duration.
     * @param _sec The duration of the toggle in seconds.
     */
    void toggle(double   _sec);
    /// Assignment
    bool operator=(bool _val);
    /// Read the pin and set the state.
    bool eval();
};



#endif /* defined(__CNC__GPIO__) */
