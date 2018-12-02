add_executable(
    iterators
    iterators
)
add_test(
    NAME "Run Iterators"
    COMMAND iterators
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
)
#add_test(
#    NAME Iterators-RUN
#    COMMAND
#    sh -c "$<TARGET_FILE:match_test> naive the test-data/modest-proposal.txt > test-data/naive-modest-match.txt"
#    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/iterators"
#)

