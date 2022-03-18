#include "Team.h"

#include <stdlib.h>
#include <string.h>

int main() {
    printf("Enter the num of teams in competition: ");
    int num_of_teams = read_integer(stdin);
    Team** competition = NULL;
    competition = (Team**)malloc(num_of_teams * sizeof(Team*));
    if (competition) {
        for (int i = 0; i < num_of_teams; ++i) {
            competition[i] = create_team(i + 1, stdin);
        }

        printf("\n--------Before sorting--------\n");
        for (int i = 0; i < num_of_teams; ++i) {
            print_team(competition[i]);
        }

        printf("\n--------After sorting--------\n");
        sort_teams(competition, num_of_teams);

        for (int i = 0; i < num_of_teams; ++i) {
            print_team(competition[i]);
        }

        for (int i = 0; i < num_of_teams; ++i) {
            delete_team(competition[i]);
        }

        free(competition);
    } else {
        perror("System error");
    }
    return 0;
}
