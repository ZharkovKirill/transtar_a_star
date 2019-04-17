#include <iostream>
#include <queue>
#define N  5
#define M  5
using namespace std;
struct cell
{
    int y,x;
    int hight;
    int path_l;
    bool visit = 0;
    int priority;


    bool operator<(cell const& rhs) const
    {
        return  (priority > rhs.priority);
    }

    void set_path(cell came_from)
    {
        path_l = came_from.path_l + abs(hight - came_from.hight) + 1;
    }

    void set_priority( cell finish )
    {
        priority = path_l + abs(x - finish.x) + abs(y - finish.y);
    }


}; //класс ячейка

void make_change( vector < vector <cell> > &field, cell to_change )
{
    int x = to_change.x;
    int y = to_change.y;
    field[y][x] = to_change;
}
vector <cell> neighbors(cell &point ,vector < vector <cell> > &field )
{
    int x = point.x;
    int y = point.y;
    vector <vector<int>> mask = {{1,0},{0,1},{-1,0},{0,-1}};
    vector <cell> res;
    for(int i = 0;i<4;i++) {
        int buf_x = x + mask[i][1];
        int buf_y = y + mask[i][0];
        if ((buf_y < N) && (buf_x < M)
        &&  (buf_x > 0) && (buf_y > 0))
        {
            res.push_back(field[buf_y][buf_x]);
        }
    }
    return  res;
}

int main()
{
    vector < vector <int> > hight_map = {{0,2,1,5,2},
                                         {1,2,1,1,5},
                                         {5,5,2,4,8},
                                         {6,1,2,5,2},
                                         {7,2,18,3,6}};
    vector < vector <cell> > field;

    for(int i = 0; i < N;i++) {
        vector<cell> collum;
        for (int j = 0; j < M; j++) {

            cell temp = {i, j,hight_map[i][j]};
            collum.push_back(temp);


        }
        field.push_back(collum);
    }
    for(auto i : field)
    {
        cout<<endl;
        for(auto j : i)
        {
            cout<<j.visit<<' ';
        }
    }
    return 0;
}