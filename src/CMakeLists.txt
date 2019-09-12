find_package(Threads REQUIRED)

hunter_add_package(intx)
find_package(intx CONFIG REQUIRED)

set(scoutone_include_dir ${PROJECT_SOURCE_DIR}/include)

add_library(scoutone
    ${scoutone_include_dir}/scoutone/scoutone.h
    scoutone.cpp
)

option(SCOUTONE_DEBUGGING "Display debugging messages during execution." ON)
if(SCOUTONE_DEBUGGING)
  target_compile_definitions(scoutone PRIVATE SCOUTONE_DEBUGGING=1)
endif()

target_include_directories(scoutone
    PUBLIC $<BUILD_INTERFACE:${scoutone_include_dir}>$<INSTALL_INTERFACE:include>
)
#target_link_libraries(scoutone PUBLIC evmc::evmc PRIVATE scoutone-buildinfo evmc::instructions intx::intx)
if(NOT WIN32)
  if(CMAKE_COMPILER_IS_GNUCXX)
    set_target_properties(scoutone PROPERTIES LINK_FLAGS "-Wl,--no-undefined")
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set_target_properties(scoutone PROPERTIES LINK_FLAGS "-Wl,-undefined,error")
  endif()
endif()

target_link_libraries(scoutone PRIVATE wabt::wabt)

install(TARGETS scoutone EXPORT scoutoneTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
