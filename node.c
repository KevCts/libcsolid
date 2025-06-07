#include "model.h"
#include <math.h>
#include <stdio.h>


void add_node(double x, double y, double z) {
    if (model.nodes_count + 1 > model.nodes_capacity) {
        model.nodes = realloc(model.nodes, (++model.nodes_capacity) * sizeof(node));
        model.forces = realloc(model.forces, (model.nodes_capacity) * 6 * sizeof(double));
        model.displacements = realloc(model.displacements, (model.nodes_capacity) * 6 * sizeof(double));
        model.boundaries = realloc(model.boundaries, (model.nodes_capacity) * 6 * sizeof(boundary));
    }

    model.nodes[model.nodes_count].id = model.nodes_count;
    model.nodes[model.nodes_count].x = x;
    model.nodes[model.nodes_count].y = y;
    model.nodes[model.nodes_count].z = z;
    for(int i = 0; i < 6; i++){
        model.boundaries[model.nodes_count + i].is_set = false;
        model.boundaries[model.nodes_count + i].value = 0;
        model.forces[model.nodes_count + i] = 0;
    }
    model.nodes_count++;
}

void set_boundary(size_t i, direction dir, double value) {
    if (i < model.nodes_count) {
        model.boundaries[6 * i + dir].is_set = true;
        model.boundaries[6 * i + dir].value = value;
    }
}

void set_force(size_t i, direction dir, double value) {
    if (i < model.nodes_count) {
        model.forces[6 * i + dir] = value;
    }
}

void edit_node(size_t i, double x, double y, double z) {
    if (model.nodes_count > i) {
        model.nodes[i].x = x;
        model.nodes[i].y = y;
        model.nodes[i].z = z;
    }
}

void list_nodes() {
    for (size_t i = 0; i < model.nodes_count; i++) {
        printf("|\t Node : %ld\t|\tx = %lf\t|\ty = %lf\t|\tz = %lf\t|\n", i, model.nodes[i].x, model.nodes[i].y, model.nodes[i].z);
    }
}

void list_boundaries() {
    for (size_t i = 0; i < model.nodes_count; i++) {
        for(int j = 0; j < 6; j++) {
            if (model.boundaries[6*i + j].is_set) {
                printf("|\t Node : %ld\t|\t", i);
                switch (j) {
                    case UX:
                        printf("UX : %lf\t|\n", model.boundaries[6*i+j].value);
                        break;
                    case UY:
                        printf("UY : %lf\t|\n", model.boundaries[6*i+j].value);
                        break;
                    case UZ:
                        printf("UZ : %lf\t|\n", model.boundaries[6*i+j].value);
                        break;
                    case RX:
                        printf("RX : %lf\t|\n", model.boundaries[6*i+j].value);
                        break;
                    case RY:
                        printf("RY : %lf\t|\n", model.boundaries[6*i+j].value);
                        break;
                    case RZ:
                        printf("RZ : %lf\t|\n", model.boundaries[6*i+j].value);
                        break;
                }
            }
        }
    }
}

void list_forces() {
    for (size_t i = 0; i < model.nodes_count; i++) {
        for(int j = 0; j < 6; j++) {
            printf("|\t Node : %ld\t|\t", i);
            switch (j) {
                case UX:
                    printf("UX : %lf\t|\n", model.forces[6*i+j]);
                    break;
                case UY:
                    printf("UY : %lf\t|\n", model.forces[6*i+j]);
                    break;
                case UZ:
                    printf("UZ : %lf\t|\n", model.forces[6*i+j]);
                    break;
                case RX:
                    printf("RX : %lf\t|\n", model.forces[6*i+j]);
                    break;
                case RY:
                    printf("RY : %lf\t|\n", model.forces[6*i+j]);
                    break;
                case RZ:
                    printf("RZ : %lf\t|\n", model.forces[6*i+j]);
                    break;
            }
        }
    }
}

void replace_node(size_t i, size_t j) {
    if(i < model.nodes_count && j < model.nodes_count) {
        node* n_old = model.nodes + i;
        node* n_new = model.nodes + j;

        for (size_t k = 0; k < model.elements_count; k++) {
            element_replace_node(model.elements + k, n_old, n_new);
        }

        model.nodes[i] = model.nodes[j];
        model.nodes[i].id = i;
    }
}

void delete_node(size_t i) {
    if(i < model.nodes_count) {
        replace_node(i, model.nodes_count - 1);
        model.nodes_count--;
    }
}

double distance(node* a, node* b) {
    return sqrt(((a->x - b->x) * (a->x - b->x)) + ((a->y - b->y) * (a->y - b->y)) + ((a->z - b->z) * (a->z - b->z)));
}
