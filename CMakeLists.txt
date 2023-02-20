cmake_minimum_required(VERSION 3.0.0)
project(preview VERSION 0.1.0)

add_subdirectory(libs)

find_package( Boost COMPONENTS regex system program_options REQUIRED )

add_executable(${PROJECT_NAME} main.cpp SyncServ.h SyncServ.cpp Clients.h ClientsBroadcast.h ClientsBroadcast.cpp ClientsCache.h ClientsCache.cpp ClientsLogger.h ClientsLogger.cpp ClientsBanner.cpp ClientsBanner.h)
if (WIN32) 
add_definitions(-D_WIN32_WINNT=0x0601)
endif()

target_link_libraries (${PROJECT_NAME} PRIVATE Boost::system)

target_include_directories( ${PROJECT_NAME} PUBLIC 
    ${CMAKE_SOURCE_DIR}
    ${Boost_INCLUDE_DIR}
)

target_compile_features (${PROJECT_NAME} PUBLIC cxx_std_20)
