#include <iostream>
#include <queue>
#define N  5
#define M  5
using namespace std;
struct cell
{
    int y,x;
    int hight;
    int path_l = 0;
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

    if(( field[y][x].priority > to_change.priority )||(!field[y][x].visit))
        field[y][x] = to_change;
}
vector <cell> neighbors(cell &point ,vector < vector <cell> > &field )
{
    point.visit = 1;
    int x = point.x;
    int y = point.y;
    vector <vector<int>> mask = {{1,0},{0,1},{-1,0},{0,-1}};
    vector <cell> res;
    for(int i = 0;i<4;i++) {
        int buf_x = x + mask[i][1];
        int buf_y = y + mask[i][0];
        if ((buf_y < N) && (buf_x < M)
        &&  (buf_x >= 0) && (buf_y >= 0))
        {
            res.push_back(field[buf_y][buf_x]);
        }
    }
    return  res;
}
int a_star(vector < vector <cell> > &field,cell &start, cell &finish)
{
    priority_queue<cell> front;
    start.visit = 1;
    front.push(start);

    cell current = front.top();

    while (!(finish.visit)||(finish.priority < front.top().priority ))
    {

        vector <cell> neb = neighbors(current,field);
        for(auto &i: neb) {
            if (!i.visit) {
                i.set_path(current);
                i.set_priority(finish);
                front.push(i);
            }
        }


        make_change(field, current);
        front.pop();
        current = front.top();
    }
    cout<<current.x<<' '<<current.y<<endl;
    return finish.path_l;
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




    cout<<a_star(field,field[0][0],field[4][4]);
    for(auto i : field)
    {
        cout<<endl;
        for(auto j : i)
        {
            cout<<j.priority<<' ';
        }
    }
    return 0;
}