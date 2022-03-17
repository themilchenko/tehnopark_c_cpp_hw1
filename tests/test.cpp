#include <gtest/gtest.h>

extern "C" {
#include "Team.h"
}

TEST(TeamTest, create_true_team) {
    const char *test_case = "12\nElbrus\n12.22\n2\n";
    FILE *stream_case = fmemopen((char *)test_case, strlen(test_case), "r");
    Team *team = create_team(2, stream_case);

    ASSERT_EQ(team->team_number_, 12);
    ASSERT_FALSE(strcmp(team->title_, "Elbrus"));
    ASSERT_DOUBLE_EQ(team->duration_, 12.22);
    ASSERT_EQ(team->num_of_point_, 2);

    delete_team(team);
    fclose(stream_case);
}

TEST(TeamTest, create_false_team) {
    const char *test_case = "a\nSome...\n12point21\nno\n";
    FILE *stream_case = fmemopen((char *)test_case, strlen(test_case), "r");
    Team *team = create_team(2, stream_case);

    ASSERT_EQ(team->team_number_, 0);
    ASSERT_STREQ(team->title_, "Some...");
    ASSERT_EQ(team->duration_, 0);
    ASSERT_EQ(team->num_of_point_, 0);
}

TEST(Team, swap_teams) {
    const char *first_test_case = "2\nMountain\n25.52\n3\n";
    FILE *first_stream_case =
        fmemopen((char *)first_test_case, strlen(first_test_case), "r");

    const char *second_case = "25\nRiver\n30.01\n5\n";
    FILE *second_stream_case =
        fmemopen((char *)second_case, strlen(second_case), "r");

    Team *first_team = (Team *)malloc(sizeof(Team));
    first_team = create_team(0, first_stream_case);

    fclose(first_stream_case);

    Team *second_team = (Team *)malloc(sizeof(Team));
    second_team = create_team(0, second_stream_case);

    fclose(second_stream_case);

    swap_teams(&first_team, &second_team);

    ASSERT_EQ(first_team->team_number_, 25);
    ASSERT_STREQ(first_team->title_, "River");
    ASSERT_DOUBLE_EQ(first_team->duration_, 30.01);
    ASSERT_EQ(first_team->num_of_point_, 5);

    ASSERT_EQ(second_team->team_number_, 2);
    ASSERT_STREQ(second_team->title_, "Mountain");
    ASSERT_DOUBLE_EQ(second_team->duration_, 25.52);
    ASSERT_EQ(second_team->num_of_point_, 3);

    delete_team(first_team);
    delete_team(second_team);
}

TEST(Team, sort_teams) {
    const int size_of_teams = 4;

    const char *first_team_case = "12\nTool\n12.22\n3\n";
    const char *second_team_case = "321\nSteel\n52.22\n6\n";
    const char *third_team_case = "456\nRiver\n33.32\n4\n";
    const char *fourth_team_case = "654\nMoon\n33.30\n4\n";

    FILE *first_stream_case =
        fmemopen((char *)first_team_case, strlen(first_team_case), "r");
    FILE *second_stream_case =
        fmemopen((char *)second_team_case, strlen(second_team_case), "r");
    FILE *third_stream_case =
        fmemopen((char *)third_team_case, strlen(third_team_case), "r");
    FILE *fourth_stream_case =
        fmemopen((char *)fourth_team_case, strlen(fourth_team_case), "r");

    Team **competition = (Team **)malloc(size_of_teams * sizeof(Team *));

    competition[0] = (Team *)malloc(sizeof(Team));
    competition[0] = create_team(0, first_stream_case);

    competition[1] = (Team *)malloc(sizeof(Team));
    competition[1] = create_team(0, second_stream_case);

    competition[2] = (Team *)malloc(sizeof(Team));
    competition[2] = create_team(0, third_stream_case);

    competition[3] = (Team *)malloc(sizeof(Team));
    competition[3] = create_team(0, fourth_stream_case);

    fclose(first_stream_case);
    fclose(second_stream_case);
    fclose(third_stream_case);
    fclose(fourth_stream_case);

    sort_teams(competition, size_of_teams);

    ASSERT_EQ(competition[0]->team_number_, 321);
    ASSERT_STREQ(competition[0]->title_, "Steel");
    ASSERT_DOUBLE_EQ(competition[0]->duration_, 52.22);
    ASSERT_EQ(competition[0]->num_of_point_, 6);

    ASSERT_EQ(competition[1]->team_number_, 654);
    ASSERT_STREQ(competition[1]->title_, "Moon");
    ASSERT_DOUBLE_EQ(competition[1]->duration_, 33.30);
    ASSERT_EQ(competition[1]->num_of_point_, 4);

    ASSERT_EQ(competition[2]->team_number_, 456);
    ASSERT_STREQ(competition[2]->title_, "River");
    ASSERT_DOUBLE_EQ(competition[2]->duration_, 33.32);
    ASSERT_EQ(competition[2]->num_of_point_, 4);

    ASSERT_EQ(competition[3]->team_number_, 12);
    ASSERT_STREQ(competition[3]->title_, "Tool");
    ASSERT_DOUBLE_EQ(competition[3]->duration_, 12.22);
    ASSERT_EQ(competition[3]->num_of_point_, 3);

    for (int i = 0; i < size_of_teams; ++i) {
        delete_team(competition[i]);
    }
    free(competition);
}
