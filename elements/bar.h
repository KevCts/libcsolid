#ifndef CSOLID_BAR_H
#define CSOLID_BAR_H

#include "common.h"

typedef struct {
    node *n1, *n2;
    section* sec;
    material* mat;
} bar;

bar* create_bar(node*, node*, section*, material*);

coomat* bar_stiffness_matrix(bar*);

bool bar_replace_node(bar*, node*, node*);

void add_bar(size_t, size_t, size_t, size_t);

void print_bar(bar* bar_to_print);

#endif
