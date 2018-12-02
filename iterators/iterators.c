
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef int (*report_callback)(FILE *outfile, const char *str, ...);

// Is it possible to make a 'yield' macro?


#pragma simple loops

void loop(FILE *outfile)
{
    for (int i = 0; i < 10; ++i) {
        fprintf(outfile, "Iteration %i\n", i);
    }
}

void loop_cb(
    FILE *outfile,
    report_callback callback
) {
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

bool next_loop(
    struct loop_iter *iter,
    struct loop_result *res
) {
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
    } else {
        fprintf(stderr, "Unknown algorithm %s\n", alg);
        fclose(outfile);
        return EXIT_FAILURE;
    }
    
    fclose(outfile);
    
    return EXIT_SUCCESS;
}
