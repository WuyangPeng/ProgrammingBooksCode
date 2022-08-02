# Install script for directory: H:/ProgrammingBooksCode/C++/高级/C++ API设计/03_Patterns

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/APIBook")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("H:/ProgrammingBooksCode/C++/高级/C++ API设计/Build/03_Patterns/pimpl_bad/cmake_install.cmake")
  include("H:/ProgrammingBooksCode/C++/高级/C++ API设计/Build/03_Patterns/pimpl_good/cmake_install.cmake")
  include("H:/ProgrammingBooksCode/C++/高级/C++ API设计/Build/03_Patterns/pimpl_boost/cmake_install.cmake")
  include("H:/ProgrammingBooksCode/C++/高级/C++ API设计/Build/03_Patterns/opaque_pointer/cmake_install.cmake")
  include("H:/ProgrammingBooksCode/C++/高级/C++ API设计/Build/03_Patterns/singleton/cmake_install.cmake")
  include("H:/ProgrammingBooksCode/C++/高级/C++ API设计/Build/03_Patterns/factory_simple/cmake_install.cmake")
  include("H:/ProgrammingBooksCode/C++/高级/C++ API设计/Build/03_Patterns/factory_extensible/cmake_install.cmake")
  include("H:/ProgrammingBooksCode/C++/高级/C++ API设计/Build/03_Patterns/proxy_simple/cmake_install.cmake")
  include("H:/ProgrammingBooksCode/C++/高级/C++ API设计/Build/03_Patterns/proxy_interface/cmake_install.cmake")
  include("H:/ProgrammingBooksCode/C++/高级/C++ API设计/Build/03_Patterns/adapter/cmake_install.cmake")
  include("H:/ProgrammingBooksCode/C++/高级/C++ API设计/Build/03_Patterns/facade/cmake_install.cmake")
  include("H:/ProgrammingBooksCode/C++/高级/C++ API设计/Build/03_Patterns/observer/cmake_install.cmake")

endif()

