#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# set(scripts_STAT_SRCS
  # ${scripts_STAT_SRCS}
  # Custom/Unell_VIP_System.cpp
  # Custom/Unell_Announcer_System.cpp
  # Custom/Unell_Login_System.cpp
  # Custom/Unell_Chat_System.cpp
  # Custom/Unell_Custom.cpp
  # Custom/Unell_Custom_NPC.cpp
  # Custom/Unell_Event.cpp
  # Custom/Unell_Area_System.cpp
  # Custom/Unell_PvP_System.cpp
  # Custom/Unell_Referer_System.cpp
  # Custom/Unell_Script.cpp
  # Custom/Unell_Script.h
  # Custom/Unell_Guild_System.cpp
  # Custom/Unell_Top_System.cpp
# )
# message("  -> Подготовленно: Кастом скрипты")


set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  ${AC_SCRIPTS_DIR}/Custom/DuelReset.cpp
  ${AC_SCRIPTS_DIR}/Custom/transmog_scripts.cpp
  ${AC_SCRIPTS_DIR}/Custom/transmog_scripts_loader.h
  ${AC_SCRIPTS_DIR}/Custom/Transmogrification.cpp
  ${AC_SCRIPTS_DIR}/Custom/Transmogrification.h
  ${AC_SCRIPTS_DIR}/Custom/AnticheatData.cpp
  ${AC_SCRIPTS_DIR}/Custom/AnticheatData.h
  ${AC_SCRIPTS_DIR}/Custom/AnticheatMgr.cpp
  ${AC_SCRIPTS_DIR}/Custom/AnticheatMgr.h
  ${AC_SCRIPTS_DIR}/Custom/AnticheatScripts.cpp
  ${AC_SCRIPTS_DIR}/Custom/cs_anticheat.cpp
)

AC_ADD_SCRIPT_LOADER("Custom" "ScriptLoader.h")

message("  -> Подготовленно: Кастом скрипты")
