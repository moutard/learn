
# === External libraries ===

# === Project Sources ===
set (HEADERS
  hgexception.h
)

set (SOURCES
  hgexception.cpp
)

# preprocess all Qt files
QT4_WRAP_CPP(HEADERS_MOC ${HEADERS})

# Create executable called raytracer, that use the modified source.
add_library(
  hellogl_utils SHARED
  ${SOURCES}
  ${HEADERS_MOC}
  )

# link the executable you just created with all the external libraries
# pthread is required by GTest
target_link_libraries(hellogl_utils)
