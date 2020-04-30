project(LedDial)

set(HEADER_FILES
        LedDial.h
        )

set(SOURCE_FILES
        LedDial.c
        )

add_library(LedDial STATIC ${SOURCE_FILES} ${HEADER_FILES})