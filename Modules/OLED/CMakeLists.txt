cmake_minimum_required(VERSION 3.22)

project( OLED LANGUAGES CXX)

add_executable( ${PROJECT_NAME}  ${PROJECT_SOURCE_DIR}/OLED.c )

target_link_libraries( ${PROJECT_NAME} PRIVATE ssd1306 )