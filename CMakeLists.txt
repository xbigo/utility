cmake_minimum_required(VERSION 3.14)

project(ApeUtility
	VERSION "0.2.0"
	DESCRIPTION "Language facilities, generic helpers, follow the STL style "
	LANGUAGES CXX)

if (NOT DEFINED APE_SUPERPROJECT)
	find_package(Ape 0.2.0 QUIET)
	if (NOT Ape_FOUND)
		find_package(ApeAmun 0.2.0 QUIET)
		if (NOT ApeAmun_FOUND)
			include(FetchContent)
			FetchContent_Declare( amun
				GIT_REPOSITORY https://github.com/xbigo/amun.git
				GIT_TAG v0.2.0
				)
			FetchContent_MakeAvailable(amun)
			include(${amun_SOURCE_DIR}/lib/amun/amun.cmake)
		endif()
		amun_fetch_lib( ape_config
			GIT_REPOSITORY ../config.git
			GIT_TAG v0.2.0
			)
		add_library(ape_config INTERFACE)
		target_include_directories(ape_config INTERFACE "${ape_config_SOURCE_DIR}/include")
	endif()
endif()
amun_disable_build_in_source()

amun_check_build(ESTL NORMAL INSTALL TEST)

get_target_property(ape_config_include_dir ape_config INTERFACE_INCLUDE_DIRECTORIES)

if(${ESTL_NORMAL})
	amun_fetch_lib( gsl
		GIT_REPOSITORY ../GSL.git
		GIT_TAG v3.1.0
		)
	set (gsl_include_dir "${gsl_SOURCE_DIR}/include")

	set(source_files all.hpp operators.hpp)
	list(TRANSFORM source_files PREPEND "include/ape/utility/" )

	add_library(ape_utility INTERFACE)
	add_library(Ape::utility ALIAS ape_utility )
	amun_enable_features(ape_utility FEATURES INTERFACE cxx_std_17)

	target_compile_definitions(ape_utility INTERFACE
		$<$<CXX_COMPILER_ID:MSVC>:
		_SCL_SECURE_NO_WARNINGS
		_SILENCE_CXX17_UNCAUGHT_EXCEPTION_DEPRECATION_WARNING
		>)
	target_include_directories(ape_utility INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
	target_sources(ape_utility INTERFACE ${source_files})

	amun_fake_project(ape_utility 
		SOURCES ${source_files} src/dummy.cpp
		INCLUDES include  ${gsl_include_dir} ${ape_config_include_dir}
		FOLDER Libs)
endif()

if(${ESTL_INSTALL})
	amun_get_cmake_install_dir(ESTL_INSTALL_DIR)

	if (NOT DEFINED APE_SUPERPROJECT)
		amun_install_targets(${ESTL_INSTALL_DIR} ape_utility)
		amun_install_config_version(${ESTL_INSTALL_DIR} NOARCH)
	endif()

	install(DIRECTORY include/ DESTINATION include)
endif()

if(${ESTL_TEST})
	amun_enable_testing()
	add_subdirectory(test)
endif()


