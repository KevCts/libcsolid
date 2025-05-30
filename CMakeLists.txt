cmake_minimum_required(VERSION 3.30)

project(libcsolid)

add_subdirectory(cvide)

set(SRCS
    model.c
    node.c
    element.c
    section.c
    material.c
    elements/bar.c
)

set(HEADERS
    model.h
    node.h
    element.h
    section.h
    material.h
    elements/bar.h
)

add_library(libcsolid ${SRCS} ${HEADERS})
target_link_libraries(libcsolid libcvide)
