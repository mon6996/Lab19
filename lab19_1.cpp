#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score)
{
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x)
{
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string file, vector<string> &name, vector<int> &score, vector<char> &grade)
{
    int i = 0, a, b, c;
    string textline;
    char temp[100];
    ifstream source(file);
    while(getline(source, textline))
    {
        string format = "%[^:]: %i %i %i";
        sscanf(textline.c_str(), format.c_str(), temp, &a, &b, &c);
        name.push_back(temp);
        score.push_back(a + b + c);
        grade.push_back(score2grade(score[i]));
        i++;
    }
}

void getCommand(string &command, string &key)
{
    cout << "Please input your command: ";
    cin >> command;
    if(toUpperStr(command) == "NAME" || toUpperStr(command) == "GRADE")
    {
        cin.ignore();
        getline(cin,key);
    }
}

void searchName(vector<string> &name, vector<int> &score, vector<char> &grade, string &key)
{
    int l = name.size(), find = 0;
    cout << "---------------------------------\n";
    for(int i = 0; i < l; i++)
    {
        if(toUpperStr(name[i]) == key)
        {
            cout << name[i] << "'s score = " << score[i] << "\n";
            cout << name[i] << "'s grade = " << grade[i] << "\n";
            find++;
        }
    }
    if(find == 0)
    {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &name, vector<int> &score, vector<char> &grade, string &key)
{
    int l = grade.size(), find = 0;
    cout << "---------------------------------\n";
    for(int i = 0; i < l; i++)
    {
        if(grade[i] == key[0])
        {
            cout << name[i] << " (" << score[i] << ")\n";
            find++;
        }
    }
    if(find == 0)
    {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}


int main()
{
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);

    do
    {
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else
        {
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }
    while(true);
    
    return 0;
}
