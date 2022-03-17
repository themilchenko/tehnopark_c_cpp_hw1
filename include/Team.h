#ifndef DZ_1_TEAM_H
#define DZ_1_TEAM_H

#include <stdio.h>

struct Team {
    int team_number_;
    char* title_;
    double duration_;
    int num_of_point_;
};

typedef struct Team Team;

/*sort teams*/
void sort_teams(Team** competition, int num_of_teams);

/*swap two teams for sorting*/
void swap_teams(Team **left, Team **right);

/*getting one symbol from input stream*/
char get_char();

/*getting integer num*/
int read_integer();

/*getting double num*/
double read_double();

/*getting string from input stream*/
char* read_string();

/*creating new team*/
Team* create_team(int num, FILE* file);

/*printing team information*/
void print_team(Team* team);

/*deleting team*/
void delete_team(Team* team);

#endif  // DZ_1_TEAM_H
