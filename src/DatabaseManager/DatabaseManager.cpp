/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#include "DatabaseManager.h"
#include "Database.h"


//======================================================================================================================
DatabaseManager::DatabaseManager(void)
{

}


//======================================================================================================================
DatabaseManager::~DatabaseManager(void)
{
	DatabaseList::iterator iter = mDatabaseList.begin();

	while(iter != mDatabaseList.end())
	{
		delete(*iter);
		iter = mDatabaseList.erase(iter);
	}
}

//======================================================================================================================
void DatabaseManager::Process(void)
{
  DatabaseList::iterator iter;
  for (iter = mDatabaseList.begin(); iter != mDatabaseList.end(); iter++)
  {
    (*iter)->Process();
  }
}


//======================================================================================================================
Database* DatabaseManager::Connect(DBType type, int8* host, uint16 port, int8* user, int8* pass, int8* schema)
{
  Database* newDatabase = 0;

  // Create our new Database object and initiailzie it.
  newDatabase = new Database(type, host, port, user, pass, schema);

  // Add the new DB to our process list.
  mDatabaseList.push_back(newDatabase);

  return newDatabase;
}



