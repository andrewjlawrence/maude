/*

    This file is part of the Maude 2 interpreter.

    Copyright 1997-2003 SRI International, Menlo Park, CA 94025, USA.
	Copyright 2017 Andrew Lawrence.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.

*/

//
//      Class for timers.
//
#ifndef _timer_hh_
#define _timer_hh_
#include "timeStuff.hh"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <boost/timer/timer.hpp>
#endif

class Timer
{
public:
  Timer(bool startRunning = false);
  
  bool getTimes(Int64& real, Int64& virt, Int64& prof) const;
  bool isRunning() const;
  void start();
  void stop();

private:
  enum Constants
  {
    CYCLE_LENGTH = 10000000  // length of timer cycle in seconds
  };

  static void startOsTimers();
  static Int64 calculateMicroseconds(const itimerval& startTime,
				     const itimerval& stopTime);
  
  static bool osTimersStarted;

  Int64 realAcc;
  Int64 virtAcc;
  Int64 profAcc;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  boost::timer::cpu_timer timer;
#else
  itimerval realStartTime;
  itimerval virtStartTime;
  itimerval profStartTime;
#endif

  bool running;
  bool valid;
};

inline bool
Timer::isRunning() const
{
  return running;
}

#endif
