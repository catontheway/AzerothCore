# CreatureScripts
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/CreatureScripts/BeastMastery.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/CreatureScripts/Doctor.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/CreatureScripts/Teleport.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/CreatureScripts/Template.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/CreatureScripts/Top.cpp")

# PlayerScripts
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/PlayerScripts/ArenaObject.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/PlayerScripts/Gurubashi.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/PlayerScripts/KillStreak.cpp")

AC_ADD_SCRIPT_LOADER("IntelligentQuantum" "${CMAKE_CURRENT_LIST_DIR}/IntelligentQuantum.h")
