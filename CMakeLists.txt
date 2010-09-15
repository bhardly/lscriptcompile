
# -*- cmake -*-

cmake_minimum_required(VERSION 2.4)

project (lscriptcompile)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(WINDOWS ON BOOL FORCE)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(LINUX ON BOOl FORCE)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(DARWIN 1)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

if (WINDOWS)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi /MDd /MP"
      CACHE STRING "C++ compiler debug options" FORCE)
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO 
      "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /Od /Zi /MD /MP"
      CACHE STRING "C++ compiler release-with-debug options" FORCE)
  set(CMAKE_CXX_FLAGS_RELEASE
      "${CMAKE_CXX_FLAGS_RELEASE} ${LL_CXX_FLAGS} /O2 /Zi /MD /MP"
      CACHE STRING "C++ compiler release options" FORCE)
  
  set(CMAKE_CXX_STANDARD_LIBRARIES "")
  set(CMAKE_C_STANDARD_LIBRARIES "")
  
  add_definitions(
      /DLL_WINDOWS=1
      /DUNICODE
      /D_UNICODE 
      /GS
      /TP
      /W3
      /c
      /Zc:wchar_t-
      /Zc:forScope
      /nologo
      /Oy-
      )
     
  if(MSVC80 OR MSVC90)
    set(CMAKE_CXX_FLAGS_RELEASE
      "${CMAKE_CXX_FLAGS_RELEASE} -D_SECURE_STL=0 -D_HAS_ITERATOR_DEBUGGING=0"
      CACHE STRING "C++ compiler release options" FORCE)
   
    add_definitions(
      /Zc:wchar_t-
      )
  endif (MSVC80 OR MSVC90)
  
  # configure win32 API for windows XP+ compatibility
  set(WINVER "0x0501" CACHE STRING "Win32 API Target version (see http://msdn.microsoft.com/en-us/library/aa383745%28v=VS.85%29.aspx)")
  add_definitions("/DWINVER=${WINVER}" "/D_WIN32_WINNT=${WINVER}")
  
  include_directories(
    src
    src/llinventory
    src/llmath
    src/llmessage
    src/llprimitive
    src/windows
    )
else (WINDOWS)
  include_directories(
    src
    src/llinventory
    src/llmath
    src/llmessage
    src/llprimitive
    )
endif (WINDOWS)

if (LINUX)
  add_definitions(
      -DLL_LINUX=1
      -D_REENTRANT
      -fexceptions
      -fno-math-errno
      -fno-strict-aliasing
      -fsigned-char
      -g
      -pthread
      )
  
  set(CMAKE_CXX_FLAGS_DEBUG "-fno-inline ${CMAKE_CXX_FLAGS_DEBUG}")
  set(CMAKE_CXX_FLAGS_RELEASE "-O2 ${CMAKE_CXX_FLAGS_RELEASE}")
endif (LINUX)

if (DARWIN)
  add_definitions(-DLL_DARWIN=1 -D_XOPEN_SOURCE)
  set(CMAKE_CXX_LINK_FLAGS "-Wl,-headerpad_max_install_names,-search_paths_first")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_CXX_LINK_FLAGS}")
  set(DARWIN_extra_cstar_flags "-mlong-branch")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DARWIN_extra_cstar_flags}")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  ${DARWIN_extra_cstar_flags}")
endif (DARWIN)

if (LINUX OR DARWIN)
  set(GCC_WARNINGS "-Wall -Wno-sign-compare -Wno-trigraphs")

  if (NOT GCC_DISABLE_FATAL_WARNINGS)
    set(GCC_WARNINGS "${GCC_WARNINGS} -Werror")
  endif (NOT GCC_DISABLE_FATAL_WARNINGS)

  set(GCC_CXX_WARNINGS "${GCC_WARNINGS} -Wno-reorder -Wno-non-virtual-dtor -Woverloaded-virtual")

  set(CMAKE_C_FLAGS "${GCC_WARNINGS} ${CMAKE_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${GCC_CXX_WARNINGS} ${CMAKE_CXX_FLAGS}")

  if (WORD_SIZE EQUAL 32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
  elseif (WORD_SIZE EQUAL 64)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
  endif (WORD_SIZE EQUAL 32)
endif (LINUX OR DARWIN)


set(lscriptcompile_SOURCE_FILES
    src/indra.l.cpp
    src/indra.y.cpp
    src/lleventtimer.cpp
    src/llfile.cpp
    src/llformat.cpp
    src/llframetimer.cpp
    src/lllivefile.cpp
    src/llscriptresource.cpp
    src/llscriptresourceconsumer.cpp
    src/llscriptresourcepool.cpp
    src/llstring.cpp
    src/llstringtable.cpp
    src/lltimer.cpp
    src/lscript_alloc.cpp
    src/lscript_alloc2.cpp
    src/lscript_bytecode.cpp
    src/lscript_error.cpp
    src/lscript_export.cpp
    src/lscript_heap.cpp
    src/lscript_heapruntime.cpp
    src/lscript_library.cpp
    src/lscript_readlso.cpp
    src/lscript_resource.cpp
    src/lscript_scope.cpp
    src/lscript_tree.cpp
    src/lscript_typecheck.cpp
    src/lscriptcompile.cpp
    src/u64.cpp
    )

add_library(lscriptcompile SHARED ${lscriptcompile_SOURCE_FILES})
