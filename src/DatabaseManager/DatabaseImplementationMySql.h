/*
---------------------------------------------------------------------------------------
This source file is part of SWG:ANH (Star Wars Galaxies - A New Hope - Server Emulator)

For more information, visit http://www.swganh.com

Copyright (c) 2006 - 2010 The SWG:ANH Team
---------------------------------------------------------------------------------------
Use of this source code is governed by the GPL v3 license that can be found
in the COPYING file or at http://www.gnu.org/licenses/gpl-3.0.html

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
---------------------------------------------------------------------------------------
*/

#ifndef ANH_DATABASEMANAGER_DATABASEIMPLEMENTATIONMYSQL_H
#define ANH_DATABASEMANAGER_DATABASEIMPLEMENTATIONMYSQL_H

#include "DatabaseImplementation.h"
#include "Utils/typedefs.h"
#include "DatabaseManager/declspec.h"

//======================================================================================================================
class DatabaseResult;

typedef struct st_mysql MYSQL;
typedef struct st_mysql_res MYSQL_RES;
typedef struct st_mysql_rows MYSQL_ROWS;


//======================================================================================================================

class DatabaseImplementationMySql : public DatabaseImplementation
{
public:
  DBMANAGER_API                                    DatabaseImplementationMySql(char* host, uint16 port, char* user, char* pass, char* schema);
  DBMANAGER_API virtual							~DatabaseImplementationMySql(void);
  
  DBMANAGER_API virtual DatabaseResult*			ExecuteSql(int8* sql,bool procedure = false);
  DBMANAGER_API virtual DatabaseWorkerThread*		DestroyResult(DatabaseResult* result);

  DBMANAGER_API virtual void						GetNextRow(DatabaseResult* result, DataBinding* binding, void* object);
  DBMANAGER_API virtual void						ResetRowIndex(DatabaseResult* result, uint64 index = 0);
  DBMANAGER_API virtual uint64					GetInsertId(void);

  DBMANAGER_API virtual uint32					Escape_String(int8* target,const int8* source,uint32 length);

private:
  MYSQL*                      mConnection;
  MYSQL_RES*                  mResultSet;
};




#endif // ANH_DATABASEMANAGER_DATABASEIMPLEMENTATIONMYSQL_H





