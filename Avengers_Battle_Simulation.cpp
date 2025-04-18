#include<bits/stdc++.h>
using namespace std ;
int k;


//pre declaraation of classes check
class Battle;
class Avenger;

class QNS
{
    private:
    int powerlevel;
    int durability;
    int energystorage;
    int heatlevel;
   // bool isshut=false;
    public:
    friend class Avenger;
    int getP() { return powerlevel;}
    int getD() { return durability;}
    int getE() {return energystorage ;}
    int getH() {return heatlevel ;}
    QNS(int p,int d,int e,int h)
    {
         powerlevel=min(5000,p) ;

         durability=d;
         energystorage=e;
         heatlevel=h; 
    }
    QNS()
    {
         powerlevel=1000;
         durability=500;
         energystorage=300;
         heatlevel=0; 
    }
    QNS(const QNS & q)
    {
        this->powerlevel=q.powerlevel;
        this->durability=q.durability;
        this->energystorage=q.energystorage;
        this->heatlevel=q.heatlevel;


    }

    QNS &operator+(const QNS & q)
    {
        this->powerlevel+=q.energystorage;
        this->powerlevel=min(5000,this->powerlevel);
        this->durability+=q.durability;
        this->energystorage+=q.powerlevel;
        return *this;
    }
    QNS &operator-(int x)
    {
        this->durability-=x;
        this->energystorage+=x;
        this->heatlevel+=x;
        return *this;
    }
    QNS &operator *(int x)
    {
        this->powerlevel=this->powerlevel+((this->powerlevel*x)/100);
        this->powerlevel=min(5000,this->powerlevel);
        this->energystorage=this->energystorage+5*(x);
        this->heatlevel=this->heatlevel+(x);
        return *this;
    }
    QNS &operator /(int x)
    {
        this->durability+=x;
        this->heatlevel-=x;
        return *this;
    }
    void boostpower(int factor)
    {
        (*this)*factor ;

    }
    bool operator ==(QNS &q)
    {
        if(this->powerlevel==q.powerlevel && this->durability==q.durability )
        {
            return true;
        }
        return false;
    }
    bool operator <(QNS &q)
    {
        if(this->powerlevel+this->durability<q.powerlevel+q.durability)
        {
            return true;
        }
        return false;

    }
    void boostpower(QNS &q)
    {
       (*this)+q;
    }

};

class Avenger
{

    private:
    string name ;
     QNS suit ;
    int attackstrength;
    public:
     friend class Battle;
     Avenger(){}
    string getname()
    {
        return name;
    }
    Avenger(string s,QNS q,int st)
    {
        name=s;suit=q;attackstrength=st;
    }
    void attack(Avenger & enemy)
    {
        (enemy.suit)-(this->attackstrength) ;
    }
    void printstatus()
    {
        cout<<name<<" " <<suit.getP()<<" "<<suit.getD()<<" "<<suit.getE()<<" "<<suit.getH()<<endl;
    }
    void upgradesuit(QNS q )
    {
        (this->suit)+q ;

    }
    void repair(int x)
    {
        (this->suit)/x;
        if(this->suit.getH()<0)
        {
            this->suit.heatlevel=0;
        }

    }

};

class Battle
{
    private:
    
    vector<Avenger>heroes;
    vector<Avenger>enemies;
    vector<string>battlelog;
    public:
    void addhero(Avenger &a)
    {
        heroes.push_back(a);
    }
    void addenemy(Avenger &a)
    {
        enemies.push_back(a);
    }
    Avenger & getavenger(string s)
    {
        for(auto &i:heroes)
        {
            if(i.getname()==s)
            {
                return i;
            }
        }
        for(auto &i:enemies)
        {
            if(i.getname()==s)
            {
                return i;
            }
        } 
        Avenger a ;
        return a;
         
    }

    void startbattle(int &count,vector<QNS>&v)
    {
        while(1)
        {
            string s;
            cin>>s;
            if(s=="End")
            {
                return ;
            } 
            else if(s=="PrintBattleLog")
            {
                printbattlelog();
            }
            else if(s=="BattleStatus")
            {
                result();
            }
            else if(s=="Attack")
            {
                string s1,s2;
                cin>>s1>>s2;
                Avenger &p1=getavenger(s1);
                Avenger & p2=getavenger(s2);
                if(p1.suit.getD()>0 && p1.suit.getH()<=500 && p2.suit.getD()>0)
                {
                     p1.attack(p2);
                      battlelog.push_back(p1.getname()+" attacks "+p2.getname());
                    if(p2.suit.getD()<=0)
                    {
                        // suit destriyed
                        battlelog.push_back(p2.getname()+" suit destroyed");
                    }
                    else if(p2.suit.getH()>500)
                    {
                        //suit overheated
                         battlelog.push_back(p2.getname()+" suit overheated");

                    }
                }
                

               
            }
            else if(s=="Repair")
            {
                string s1;
                int x;
                cin>>s1>>x;

                Avenger&p1=getavenger(s1);
                p1.repair(x);
                battlelog.push_back(s1+" repaired");
            }
            else if(s=="BoostPowerByFactor")
            {
                string s1;
                int x;
                cin>>s1>>x;
                Avenger &p1=getavenger(s1);
                p1.suit.boostpower(x);
                battlelog.push_back(p1.getname()+" boosted");
                if(p1.suit.getH()>500)
                {
                    battlelog.push_back(p1.getname()+" suit overheated");
                }
            
            }
            else if(s=="BoostPower")
            {
                string s1;
                int p,d,e,h;
                cin>>s1>>p>>d>>e>>h;
                QNS q(p,d,e,h);
                Avenger & p1=getavenger(s1);
                p1.suit.boostpower(q);
                battlelog.push_back(p1.getname()+" boosted");
                if(p1.suit.getH()>500)
                {
                    battlelog.push_back(p1.getname()+" suit overheated");
                }

            }
            else if(s=="AvengerStatus")
            {
                string s1;
                cin>>s1;
                Avenger &p1=getavenger(s1);
                p1.printstatus();
                
            }
            else if(s=="Upgrade")
            {
               
                string s1;
                    cin>>s1;
                    Avenger &p1=getavenger(s1);
                 if(count<k)
                {
                   
                    p1.upgradesuit(v[count]);
                    count++;
                    battlelog.push_back(p1.getname()+" upgraded");

                    
                }
                else
                {
                    battlelog.push_back(p1.getname()+" upgrade"+" Fail");
                    
                }
            }
        }
    }

    

    void printbattlelog()
    {
        for(auto &i:battlelog)
        {
            cout<<i<<endl;
        }
    }
    int result()
    {
            int sum1=0,sum2=0;
            for(auto &i:heroes)
            {
                if(i.suit.getD()>0) sum1+=i.suit.getD()+i.suit.getP(); 
            }
            for(auto &i:enemies)
            {
                if(i.suit.getD()>0) sum2+=i.suit.getD()+i.suit.getP(); 
            }   
            if(sum1==sum2)
            { 
             cout<<"tie"<<endl;
             return 0;}
            else if(sum1>sum2)
            { cout<<"heroes are winning"<<endl; return 1;}
            else
            { cout<<"enemies are winning"<<endl; return -1;}

    }
};



int main()
{
    int n,m;
    cin>>k>>n>>m;
    vector<QNS>v;
    Battle B;
    for(int i=0;i<k;i++)
    {
        int p,d,e,h;
        cin>>p>>d>>e>>h;
        QNS q(p,d,e,h);
        v.push_back(q);
    }
    int  count=0;
    for(int i=0;i<n;i++)
    {
        string s;
        cin>>s;
        int x;
        cin>>x;
        if(count>=k)
        {
            cout<<s<<" is out of fight"<<endl;//check

        }
        else
        {
            Avenger a(s,v[count],x);
            count++;
            B.addhero(a);
            
        }
    }
    for(int i=0;i<m;i++)
    {
        string s;
        cin>>s;
        int x;
        cin>>x;
        if(count>=k)
        {
            cout<<s<<" is out of fight"<<endl;//check

        }
        else
        {
            Avenger a(s,v[count],x);
            count++;
            B.addenemy(a);
            
        }
    }
    string s;
    cin>>s;
    if(s=="BattleBegin")
    {
        B.startbattle(count,v);
    }

}