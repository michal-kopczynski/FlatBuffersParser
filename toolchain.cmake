message(STATUS "toolchain")

set(VCPKG_TARGET_TRIPLET "x64-linux")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH} $ENV{HOME}/Tools/vcpkg/scripts/buildsystems/vcpkg.cmake")

include($ENV{HOME}/Tools/mk/Tools/vcpkg/scripts/buildsystems/vcpkg.cmake)
