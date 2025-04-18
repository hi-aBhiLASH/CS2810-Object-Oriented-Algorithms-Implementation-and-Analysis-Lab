#include<bits/stdc++.h>
using namespace std ;
int senapati_count;
int dandanayaka_count;
int chaturangini_count;
template<typename T>
class comparator
{
   public:
    bool operator()(T a,T  b)
{
    if(a->getrank()==b->getrank())
    {
        return a->getid()<b->getid();

    }
    else
    {
        map<string,int>m;
        string s1="SENAPATI",s2="DANDANAYAKA",s3="CHATURANGINI";
        m[s1]=0;
        m[s2]=1;
        m[s3]=2;
        
        return m[a->getrank()]<m[b->getrank()];

    }
}
};


class Sentinel
{
    public:
   virtual void countHigherRanked(){}
   virtual string getrank(){ return "";}
   virtual int getid(){ return 0;}
   Sentinel(){}
};
class Senapati:public Sentinel
{
    private:
    int id;
    string name ;
    string rank;
    public:
    string getrank(){return rank;}
    int getid(){return  id;}
    Senapati(int i,string n,string ra):Sentinel()
    {
        id=i;
        name=n;
        rank=ra;
    }
    void countHigherRanked()
    {
        cout<<0<<"\n";

    }

};
class Chaturangini:public Sentinel
{
    private:
    int id;
    string name ;
    string rank;
    public:
    string getrank(){return rank;}
    int getid(){return  id;}
    Chaturangini(int i,string n,string ra):Sentinel()
    {
        id=i;
        name=n;
        rank=ra;
    }
    void countHigherRanked()
    {
        cout<<dandanayaka_count+senapati_count<<"\n";

    }

};
class Dandanayaka:public Sentinel
{
    private:
    int id;
    string name ;
    string rank;
    public:
    string getrank(){return rank;}
    int getid(){return  id;}
    Dandanayaka(int i,string n,string ra):Sentinel()
    {
        id=i;
        name=n;
        rank=ra;
    }
    void countHigherRanked()
    {
        cout<<senapati_count<<"\n";

    }

};
template<typename T >
class Kingdom
{
    private:
    vector<T>nodes;
    vector<vector<int>>adjlist;
    vector<vector<int>>cover;
    int n;
    public:
    Kingdom()
    {
        cin>>n;
        adjlist.assign(n,vector<int>());
        for(int i=0;i<n-1;i++)
        {
            int u,v;
            cin>>u>>v;
            adjlist[u].push_back(v);
            adjlist[v].push_back(u);
        }
        for(int i=0;i<n;i++)
        {
            T ptr;
            int id=i;
            string name,rank;
            cin>>name>>rank;
            if(rank=="SENAPATI")
            {
                ptr=new Senapati(id,name,rank);
                senapati_count++;
            }
            else if(rank=="DANDANAYAKA")
            {
                ptr=new Dandanayaka(id,name,rank);
                dandanayaka_count++;
            }
             else if(rank=="CHATURANGINI")
            {
                ptr=new Chaturangini(id,name,rank);
                chaturangini_count++;
            }
            nodes.push_back(ptr);
        }
        
    }
    void countHigherRanked(int i)
        {
            nodes[i]->countHigherRanked();
        }
     void printsortednodes()
        {
            vector<T>sortnodes(nodes.begin(),nodes.end() );
            sort(sortnodes.begin(),sortnodes.end(),comparator<T>());
            for(int i=0;i<n;i++)
            {
                cout<<sortnodes[i]->getid()<<" ";
            }
            cout<<endl;
        }
         void minimum_coververtex()
        {
                // cout<<91<<endl;
                cover.assign(n,vector<int>(2,-1));
                cout<<(min(dfs(0,0,-1),dfs(0,1,-1)))<<endl;//0 s parent is -1
        }
        int dfs(int i,int include,int parent)
        {
            //0 index refers to not included ,1-included
            if(cover[i][include]!=-1) return cover[i][include];
            int sum=0;
            if(include)sum=1;
            for(auto j : adjlist[i])
            {
                if(parent !=j)
                {
                    // cout<<i<<" "<<j<<endl;

                    if(include==0)
                    {
                        sum+=dfs(j,1,i);
                    }
                    else
                    {
                        sum+=min(dfs(j,0,i),dfs(j,1,i));
                    }
                }
            }
            // cout<<i<<" "<<include<<" "<<sum<<endl;
            cover[i][include]=sum;
            return sum;

        }


};


int main()
{
    Kingdom<Sentinel *> K;
    int q;
    cin>>q;
    while(q--)
    {
        int query;
        cin>>query;
        if(query==1)
        {
            K.minimum_coververtex();
        }
        else if(query==2)
        {
            K.printsortednodes();
        }
        else if(query==3)
        {
           int i;
           cin>>i;
            K.countHigherRanked(i);
        }
    }

}

