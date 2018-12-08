#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <cstdio>

#define assertTest(expression)\
    do {\
        if (!(expression)) {\
            printf("Assertion failed at %s:%d: "\
                   "in function \"%s\" "\
                   "with assertion \"%s\".\n",\
                   __FILE__, __LINE__, __func__, (#expression));\
        }\
    } while (0)

#define assertException(command, exception)\
    do {\
        try {\
            (command);\
            assertTest(false);\
        } catch (const exception &ex) {\
        } catch (...) {\
            assertTest(false);\
        }\
    } while (0)

#define assertNumberInArray(array, size, number)\
    do {\
        bool notFound = true;\
        for (int _i = 0; _i < (size); _i++) {\
            if ((array)[_i] == (number)) {\
                notFound = false;\
                break;\
            }\
        }\
        assertTest(!notFound);\
    } while (0)

#endif //TESTUTILS_H
