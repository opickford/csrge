# CMakeList.txt : CMake project for the game.
#

find_package(caudio REQUIRED)

# Compile the engine as a static .lib to be used by the game/tools.
add_executable (game
	"main.c"
 )

 # Link the light baking tool to the engine
target_link_libraries(game PRIVATE engine caudio::caudio)

target_include_directories (game PRIVATE "${CMAKE_SOURCE_DIR}/engine")

set_target_properties(game PROPERTIES FOLDER "game")

# TODO: Add tests and install targets if needed.
