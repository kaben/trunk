# ------------------------------------------------------------------------------
# Quick & dirty OpenNI+CMake support for CloudCompare
# ------------------------------------------------------------------------------

set( LIBOPENNI2_INCLUDE_DIR "" CACHE PATH "Include directory of OpenNI2" )
set( LIBOPENNI2_LIBRARY_FILE "" CACHE FILEPATH "Library file of OpenNI2" )
if (WIN32)
	set( LIBOPENNI2_SHARED_LIBRARY_FILE "" CACHE FILEPATH "Shared library file of OpenNI2 (dll)" )
endif()

if ( NOT LIBOPENNI2_INCLUDE_DIR )
    message( SEND_ERROR "Fill in the OpenNI2 include folder path (LIBOPENNI2_INCLUDE_DIR)" )
endif()
if ( NOT LIBOPENNI2_LIBRARY_FILE )
    message( SEND_ERROR "Fill in the OpenNI2 library file path (LIBOPENNI2_LIBRARY_FILE)" )
endif()

include_directories( ${LIBOPENNI2_INCLUDE_DIR}/Include )
include_directories( ${LIBOPENNI2_INCLUDE_DIR}/Samples/Common )

# Link project with OpenNI2 library and export Dll(s) to specified destinations
function( target_link_OpenNI2 ) # 2 arguments: ARGV0 = project name / ARGV1 = shared lib export folder

	if( LIBOPENNI2_LIBRARY_FILE )

		target_link_libraries( ${PROJECT_NAME} ${LIBOPENNI2_LIBRARY_FILE} )

		# post-build events: we need to export OpenNI2.dll as well!
		if ( WIN32 AND ARGV1 )
			if( LIBOPENNI2_SHARED_LIBRARY_FILE )
				string( REPLACE \\ / LIBOPENNI2_SHARED_LIBRARY_FILE ${LIBOPENNI2_SHARED_LIBRARY_FILE} )
				install_ext( FILES ${LIBOPENNI2_SHARED_LIBRARY_FILE} ${ARGV1} )
			endif()
		endif()

	else()

		message( SEND_ERROR "No OpenNI2 library file specified (LIBOPENNI2_LIBRARY_FILE)" )

	endif()

endfunction()
