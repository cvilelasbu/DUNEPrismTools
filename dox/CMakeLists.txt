file(GLOB FLUXSCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/*.md)
install(PROGRAMS ${FLUXSCRIPTS} DESTINATION ${CMAKE_INSTALL_PREFIX}/dox/)
