# ------------------------------------------------------------------------------
# Quick & dirty OpenNI+CMake support for CloudCompare
# ------------------------------------------------------------------------------

set( OPENNI2_INCLUDE_DIR "" CACHE PATH "Include directory of OpenNI2" )
set( OPENNI2_INCLUDE_DIR "" CACHE FILEPATH "Library file of OpenNI2" )
if (WIN32)
	set( OPENNI2_SHARED_LIBRARY_FILE "" CACHE FILEPATH "Shared library file of OpenNI2 (dll)" )
endif()

if ( NOT OPENNI2_INCLUDE_DIR )
    message( SEND_ERROR "Fill in the OpenNI2 include folder path (OPENNI2_INCLUDE_DIR)" )
endif()
if ( NOT OPENNI2_INCLUDE_DIR )
    message( SEND_ERROR "Fill in the OpenNI2 library file path (OPENNI2_INCLUDE_DIR)" )
endif()

include_directories( ${OPENNI2_INCLUDE_DIR}/Include )
include_directories( ${OPENNI2_INCLUDE_DIR}/Samples/Common )

# Link project with OpenNI2 library and export Dll(s) to specified destinations
function( target_link_OpenNI2 ) # 2 arguments: ARGV0 = project name / ARGV1 = shared lib export folder

	if( OPENNI2_INCLUDE_DIR )

		target_link_libraries( ${PROJECT_NAME} ${OPENNI2_INCLUDE_DIR} )

		# post-build events: we need to export OpenNI2.dll as well!
		if ( WIN32 AND ARGV1 )
			if( OPENNI2_SHARED_LIBRARY_FILE )
				string( REPLACE \\ / OPENNI2_SHARED_LIBRARY_FILE ${OPENNI2_SHARED_LIBRARY_FILE} )
				install_ext( FILES ${OPENNI2_SHARED_LIBRARY_FILE} ${ARGV1} )
			endif()
		endif()

	else()

		message( SEND_ERROR "No OpenNI2 library file specified (OPENNI2_INCLUDE_DIR)" )

	endif()

endfunction()
