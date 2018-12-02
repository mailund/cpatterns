add_executable(
    iterators
    iterators
)
add_test(
    NAME Iterators_Run_Loop
    COMMAND sh -c "$<TARGET_FILE:iterators> loop > loop.txt"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)
add_test(
    NAME Iterators_Run_Loop_Iterator
    COMMAND sh -c "$<TARGET_FILE:iterators> loop_iter > loop_iter.txt"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)
add_test(
    NAME Iterators-Compare_Loop
    COMMAND
    cmp loop.txt loop_iter.txt
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)

