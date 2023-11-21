cmake_minimum_required(VERSION 3.12)

project(MyPythonProject)


find_package(Python COMPONENTS Development Interpreter)


if(Python_FOUND)
    message(STATUS "Python Found: ${Python_VERSION}")

    include_directories(${Python_INCLUDE_DIRS})

    link_directories(${Python_LIBRARY_DIRS})

    add_custom_command(
        OUTPUT test.c test.h
        COMMAND python3 -m cython test.pyx
        DEPENDS test.pyx
    )

    add_executable(my_program main.cpp test.c)

    message(STATUS "Python include dirs: ${Python_LIBRARIES}")

    target_link_libraries(my_program PRIVATE ${Python_LIBRARIES})

    add_custom_target(install_dependencies
        COMMAND pip3 install -r ${CMAKE_CURRENT_SOURCE_DIR}/requirements.txt
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

    add_dependencies(my_program install_dependencies)

    add_custom_target(build_all DEPENDS install_dependencies my_program)
else()
    message(FATAL_ERROR "Python not found. Please make sure Python is installed.")
endif()
