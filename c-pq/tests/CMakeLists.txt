set(MIN_HEAP_TEST_SOURCES
    test_min_heap_insert_extract.c
    test_min_heap_pq_decrease_key.c
    test_min_heap_remove.c
    test_min_heap_merge.c
)

set(FIB_HEAP_TEST_SOURCES
    test_fib_heap_insert_extract.c
    test_fib_heap_pq_decrease_key.c
    test_fib_heap_remove.c
    test_fib_heap_merge.c
)

foreach(test_src ${MIN_HEAP_TEST_SOURCES} ${FIB_HEAP_TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} PRIVATE priority_queue)
    target_include_directories(${test_name} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
    )
endforeach()
