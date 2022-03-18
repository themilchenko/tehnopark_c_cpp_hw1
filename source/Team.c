#include "Team.h"

#include <stdlib.h>
#include <string.h>

Team *create_team(int num, FILE *file) {
    Team *element = (Team *)calloc(1, sizeof(Team));

    if (!element) {
        return NULL;
    }

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

void print_team(const Team *team) {
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
    free(team->title_);
    free(team);
}

void swap_teams(Team **left, Team **right) {
    if (*left && *right && *left != *right) {
        Team *temp = *right;
        *right = *left;
        *left = temp;
    }
}

void sort_teams(Team **competition, const int num_of_teams) {
    if (!competition) {
        return;
    }

    for (int i = 0; i < num_of_teams; ++i) {
        for (int j = 0; j < num_of_teams - i - 1; ++j) {
            if (!competition[j] || !competition[j + 1]) {
                return;
            }

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
