#include "Team.h"

#include <stdlib.h>
#include <string.h>

Team *create_team(int num, FILE *file) {
    Team *element = (Team *)malloc(sizeof(Team));

    if (!element) {
        return NULL;
    }

    element->team_number_ = 0;
    element->title_ = NULL;
    element->duration_ = 0;
    element->num_of_point_ = 0;

    printf("### Enter the information about %d team ###\n", num);

    printf("+ Enter the number of team: ");
    element->team_number_ = read_integer(file);

    printf("+ Enter the name of team: ");
    element->title_ = read_string(file);

    if (!element->title_) {
        free(element);
        return NULL;
    }

    printf("+ Enter the duration on track: ");
    element->duration_ = read_double(file);

    printf("+ Enter the num of points on track: ");
    element->num_of_point_ = read_integer(file);

    return element;
}

void print_team(Team *team) {
    if (!team) {
        return;
    }

    printf("=========================\n");
    printf("Number: %d\n", team->team_number_);
    printf("Name: %s\n", team->title_);
    printf("Duration: %.2f minute(s)\n", team->duration_);
    printf("Points: %d\n", team->num_of_point_);
    printf("=========================\n");
}

void delete_team(Team *team) {
    if (!team) {
        return;
    }

    if (team->title_) {
        free(team->title_);
        team->title_ = NULL;
    }
    free(team);
}

char get_char(FILE *file) {
    char symbol = '\0';
    int result = 0;

    do {
        result = fscanf(file, "%c", &symbol);
    } while (result != 1);
    return symbol;
}

char *read_string(FILE *file) {
    struct String {
        char *str_;
        size_t size_;
        int capacity_;
    } string = {NULL, 0, 0};

    int symbol = '\0';
    char *copy_str = NULL;

    while (symbol = get_char(file), symbol != EOF && symbol != '\n') {
        int is_memory_allocate = 0;

        /*if buffer is empty*/
        if (string.capacity_ == 0) {
            string.capacity_ = 1;
            is_memory_allocate = 1;
            /*if size more than capacity*/
        } else if (string.capacity_ > 0 &&
                   string.size_ + 1 >= string.capacity_) {
            string.capacity_ *= 2;
            is_memory_allocate = 1;
        } else {
            is_memory_allocate = 0;
        }

        if (is_memory_allocate) {
            copy_str = (char *)malloc((string.capacity_ + 1) * sizeof(char));
            if (string.str_) {
                copy_str =
                    strncpy(copy_str, string.str_, string.size_ * sizeof(char));
                free(string.str_);
                string.str_ = NULL;
            }
            string.str_ = copy_str;
        }
        string.str_[string.size_++] = symbol;
        string.str_[string.size_] = '\0';
    }
    return string.str_;
}

int read_integer(FILE *file) {
    int symbol = '\0';
    int result = 0;

    while (symbol = get_char(file), symbol != EOF && symbol != '\n') {
        if (symbol >= '0' && symbol <= '9') {
            result = result * 10 + symbol - '0';
        } else {
            char *str_to_delete = read_string(file);
            free(str_to_delete);
            return 0;
        }
    }

    return result;
}

double read_double(FILE *file) {
    int symbol = '\0';
    double result = 0;
    int after_point = 0;
    double exp = 10;

    while (symbol = get_char(file), symbol != EOF && symbol != '\n') {
        if ((symbol >= '0' && symbol <= '9') && !after_point) {
            result = result * 10 + symbol - '0';
        } else if ((symbol == '.' || symbol == ',') && !after_point) {
            after_point = 1;
        } else if (after_point) {
            result = result + (double)((symbol - '0') / exp);
            exp *= 10;
        } else {
            char *str_to_delete = read_string(file);
            free(str_to_delete);
            return 0;
        }
    }
    return result;
}

void swap_teams(Team **left, Team **right) {
    if (*left && *right && *left != *right) {
        Team *temp = *right;
        *right = *left;
        *left = temp;
    }
}

void sort_teams(Team **competition, const int num_of_teams) {
    for (int i = 0; i < num_of_teams; ++i) {
        for (int j = 0; j < num_of_teams - i - 1; ++j) {
            if ((competition[j]->num_of_point_ <
                 competition[j + 1]->num_of_point_) ||
                ((competition[j]->num_of_point_ ==
                  competition[j + 1]->num_of_point_) &&
                 (competition[j]->duration_ > competition[j + 1]->duration_))) {
                swap_teams(&competition[j], &competition[j + 1]);
            }
        }
    }
}
