cmake_minimum_required(VERSION 3.8)

include(cmake/cable/bootstrap.cmake)
include(CableBuildInfo)
include(CableBuildType)
include(CableCompilerSettings)
include(CableToolchains)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

include(Hunter/init)

cable_configure_toolchain(DEFAULT cxx17-pic)

cable_set_build_type(DEFAULT RelWithDebInfo CONFIGURATION_TYPES Debug;Release;RelWithDebInfo)

set(CMAKE_DEBUG_POSTFIX "")

project(scoutone)
set(PROJECT_VERSION 0.1.0-alpha.0)

cable_configure_compiler()
if(CABLE_COMPILER_GNULIKE)
    # TODO: fix the warnings instead
    add_compile_options(-Wno-pedantic)
endif()

cable_add_buildinfo_library(PROJECT_NAME scoutone EXPORT scoutoneTargets)

option(BUILD_SHARED_LIBS "Build libraries as shared" ON)

include(ProjectWabt)

add_subdirectory(src)

install(DIRECTORY include/scoutone DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

write_basic_package_version_file(scoutoneConfigVersion.cmake COMPATIBILITY SameMajorVersion)

configure_package_config_file(
    cmake/Config.cmake.in
    scoutoneConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/scoutone
)

install(
    EXPORT scoutoneTargets
    NAMESPACE scoutone::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/scoutone
)

install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/scoutoneConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/scoutoneConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/scoutone
)

if(WIN32)
    set(CPACK_GENERATOR ZIP)
else()
    set(CPACK_GENERATOR TGZ)
endif()
set(CPACK_PACKAGE_FILE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_CHECKSUM SHA256)
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY FALSE)
include(CPack)
