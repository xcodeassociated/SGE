message(STATUS "External project: Boost")
message(STATUS "INSTALL_DEPENDENCIES_DIR: ${INSTALL_DEPENDENCIES_DIR}")

set(BOOST_PREFIX "${INSTALL_DEPENDENCIES_DIR}/boost_prefix")
set( Boost_Bootstrap_Command )

if( UNIX )
  set( Boost_url "https://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz")
  set( Boost_Bootstrap_Command ./bootstrap.sh )
  set( Boost_b2_Command ./b2 )
else()
  if( WIN32 )
    set( Boost_url "https://sourceforge.net/projects/boost/files/boost/1.65.1/boost_1_65_1.zip")
    set( Boost_Bootstrap_Command bootstrap.bat )
    set( Boost_b2_Command b2.exe )
  endif()
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(Boost_address_model 64)
else()
  set(Boost_address_model 32)
endif()

if (MSVC_VERSION EQUAL 1500) #VS2008
set(boost_toolset "--toolset=msvc-9.0")
elseif(MSVC_VERSION EQUAL 1600) #VS2010
set(boost_toolset "--toolset=msvc-10.0")
elseif(MSVC_VERSION EQUAL 1700) #VS2012
set(boost_toolset "--toolset=msvc-11.0")
elseif(MSVC_VERSION EQUAL 1800) #VS2013
set(boost_toolset "--toolset=msvc-12.0")
elseif(MSVC_VERSION EQUAL 1900) #VS2015
set(boost_toolset "--toolset=msvc-14.0")

elseif(MSVC_VERSION EQUAL 1910) 
set(boost_toolset "--toolset=msvc-14.1")
elseif(MSVC_VERSION EQUAL 1911) 
set(boost_toolset "--toolset=msvc-14.11")
elseif(MSVC_VERSION EQUAL 1912) 
set(boost_toolset "--toolset=msvc-14.12")
elseif(MSVC_VERSION EQUAL 1913) 
set(boost_toolset "--toolset=msvc-14.13")
elseif(MSVC_VERSION EQUAL 1914) 
set(boost_toolset "--toolset=msvc-14.14")
endif()

if(${BUILD_SHARED_LIBS} MATCHES OFF)
  set(BUILD_LIBS "static")
elseif(${BUILD_SHARED_LIBS} MATCHES ON)
  set(BUILD_LIBS "shared")
endif()

message(STATUS "BOOST_BUILD_CMD: ${BOOST_BUILD_CMD}")

ExternalProject_Add(BOOST_EXTERNAL
	PREFIX ${BOOST_PREFIX}
	BUILD_IN_SOURCE ON
	URL ${Boost_url}
	UPDATE_COMMAND ""
	CONFIGURE_COMMAND ${Boost_Bootstrap_Command} --prefix=${INSTALL_DEPENDENCIES_DIR}/boost_prefix
	BUILD_COMMAND ${Boost_b2_Command} install -j${PROCESSOR_COUNT} --prefix=${INSTALL_DEPENDENCIES_DIR}/boost --with-thread --with-filesystem --with-system --with-date_time --with-program_options --threading=multi link=static 
	INSTALL_COMMAND ""
	INSTALL_DIR ${INSTALL_DEPENDENCIES_DIR}/boost
	LOG_DOWNLOAD ON
	LOG_UPDATE ON
	LOG_CONFIGURE ON 
	LOG_BUILD ON
	LOG_INSTALL ON 
)

set(BOOST_ROOT ${INSTALL_DEPENDENCIES_DIR}/boost)
set(Boost_INCLUDE_DIR ${INSTALL_DEPENDENCIES_DIR}/boost/include)
set(Boost_LIBRARY_DIR ${INSTALL_DEPENDENCIES_DIR}/boost/lib)

message(STATUS "EXTERNAL BOOST_ROOT: ${BOOST_ROOT}")
message(STATUS "EXTERNAL Boost_INCLUDE_DIR: ${Boost_INCLUDE_DIR}")
message(STATUS "EXTERNAL Boost_LIBRARY_DIR: ${Boost_LIBRARY_DIR}")