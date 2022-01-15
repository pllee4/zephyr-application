# MCU-specific flags
if (BUILD_POSIX_NATIVE)
    set(MCU_FLAGS "-m32")
endif()

set(GCC_FLAG "-lgcc")

# Main application 
add_subdirectory(app)
add_subdirectory(modules)