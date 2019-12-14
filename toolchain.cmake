message(STATUS "toolchain")

set(VCPKG_TARGET_TRIPLET "x64-linux")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH} /home/mk/Tools/vcpkg/scripts/buildsystems/vcpkg.cmake")

include(/home/mk/Tools/vcpkg/scripts/buildsystems/vcpkg.cmake) #needed?