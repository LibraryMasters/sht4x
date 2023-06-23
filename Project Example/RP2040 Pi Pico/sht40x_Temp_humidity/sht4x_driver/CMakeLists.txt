add_library(
    sht4x_driver
    src/sht40x_driver.c
    src/sht40x_driver_basic.c
    src/sht40x_driver_interface.c
    src/sht40x_driver.h
    src/sht40x_driver_basic.h
    src/sht40x_driver_interface.h
)

target_include_directories(sht4x_driver PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")