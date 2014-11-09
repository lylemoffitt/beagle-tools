//
//  pwm.h
//
//  Created by Lyle Moffitt on 11/3/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#ifndef __CNC__pwm__
#define __CNC__pwm__

#include "macros.h"
#include "device.h"
#include "formatting.h"

#include <string>
#include <mutex>
#include <unordered_map>


#if defined(TESTING) && !defined(BEAGLEBONE) 
#define BASE_PATH "test_gpio/gpio"
#else
#define BASE_PATH "/sys/class/gpio/gpio"
#endif//TESTING

namespace pwm_config 
{
    const std::string base_path = "/sys/devices/ocp.3/";
    
    const std::string PWM_0A ("pwm_test_P9_31.11/");
    const std::string PWM_1A ("pwm_test_P8_36.12/");
    const std::string PWM_2A ("pwm_test_P8_45.13/");
    


    
    constexpr double std_duty = 0.5;
};



/// A collection of devices used to emulate a single GPIO pin
class pwm : private std::unordered_map<std::string,dev&>  
{
    /// The full path to the directory that contains the devices.
    const std::string                               path;
    /// The associated devices.
public:
    
    /** The total period of the PWM signal (read/write).
     Value is in nanoseconds and is the sum of the active and inactive
     time of the PWM.
     */
    device<size_t>                              period;
    /** Changes the polarity of the PWM signal (read/write).
     Writes to this property only work if the PWM chip supports changing
     the polarity. The polarity can only be changed if the PWM is not
     enabled. Value is the string "normal" or "inversed".
     */
    device<bool>                                polarity;
    /** The active time of the PWM signal (read/write).
     Value is in nanoseconds and must be less than the period.
     */
    device<size_t>                              duty;
    /** Enable/disable the PWM signal (read/write).
     0 - disabled
     1 - enabled
     */
    device<bool>                                run;

    using std::unordered_map<std::string,dev&>::operator[];
    using std::unordered_map<std::string,dev&>::begin;
    using std::unordered_map<std::string,dev&>::end;
    using std::unordered_map<std::string,dev&>::at;


    /// Constructor
    pwm(std::string _name = pwm_config::PWM_0A, 
        std::string _base = pwm_config::base_path);
    
    /// Copy constructor
    pwm(const pwm & _p);
    

    
    /** Flip pin state for specified duration.
     \param     delay       The delay in seconds (expressed as float).
     */
    void toggle(double  delay = 0);
    

    void operator= (std::pair<size_t,size_t> _ratio);
    void operator= (double _duty);
    
private:

    
};




#endif /* defined(__CNC__pwm__) */
