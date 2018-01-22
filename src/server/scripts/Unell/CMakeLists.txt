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
  ${AC_SCRIPTS_DIR}/Unell/Unell_Announcer_System.cpp
  ${AC_SCRIPTS_DIR}/Unell/Unell_Area_System.cpp
  ${AC_SCRIPTS_DIR}/Unell/Unell_Chat_System.cpp
  ${AC_SCRIPTS_DIR}/Unell/Unell_Custom.cpp
  ${AC_SCRIPTS_DIR}/Unell/Unell_Custom_NPC.cpp
  # ${AC_SCRIPTS_DIR}/Unell/Unell_GO_System.cpp
  ${AC_SCRIPTS_DIR}/Unell/Unell_Guild_System.cpp
  ${AC_SCRIPTS_DIR}/Unell/Unell_Level_System.cpp
  ${AC_SCRIPTS_DIR}/Unell/Unell_Login_System.cpp
  ${AC_SCRIPTS_DIR}/Unell/Unell_PvP_System.cpp
  ${AC_SCRIPTS_DIR}/Unell/Unell_Referer_System.cpp
  # ${AC_SCRIPTS_DIR}/Unell/Unell_Reforger_System.cpp
  ${AC_SCRIPTS_DIR}/Unell/Unell_Script.cpp
  ${AC_SCRIPTS_DIR}/Unell/Unell_Script.h
  ${AC_SCRIPTS_DIR}/Unell/Unell_Top_System.cpp
  ${AC_SCRIPTS_DIR}/Unell/Unell_VIP_System.cpp
  ${AC_SCRIPTS_DIR}/Unell/Unell_Arena_System.cpp
  ${AC_SCRIPTS_DIR}/Unell/Unell_Arena_System.h
)

AC_ADD_SCRIPT_LOADER("Unell" "ScriptLoader.h")

message("  -> Подготовленно: Unell скрипты")
