#include <iostream>
using namespace std;

struct Runner
{
    int stamina;
    int speed;
};

bool canFollow(Runner current, Runner next)
{
    return current.speed + current.stamina >= next.stamina;
}

bool validLastTwo(Runner a, Runner b, double average)
{
    return a.stamina >= average && b.stamina >= average;
}

bool swappedArrangementValid(Runner a, Runner b)
{
    return canFollow(b, a);
}

void printOrder(Runner order[], int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "(" << order[i].stamina
             << ", " << order[i].speed << ") ";

        if (i != N - 1)
            cout << "-> ";
    }

    cout << endl;
}

void generateOrder(
    Runner runners[],
    Runner order[],
    bool used[],
    int N,
    int pos,
    double average)
{
    if (pos == N)
    {
        if (!validLastTwo(order[N - 2], order[N - 1], average))
            return;

        if (N >= 2)
        {
            if (swappedArrangementValid(order[N - 2], order[N - 1]))
                return;
        }

        printOrder(order, N);
        return;
    }

    for (int i = 0; i < N; i++)
    {
        if (used[i])
            continue;

        if (pos > 0)
        {
            if (!canFollow(order[pos - 1], runners[i]))
                continue;
        }

        if (pos >= N - 2)
        {
            if (runners[i].stamina < average)
                continue;
        }

        used[i] = true;
        order[pos] = runners[i];

        generateOrder(
            runners,
            order,
            used,
            N,
            pos + 1,
            average);

        used[i] = false;
    }
}

int main()
{
    int N;

    cout << "Enter number of runners: ";
    cin >> N;

    Runner runners[20];
    Runner order[20];
    bool used[20] = {false};

    double totalStamina = 0;

    for (int i = 0; i < N; i++)
    {
        cout << "\nRunner " << i + 1 << endl;

        cout << "Stamina: ";
        cin >> runners[i].stamina;

        cout << "Speed: ";
        cin >> runners[i].speed;

        totalStamina += runners[i].stamina;
    }

    double average = totalStamina / N;

    cout << "\nAverage stamina = " << average << endl;

    cout << "\nValid Running Orders:\n";

    generateOrder(
        runners,
        order,
        used,
        N,
        0,
        average);

    return 0;
}