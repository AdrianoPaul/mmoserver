/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_ZONESERVER_ITEM_FACTORY_H
#define ANH_ZONESERVER_ITEM_FACTORY_H

#include "FactoryBase.h"
#include "ObjectFactoryCallback.h"

#define		gItemFactory	ItemFactory::getSingletonPtr()

//=============================================================================

class Item;
class Database;
class DataBinding;
class DispatchClient;
class ObjectFactoryCallback;

//=============================================================================

enum ItemFactoryQuery
{
	ItemFactoryQuery_MainData				= 1,
	ItemFactoryQuery_Attributes				= 2,
	NonPersistantItemFactoryQuery_MainData	= 3,
	ItemFactoryQuery_Items					= 4
};

//=============================================================================

class ItemFactory : public FactoryBase, public ObjectFactoryCallback
{
	public:

		static	ItemFactory*	getSingletonPtr() { return mSingleton; }
		static	ItemFactory*	Init(Database* database);

		virtual ~ItemFactory();

		virtual void			handleObjectReady(Object* object,DispatchClient* client);

		void					handleDatabaseJobComplete(void* ref,DatabaseResult* result);
		void					requestObject(ObjectFactoryCallback* ofCallback,uint64 id,uint16 subGroup,uint16 subType,DispatchClient* client);
		void					requestContainerContent(ObjectFactoryCallback* ofCallback,uint64 id,uint16 subGroup,uint16 subType,DispatchClient* client, uint32 depth = 0);

	private:

		ItemFactory(Database* database);

		void					_postProcessAttributes(Object* object);

		void					_setupDatabindings();
		void					_destroyDatabindings();

		Item*					_createItem(DatabaseResult* result);

		static ItemFactory*		mSingleton;
		static bool				mInsFlag;

		DataBinding*			mItemIdentifierBinding;
		DataBinding*			mItemBinding;
};

//=============================================================================

class ItemIdentifier
{
	public:

		ItemIdentifier(){}
		~ItemIdentifier(){}

		uint32	mFamilyId;
		uint32	mTypeId;
};

//=============================================================================

#endif

