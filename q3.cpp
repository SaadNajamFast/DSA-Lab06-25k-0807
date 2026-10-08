#include <iostream>
#include <string>
using namespace std;

struct Student
{
    string name;
    string category;
    int minTokens;
    int maxTokens;
    int priority;
};

Student students[20];
int allocation[20];

int N;
int totalTokens;
int threshold;

bool categoryHasSameTokens(int index, int value)
{
    for (int i = 0; i < index; i++)
    {
        if (students[i].category == students[index].category &&
            allocation[i] == value)
        {
            return true;
        }
    }

    return false;
}

bool priorityValid(int index, int value)
{
    for (int i = 0; i < index; i++)
    {
        if (students[i].priority > students[index].priority)
        {
            if (allocation[i] < value)
                return false;
        }

        if (students[i].priority < students[index].priority)
        {
            if (allocation[i] > value)
                return false;
        }
    }

    return true;
}

bool checkFinalConditions()
{
    int highTotal = 0;
    int lowTotal = 0;

    bool hasMinimum = false;
    bool hasMaximum = false;

    for (int i = 0; i < N; i++)
    {
        if (allocation[i] == students[i].minTokens)
            hasMinimum = true;

        if (allocation[i] == students[i].maxTokens)
            hasMaximum = true;

        if (students[i].priority == 1)
            highTotal += allocation[i];
        else
            lowTotal += allocation[i];
    }

    if (highTotal - lowTotal < threshold)
        return false;

    if (!hasMinimum)
        return false;

    if (!hasMaximum)
        return false;

    return true;
}

bool allocateTokens(int index, int usedTokens)
{
    if (index == N)
    {
        return checkFinalConditions();
    }

    for (int tokens = students[index].minTokens;
         tokens <= students[index].maxTokens;
         tokens++)
    {
        if (categoryHasSameTokens(index, tokens))
            continue;

        if (!priorityValid(index, tokens))
            continue;

        if (usedTokens + tokens > totalTokens)
            continue;

        allocation[index] = tokens;

        if (allocateTokens(index + 1,
                           usedTokens + tokens))
            return true;

        allocation[index] = 0;
    }

    return false;
}

int main()
{
    cin >> N;
    cin >> totalTokens;
    cin >> threshold;

    for (int i = 0; i < N; i++)
    {
        cin >> students[i].name;
        cin >> students[i].category;
        cin >> students[i].minTokens;
        cin >> students[i].maxTokens;
        cin >> students[i].priority;

        allocation[i] = 0;
    }

    if (allocateTokens(0, 0))
    {
        int totalUsed = 0;
        int breakfast = 0;
        int lunch = 0;
        int dinner = 0;

        for (int i = 0; i < N; i++)
        {
            cout << students[i].name << " -> "
                 << allocation[i] << endl;

            totalUsed += allocation[i];

            if (students[i].category == "Breakfast")
                breakfast += allocation[i];
            else if (students[i].category == "Lunch")
                lunch += allocation[i];
            else if (students[i].category == "Dinner")
                dinner += allocation[i];
        }

        int emergency = 0;

        if (totalUsed > totalTokens)
            emergency = totalUsed - totalTokens;

        cout << "Breakfast = " << breakfast << endl;
        cout << "Lunch = " << lunch << endl;
        cout << "Dinner = " << dinner << endl;
        cout << "Emergency Tokens Used = "
             << emergency << endl;
        cout << "Unused Tokens = "
             << totalTokens - totalUsed + emergency << endl;
    }
    else
    {
        cout << "No valid allocation exists." << endl;
    }

    return 0;
}