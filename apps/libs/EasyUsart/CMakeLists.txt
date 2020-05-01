project(EasyUsart C CXX)

set(HEADER_FILES
        EasyUsart.h
        )

set(SOURCE_FILES
        EasyUsart.c
        )

add_library(EasyUsart STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(EasyUsart opencm3_stm32f3)
