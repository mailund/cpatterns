add_executable(
    iterators
    iterators
)
add_test(
    NAME Iterators_Run_Loop
    COMMAND iterators loop loop.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)
add_test(
    NAME Iterators_Run_Loop_Callback
    COMMAND iterators loop_cb loop_cb.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)
add_test(
    NAME Iterators_Run_Loop_Iterator
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


