
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef int (*report_callback)(FILE *outfile, const char *str, ...);

// Is it possible to make a 'yield' macro?


#pragma mark simple loops

void loop(FILE *outfile)
{
    for (int i = 0; i < 10; ++i) {
        fprintf(outfile, "Iteration %i\n", i);
    }
}

void loop_cb(FILE *outfile,
             report_callback callback)
{
    for (int i = 0; i < 10; ++i) {
        callback(outfile, "Iteration %i\n", i);
    }
}

struct loop_iter {
    int i;
};
struct loop_result {
    int i;
};

void init_loop_iter(struct loop_iter *iter)
{
    iter->i = 0;
}
void dealloc_loop_iter(struct loop_iter *iter)
{
    // nothing
}

bool next_loop(struct loop_iter *iter,
               struct loop_result *res)
{
    // The loop is initialised (int i = 0) in the
    // iteration initialisation, but the loop
    // variable, i, should be incremented after
    // we yield. We need to report the old i
    // but continue from the next i.
    if (iter->i < 10) {
        res->i = iter->i;
        iter->i++;
        return true;
    }
    return false;
}

void loop_iteration(FILE *outfile)
{
    struct loop_iter iter;
    struct loop_result result;
    
    init_loop_iter(&iter);
    while (next_loop(&iter, &result)) {
        fprintf(outfile, "Iteration %d\n", result.i);
    }
    dealloc_loop_iter(&iter);
}

#pragma mark simple loop unwrapped

void loop2(FILE *outfile)
{
    //init:
    int i = 0;
loop:
    // report
    fprintf(outfile, "Iteration %i\n", i);
    // update frame
    i++;
    // next state
    if (i < 10) goto loop;
}

enum loop2_labels { INIT, LOOP, DONE };
struct loop2_iter {
    // Execution pointer
    enum loop2_labels state;
    // Function call frame
    int i;
};

bool next_loop2(struct loop2_iter *iter,
                struct loop_result *res)
{
    while (true) {
        switch(iter->state) {
            case INIT:
                iter->i = 0;
                iter->state = LOOP;
                break;

            case LOOP:
                // prepare report
                res->i = iter->i;

                // update frame
                iter->i++;
                // update state
                if (!(iter->i < 10))
                    iter->state = DONE;

                // yield
                return true;

            case DONE:
                return false;
        }
    }
}

void init_loop2_iter(struct loop2_iter *iter)
{
    iter->state = INIT;
}
void dealloc_loop2_iter(struct loop2_iter *iter)
{
    // nothing
}

void loop2_iteration(FILE *outfile)
{
    struct loop2_iter iter;
    struct loop_result result;

    init_loop2_iter(&iter);
    while (next_loop2(&iter, &result)) {
        fprintf(outfile, "Iteration %d\n", result.i);
    }
    dealloc_loop2_iter(&iter);
}

#pragma mark nested loops

void nested_loop(FILE *outfile)
{
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            fprintf(outfile, "Iteration %i x %i\n", i, j);
        }
    }
}

void nested_loop2(FILE *outfile)
{
    // frame
    int i, j;

    // init:
    i = 0;

outer_loop:
    j = 0;

inner_loop:
    // report
    fprintf(outfile, "Iteration %i x %i\n", i, j);
    // update frame
    j++;
    // update state
    if (j < 10) goto inner_loop;

    // outer loop
    // update frame
    i++;
    // update state
    if (i < 10) goto outer_loop;

}


enum nested_loop_state {
    NESTED_INIT,
    NESTED_OUTER_LOOP,
    NESTED_INNER_LOOP_PRE_REPORT,
    NESTED_INNER_LOOP_POST_REPORT,
    NESTED_DONE
};
struct nested_loop_iter {
    enum nested_loop_state state;
    int i;
    int j;
};
struct nested_loop_result {
    int i;
    int j;
};

void init_nested_loop_iter(struct nested_loop_iter *iter)
{
    iter->state = NESTED_INIT;
}
void dealloc_nested_loop_iter(struct nested_loop_iter *iter)
{
    // nothing
}

bool next_nested_loop(struct nested_loop_iter *iter,
                      struct nested_loop_result *res)
{
    while (true) {
        switch(iter->state) {
            case NESTED_INIT:
                iter->i = 0;
                iter->state = NESTED_OUTER_LOOP;
                break;

            case NESTED_OUTER_LOOP:
                iter->j = 0;
                iter->state = NESTED_INNER_LOOP_PRE_REPORT;
                break;

            case NESTED_INNER_LOOP_PRE_REPORT:
                // Frame is already correct, so just report
                // and update the execution state
                res->i = iter->i;
                res->j = iter->j;
                iter->state = NESTED_INNER_LOOP_POST_REPORT;
                // Yield
                return true;

            case NESTED_INNER_LOOP_POST_REPORT:
                iter->j++;
                if (iter->j < 10) {
                    iter->state = NESTED_INNER_LOOP_PRE_REPORT;
                    break;
                }
                iter->i++;
                if (iter->i < 10) {
                    iter->state = NESTED_OUTER_LOOP;
                    break;
                }
                iter->state = NESTED_DONE;
                break;

            case NESTED_DONE:
                return false;
        }
    }
}

void nested_loop_iteration(FILE *outfile)
{
    struct nested_loop_iter iter;
    struct nested_loop_result result;
    
    init_nested_loop_iter(&iter);
    while (next_nested_loop(&iter, &result)) {
        fprintf(outfile, "Iteration %i x %i\n", result.i, result.j);
    }
    dealloc_nested_loop_iter(&iter);
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        // LCOV_EXCL_START
        fprintf(stderr, "Need two arguments, the function and the output file\n");
        return EXIT_FAILURE;
        // LCOV_EXCL_STOP
    }
    const char *alg = argv[1];
    const char *fname = argv[2];
    
    FILE *outfile = fopen(fname, "w");
    if (!outfile) {
        // LCOV_EXCL_START
        fprintf(stderr, "Could not open %s\n", fname);
        return EXIT_FAILURE;
        // LCOV_EXCL_STOP
    }
    
    if (strcmp(alg, "loop") == 0) {
        loop(outfile);
    } else if (strcmp(alg, "loop_cb") == 0) {
        loop_cb(outfile, fprintf);
    } else if (strcmp(alg, "loop_iter") == 0) {
        loop_iteration(outfile);
    } else if (strcmp(alg, "loop2") == 0) {
        loop2(outfile);
    } else if (strcmp(alg, "loop2_iter") == 0) {
        loop2_iteration(outfile);

    } else if (strcmp(alg, "nested_loop") == 0) {
        nested_loop(outfile);
    } else if (strcmp(alg, "nested_loop2") == 0) {
        nested_loop2(outfile);
    } else if (strcmp(alg, "nested_loop_iter") == 0) {
        nested_loop_iteration(outfile);


    } else {
        fprintf(stderr, "Unknown algorithm %s\n", alg);
        fclose(outfile);
        return EXIT_FAILURE;
    }
    
    fclose(outfile);
    
    return EXIT_SUCCESS;
}
