	   /*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_ZONESERVER_HARVESTER_OBJECT_FACTORY_H
#define ANH_ZONESERVER_HARVESTER_OBJECT_FACTORY_H

#include "ObjectFactoryCallback.h"
#include "FactoryBase.h"

#define gHarvesterFactory HarvesterFactory::getSingletonPtr()


//=============================================================================

class Database;
class DataBinding;
class DispatchClient;
class HarvesterObject;

//=============================================================================

enum HFQuery
{
	HFQuery_MainData		= 1,
	HFQuery_ResourceData	= 2,
	HFQuery_byDeed			= 3,
	HFQuery_AdminData		= 4,
	HFQuery_AttributeData	= 5

};

//=============================================================================

class HarvesterFactory : public FactoryBase, public ObjectFactoryCallback
{
	public:

		static HarvesterFactory*	getSingletonPtr() { return mSingleton; }
		static HarvesterFactory*	Init(Database* database);

		~HarvesterFactory();

		virtual void	handleObjectReady(Object* object,DispatchClient* client);
		void			handleDatabaseJobComplete(void* ref,DatabaseResult* result);
		void			requestObject(ObjectFactoryCallback* ofCallback,uint64 id,uint16 subGroup,uint16 subType,DispatchClient* client);

		void			releaseAllPoolsMemory();

	private:

		HarvesterFactory(Database* database);

		void			_setupDatabindings();
		void			_destroyDatabindings();

		void			_createHarvester(DatabaseResult* result, HarvesterObject* harvester);

		static HarvesterFactory*	mSingleton;
		static bool					mInsFlag;


		DataBinding*				mHarvesterBinding;

};

//=============================================================================


#endif


