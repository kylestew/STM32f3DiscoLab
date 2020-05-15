cmake_minimum_required(VERSION 3.9)

include_directories(libs)
add_subdirectory(libs)

add_subdirectory(01-miniblink)
add_subdirectory(02-button)
add_subdirectory(03-led-ring)
add_subdirectory(04-usart)
add_subdirectory(05-analog)


#add_subdirectory(05-debounce)


