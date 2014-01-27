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

#include "CityFactory.h"

#include <cppconn/resultset.h>

#include "Utils/utils.h"

#include "DatabaseManager/Database.h"
#include "DatabaseManager/DatabaseResult.h"

#include "City.h"
#include "ZoneServer/Objects/ObjectFactoryCallback.h"


CityFactory::CityFactory(swganh::app::SwganhKernel*	kernel) : FactoryBase(kernel)
{}

//=============================================================================

CityFactory::~CityFactory()
{}

//=============================================================================

void CityFactory::handleDatabaseJobComplete(void* ref,swganh::database::DatabaseResult* result)
{
}

//=============================================================================

void CityFactory::requestObject(ObjectFactoryCallback* ofCallback,uint64 id,uint16 subGroup,uint16 subType,DispatchClient* client)
{
    // setup our statement
	std::stringstream sql;
    
    sql << "SELECT cities.id,cities.city_name,planet_regions.region_name,planet_regions.region_file,planet_regions.x,planet_regions.z,"
        << "planet_regions.width,planet_regions.height FROM " << mDatabase->galaxy() << ".cities"
		<< " INNER JOIN " << mDatabase->galaxy() << ".planet_regions ON (cities.city_region = planet_regions.region_id)"
        << " WHERE (cities.id = " << id << ");";


    mDatabase->executeAsyncSql(sql, [=] (swganh::database::DatabaseResult* result) {
        if (!result) {
            return;
        }

        std::unique_ptr<sql::ResultSet>& result_set = result->getResultSet();

        if (!result_set->next()) {
            LOG(warning) << "Unable to load city with region id: " << id;
            return;
        }

        std::shared_ptr<City> city = std::make_shared<City>();
        city->setId(result_set->getUInt64(1));
        city->setCityName(result_set->getString(2));
        city->setRegionName(result_set->getString(3));
        city->setNameFile(result_set->getString(4));
        city->mPosition.x = result_set->getDouble(5);
        city->mPosition.z = result_set->getDouble(6);
        city->setWidth(result_set->getDouble(7));
        city->setHeight(result_set->getDouble(8));

        city->setLoadState(LoadState_Loaded);

        ofCallback->handleObjectReady(city);
    });
}
