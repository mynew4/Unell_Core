/*
 * Copyright (C) 
 *
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef _UNELLDATABASE_H
#define _UNELLDATABASE_H

#include "DatabaseWorkerPool.h"
#include "MySQLConnection.h"

class UnellDatabaseConnection : public MySQLConnection
{
    public:
        //- Constructors for sync and async connections
        UnellDatabaseConnection(MySQLConnectionInfo& connInfo) : MySQLConnection(connInfo) { }
        UnellDatabaseConnection(ACE_Activation_Queue* q, MySQLConnectionInfo& connInfo) : MySQLConnection(q, connInfo) { }

        //- Loads database type specific prepared statements
        void DoPrepareStatements();
};

typedef DatabaseWorkerPool<UnellDatabaseConnection> UnellDatabaseWorkerPool;

enum UnellDatabaseStatements
{
    /*  Naming standard for defines:
        {DB}_{SEL/INS/UPD/DEL/REP}_{Summary of data changed}
        When updating more than one field, consider looking at the calling function
        name for a suiting suffix.
    */

	UNELL_SEL_COMMANDS,

    MAX_UNELLDATABASE_STATEMENTS
};

#endif
