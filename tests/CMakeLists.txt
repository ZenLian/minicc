# add_subdirectory(recipes)

add_executable(mutex_test mutex_test.cc)
target_link_libraries(mutex_test pthread)
add_test(NAME mutex_test COMMAND mutex_test)

# add_executable(blocking_queue_test BlockingQueue_test.cc)
# target_link_libraries(blocking_queue_test pthread)

add_executable(count_down_latch_test CountDownLatch_test.cc)
target_link_libraries(count_down_latch_test minicc)
