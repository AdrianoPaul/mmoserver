/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#include "Timer.h"
#include "TimerCallback.h"

//==============================================================================================================================

Timer::Timer(uint32 id,TimerCallback* callback,uint64 interval, void* container)
: mContainer(container)
, mCallback(callback)
, mId(id)
, mInterval(interval)
{
	if(mInterval < 100)
		mInterval = 100;

	mLastTick = Anh_Utils::Clock::getSingleton()->getLocalTime();

    boost::thread t(&Timer::Run, this);
    mThread = boost::move(t);
}

//==============================================================================================================================

Timer::~Timer()
{
    mThread.interrupt();
    mThread.join();
}

//==============================================================================================================================

void Timer::Run()
{
	uint64 currentTick;

	while(true)
	{
		currentTick = Anh_Utils::Clock::getSingleton()->getLocalTime();

		if(currentTick - mLastTick >= mInterval)
		{
			mCallback->handleTimer(mId,mContainer);
			mLastTick = currentTick;
		}

        boost::this_thread::sleep(boost::posix_time::milliseconds(10));
	}
}

//==============================================================================================================================



