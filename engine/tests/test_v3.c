#ifndef TEST_V3_H
#define TEST_V3_H

#include "test_utils.h"

#include <maths/vector3.h>

#include <stdio.h>
#include <stdlib.h>

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