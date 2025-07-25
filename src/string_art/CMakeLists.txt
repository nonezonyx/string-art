cmake_policy(SET CMP0167 NEW)
find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(OpenCV REQUIRED)

file(GLOB METRIC_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/metrics/*.cpp)

foreach(METRIC_SOURCE ${METRIC_SOURCES})
    get_filename_component(METRIC_NAME ${METRIC_SOURCE} NAME_WE)

    add_library(metric_${METRIC_NAME} SHARED ${METRIC_SOURCE} string_art.cpp abstract_metric.cpp)

    target_link_libraries(metric_${METRIC_NAME}
        PRIVATE
            Boost::filesystem
            Boost::system
            ${OpenCV_LIBS}
    )

    set_target_properties(metric_${METRIC_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/metrics
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/metrics
        PREFIX ""
    )

    list(APPEND METRIC_TARGETS metric_${METRIC_NAME})
endforeach()

file(GLOB SOLVER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/solvers/*.cpp)

foreach(SOLVER_SOURCE ${SOLVER_SOURCES})
    get_filename_component(SOLVER_NAME ${SOLVER_SOURCE} NAME_WE)

    add_library(solver_${SOLVER_NAME} SHARED ${SOLVER_SOURCE} string_art.cpp abstract_solver.cpp abstract_metric.cpp)

    target_link_libraries(solver_${SOLVER_NAME}
        PRIVATE
            Boost::filesystem
            Boost::system
            ${OpenCV_LIBS}
    )

    set_target_properties(solver_${SOLVER_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/solvers
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/solvers
        PREFIX ""
    )

    list(APPEND SOLVER_TARGETS solver_${SOLVER_NAME})
endforeach()

add_library(string_art_lib STATIC
    string_art.cpp
    abstract_metric.cpp
    abstract_solver.cpp
)

target_link_libraries(string_art_lib
    PUBLIC
        Boost::filesystem
        Boost::system
        ${OpenCV_LIBS}
)

target_include_directories(string_art_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)
