macro (add_test_OVU name)
	add_executable(${name} ${name}.cpp)
	add_test(${name} ${name})

	set_property(TEST ${name} PROPERTY
		ENVIRONMENT "LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/backend/OVU"
	)

	target_link_libraries(${name} Qt5::Test OVUbackend)
endmacro (add_test_OVU)
