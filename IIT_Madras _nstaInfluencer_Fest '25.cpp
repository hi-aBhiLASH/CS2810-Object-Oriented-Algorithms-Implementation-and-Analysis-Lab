#include<bits/stdc++.h>
using namespace std;
#define all(a) a.begin(), a.end()
class GraphAlgorithm
{   
    public:
    GraphAlgorithm(int &n1,int &m1,vector<int> & hypescore1,vector<vector<int>> & adjlist1)
    {
        n=n1;m=m1;hypescore=hypescore1;adjlist=adjlist1;
    }
    GraphAlgorithm(int &n1,int &m1,vector<vector<int>> & adjlist1)
    {
        n=n1;m=m1;adjlist=adjlist1;
    }
    virtual bool  query(){
        return true;
    }
    protected:
        int n,m;
        vector<int>hypescore;
        vector<vector<int>>adjlist; 



};
class isCycle :public GraphAlgorithm
{
    public:
    isCycle(int &n1,int &m1,vector<vector<int>> & adjlist1):GraphAlgorithm(n1,m1,adjlist1)
    {

    }
void dfs(vector<int>& colour,int &back_edge,vector<vector<int>>&adjlist,int u)
{
    colour[u]=1;
    for(auto v:adjlist[u])
    {
        if(colour[v]==0)
        {
           dfs(colour,back_edge,adjlist,v);
        }
        else if(colour[v]==1)
        {
            back_edge=1;
            return ;
        }
    }
    colour[u]=2;
}
    bool query()
    {
        vector<int>colour(n+1,0);//0-white,1-gray,2-black
        int back_edge=0;
        for(int i=0;i<n;i++)
        {
           if(colour[i+1]==0) dfs(colour,back_edge,adjlist,i+1);
        }
        if(back_edge==1)
        {
            cout<<"YES"<<endl;
            return true ;

        }
        else{ cout<<"NO"<<endl; return false ;} 
    }
};
class indepComponent:public GraphAlgorithm
{
     public:
    indepComponent(int &n1,int &m1,vector<vector<int>> & adjlist1):GraphAlgorithm(n1,m1,adjlist1)
    {

    }
    void dfs(vector<int>& colour,vector<int>& vfinish,vector<vector<int>>&adjlist,int u)
{
    colour[u]=1;
    for(auto v:adjlist[u])
    {
        if(colour[v]==0)
        {
           dfs(colour,vfinish,adjlist,v);
        }
    }
    colour[u]=2;
    vfinish.push_back(u);
}
void dfs2(vector<int>& colour,vector<int>& components,vector<vector<int>>&adjlist,int u)
{
    colour[u]=1;
    components.push_back(u);
    for(auto v:adjlist[u])
    {
        if(colour[v]==0)
        {
           dfs(colour,components,adjlist,v);
        }
    }
    colour[u]=2;
   
}

    bool  query()
    {
         vector<vector<int>>adjlistT; 
        vector<int>colour(n+1,0);
        vector<int>colour1(n+1,0);
       // adjlist.assign(n+1,vector<int>());
        adjlistT.assign(n+1,vector<int>());
        for(int i=0;i<adjlist.size()-1;i++)
       {
             for(auto v:adjlist[i+1])
             {
                     adjlistT[v].push_back(i+1);      
             }
       }
        vector<int>vfinish;
        for(int i=1;i<=n;i++)
        {
            if(colour[i]==0)
            {
                dfs(colour,vfinish,adjlist,i);    
            }
        }
       reverse(all(vfinish));
        vector<vector<int>>scc;
       //aout(vfinish);nl;
       for(auto  u:vfinish )
       {
            if(colour1[u]==0)
            {
                vector<int>components;
                dfs2(colour1,components,adjlistT,u);  
                 scc.push_back(components);

            }
       }
       int max_size=0;
        for(int i=0;i<scc.size();i++)
       {
            max_size=max(max_size,(int)scc[i].size());
       }
       cout<<scc.size()<<" "<<max_size<<endl;
      
        return true ;
    }
};
class validOrder: public GraphAlgorithm
{
    public:
    validOrder(int &n1,int &m1,vector<vector<int>> & adjlist1):GraphAlgorithm(n1,m1,adjlist1)
    {

    }
    void dfs(vector<int>& colour,int &back_edge,vector<vector<int>>&adjlist,int u)
{
    colour[u]=1;
    for(auto v:adjlist[u])
    {
        if(colour[v]==0)
        {
           dfs(colour,back_edge,adjlist,v);


        }
        else if(colour[v]==1)
        {
            back_edge=1;
            return ;
        }
    }
    colour[u]=2;
}
    bool  query()
    {
        vector<int>colour(n+1,0);//0-white,1-gray,2-black
        int back_edge=0;
        for(int i=0;i<n;i++)
        {
            if(colour[i+1]==0) dfs(colour,back_edge,adjlist,i+1);
        }
        if(back_edge==1)
        {
            cout<<"NO"<<endl;
            return true ;

        }
       // else{ cout<<"NO"<<endl; return false ;}
        //topo code starts
       vector<int>indegree(n+1,0);
             for(int i=0;i<adjlist.size() - 1;i++)
       {
             for(auto v:adjlist[i+1])
             {
                    indegree[v]++;
             }
       }
       priority_queue<int,vector<int>,greater<int>> next_v;
       for(int i=1;i<=n;i++)
       {
          if(indegree[i]==0)  
          { 
                next_v.push(i);
           }
       }
       while(!next_v.empty())
       {
         int u=next_v.top();
            next_v.pop();
            cout<<u<<" ";
            for(auto v: adjlist[u])
            {
                 
                    indegree[v]--;
                    if(indegree[v]==0)
                    {
                        next_v.push(v);
                    }
                
            }
       }
       cout<<endl;
        return  true ;
    }
};
class maxhype:public GraphAlgorithm
{
    public:
    maxhype(int &n1,int &m1,vector<int>hypescore1,vector<vector<int>> & adjlist1):GraphAlgorithm(n1,m1,hypescore1,adjlist1)
    {

    }
    void dfs(vector<int>& colour,vector<int>& vfinish,vector<vector<int>>&adjlist,int u)
{
    colour[u]=1;
    for(auto v:adjlist[u])
    {
        if(colour[v]==0)
        {
           dfs(colour,vfinish,adjlist,v);
        }
    }
    colour[u]=2;
    vfinish.push_back(u);
}
void dfsssc(vector<int>& colour,vector<int>& vfinish,vector<set<int>>&adjlist,int u)
{
    colour[u]=1;
    for(auto v:adjlist[u])
    {
        if(colour[v]==0)
        {
           dfsssc(colour,vfinish,adjlist,v);
        }
    }
    colour[u]=2;
    vfinish.push_back(u);
}
void dfs2(vector<int>& colour,vector<int>& components,vector<vector<int>>&adjlist,int u)
{
    colour[u]=1;
    components.push_back(u);
    for(auto v:adjlist[u])
    {
        if(colour[v]==0)
        {
           dfs(colour,components,adjlist,v);
        }
    }
    colour[u]=2;
   
}

    bool  query()
    {
        vector<vector<int>>adjlistT; 
        vector<int>colour(n+1,0);
        vector<int>colour1(n+1,0);
       // adjlist.assign(n+1,vector<int>());
        adjlistT.assign(n+1,vector<int>());
        for(int i=0;i<adjlist.size()-1;i++)
       {
             for(auto v:adjlist[i+1])
             {
                     adjlistT[v].push_back(i+1);      
             }
       }
        vector<int>vfinish;
        for(int i=1;i<=n;i++)
        {
            if(colour[i]==0)
            {
                dfs(colour,vfinish,adjlist,i);    
            }
        }
       reverse(all(vfinish));
        vector<vector<int>>scc;
       //aout(vfinish);nl;
       for(auto  u:vfinish )
       {
            if(colour1[u]==0)
            {
                vector<int>components;
                dfs2(colour1,components,adjlistT,u);  
                 scc.push_back(components);

            }
           

       }
       int max_size=0;
         for(int i=0;i<scc.size();i++)
       {
            max_size=max(max_size,(int)scc[i].size());
       }
        vector<set<int>>adjlistscc(scc.size()+1,set<int>());
            unordered_map<int,int>mapping;
            for(int i=0;i<scc.size();i++)
            {
             for(auto v:scc[i])
             {
                mapping[v]=i+1;
             }
             

            }       
            for(int i=1;i<adjlist.size();i++)
            {
             for(auto v:adjlist[i])
             {
                    if(mapping[i]!=mapping[v])
                    {
                          adjlistscc[mapping[i]].insert(mapping[v]);

                    }
             }
             
            }
            int n1=scc.size();
            vector<int>colour3(n1+1,0);
            vector<int>sscfinish;
            for(int i=1;i<=n1;i++)
            {
                if(colour3[i]==0)
                {
                    dfsssc(colour3,sscfinish,adjlistscc,i);    
                }
            }
            reverse(all(sscfinish));
            vector<int>dp(scc.size()+1,0);
            for(int i=0;i<n;i++)
            {
                dp[mapping[i+1]]+=hypescore[i];
            }
            for(int i=1;i<=n1;i++)
            {
                int j=sscfinish[i-1];
                for(auto v:adjlistscc[j])
                {
                    dp[v]=max(dp[v],dp[v]+dp[j] );
                }
            }
            cout<<*max_element(all(dp))<<endl;

        return true ;
    }   
};


int main()
{
        int n,m;
        vector<int>hypescore;
        vector<vector<int>>adjlist; 
         cin>>n>>m;
        hypescore.assign(n,0);
        for(int i=0;i<n;i++)
        {
            cin>>hypescore[i];
        }
        adjlist.assign(n+1,vector<int>());
        for(int i=0;i<m;i++)
        {
            int u,v;
            cin>>u>>v;
            adjlist[u].push_back(v);
        }

    isCycle cycle(n,m,adjlist);
    indepComponent component(n,m,adjlist);
    validOrder order(n,m,adjlist);
    maxhype hype(n,m,hypescore,adjlist);
    int q;
    cin>>q;
    while(q--)
    {
        int query;
        cin>>query;
        GraphAlgorithm * ptr ;
        if(query==1)
        {
            ptr=&cycle;
        }
        else if(query==2)
        {
            ptr=&component;
        }
        else if (query==3)
        {
            ptr=&order ;
        }
        else
        {
            ptr=&hype ;
        }
        ptr->query() ;
    }


}