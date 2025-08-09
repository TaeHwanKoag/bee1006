###########################################################
#
# UTRX_APP mission build setup
#
# This file is evaluated as part of the "prepare" stage
# and can be used to set up prerequisites for the build,
# such as generating header files
#
###########################################################

# The list of header files that control the UTRX_APP configuration
set(UTRX_APP_MISSION_CONFIG_FILE_LIST
  utrx_app_fcncodes.h
  utrx_app_interface_cfg.h
  utrx_app_mission_cfg.h
  utrx_app_perfids.h
  utrx_app_msg.h
  utrx_app_msgdefs.h
  utrx_app_msgstruct.h
  utrx_app_tbl.h
  utrx_app_tbldefs.h
  utrx_app_tblstruct.h
  utrx_app_topicids.h
)

if (CFE_EDS_ENABLED_BUILD)

  # In an EDS-based build, these files come generated from the EDS tool
  set(UTRX_APP_CFGFILE_SRC_utrx_app_interface_cfg "utrx_app_eds_designparameters.h")
  set(UTRX_APP_CFGFILE_SRC_utrx_app_tbldefs       "utrx_app_eds_typedefs.h")
  set(UTRX_APP_CFGFILE_SRC_utrx_app_tblstruct     "utrx_app_eds_typedefs.h")
  set(UTRX_APP_CFGFILE_SRC_utrx_app_msgdefs       "utrx_app_eds_typedefs.h")
  set(UTRX_APP_CFGFILE_SRC_utrx_app_msgstruct     "utrx_app_eds_typedefs.h")
  set(UTRX_APP_CFGFILE_SRC_utrx_app_fcncodes      "utrx_app_eds_cc.h")

endif(CFE_EDS_ENABLED_BUILD)

# Create wrappers around the all the config header files
# This makes them individually overridable by the missions, without modifying
# the distribution default copies
foreach(UTRX_APP_CFGFILE ${UTRX_APP_MISSION_CONFIG_FILE_LIST})
  get_filename_component(CFGKEY "${UTRX_APP_CFGFILE}" NAME_WE)
  if (DEFINED UTRX_APP_CFGFILE_SRC_${CFGKEY})
    set(DEFAULT_SOURCE GENERATED_FILE "${UTRX_APP_CFGFILE_SRC_${CFGKEY}}")
  else()
    set(DEFAULT_SOURCE FALLBACK_FILE "${CMAKE_CURRENT_LIST_DIR}/config/default_${UTRX_APP_CFGFILE}")
  endif()
  generate_config_includefile(
    FILE_NAME           "${UTRX_APP_CFGFILE}"
    ${DEFAULT_SOURCE}
  )
endforeach()
