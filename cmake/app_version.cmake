function(app_version app)
  set(optional "")
  set(one VERSION)
  set(multiple "")
  cmake_parse_arguments(APP "${optional}" "${one}" "${multiple}" "${ARGN}")
  message(STATUS "app_default_version: " ${APP_VERSION})

  string(REGEX REPLACE "([0-9]+)\\..*" "\\1" APP_VERSION_MAJOR ${APP_VERSION})
  string(REGEX REPLACE "[0-9]+\\.([0-9]+).*" "\\1" APP_VERSION_MINOR ${APP_VERSION})
  string(REGEX REPLACE "[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" APP_VERSION_PATCH ${APP_VERSION})

  set("APP_VERSION" "${APP_VERSION}" PARENT_SCOPE)
  set("APP_VERSION_MAJOR" "${APP_VERSION_MAJOR}" PARENT_SCOPE)
  set("APP_VERSION_MINOR" "${APP_VERSION_MINOR}" PARENT_SCOPE)
  set("APP_VERSION_PATCH" "${APP_VERSION_PATCH}" PARENT_SCOPE)

endfunction()