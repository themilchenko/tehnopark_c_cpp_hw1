cmake_minimum_required(VERSION 3.18)

project("DZ1" LANGUAGES C)

# объявление стандарта
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_definitions(DEBUG)

option(SANITIZERS "Turn on sanitizers" OFF)

set(${PROJECT_NAME}_TEAM_H ${CMAKE_SOURCE_DIR}/include/Team.h)
set(${PROJECT_NAME}_INPUT_C ${CMAKE_SOURCE_DIR}/source/input.c)
set(${PROJECT_NAME}_TEAM_C ${CMAKE_SOURCE_DIR}/source/Team.c)
set(${PROJECT_NAME}_MAIN_C ${CMAKE_SOURCE_DIR}/source/main.c)

add_compile_options(-fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer)
add_link_options(-fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer)

add_executable(${PROJECT_NAME} source/main.c)
add_library(${PROJECT_NAME}_Team ${${PROJECT_NAME}_TEAM_C} ${${PROJECT_NAME}_INPUT_C})

if (SANITIZERS)
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
endif()

target_compile_options(${PROJECT_NAME}_Team PUBLIC -fprofile-arcs -ftest-coverage -O0)
target_link_options(${PROJECT_NAME}_Team PUBLIC -fprofile-arcs -ftest-coverage)

IF (APPLE)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
ENDIF ()

# линковка
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_Team)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(GCC_WARNINGS
        -Wmisleading-indentation
        -Wall
        -Wextra
        -Wshadow
        -Wcast-align
        -Wunused
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2
        -Werror
        -g
        -O0
        )
add_compile_options(${GCC_WARNINGS})

enable_testing()
add_subdirectory(tests)