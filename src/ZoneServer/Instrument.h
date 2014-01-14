/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_ZONESERVER_TANGIBLE_INSTRUMENT_H
#define ANH_ZONESERVER_TANGIBLE_INSTRUMENT_H

#include "Item.h"

//=============================================================================

class Instrument : public Item
{
	friend class ItemFactory;

	public:

		Instrument();
		virtual ~Instrument();
		

		virtual void	prepareCustomRadialMenu(CreatureObject* creatureObject, uint8 itemCount);
		virtual void	handleObjectMenuSelect(uint8 messageType,Object* srcObject);
		void			sendAttributes(PlayerObject* playerObject);

	private:
};

//=============================================================================

#endif

