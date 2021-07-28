cmake_minimum_required(VERSION 3.19)
project(philo C)

set(CMAKE_C_STANDARD 99)

##AUTOSET C-FILES
##AUX_SOURCE_DIRECTORY(./src/main SRC)
AUX_SOURCE_DIRECTORY(./src/bonus BONUS)


add_executable(philo
        ${SRC} ${BONUS}
        )

set(HDR_PATH ${PROJECT_SOURCE_DIR}/include)

##FIND LIBRARY PTHREAD
find_library(PTHREAD_LIBRARY pthread)

##INCLUDE HDR PATH
target_include_directories(philo PUBLIC
        ${HDR_PATH}
        )

##INCLUDE LIBRARIES
target_link_libraries(philo
        ${PTHREAD_LIBRARY}
        )

