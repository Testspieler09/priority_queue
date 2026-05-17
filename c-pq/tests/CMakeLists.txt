set(TEST_SOURCES
				test_insert_extract.c
				test_decrease_key.c
				test_remove.c
				test_merge.c
)

foreach(test_src ${TEST_SOURCES})
	get_filename_component(test_name ${test_src} NAME_WE)

	add_executable(${test_name} ${test_src})
	target_link_libraries(${test_name} PRIVATE priority_queue)
	target_include_directories(${test_name} PRIVATE
					${CMAKE_CURRENT_SOURCE_DIR}/../src
	)
endforeach()
