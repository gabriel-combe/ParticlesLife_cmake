add_library(
  glad
  src/glad.c
  includes/glad/glad.h
  includes/KHR/khrplatform.h
)

target_include_directories(glad PUBLIC includes)
