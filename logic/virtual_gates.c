//
// Created by pepsipu on 5/28/19.
//

#include "virtual_gates.h"
#include <string.h>

char *or(char *a, char *b) {
    if (!strcmp(a, "1") || !strcmp(b, "1")) {
        return "1";
    }
    return "0";
}

char *and(char *a, char *b) {
    if (!strcmp(a, "1") && !strcmp(b, "1")) {
        return "1";
    }
    return "0";
}

char *not(char *a) {
    if (!strcmp(a, "0")) {
        return "1";
    }
    return "0";
}