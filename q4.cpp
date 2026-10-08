#include <iostream>
using namespace std;

const int N = 4;
const int M = 4;

int people[N][M] =
    {
        {8, 12, -1, 6},
        {5, 10, 7, -1},
        {-1, 9, 15, 4},
        {6, -1, 8, 11}};

int units[N][M] =
    {
        {2, 3, -1, 2},
        {1, 3, 2, -1},
        {-1, 2, 4, 1},
        {2, -1, 2, 3}};

bool selected[N][M];
bool bestSelected[N][M];

int capacity;
int bestPeople = 0;
int bestUnits = 0;

bool rowHasSelection(int row)
{
    for (int col = 0; col < M; col++)
    {
        if (selected[row][col])
            return true;
    }

    return false;
}

int selectedHighRiskCount()
{
    int count = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (selected[i][j] && people[i][j] >= 10)
                count++;
        }
    }

    return count;
}

void saveBest(int rescuedPeople, int usedUnits)
{
    bestPeople = rescuedPeople;
    bestUnits = usedUnits;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            bestSelected[i][j] = selected[i][j];
        }
    }
}

void solve(int index, int rescuedPeople, int usedUnits)
{
    if (index == N * M)
    {
        for (int i = 0; i < N; i++)
        {
            bool hasAffected = false;

            for (int j = 0; j < M; j++)
            {
                if (people[i][j] != -1)
                {
                    hasAffected = true;
                    break;
                }
            }

            if (hasAffected && !rowHasSelection(i))
                return;
        }

        if (rescuedPeople > bestPeople)
            saveBest(rescuedPeople, usedUnits);

        return;
    }

    int row = index / M;
    int col = index % M;

    if (people[row][col] == -1)
    {
        solve(index + 1, rescuedPeople, usedUnits);
        return;
    }

    solve(index + 1, rescuedPeople, usedUnits);

    int additionalUnit = 0;

    if (people[row][col] >= 10 &&
        selectedHighRiskCount() >= 1)
    {
        additionalUnit = 1;
    }

    int requiredUnits = units[row][col] + additionalUnit;

    if (usedUnits + requiredUnits <= capacity)
    {
        selected[row][col] = true;

        solve(index + 1,
              rescuedPeople + people[row][col],
              usedUnits + requiredUnits);

        selected[row][col] = false;
    }
}

int main()
{
    cin >> capacity;

    solve(0, 0, 0);

    if (bestPeople == 0)
    {
        cout << "No valid allocation exists." << endl;
        return 0;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (bestSelected[i][j])
            {
                cout << "(" << i << ", " << j << ")"
                     << " -> People: "
                     << people[i][j]
                     << ", Units: "
                     << units[i][j]
                     << endl;
            }
        }
    }

    cout << "Total People Rescued = "
         << bestPeople << endl;

    cout << "Total Rescue Units Used = "
         << bestUnits << endl;

    cout << "Remaining Units = "
         << capacity - bestUnits << endl;

    return 0;
}