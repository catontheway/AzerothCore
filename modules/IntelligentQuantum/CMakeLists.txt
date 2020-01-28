#BGScripts
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/BGScripts/CrossFactionBG/CrossFactionBG.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/BGScripts/CrossFactionBG/CrossFactionBGScript.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/BGScripts/Solo3v3/Solo3v3.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/BGScripts/BattlegroundsReward.cpp")

# CreatureScripts
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/CreatureScripts/Transmogrification/Transmogrification.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/CreatureScripts/Transmogrification/Transmogrifier.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/CreatureScripts/BeastMastery.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/CreatureScripts/CharacterTools.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/CreatureScripts/Doctor.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/CreatureScripts/ExChanger.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/CreatureScripts/Teleport.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/CreatureScripts/Template.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/CreatureScripts/Top.cpp")

# PlayerScripts
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/PlayerScripts/ArenaObject.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/PlayerScripts/Censure.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/PlayerScripts/Duel.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/PlayerScripts/GuildSystem.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/PlayerScripts/Gurubashi.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/PlayerScripts/KillStreak.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/PlayerScripts/Level.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/PlayerScripts/Login.cpp")

AC_ADD_SCRIPT_LOADER("IntelligentQuantum" "${CMAKE_CURRENT_LIST_DIR}/IntelligentQuantum.h")
