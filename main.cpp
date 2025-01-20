#include <iostream>
#include <string>
//#include <fstream>
using namespace std;

int main()
{
    //ifstream file("input.txt");
    // Numero de casos
    int C;
    cin >> C;
    cin.ignore();

    for (int i = 0; i < C; i++){
        string expression;
        getline(cin, expression);
        cout << expression << endl;
    }
    return 0;
}