#include<bits/stdc++.h>
using namespace std ;
int n,m;
class Node
{
    private:
    string name;
    int distance;
    bool even;
    public:
    bool  operator <(Node  &  b)
    {
        if((this->getdistance()< b.getdistance()))
        {
            return true ;
        }
        else return false ;

    }
    Node(){}
    Node(string s)
    {
        name=s;
        distance=INT_MAX;
    }
    int getdistance()
    {
        return distance ;
    }
    void setdistance(int p)
    {
        distance=p;
    }
    string getname()
    {
        return name;
    }
    bool checkeven()
    {
        return even;
    }
    void seteven(bool p)
    {
        even=p;
    }



};

template< typename T>
class Priority_queue
{
    private:
    vector< T >arr ;
    int size;
    public:
    Priority_queue()
    {
        arr.resize(2*m+4);
        size=0;
    }
    bool empty()
    {
        if(size==0)
        {
            return true ;
        }
        else return  false ;
    }
    void percolatedown(int i)
    {
        if(i*2+2 >size)
        {
            return ;
        }
        else if(i*2+2==size)
        {
            int child=2*i+1;
            if(!(arr[i]<arr[child]))
            {
                swap(arr[i],arr[child] );return ;
            }   
        }
        else
        {
            int child1=2*i+1;
            int child2=2*i+2;
            int minchild;
            if((arr[child1]<arr[child2]))
            {
                minchild=child1;
            }  
            else minchild=child2;
            if(!(arr[i]<arr[minchild]))
            {
                swap(arr[i],arr[minchild] );
                percolatedown(minchild);

            } 

        }
        

    }
    void percolateup(int i)
    {
        if(i==0) return ;
        int parent=(i-1)/2;
        if(arr[i]<arr[parent])
        {
            swap(arr[i],arr[parent]);
            percolateup(parent);

        }
        else return;

    }
    T top()
    {
        return arr[0];
    }
    void push(const T & a)
    {
       
        arr[size]=a;
         size++;
        percolateup(size-1);

    }
    void pop()
    {
        swap(arr[0],arr[size-1]);   
        size--;
        percolatedown(0);
    }
    


};


int main()
{


    
    cin>>n>>m;
    map<string,int>hash;
    vector<Node>nodes;
    for(int i=0;i<n;i++)
    {
        string s;
        cin>>s;

        hash[s]=i;
        Node n(s);
        nodes.push_back(n);
    }
    vector<vector<pair<int,int>>>graph(n,vector<pair<int,int>>());
    for(int i=0;i<m;i++)
    {
        string  u1,v1;
        int w;
        cin>>u1>>v1>>w;
        int u=hash[u1],v=hash[v1];
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});//filter the edges check

    }
    string s1,s2;
    cin>>s1>>s2;
    int start=hash[s1],end=hash[s2];
    // cout<<0<<endl;return 0;
    // Priority_queue<int>p;
    // for(int i=0;i<n;i++)
    // {
    //     p.push(n-i);
    // }
    // p.push(0);
    // // p.pop();
    // for(int i=0;i<n;i++)
    // {
    //     cout<<p.top()<<" ";
    //     p.pop();
    //     p.push(2);
    // }
    // return 0 
    // for(int i=0;i<n;i++)
    // {
    //     for(auto v:graph[i]) cout<<v.first<<v.second<<" ";
    //     cout<<endl;
    // }
    Priority_queue<Node>pq;
    nodes[start].setdistance(0);
    nodes[start].seteven(true);
    pq.push(nodes[start]);
    vector<int>evenset(n,0),oddset(n,0);
    vector<vector<int>>dist(n,vector<int>(2,INT_MAX));//0-even,1-odd
    while(!pq.empty())
    {
        Node n=pq.top();
        pq.pop();

        int i=hash[n.getname()];
        // cout<<13<<" "<<i<<endl;
        if(((!evenset[i] )&&n.checkeven() )||((!oddset[i] )&&(!n.checkeven()) ))
        {
            if(n.checkeven() )
            {
                dist[i][0]=n.getdistance();
                evenset[i]=1;
                // cout<<23<<" "<<i<<endl;
            }
            else
            {
                dist[i][1]=n.getdistance();
                oddset[i]=1;
                // cout<<33<<" "<<i<<endl;

            }
            for(auto j:graph[i])
            {
                int v=j.first,w=j.second ;
                // cout<<v<<" "<<endl;
                    if(n.checkeven() && oddset[v]==0 && n.getdistance() +w<dist[v][1] )
                    {
                    //    cout<<43<<" "<<i<<endl;
                        Node n1(nodes[v].getname() )  ;
                        n1.seteven(false);
                        n1.setdistance(n.getdistance() +w) ;
                        pq.push(n1);
                    }
                    else  if((!n.checkeven()) && evenset[v]==0 && n.getdistance()+w<dist[v][0] )
                    {
                        // cout<<53<<" "<<i<<endl;
                        Node n1(nodes[v].getname() )  ;
                        n1.seteven(true);
                        n1.setdistance(n.getdistance() +w) ;
                        pq.push(n1);
                    }
                    

            }

        }
        

    }
    if(dist[end][0]==INT_MAX)
    {
        cout<<-1<<endl;
    }
    else
    {
        cout<<dist[end][0]<<endl;
    }






}
