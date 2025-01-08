# CMakeList.txt : CMake project for BattleshipC++, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (BattleshipC++ "BattleshipC++.cpp" "BattleshipC++.h" "Helper.h" "UserInteract.cpp" "UserInteract.h" "Mygameclass.h" "Mygameclass.cpp" "Temp.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BattleshipC++ PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
