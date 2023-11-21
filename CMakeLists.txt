cmake_minimum_required(VERSION 3.12)

project(MyPythonProject)

# Find Python
find_package(Python COMPONENTS Development Interpreter)

# Check if Python was found
if(Python_FOUND)
    message(STATUS "Python Found: ${Python_VERSION}")

    # Add the path to the Python header files
    include_directories(${Python_INCLUDE_DIRS})

    # Add the path to the Python library
    link_directories(${Python_LIBRARY_DIRS})

    # generate test.c and test.h from test.pyx
    add_custom_command(
        OUTPUT test.c test.h
        COMMAND python3 -m cython test.pyx
        DEPENDS test.pyx
    )

    # Add your C++ source file
    add_executable(my_program main.cpp test.c)

    message(STATUS "Python include dirs: ${Python_LIBRARIES}")
    # Link against the Python library
    target_link_libraries(my_program PRIVATE ${Python_LIBRARIES})

    # Add custom command to install dependencies using pip3
    add_custom_target(install_dependencies
        COMMAND pip3 install -r ${CMAKE_CURRENT_SOURCE_DIR}/requirements.txt
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

    # Add the custom command as a dependency to the my_program target
    add_dependencies(my_program install_dependencies)

    # Make install_dependencies run when invoking cmake .
    add_custom_target(build_all DEPENDS install_dependencies my_program)
else()
    message(FATAL_ERROR "Python not found. Please make sure Python is installed.")
endif()
