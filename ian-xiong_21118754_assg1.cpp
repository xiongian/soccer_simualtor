/*  Name: Ian Xiong
    ID: 21118754
    Date: 09/21/24
    Course: SYDE 121
    Room #: RCH 301
    Assignment #1
    Filename: ian-xiong_21118754_assg1.cpp
    Project Name: Soccer Simulator

    Purpose: Simulates a soccer match with 30 events with chances of an open shot, free kick, or penalty.
    Scenarios include scoring goals, blocked by goalkeeper, missing the target, or blocked by a front defender.
    Displays statistics at halftime and fulltime.

    Edit 1: 09/21/24
    Tested to see if team determiner worked. Ran the program and the the function "team_test" works.

    Edit 2: 09/22/24
    Added base structure for multiple functions testing open shot, freekicks, and penalties. Tested values for open_shot function by limiting event_num options to 1 and 2
    and outputting play by play. Tested values 1 and 2 for event_num. The function open_shot works and outputs a random event.

    Edit 3: 09/23/24
    Had trouble with the game producing the same values everytime. I changed the modulo back to 6, and tested values
    of "freekick" and "penalty" under those respective functions, and figured out that it wasn't generating a new seed.
    I fixed it by moving srand(null) outside of the for loop.

    Created function output_stats that prints out halftime and fulltime stats. Added a nested for loop to simulate two halves of 15
    rounds, but had issues running the second half of 15 events. Moved the half_counter outside of the inner for loop in run_soccer_simulator
    so that it would count properly and not reset to zero.

    Shots blocked isn't tracking right. Limited values for event_num to be 1 and 2, added shots_blocked counter to case 1.

    Edit 4: 09/25/24
    Completed the free_kick() and penalty() and foul_checker() functions. Did memory testing and issues arise with shots blocked and shots on goal.
    Adjusted parts of open_shot(), free_kick(), and penalty(). Checked again and stats match up.
    */

// Imports librarys
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
using namespace std;

// Global constants
const int TOTAL_NUM_OF_EVENTS = 15;
const int TOTAL_NUM_OF_HALVES = 2;

// Global variables
char team;
int goals_A = 0;
int goals_B = 0;
int shots_on_goal_A = 0;
int shots_on_goal_B = 0;
int shots_off_goal_A = 0;
int shots_off_goal_B = 0;
int shots_blocked_A = 0;
int shots_blocked_B = 0;
int fouls_A = 0;
int fouls_B = 0;
int yellow_cards_A = 0;
int yellow_cards_B = 0;
int red_cards_A = 0;
int red_cards_B = 0;

// Tests if event involves team A or team B
char team_test ( int event_num )
{
    team = ( event_num % 2 == 1 ) ? 'A' : 'B';
    return team;
}

// Generates a 4-case scenario for an open shot and counts goals, shots on goal, shots off goal, and shots blocked
int open_shot ()
{
    int possible_goal = rand () % 4;

    switch ( possible_goal )
    {
    case 0:
        ( team == 'A' ) ? goals_A ++, shots_on_goal_A ++ : goals_B ++, shots_on_goal_B ++;
        cout << "A player from Team " << team << " has scored an absolute banger of a goal!" << endl;
        break;
    case 1:
        ( team == 'A' ) ? shots_on_goal_A ++ : shots_on_goal_B ++;
        cout << "Close! Team " << team << " shot was saved by the fantastic goalkeeper!" << endl;
        break;
    case 2:
        ( team == 'A' ) ? shots_off_goal_A ++ : shots_off_goal_B ++;
        cout << "Way off! Team " << team << " misses the goal completely!" << endl;
        break;
    case 3:
        ( team == 'A' ) ? shots_blocked_A ++ : shots_blocked_B ++;
        cout << "Blocked! Team " << team << "'s shot is rejected by a front defender!" << endl;
        break;
    }

    return 0;
}

// Generates a red card or yellow card or no card for free kicks and penalties
void foul_checker ()
{
    int possible_card = rand () % 3;
    switch ( possible_card )
    {
    case 1:
        ( team == 'A' ) ? yellow_cards_A ++ : yellow_cards_B ++;
        cout << "YELLOW CARD! ";
        break;
    case 2:
        ( team == 'A' ) ? red_cards_A ++ : red_cards_B ++;
        cout << "RED CARD! ";
        break;
    }
}

// Generates a 4-case scenario for an free kick and counts goals, shots on goal, shots off goal, and shots blocked
int free_kick ()
{
    int possible_goal = rand () % 4;

    // Checks if a card is given
    foul_checker ();

    switch ( possible_goal )
    {
    case 0:
        ( team == 'A' ) ? goals_A ++, shots_on_goal_A ++ : goals_B ++, shots_on_goal_B ++;
        cout << "Free kick! A striker from Team " << team << " has scored a bullet into the top right corner!" << endl;
        break;
    case 1:
        ( team == 'A' ) ? shots_on_goal_A ++ : shots_on_goal_B ++;
        cout << "Free kick! Team " << team << "'s shot was is BLOCKED by the fantastic goalkeeper!" << endl;
        break;
    case 2:
        ( team == 'A' ) ? shots_off_goal_A ++ : shots_off_goal_B ++;
        cout << "Free kick! Team " << team << "'s free kick misses the goal completely!" << endl;
        break;
    case 3:
        ( team == 'A' ) ? shots_blocked_A ++ : shots_blocked_B ++;
        cout << "Free kick! Team " << team << "'s shot is REJECTED by the wall!" << endl;
        break;
    }

    ( team == 'A' ) ? fouls_A++ : fouls_B++;

    return 0;
}

// // Generates a 3-case scenario for an penalty and counts goals, shots on goal, shots off goal, and shots blocked
int penalty ()
{
    int possible_goal = rand () % 3;

    // Checks if card is given
    foul_checker ();

    switch ( possible_goal )
    {
    case 0:
        ( team == 'A' ) ? goals_A ++, shots_on_goal_A ++ : goals_B ++, shots_on_goal_B ++;
        cout << "Penalty! Team " << team << " scores!" << endl;
        break;
    case 1:
        ( team == 'A' ) ? shots_on_goal_A ++ : shots_on_goal_B ++;
        cout << "Penalty! Team " << team << "'s shot was denied by the goalkeeper!" << endl;
        break;
    case 2:
        ( team == 'A' ) ? shots_off_goal_A ++ : shots_off_goal_B ++;
        cout << "Penalty! Team " << team << "'s shot misses the goal completely!" << endl;
        break;
    }

    ( team == 'A' ) ? fouls_A ++ : fouls_B ++;

    return 0;
}

// Outputs the statistics during game halftime and fulltime
void output_stats ( int half_counter )
{
    string stat_header = ( half_counter == TOTAL_NUM_OF_HALVES ) ? "FULLTIME STATS" : "HALFTIME STATS";
    cout << "---------------------" << stat_header << "---------------------" << endl;
    cout << "Current score:    Team A " << goals_A << " - " << goals_B << " Team B" << endl;
    cout << "Shots on goal:    Team A " << shots_on_goal_A << " - " << shots_on_goal_B << " Team B" << endl;
    cout << "Shots off goal:   Team A " << shots_off_goal_A << " - " << shots_off_goal_B << " Team B" << endl;
    cout << "Shots blocked:    Team A " << shots_blocked_A << " - " << shots_blocked_B << " Team B" << endl;
    cout << "Fouls:            Team A " << fouls_A << " - " << fouls_B << " Team B" << endl;
    cout << "Yellow cards:     Team A " << yellow_cards_A << " - " << yellow_cards_B << " Team B" << endl;
    cout << "Red cards:        Team A " << red_cards_A << " - " << red_cards_B << " Team B" << endl;
    cout << "---------------------" << stat_header << "---------------------" << endl;
}

// The simulator function that initiates the game
int run_soccer_simulator ()
{
    // Generates a seed from time
    srand ( time (0) );
    int half_counter = 0;

    // Simulates two halves of 15 rounds
    for ( int halves = 1; halves <= TOTAL_NUM_OF_HALVES; halves++ )
    {
        for ( int events = 1; events <= TOTAL_NUM_OF_EVENTS; events++ )
        {
            // Generates a random event number from 1 - 6
            int event_num = rand () % 6 + 1;

            // Determines which team the event involves
            team = team_test ( event_num );

            // Determines whether an open shot, free kick, or penalty occurs
            if ( event_num <= 2 )
            {
                open_shot ();
            }
            else if ( event_num <= 4 )
            {
                free_kick ();
            }
            else
            {
                penalty ();
            }

            sleep (1);
        }
        half_counter++;
        output_stats ( half_counter );
        sleep (5);
    }

    return 0;
}

// The main function that runs the soccer game
int main ()
{
    run_soccer_simulator ();
    return 0;
}
