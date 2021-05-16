//ORIGINAL 


#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;


typedef struct
{
    int arrow[MAX];
    int arrowcount;
}
candidate;

// Array of candidates
string candidates[MAX];
candidate cndt[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pair sorted[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int startingpt;
int voter_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_for_cycle(int cndtwhowon);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    voter_count = get_int("Number of voters: ");

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferences[i][j] = 0;
        }
    }

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] == preferences[j][i])
            {
                continue;
            }
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int counter = 0;
    for (int j = voter_count; j > 0; j--)
    {
        for (int i = 0; i < pair_count; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner] == j)
            {
                sorted[counter].winner = pairs[i].winner;
                sorted[counter].loser = pairs[i].loser;
                counter++;
            }
        }
    }
    
    for (int i = 0; i < pair_count; i++)
    {
        pairs[i].winner = sorted[i].winner;
        pairs[i].loser = sorted[i].loser;
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        startingpt = pairs[i].loser;
        if (!check_for_cycle(pairs[i].winner))
        {
            cndt[pairs[i].loser].arrow[cndt[pairs[i].loser].arrowcount] = pairs[i].winner;
            cndt[pairs[i].loser].arrowcount++;
        }
        else
        {
            break;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (cndt[i].arrowcount == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

bool check_for_cycle(int cndtwhowon)
{
    if (cndt[cndtwhowon].arrowcount == 0 && cndtwhowon == startingpt)
    {
        return true;
    }
    
    for (int i = 0; i < cndt[cndtwhowon].arrowcount ; i++)
    {
        if (check_for_cycle(cndt[cndtwhowon].arrow[i]))
        {
            return true;
        }
       
    }
    return false;
    
}

