#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
using namespace std;

struct Exp
{
    int n;
    bool operator<(Exp obj)
    {
        return n < obj.n;
    }
};

struct CmpExp
{
    bool operator()(Exp a, Exp b)
    {
        return a.n > b.n;
    }
};

int main(int argc, char const *argv[])
{
    priority_queue<Exp, vector<Exp>, CmpExp> minHeap;
    Exp a[10];
    for(int i = 0; i < 10;i++)
    {
        a[i].n = rand()*i;
        minHeap.push(a[i]);
    }
    
    while(!minHeap.empty())
    {
        cout << minHeap.top().n << endl;
        minHeap.pop();
    }
    

    


    return 0;
}
