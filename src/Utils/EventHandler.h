/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_UTILS_EVENTHANDLER_H
#define ANH_UTILS_EVENTHANDLER_H

#include <boost/ptr_container/ptr_map.hpp>
#include <typeinfo>


//======================================================================================================================

namespace Anh_Utils
{

class TypeInfo;

//======================================================================================================================
//
// Event
//

class Event
{
	public:

		virtual ~Event(){};
};

//======================================================================================================================
//
// HandlerFunctionBase
//

class HandlerFunctionBase
{
	public:

		virtual ~HandlerFunctionBase(){};
		void execute(const Event* event){ call(event); }

	private:

		virtual void call(const Event*) = 0;
};

//======================================================================================================================
//
// MemberFunctionHandler
//

template <class T,class EventT>
class MemberFunctionHandler : public HandlerFunctionBase
{
	public:

		typedef void (T::*MemberFunc)(const EventT*);
		MemberFunctionHandler(T* instance,MemberFunc memFn) : mInstance(instance),mFunction(memFn){}

		void call(const Event* event)
		{
			(mInstance->*mFunction)(static_cast<const EventT*>(event));
		}

	private:

		T*			mInstance;
		MemberFunc	mFunction;
};

//======================================================================================================================
//
// EventHandler
//

class EventHandler
{
public:
	virtual ~EventHandler();

	void handleEvent(const Event*);

	template <class T,class EventT>
	void registerEventFunction(T*,void(T::*memFn)(const EventT*));

private:
	typedef boost::ptr_map<const TypeInfo, HandlerFunctionBase> Handlers;
	Handlers mHandlers;
};

//======================================================================================================================
//
// registerEventFunction
//

template <class T,class EventT>
void EventHandler::registerEventFunction(T* obj,void (T::*memFn)(const EventT*))
{
	mHandlers.insert(TypeInfo(typeid(EventT)), new MemberFunctionHandler<T,EventT>(obj,memFn));
}

//======================================================================================================================
//
// TypeInfo
//

class TypeInfo
{
	public:

        explicit TypeInfo(const std::type_info& info) : mTypeInfo(info) {};

		bool operator < (const TypeInfo& rhs) const
		{
			return mTypeInfo.before(rhs.mTypeInfo) != 0;
		}

	private:

        const std::type_info& mTypeInfo;
};

//======================================================================================================================

}

#endif
