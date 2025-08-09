project(CFE_UTRX_APP C)

set(APP_SRC_FILES
  fsw/src/utrx_app.c
  fsw/src/utrx_app_cmds.c
  fsw/src/utrx_app_utils.c
  device/src/utrx.c
)

if (CFE_EDS_ENABLED_BUILD)
  list(APPEND APP_SRC_FILES
    fsw/src/utrx_app_eds_dispatch.c
  )
else()
  list(APPEND APP_SRC_FILES
    fsw/src/utrx_app_dispatch.c
  )
endif()

# # Create the app module
add_cfe_app(utrx ${APP_SRC_FILES})

target_include_directories(utrx PUBLIC
  fsw/inc
  fsw/src
  device/inc
  ../../submodules/libgscsp/lib/libgattos-uc_client_client/include
../../submodules/libgscsp/lib/isl-modem-app_client/include
../../submodules/libgscsp/lib/libaardvark/include
../../submodules/libgscsp/lib/libadcs_client/include
../../submodules/libgscsp/lib/libfp_client/include
../../submodules/libgscsp/lib/libftp_client/include
../../submodules/libgscsp/lib/libgosh_client/include
../../submodules/libgscsp/lib/libgscsp/include
../../submodules/libgscsp/lib/libgscsp/lib/libcsp/include
../../submodules/libgscsp/lib/libgscsp/lib/libcsp/src # #include <csp_conn.h>
../../submodules/libgscsp/lib/libgssb_client/include
../../submodules/libgscsp/lib/libhk_client/include
../../submodules/libgscsp/lib/libnanopb_client/include
../../submodules/libgscsp/lib/libp60_client/include
../../submodules/libgscsp/lib/libparam_client/include
../../submodules/libgscsp/lib/libparam_client/include/deprecated
../../submodules/libgscsp/lib/librgosh_client/include
../../submodules/libgscsp/lib/libutil/include
../../submodules/libgscsp/build/lib/libgscsp/lib/libcsp/include
../../submodules/libgscsp/lib/nanocom-ax_client/include
../../cfe/modules/srl/fsw/src
)
# target_include_directories(utrx_app PRIVATE /usr/include)
# target_link_libraries(utrx_app PRIVATE /usr/lib/x86_64-linux-gnu/libgpiod.a)

target_compile_options(utrx PRIVATE -Wno-pedantic -Wno-error=pedantic)


# Include the public API from utrx_lib to demonstrate how
# to call library-provided functions
add_cfe_app_dependency(utrx sample_lib srl)

# # Add table
add_cfe_tables(utrx fsw/tables/utrx_app_tbl.c)


# If UT is enabled, then add the tests from the subdirectory
# Note that this is an app, and therefore does not provide
# stub functions, as other entities would not typically make
# direct function calls into this application.
if (ENABLE_UNIT_TESTS)
  add_subdirectory(unit-test)
endif (ENABLE_UNIT_TESTS)
