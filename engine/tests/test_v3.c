#ifndef TEST_V3_H
#define TEST_V3_H

#include <maths/vector3.h>

#include <stdio.h>
#include <stdlib.h>

#define CSRGE_ASSERT(expr) do \
if (!(expr)) \
{  \
    fprintf(stderr, "Assertion failed: %s\n"    \
                    "  in file %s, line %d\n",  \
            #expr, __FILE__, __LINE__);         \
    exit(1);                                    \
} \
while(0)

static void test_add()
{
    V3 a = { 0, 0, 0 };
    V3 b = { 1, 2, 3 };
    V3 c = v3_add_v3(a, b);

    CSRGE_ASSERT(c.x == 1 && c.y == 2 && c.z == 3);
}

int main()
{
    test_add();
    return 0;
}

#endif