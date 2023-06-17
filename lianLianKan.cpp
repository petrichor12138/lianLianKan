//
// Created by Bruce Yang on 2023/6/17.
//
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>

using namespace std;

class lianLianKan
{
    int length;
    int width;
    vector<vector<int>> map;
public:
    lianLianKan(int _length, int _width): length(_length), width(_width)
    {
        vector<vector<int>> _map(_length, vector<int>(_width, 0));
        this->map = _map;
    }

    void initMap()
    {

    }

    void printMap()
    {
        for(int i = 0; i < this->width; ++i)
        {
            for(int j = 0; j < this->length; ++j)
            {
                cout << setw(2) << this->map[i][j];
            }
            cout << endl;
        }
    }

    static void showOptions()
    {
        cout << "请输入对应的数字以操作：";
        cout << "1: 输入坐标以消除" << '\t';
        cout << "2: 请求帮助" << '\t';
    }

    int getOptions(int choice)
    {
        cin >> choice;
        return choice;
    }

};

int main()
{
    lianLianKan* game = new lianLianKan(8, 5);
    game->printMap();
}
