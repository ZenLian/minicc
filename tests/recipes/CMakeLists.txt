add_executable(mutex_test mutex_test.cc)
target_link_libraries(mutex_test pthread)
add_test(NAME mutex_test COMMAND mutex_test)
