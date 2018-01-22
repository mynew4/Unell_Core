/*
 * Copyright (C) 
 *
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#include "UnellDatabase.h"

void UnellDatabaseConnection::DoPrepareStatements()
{
    if (!m_reconnecting)
        m_stmts.resize(MAX_UNELLDATABASE_STATEMENTS);

	PrepareStatement(UNELL_SEL_COMMANDS, "SELECT name, security, help FROM command", CONNECTION_SYNCH);
}
