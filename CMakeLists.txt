# This file is part of OS_Concepts.
#
# OS_Concepts is free software: you can redistribute it and/or modify it under 
# the terms of the GNU General Public License as published by the Free Software 
# Foundation, either version 3 of the License, or (at your option) any later version.
#
# OS_Concepts is distributed in the hope that it will be useful, but WITHOUT ANY 
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
# PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along 
# with OS_Concepts. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.27.2)

set(CXX_STANDARD 23)
set(C_STANDARD 23)

project(os_concepts)

set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BASE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BASE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR}/bin)

set(CMAKE_CXX_FLAGS "-g -Og")
set(CMAKE_C_FLAGS "-g -Og")

file(GLOB cmake_srcs ${CMAKE_CURRENT_SOURCE_DIR}/cmake/*.cmake)

include(${cmake_srcs})