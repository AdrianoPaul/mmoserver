/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_ZONESERVER_INVENTORY_FACTORY_H
#define ANH_ZONESERVER_INVENTORY_FACTORY_H

#include "FactoryBase.h"
#include "ObjectFactoryCallback.h"

#define	gInventoryFactory	InventoryFactory::getSingletonPtr()

//=============================================================================

class Database;
class DataBinding;
class DispatchClient;
class Inventory;
class TangibleFactory;

//=============================================================================

enum IFQuery
{
	IFQuery_MainInventoryData	= 1,
	IFQuery_ObjectCount			= 2,
	IFQuery_Objects				= 3
};

//=============================================================================

class InventoryFactory : public FactoryBase, public ObjectFactoryCallback
{
	public:

		static InventoryFactory*	getSingletonPtr() { return mSingleton; }
		static InventoryFactory*	Init(Database* database);

		~InventoryFactory();

		virtual void	handleObjectReady(Object* object,DispatchClient* client);
		void			handleDatabaseJobComplete(void* ref,DatabaseResult* result);
		void			requestObject(ObjectFactoryCallback* ofCallback,uint64 id,uint16 subGroup,uint16 subType,DispatchClient* client);

	private:

		InventoryFactory(Database* database);

		void		_setupDatabindings();
		void		_destroyDatabindings();

		Inventory*	_createInventory(DatabaseResult* result);

		static InventoryFactory*	mSingleton;
		static bool				mInsFlag;

		TangibleFactory*			mTangibleFactory;

		DataBinding*				mInventoryBinding;
};

//=============================================================================


#endif



