#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// Tail recursion is just a loop, so consider
// a recursive function that recurse twice
int binsum(const int *x, int from, int to)
{
    // start
    if (to - from > 1) {
        int mid = (from + to) / 2;
        // recurse 1
        int left = binsum(x, from, mid);
        // recurse 2
        int right = binsum(x, mid, to);
        // after recurse 2
        // yield
        printf("x[%d:%d] == %d\n", from, to, left + right);
        return left + right;

    } else {
        // else
        // yield
        printf("x[%d] == %d\n", from, x[from]);
        return x[from];
    }

    assert(false);
}

// FIXME: you can make the stack much more efficient
// if you do not use a linked list where you
// allocated and deallocate all the time...
struct binsum_frame {
    int from, mid, to;
    struct binsum_frame *next;
};

enum binsum_state {
    START,
    RECURSE1,
    RECURSE2,
    ELSE
};
struct binsum_iter {
    const int *x;
    enum binsum_state state;
    struct binsum_frame *frames;
};

static void push_frame(struct binsum_iter *iter,
                       int from, int mid, int to)
{
    struct binsum_frame *frame = malloc(sizeof(struct binsum_frame));
    frame->from = from;
    frame->mid = mid;
    frame->to = to;
    frame->next = iter->frames;
    iter->frames = frame;
}

static void pop_frame(struct binsum_iter *iter)
{
    assert(iter->frames);
    struct binsum_frame *frame = iter->frames;
    iter->frames = frame->next;
    free(frame);
}


void init_binsum_iter(struct binsum_iter *iter,
                      int *x, int from, int to)
{
    iter->x = x;
    iter->state = START;
    iter->frames = 0;
    push_frame(iter, from, from, to);
}
void dealloc_binsum_iter(struct binsum_iter *iter)
{
    struct binsum_frame *frame, *next;
    frame = iter->frames;
    while (frame) {
        next = frame->next;
        free(frame);
        frame = next;
    }
}
struct binsum_result {
    int from, to, val;
};
bool next_binsum_iter(struct binsum_iter *iter,
                      struct binsum_result *res)
{
    while (true) {
        struct binsum_frame *frame = iter->frames;
        if (!frame) return false;

        switch (iter->state) {
            case START:
                if (frame->to - frame->from > 1) {
                    frame->mid = (frame->from + frame->to) / 2;
                    iter->state = RECURSE1;
                } else {
                    iter->state = ELSE;
                }
                break;

            case RECURSE1:
                break;

            case RECURSE2:
                break;

            case ELSE:
                res->from = frame->from;
                res->to   = frame->to;
                res->val  = iter->x[frame->from];
                // return means popping the frame -- we do this before we yield
                pop_frame(iter);
                return true;

            default:
                break;
        }
        free(frame);
    }
}


int main(int argc, const char **argv)
{
    int x[] = { 1, 2, 3, 4, 5 };
    int from = 0, to = 5;
    binsum(x, from, to);
    return EXIT_SUCCESS;
}
