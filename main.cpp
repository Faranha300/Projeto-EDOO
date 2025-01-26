#include <iostream>
#include "src/Parser.h"
using namespace std;

int main() {
    int numCases;
    cin >> numCases;
    cin.ignore();

    for (int i = 0; i < numCases; ++i) {
        string expression;
        getline(cin, expression);

        Parser parser(expression);
        cout << parser.evaluate() << endl;
    }

    return 0;
}
