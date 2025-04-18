#include<bits/stdc++.h>
using namespace std ;
#define int long long int 
#define mod 1000000007


class currencysorter
{
    private:
    vector<int>a;
    public:
    currencysorter()
    {
                int n;
                cin>>n;
                a.resize(n);
                for(int i=0;i<n;i++)
                {
                    cin>>a[i];
                }
    }
    int partition(vector<int>&a,int l,int r)
    {
        int pivot=a[r];
        int i=l-1;
        for(int j=l;j<r;j++)
        {
            if(a[j]<pivot)
            {
                i++;
                swap(a[i],a[j]);
            }
        }

        swap(a[i+1],a[r]);

        return i+1;

    }
    void quicksort(vector<int>&a,int l,int r)
    {
        if(l<r)
        {
            int p=partition(a,l,r);
            quicksort(a,l,p-1);
            quicksort(a,p+1,r);
        }
    }
    void operator()()
    {
        
        quicksort(a,0,a.size()-1);
        print();
    }
    void print()
    {
        for(int i=0;i<a.size();i++)
        {
            cout<<a[i]<<" ";
        }
        cout<<endl;
    }
};
class fibanoociGeneartor
{
   public:
   int operator()(int n)
   {
       if(n==0)
       {
           return 0;
       }
        if(n==1)
        {
            return 1;
        }
        n--;
         
        int f[2][2]={{1,1},{1,0}};
        int a=1,b=0;
        while(n>0)
        {
            if(n%2!=0)
            {
                int x=(a*f[0][0]+b*f[0][1])%mod;
                int y=(a*f[1][0]+b*f[1][1] )%mod;
                a=x;
                b=y;
            }
            int x=f[0][0]*f[0][0]+f[0][1]*f[1][0];x%=mod;
            int y=f[0][0]*f[0][1]+f[0][1]*f[1][1];y%=mod;
            int z=f[1][0]*f[0][0]+f[1][1]*f[1][0];z%=mod;
            int w=f[1][0]*f[0][1]+f[1][1]*f[1][1];w%=mod;
            f[0][0]=x;

            f[0][1]=y;
            f[1][0]=z;
            f[1][1]=w;
            n=n/2;   
        }

         return a%mod;
       
   }

   
  

};
class Primecalculator
{
   vector<int>primes;
    public:
     Primecalculator()
    {
         int n=1000003;
         vector<bool>arr(n+1,true);
        for(int i=2;i<=n;i++)
        {
            if(arr[i]==true)
            {
                primes.push_back(i);
                for(int j=i*i;j<=n;j+=i)
                {
                    arr[j]=false;
                }
            }
        }

    }

    void printprimes(int l,int r)
    {
    int n=r-l+1;
    
    vector<bool>arr(n,true);
    for(int i=0;i<primes.size() && primes[i]<=r;i++)
    {
        int start=((l-1+primes[i])/primes[i])*primes[i];
        if(start==primes[i])
        {
            start+=primes[i];
        }
        for(int j=start;j<=r;j+=primes[i])
        {
            arr[j-l]=false;
            //cout<<10;

        }
    }
    if(l==1)
    {
        arr[0]=false;
    }   
    for(int i=0;i<n;i++)
        {
            if(arr[i]==true)
            {
                cout<<i+l<<" ";
            }
        }
        cout<<endl;
    }
    void  printprimesum(int l,int r)
    {
    int n=r-l+1;
    
    vector<bool>arr(n,true);
    for(int i=0;i<primes.size();i++)
    {
        int start=((l-1+primes[i])/primes[i])*primes[i];
         if(start==primes[i])
        {
            start+=primes[i];
        }
        for(int j=start;j<=r;j+=primes[i])
        {
            arr[j-l]=false;
        }
    }
     if(l==1)
    {
        arr[0]=false;
    }  
    int sum=0;
        for(int i=0;i<n;i++)
        {
            if(arr[i]==true)
            {
                sum+=i+l;
            }
        }
        cout<<sum<<endl;
    }


};
class NumberAnalyzer
{
        public:
        void isSquareFree(int x)
        {
            bool ans=true;
            if(x%4!=0)
            {
            for(int i=3;i*i<=x;i+=2)
            {
                if(x%i==0){
                    x /= i;
                    if(x%i==0)
                    {
                        ans=false;
                        break;
                    }
                }
                
            }

            }
            else
            {
                
                    ans=false;
                
            }
            

            if(ans)
            {
                cout<<"yes"<<endl;
            }
            else
            {
                cout<<"no"<<endl;
            }
        }
        void countDivisors(int x)
        {
            int count=0;
            int n=x;
            for(int i=1;i<=(int)sqrt(x);i++)
            {
                if(n%i==0)
                {
                    if(n/i==i)
                    {
                        count++;
                    }
                    else
                    {
                        count+=2;
                    }
                }
            }
            cout<<count<<endl;
        }
        void sumOfDivisors(int x)
        {
            int sum=0;
            int n=x;
            for(int i=1;i<=(int)sqrt(x);i++)
            {
                if(n%i==0)
                {
                    if(n/i==i)
                    {
                        sum+=i;
                    }
                    else
                    {
                        sum+=i+n/i;
                    }
                }
            }
            cout<<sum<<endl;
        }

};






int32_t main()
{
        int k;
        cin>>k;
        if(k==1)
        {
            int t;
            cin>>t;
            while(t--)
            {
                currencysorter C;
                C();

                
            }
        }
        else if(k==2)
        {
            int t;
            cin>>t;
            fibanoociGeneartor F;    
            while(t--)
            {
                int i;
                cin>>i;
                cout<<F(i)<<endl;
            }
        }
        else if(k==3)
        {
            int t;                    

            cin>>t;
            Primecalculator p ;
            while(t--)
            {
                string s;
                cin>>s;int l,r;
                cin>>l>>r;
                
                if(s=="printPrimes")
                {
                    p.printprimes(l,r);
                }
                else
                {
                    p.printprimesum(l,r);
                }
            }
        }
        else if(k==4)
        {
            int t;  
            cin>>t;
            while(t--)
            {
                string s;
                cin>>s;int l;
                cin>>l;
                NumberAnalyzer N;
                if(s=="sumOfDivisors")
                {
                    N.sumOfDivisors(l);
                    
                }
                else if(s=="isSquareFree")
                {
                    N.isSquareFree(l);
                }
                else
                {
                    N.countDivisors(l);
                }
            }
        }
}