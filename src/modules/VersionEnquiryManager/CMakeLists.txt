if (BUILD_TESTS)
    # for unit test
    cmake_minimum_required(VERSION 3.13.1)
    find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
    project(version_enquiry_manager_test)

    target_sources(app PRIVATE src/VersionEnquiryManager.c test/VersionEnquiryManagerTest.c)
    target_include_directories(app PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
else()
    add_library(VersionEnquiryManager src/VersionEnquiryManager.c)
    set_target_properties(VersionEnquiryManager PROPERTIES
        COMPATIBLE_INTERFACE_NUMBER_MIN ENQUIRY_MGR_VER_MIN
        COMPATIBLE_INTERFACE_NUMBER_MAX ENQUIRY_MGR_VER_MAX
        INTERFACE_ENQUIRY_MGR_VER_MIN 2
        INTERFACE_ENQUIRY_MGR_VER_MAX 2
    )
    target_include_directories(VersionEnquiryManager PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()
