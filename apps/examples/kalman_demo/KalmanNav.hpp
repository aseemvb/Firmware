/****************************************************************************
 *
 *   Copyright (C) 2012 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file KalmanNav.hpp
 *
 * kalman filter navigation code
 */

#pragma once

#include <nuttx/config.h>

#include <systemlib/math/Vector.hpp>
#include <systemlib/math/Matrix.hpp>
#include <systemlib/math/Kalman.hpp>
#include <systemlib/control/blocks.hpp>
#include <systemlib/control/block/UOrbSubscription.hpp>
#include <systemlib/control/block/UOrbPublication.hpp>

#include <uORB/topics/vehicle_attitude.h>
#include <uORB/topics/vehicle_global_position.h>
#include <uORB/topics/sensor_combined.h>
#include <uORB/topics/vehicle_gps_position.h>

#include <drivers/drv_hrt.h>
#include <poll.h>
#include <unistd.h>

class KalmanNav : public control::SuperBlock
{
public:
    KalmanNav(SuperBlock * parent, const char * name);
    virtual ~KalmanNav() {};
    void update();
    virtual void updatePublications();
    void predict();
    void correctMag();
    void correctGps();
protected:
    math::Kalman _kalman;
    math::Matrix G;
    math::Matrix V;
    math::Matrix HMag;
    math::Matrix RMag;
    math::Matrix HGps;
    math::Matrix RGps;
    math::Matrix Dcm;
    control::UOrbSubscription<sensor_combined_s> _sensors;
    control::UOrbSubscription<vehicle_gps_position_s> _gps;
    control::UOrbPublication<vehicle_global_position_s> _pos;
    control::UOrbPublication<vehicle_attitude_s> _att;
    uint64_t _gpsTimeStamp;
    uint64_t _magTimeStamp;
    uint64_t _outTimeStamp;
    uint64_t _pubTimeStamp;
    uint16_t _navFrames;
};
