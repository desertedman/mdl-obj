cmake_minimum_required(VERSION 3.11) # Use fetchcontent
project(mdl-obj VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
  ${PROJECT_NAME}
  # src/main.cpp
  src/main2.cpp
)

target_compile_definitions(
  ${PROJECT_NAME} PRIVATE
  TINYOBJLOADER_IMPLEMENTATION
)

# Make Visual Studio invoke in the correct directory
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
  )

  target_compile_options(${PROJECT_NAME} PRIVATE
    # /W4
    # /WX
    # /permissive-
  )

  # Strict errors
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(${PROJECT_NAME} PRIVATE
    # -Wall
    # -Wextra
    # -Werror
    # -pedantic-errors
  )
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
