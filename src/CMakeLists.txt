add_library(minicc
    ./CountDownLatch.cc
    )
target_link_libraries(minicc pthread)
