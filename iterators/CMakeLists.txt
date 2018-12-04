add_executable(
    iterators
    iterators.c
)
add_test(
    NAME Iterators-Run-Loop
    COMMAND iterators loop loop.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)
add_test(
    NAME Iterators-Run-Loop-Callback
    COMMAND iterators loop_cb loop_cb.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)
add_test(
    NAME Iterators-Run-Loop-Iterator
    COMMAND iterators loop loop_iter.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)

add_test(
    NAME Iterators-Compare-Loop-Callback
    COMMAND
    cmp loop.txt loop_cb.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)
add_test(
    NAME Iterators-Compare-Loop-Iterator
    COMMAND
    cmp loop.txt loop_iter.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)

add_test(
    NAME Iterators-Run-Unfolded-Loop
    COMMAND iterators loop2 loop2.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)
add_test(
    NAME Iterators-Run-Unfolded-Loop-Iterator
    COMMAND iterators loop2_iter loop2_iter.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)
add_test(
    NAME Iterators-Compare-Loop-Unfolded
    COMMAND
    cmp loop.txt loop2.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)
add_test(
    NAME Iterators-Compare-Loop-Unfolded-Iterator
    COMMAND
    cmp loop.txt loop2_iter.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)


add_test(
    NAME Iterators-Run-Nested-Loop
    COMMAND iterators nested_loop nested_loop.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)
add_test(
    NAME Iterators-Run-Unwrapped-Nested-Loop
    COMMAND iterators nested_loop2 nested_loop2.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)
add_test(
    NAME Iterators-Run-Nested-Loop-Iterator
    COMMAND iterators nested_loop_iter nested_loop_iter.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)

add_test(
    NAME Iterators-Compare-Nested-Loop-Unfolded
    COMMAND
    cmp nested_loop.txt nested_loop2.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)
add_test(
    NAME Iterators-Compare-Nested-Loop-Iterator
    COMMAND
    cmp nested_loop.txt nested_loop_iter.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)

add_executable(
    iter_recursion
    iter_recursion.c
)
