cmake_minimum_required(VERSION 3.5)
project(OnlineStore CXX)

include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)
if (NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
    # Do nothing
elseif (HAS_ANY AND HAS_STRING_VIEW AND HAS_COROUTINE)
    set(CMAKE_CXX_STANDARD 20)
elseif (HAS_ANY AND HAS_STRING_VIEW)
    set(CMAKE_CXX_STANDARD 17)
else ()
    set(CMAKE_CXX_STANDARD 14)
endif ()



set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cc database/DataBaseHelper.h database/DataBaseHelper.cc
        controllers/userController.h controllers/userController.cc
        controllers/typeController.cc controllers/typeController.h
        controllers/deviceController.cc  controllers/deviceController.cc
        controllers/brandController.cc controllers/brandController.h
        Middleware/ErrorHandlingMiddleware.cc
        Middleware/ErrorHandlingMiddleware.h error/ApiError.cc error/ApiError.h
        entity/User.cc entity/User.h entity/Brand.cc entity/Brand.h

        entity/Device.cc entity/Device.h entity/Type.cc entity/Type.h
        database/Mutex.cc database/Mutex.h imgdump/imgUpload.cpp imgdump/imgUpload.h
        Exception/ForbiddenException.cpp Exception/ForbiddenException.h
        utils/jwtService.cc utils/jwtService.h Middleware/authMiddleware.cpp Middleware/authMiddleware.h filters/authenticationFilter.cpp filters/authenticationFilter.h filters/authFilter.cc filters/authFilter.h filters/adminRoleFilter.h filters/adminRoleFilter.cc filters/adminRoleFilter.cc filters/adminRoleFilter.cc entity/JwtResponseDTO.cc entity/JwtResponseDTO.h decorators/UpdateDecorators.h decorators/DeviceUpdateDecorator.h entity/Cart.cpp entity/Cart.h entity/Rating.cpp entity/Rating.h controllers/api_ratingController.h entity/DeviceInfo.cpp entity/DeviceInfo.h controllers/api_deviceInfoController.h decorators/DeviceInfoUpdateDecorator.cpp decorators/DeviceInfoUpdateDecorator.h)

#add_subdirectory(../jwt-cpp)
#target_link_libraries(${PROJECT_NAME} PRIVATE jwt-cpp)
find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

add_subdirectory(external/libbcrypt)
target_link_libraries(${PROJECT_NAME} PRIVATE bcrypt)

# ##############################################################################
# If you include the drogon source code locally in your project, use this method
# to add drogon 
# add_subdirectory(drogon) 
# target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
#
# and comment out the following lines
find_package(Drogon CONFIG REQUIRED)

find_package(fmt )
if (fmt_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${fmt_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${fmt_LIBRARIES})
endif ()

#find_package(Boost 1.70 COMPONENTS
#        program_options
#        unit_test_framework
#        REQUIRED
#       )

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)
target_include_directories(${PROJECT_NAME} PRIVATE ${PQXX_LIB_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${PQ_LIB_INCLUDE_DIRS})

target_link_libraries(

        ${PROJECT_NAME} PUBLIC Drogon::Drogon
        PUBLIC pthread
        fmt
        ${PQXX_LIB}
        ${PQ_LIB}
)

#target_link_libraries(
#    server PUBLIC
#    ${Boost_LIBRARIES}
#     pthread
#    fmt
#    pq
#   pqxx
#)

# ##############################################################################

if (CMAKE_CXX_STANDARD LESS 17)
    # With C++14, use boost to support any, string_view and filesystem
    message(STATUS "use c++14")
    find_package(Boost 1.61.0 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC Boost::boost)
elseif (CMAKE_CXX_STANDARD LESS 20)
    message(STATUS "use c++17")
else ()
    message(STATUS "use c++20")
endif ()

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)
aux_source_directory(utils UTIL_SRC)

drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
                    ${CMAKE_CURRENT_BINARY_DIR})
# use the following line to create views with namespaces.
# drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
#                     ${CMAKE_CURRENT_BINARY_DIR} TRUE)
# use the following line to create views with namespace CHANGE_ME prefixed
# and path namespaces.
# drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
#                     ${CMAKE_CURRENT_BINARY_DIR} TRUE CHANGE_ME)

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                   ${CMAKE_CURRENT_SOURCE_DIR}/models)
target_sources(${PROJECT_NAME}
               PRIVATE
               ${SRC_DIR}
               ${CTL_SRC}
               ${FILTER_SRC}
               ${PLUGIN_SRC}
               ${MODEL_SRC})
# ##############################################################################
# uncomment the following line for dynamically loading views 
# set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS ON)

# ##############################################################################

add_subdirectory(test)
