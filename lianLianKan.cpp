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
    int pairCount;
    vector<vector<int>> map;
public:
    lianLianKan(int _width, int _length): length(_length), width(_width)
    {
        vector<vector<int>> _map(_width + 2, vector<int>(_length + 2, 0));
        this->pairCount = _width * _length / 2;
        this->map = _map;
    }

    void initMap()
    {
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> distribution(1, 9);
        uniform_int_distribution<int> positionX(1, this->width);
        uniform_int_distribution<int> positionY(1, this->length);

        for(int i = 1; i <= this->width; ++i)
        {
            for(int j = 1; j <= this->length; ++j)
            {
                if(this->map[i][j] != 0)
                    continue;
                int key = distribution(generator);
                this->map[i][j] = key;
                int anotherX = positionX(generator);
                int anotherY = positionY(generator);
                while((anotherX == i && anotherY == j) || this->map[anotherX][anotherY] != 0)
                {
                    anotherX = positionX(generator);
                    anotherY = positionY(generator);
                }
                this->map[anotherX][anotherY] = key;
            }
        }
    }

    void printMap()
    {
        for(int i = 1; i <= this->width; ++i)
        {
            for(int j = 1; j <= this->length; ++j)
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
        cout << "3: 退出游戏" << endl;
    }

    bool straightLineEliminate(int x1, int y1, int x2, int y2)
    {
        if(x1 == x2)
        {
            if(abs(y1 - y2) == 1)
                return true;
            int minY = min(y1, y2);
            int maxY = max(y1, y2);
            for(int i = minY + 1; i < maxY; ++i)
            {
                if(this->map[x1][i] != 0)
                    return false;
            }
        }
        else if(y1 == y2)
        {
            if(abs(x1 - x2) == 1)
                return true;
            int minX = min(x1, x2);
            int maxX = max(x1, x2);
            for(int i = minX + 1; i < maxX; ++i)
            {
                if(this->map[i][y1] != 0)
                    return false;
            }
        }
        return true;
    }

    bool polyLineEliminate(int x1, int y1, int x2, int y2)
    {
        int upCrossPointX = x1;
        int upCrossPointY = y2;
        int downCrossPointX = x2;
        int downCrossPointY = y1;
        if(this->map[upCrossPointX][upCrossPointY] != 0 ||
        this->map[downCrossPointX][downCrossPointY] != 0)
            return false;
        if(straightLineEliminate(x1, y1, upCrossPointX, upCrossPointY) &&
                straightLineEliminate(x2, y2, upCrossPointX, upCrossPointY))
        {
            return true;
        }
        if(straightLineEliminate(x1, y1, downCrossPointX, downCrossPointY) &&
                straightLineEliminate(x2, y2, downCrossPointX, downCrossPointY))
        {
            return true;
        }
        return false;
    }

    bool doubleAngleLineEliminate(int x1, int y1, int x2, int y2)
    {
        int crossPointX, crossPointY;
        crossPointX = x1 - 1;
        crossPointY = y1;
        while(crossPointX >= 0 && this->map[crossPointX][y1] == 0)
        {
            if(polyLineEliminate(crossPointX, y1, x2, y2))
                return true;
            else
                -- crossPointX;
        }

        crossPointX = x1 + 1;
        crossPointY = y1;
        while(crossPointX < this->length + 1 && this->map[crossPointX][y1] == 0)
        {
            if(polyLineEliminate(crossPointX, y1, x2, y2))
                return true;
            else
                ++ crossPointX;
        }

        crossPointX = x1;
        crossPointY = y1 - 1;
        while(crossPointY >= 0 && this->map[x1][crossPointY] == 0)
        {
            if(polyLineEliminate(x1, crossPointY, x2, y2))
                return true;
            else
                -- crossPointY;
        }

        crossPointX = x1;
        crossPointY = y1 + 1;
        while(crossPointX < this->width + 1 && this->map[x1][crossPointY] == 0)
        {
            if(polyLineEliminate(x1, crossPointY, x2, y2))
                return true;
            else
                ++ crossPointY;
        }

        return false;
    }



    bool eliminate(int x1, int y1, int x2, int y2)
    {
        if(this->map[x1][y1] != this->map[x2][y2])
        {
            cout << "无法消除，请重新输入" <<endl;
            return false;
        }
        if(straightLineEliminate(x1, y1, x2, y2))
        {
            this->map[x1][y1] = 0;
            this->map[x2][y2] = 0;
            -- this->pairCount;
            cout << "消除成功" <<endl;
            return true;
        }
        if(polyLineEliminate(x1, y1, x2, y2))
        {
            this->map[x1][y1] = 0;
            this->map[x2][y2] = 0;
            -- this->pairCount;
            cout << "消除成功" <<endl;
            return true;
        }
        if(doubleAngleLineEliminate(x1, y1, x2, y2))
        {
            this->map[x1][y1] = 0;
            this->map[x2][y2] = 0;
            -- this->pairCount;
            cout << "消除成功" <<endl;
            return true;
        }

        cout << "无法消除，请重新输入" <<endl;
        return false;
    }

    pair<int ,int> getFirst()
    {
        for(int i = 1; i <= this->width; ++i)
        {
            for(int j = 1; j <= this->length; ++j)
            {
                if(this->map[i][j] != 0)
                {
                    return {i, j};
                }
            }
        }
        return {};
    }

    void hint()
    {
        //pair<int, int> hintPosition = getFirst();
        //int key = this->map[hintPosition.first][hintPosition.second];
        for(int i = 1; i <= this->width; ++i)
        {
            for(int j = 1; j <= this->length; ++j)
            {
                if(this->map[i][j] == 0)
                {
                    continue;
                }
                else
                {
                    int key = this->map[i][j];
                    for(int m = 1; m <= this->width && m != i; ++m)
                    {
                        for(int n = 1; n <= this->length && n != j; ++n)
                        {
                            if(this->map[m][n] != key)
                                continue;
                            if(straightLineEliminate(i, j, m, n)
                            || polyLineEliminate(i, j, m, n)
                            || doubleAngleLineEliminate(i, j, m, n))
                            {
                                cout << "可消除的坐标为" << i << ' ' << j << ' ' << m << ' ' << n << endl;
                                return ;
                            }
                        }
                    }
                }

            }
        }
        cout << "无可消除的坐标, 可以退出游戏" << endl;
    }

    void game()
    {
        if(this->pairCount == 0)
        {
            cout << "恭喜你赢了！" << endl;
            return ;
        }
        printMap();
        showOptions();
        int option;
        cin >> option;
        if(option == 1)
        {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            eliminate(x1, y1, x2, y2);
            game();
        }
        else if(option == 2)
        {
            hint();
            game();
        }
        else if(option == 3)
        {
            cout << "游戏退出！" << endl;
            return ;
        }
    }

};

int main()
{
    lianLianKan* game = new lianLianKan(4, 5);
    game->initMap();
    game->game();
    delete game;
}
