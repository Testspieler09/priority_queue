function(add_pq_example name)
    add_executable(${name} ${name}.c)

    target_link_libraries(${name}
        PRIVATE priority_queue
    )

    target_include_directories(${name}
       PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src
    )
endfunction()

add_pq_example(basic_usage_min_heap_pq)
add_pq_example(basic_usage_fib_heap_pq)
