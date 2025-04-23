add_library(MathFunctions MathFunctions.cpp)

target_include_directories(MathFunctions PUBLIC wordchecker_compiler_flags)

option(USE_MYMATH "Use WordChecker provided math implementation" OFF)

if(USE_MYMATH)
	target_include_directories(SqrtLibrary PUBLIC wordchecker_compiler_flags)

	target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")

	add_library(SqrtLibrary STATIC
				mysqrt.cpp
			    )

	target_link_libraries(MathFunctions PRIVATE SqrtLibrary)
endif()

target_include_directories(MathFunctions
						   INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
						   )

