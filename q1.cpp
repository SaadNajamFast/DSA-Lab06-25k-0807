#include <iostream>
#include <string>
using namespace std;

void generateCodes(int pos, int N, int targetSum,
                   int currentSum, string code,
                   bool used[], string targetCode,
                   bool &found)
{
    if (pos == N)
    {
        if (currentSum == targetSum)
        {
            cout << code << endl;

            if (code == targetCode)
                found = true;
        }

        return;
    }

    for (int digit = 0; digit <= 9; digit++)
    {
        if (pos == 0 && digit == 0)
            continue;

        if (used[digit])
            continue;

        if (currentSum + digit > targetSum)
            continue;

        used[digit] = true;

        generateCodes(
            pos + 1,
            N,
            targetSum,
            currentSum + digit,
            code + char('0' + digit),
            used,
            targetCode,
            found);

        used[digit] = false;
    }
}

int main()
{
    int N, targetSum;
    string targetCode;

    cout << "Enter number of positions: ";
    cin >> N;

    cout << "Enter target sum: ";
    cin >> targetSum;

    cout << "Enter target code: ";
    cin >> targetCode;

    bool used[10] = {false};
    bool found = false;

    cout << "\nValid Codes:\n";

    generateCodes(
        0,
        N,
        targetSum,
        0,
        "",
        used,
        targetCode,
        found);

    if (found)
        cout << "\nTarget code CAN be formed.\n";
    else
        cout << "\nTarget code CANNOT be formed.\n";

    return 0;
}