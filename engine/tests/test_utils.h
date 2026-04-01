#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#define CSRGE_ASSERT(expr) do \
if (!(expr)) \
{  \
    fprintf(stderr, "Assertion failed: %s\n"    \
                    "  in file %s, line %d\n",  \
            #expr, __FILE__, __LINE__);         \
    exit(1);                                    \
} \
while(0)

#endif