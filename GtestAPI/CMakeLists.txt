cmake_minimum_required(VERSION 3.12)

project(GtestAPI)

# 设置源文件和头文件的路径
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/GtestAPI.cpp)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(MIN_EYE_VERSION 2.1.0)

# 设置可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# 添加可执行文件
add_executable(GtestAPI ${SOURCES})

# 添加头文件的搜索路径
target_include_directories(GtestAPI PRIVATE ${INCLUDE_DIR})

# 设置GTest调试和发布版本的库文件路径
set(DEBUG_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/debug)
set(RELEASE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/release)

# 根据构建类型选择不同的库文件路径和后缀
if(CMAKE_BUILD_TYPE MATCHES Debug)
    # 调试模式
    target_link_directories(GtestAPI PRIVATE ${DEBUG_LIB_DIR})
    target_link_libraries(GtestAPI PRIVATE gmock_main gtest_main)

    # 设置调试模式下的编译选项
    target_compile_definitions(GtestAPI PRIVATE _ITERATOR_DEBUG_LEVEL=2)
    
    if(WIN32)
        find_package(MechEyeApi ${MIN_EYE_VERSION} REQUIRED CONFIG PATHS "$ENV{MECHEYE_DIR}/API")
        if(NOT MechEyeApi_FOUND)
            message(FATAL_ERROR "MechEyeApi not found. Please install MechEyeApi with version ${MIN_EYE_VERSION} or higher.")
        endif()

        # 添加mecheye lib_debug文件的搜索路径
        target_link_directories(GtestAPI PRIVATE "$ENV{MECHEYE_DIR}/API/lib_debug")
        target_link_libraries(GtestAPI PRIVATE MechEyeApid)

        target_compile_options(GtestAPI PRIVATE /MDd)
    else()
        find_package(Threads REQUIRED)
        target_link_libraries(GtestAPI PRIVATE Threads::Threads)
        target_compile_options(GtestAPI PRIVATE -g)
    endif()
else()
    # 发布模式
    target_link_directories(GtestAPI PRIVATE ${RELEASE_LIB_DIR})
    target_link_libraries(GtestAPI PRIVATE gmock_main gtest_main)

    # 添加mecheye lib文件的搜索路径
    target_link_directories(GtestAPI PRIVATE "$ENV{MECHEYE_DIR}/API/lib")
    target_link_libraries(GtestAPI PRIVATE MechEyeApi)

    # 设置发布模式下的编译选项
    target_compile_definitions(GtestAPI PRIVATE _ITERATOR_DEBUG_LEVEL=0)
    
    if(WIN32)
        find_package(MechEyeApi ${MIN_EYE_VERSION} REQUIRED CONFIG PATHS "$ENV{MECHEYE_DIR}/API")
        if(NOT MechEyeApi_FOUND)
            message(FATAL_ERROR "MechEyeApi not found. Please install MechEyeApi with version ${MIN_EYE_VERSION} or higher.")
        endif()

        target_compile_options(GtestAPI PRIVATE /MD)
    else()
        find_package(Threads REQUIRED)
        target_link_libraries(GtestAPI PRIVATE Threads::Threads)
        target_compile_options(GtestAPI PRIVATE -O3)

        # ubuntu下查找MechEye库
        find_package(PkgConfig)
        if(NOT PkgConfig_FOUND)
            message(FATAL_ERROR "PkgConfig not found.")
        else()
            pkg_check_modules(MECHEYEAPI REQUIRED MechEyeApi>=${MIN_EYE_VERSION})
            if(NOT MECHEYEAPI_FOUND)
                message(FATAL_ERROR "MechEyeApi not found. Please install MechEyeApi with version ${MIN_EYE_VERSION} or higher.")
            endif()
        endif()
    endif()
endif()

# 链接MechEye头文件库和DLL库
include_directories(${MECHEYEAPI_INCLUDE_DIRS})
link_directories(${MECHEYEAPI_LIBRARY_DIRS})

# 链接共享库文件
target_link_libraries(GtestAPI PRIVATE gmock gtest)
