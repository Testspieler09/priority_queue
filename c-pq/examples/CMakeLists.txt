add_executable(basic_usage_min_heap_pq basic_usage_min_heap_pq.c)

target_link_libraries(basic_usage_min_heap_pq
    PRIVATE priority_queue
)

target_include_directories(basic_usage_min_heap_pq
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src
)
