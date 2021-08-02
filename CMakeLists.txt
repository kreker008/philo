cmake_minimum_required(VERSION 3.19)
project(philo C)

set(CMAKE_C_STANDARD 99)

set(MAIN_PATH ${PROJECT_SOURCE_DIR}/philo)
set(BONUS_PATH ${PROJECT_SOURCE_DIR}/philo_bonus)

set(HDR_MAIN_PATH ${MAIN_PATH}/include)
set(SRC_MAIN_PATH ${MAIN_PATH}/src)

set(HDR_BONUS_PATH ${BONUS_PATH}/include)
set(SRC_BONUS_PATH ${BONUS_PATH}/src)

##AUTOSET C-FILES
##AUX_SOURCE_DIRECTORY(${SRC_MAIN_PATH} MAIN_SRC)
AUX_SOURCE_DIRECTORY(${SRC_BONUS_PATH} BONUS_SRC)

add_executable(philo
        ${MAIN_SRC} ${BONUS_SRC}
        )

##FIND LIBRARY PTHREAD
find_library(PTHREAD_LIBRARY pthread)

##INCLUDE HDR PATH
target_include_directories(philo PUBLIC
        ${HDR_MAIN_PATH} ${HDR_BONUS_PATH}
        )

##INCLUDE LIBRARIES
target_link_libraries(philo
        ${PTHREAD_LIBRARY}
        )

