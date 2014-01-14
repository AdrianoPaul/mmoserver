/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_ZONESERVER_TANGIBLE_OBJECT_H
#define ANH_ZONESERVER_TANGIBLE_OBJECT_H

#include "ObjectContainer.h"
#include "TangibleEnums.h"

//=============================================================================

class TangibleObject :	public ObjectContainer
{
	friend class ObjectFactory;
	friend class PlayerObjectFactory;
	friend class InventoryFactory;
	friend class NonPersistentItemFactory;

	public:

		TangibleObject();
		TangibleObject(uint64 id,uint64 parentId,const string model,TangibleGroup tanGroup = TanGroup_None,TangibleType tanType = TanType_None,const string name = "",const string nameFile = "",const string detailFile = "");
		virtual ~TangibleObject();

		virtual void		prepareCustomRadialMenuInCell(CreatureObject* creatureObject, uint8 itemCount);

		virtual void		upDateFactoryVolume(string amount){;}
		string				getName() const { return mName; }
		void				setName(const int8* name){ mName = name; }
		string				getNameFile() const { return mNameFile; }
		void				setNameFile(const int8* file){ mNameFile = file; }
		string				getDetailFile(){ return mDetailFile; }
		void				setDetailFile(const int8* file){ mDetailFile = file; }
		string				getColorStr(){ return mColorStr; }
		void				setColorStr(const int8* coloStr){ mColorStr = coloStr; }

		//============================================================
		//sets ParentId - for item table objects in the db and Object
		virtual void		setParentIdIncDB(uint64 parentId);

		string				getCustomizationStr() const { return mCustomizationStr; }
		void				setCustomizationStr(const uint8* custStr){ mCustomizationStr = (int8*)custStr; }
		void				setCustomization(uint8 index, uint16 val, uint8 length = 73){ mCustomization[index] = val;buildTanoCustomization(length); }
		uint16*				getCustomization(){ return &mCustomization[0]; }
		uint16				getCustomization(uint8 index){ return mCustomization[index]; }
		void				buildTanoCustomization(uint8 len);

		string				getUnknownStr1() const { return mUnknownStr1; }
		void				setUnknownStr1(const int8* unknownStr){ mUnknownStr1 = unknownStr; }
		string				getUnknownStr2() const { return mUnknownStr2; }
		void				setUnknownStr2(const int8* unknownStr){ mUnknownStr2 = unknownStr; }
		
		string				getCustomName() const { return mCustomName; }
		void				setCustomName(const int8* name){ mCustomName = name; }
		void				setCustomNameIncDB(const int8* name);

		TangibleGroup		getTangibleGroup() const{ return mTanGroup; }
		void				setTangibleGroup(TangibleGroup group){ mTanGroup = group; }
		TangibleType		getTangibleType() const { return mTanType; }
		void				setTangibleType(TangibleType type){ mTanType = type; }

		uint32				getMaxCondition() const { return mMaxCondition; }
		void				setMaxCondition(uint32 maxCondition){ mMaxCondition = maxCondition; }
		uint32				getDamage() const { return mDamage; }
		void				setDamage(uint32 damage){ mDamage = damage; }

		virtual uint32		getCategoryBazaar(){ return 0; }
		string				getBazaarTang(){ return getModelString(); }

		float				getComplexity(){ return mComplexity; }
		void				setComplexity(float complexity){ mComplexity = complexity; }

		void				initTimer(int32 count,int32 interval,uint64 startTime);
		bool				updateTimer(uint64 callTime);
		int32				getTimer() const { return mTimer; }
		void				setTimer(int32 timer){ mTimer = timer; }

		bool				getStatic()const { return mStatic; }
		void				setStatic(bool isStatic){ mStatic = isStatic; }
	protected:

		string				mCustomizationStr;
		string				mCustomName;
		string				mName;
		string				mNameFile;
		string				mColorStr;
		string				mDetailFile;
		string				mUnknownStr1;
		string				mUnknownStr2;
		uint16				mCustomization[256];
		TangibleGroup		mTanGroup;
		TangibleType		mTanType;
		float				mComplexity;
		uint64				mLastTimerUpdate;
		int32				mTimer;
		uint32				mCustomizationSize;
		uint32				mDamage;
		uint32				mMaxCondition;
		uint32				mTimerInterval;
		bool				mStatic;
};

//=============================================================================

#endif

