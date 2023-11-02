cmake_minimum_required(VERSION 3.22)
project(eetc_eett)

if (NOT DEFINED CMAKE_MSVC_RUNTIME_LIBRARY)
    if (EETC_EETT_MIMALLOC)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    else ()
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif ()
endif ()

include(cmake/buildcache.cmake)
include(cmake/pkg.cmake)

# --- LINT ---
option(EETC_EETT_LINT "Run clang-tidy with the compiler." OFF)
if (EETC_EETT_LINT)
    # clang-tidy will be run on all targets defined hereafter
    include(cmake/clang-tidy.cmake)
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(eetc-eett-compile-options
            -Weverything
            -Wno-c++98-compat
            -Wno-c++98-compat-pedantic
            -Wno-newline-eof
            -Wno-missing-prototypes
            -Wno-padded
            -Wno-double-promotion
            -Wno-undef
            -Wno-undefined-reinterpret-cast
            -Wno-float-conversion
            -Wno-global-constructors
            -Wno-exit-time-destructors
            -Wno-switch-enum
            -Wno-c99-designator
            -Wno-zero-as-null-pointer-constant
            -Wno-missing-noreturn
            -Wno-undefined-func-template
            -Wno-unsafe-buffer-usage
            -Wno-c++20-compat
            -Werror)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    set(eetc-eett-compile-options -Wall -Wextra -Werror)
elseif (MSVC)
    set(eetc-eett-compile-options /WX)
else ()
    set(eetc-eett-compile-options
            -Wall
            -Wextra
            -Wno-maybe-uninitialized)
    if (NOT CMAKE_CROSSCOMPILING)
        set(eetc-eett-compile-options ${eetc-eett-compile-options} -Werror)
    endif ()
endif ()

# --- LIB ---
file(GLOB_RECURSE eetc-eett-files src/*.cc)
add_library(eetc-eett ${eetc-eett-files})
target_include_directories(eetc-eett PUBLIC include)
target_link_libraries(eetc-eett PUBLIC cista soro-s utl)
target_compile_features(eetc-eett PUBLIC cxx_std_20)
target_compile_options(eetc-eett PRIVATE ${eetc-eett_compile-options})
