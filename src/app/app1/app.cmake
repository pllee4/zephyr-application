include(app_version)

app_version(${APP_NAME} VERSION 0.1.1)

configure_file(version/app_version.h.in ${APP_NAME}/include/app_version.h)
target_include_directories(app PRIVATE ${CMAKE_BINARY_DIR}/src/app/${APP_NAME}/include)

target_sources(app PRIVATE ${APP_NAME}/main.c)
target_link_libraries(app PRIVATE VersionEnquiryManager)
target_compile_definitions(app PRIVATE
    ENQUIRY_MGR_VER_MIN=$<TARGET_PROPERTY:ENQUIRY_MGR_VER_MIN>
    ENQUIRY_MGR_VER_MAX=$<TARGET_PROPERTY:ENQUIRY_MGR_VER_MAX>
)