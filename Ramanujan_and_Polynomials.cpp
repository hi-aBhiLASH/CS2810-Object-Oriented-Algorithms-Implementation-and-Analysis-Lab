#include<bits/stdc++.h>
using namespace std ;
#define int long long int 
#define float long double 
class Int 
{
    int p;
    public:
    Int(int k)
    {
        cin>>p;
    }
    Int(){p=0;}
    Int operator+(Int i2)
    {
        Int i3;
        i3.p=p+i2.p;
        return i3;
    }
    Int operator*(int k)
    {
        Int i3;
        i3.p=p*k;
        return i3;
    }
    Int operator-(Int i2)
    {
        Int i3;
        i3.p=p-i2.p;
        return i3;
    }
    Int operator*(Int i2)
    {
        Int i3;
        i3.p=p*i2.p;
        return i3;
    }
    friend ostream &operator<<(ostream &cout, Int i)
    {
        cout<<i.p;
        return cout;
    }
};
class Float
{
    float p;
    public:
    Float(int k)
    {
        cin>>p;
    }
    Float(){p=0.0;}
    Float operator+(Float f2)
    {
        Float f3;
        f3.p=p+f2.p;
        return f3;
    }
    Float operator*(int k)
    {
        Float f3;
        f3.p=p*k;
        return f3;
    }
    Float operator*(Float f2)
    {
        Float f3;
        f3.p=p*f2.p;
        return f3;
    }
    Float operator-(Float f2)
    {
        Float f3;
        f3.p=p-f2.p;
        return f3;
    }
    friend ostream &operator<<(ostream &cout, Float f)
    {
        cout<<fixed<<setprecision(6)<<f.p;
        return cout;
    }
};
class String 
{
    string p;
    public:
    friend ostream &operator<<(ostream &cout, String s)
    {
        cout<<s.p;
        return cout;
    }
    String(int k)
    {
        cin>>p;
    }
    String(){p=""; }
    String operator+(String s2)
    {
        String s3;
        s3.p="";
        s3.p=p+s2.p;
        return s3;
    }
    String operator*(int k)
    {
        String s3;
        s3.p="";
        for(int i=0;i<k;i++)
        {
            s3.p+=p;
        }
        return s3;
    }
};
class Complex
{
    Int real;
    Int imag;
    public:
    
    Complex(int k)
    {
        Int f1(1);
        real=f1;
        Int f2(1);
        imag=f2;
    }
    Complex(){}
    Complex operator+(Complex c2)
    {
        Complex c3;
        c3.real=real+c2.real;
        c3.imag=imag+c2.imag;
        return c3;
    }
    Complex operator*(int k)
    {
        Complex c3;
        c3.real=real*k;
        c3.imag=imag*k;
        return c3;
    }
    Complex operator*(Complex c2)
    {
        Complex c3;
        c3.real=real*c2.real-imag*c2.imag;
        c3.imag=real*c2.imag+imag*c2.real;
        return c3;
    }
    Complex operator-(Complex c2)
    {
        Complex c3;
        c3.real=real-c2.real;
        c3.imag=imag-c2.imag;
        return c3;
    }
    friend ostream &operator<<(ostream &cout, Complex c)
    {
        cout<<c.real<<" "<<c.imag;
        return cout;
    }
};
template<typename datatype>
class Polynomial
{
    int n;
    vector<datatype>v;
    public:
    Polynomial()
    {
        cin>>n;
        for(int i=0;i<n;i++)
        {
            datatype  g(1);
             v.push_back(g);  
        }
    }
    void  operator*(Polynomial <datatype> P2)
    {
        vector<datatype>v2=P2.v;
        int n2=P2.n;
        int p=(int)ceil(log2(max(n,n2)));
        int N=(int)pow(2,p);
        v.resize(N);
        v2.resize(N);
        vector<datatype>v3(2*N);
        v3=karastuba(v,v2,N);
        v3.resize(n+n2-1);
        int n0=(2*N)-n-n2;
        for(int i=0;i<v3.size();i++)
        {
            cout<<v3[i]<<" ";
        }
        cout<<endl;

    }
    vector<datatype> karastuba(vector<datatype>v1,vector<datatype>v2,int N)
    {
        if(N==1)
        {
            vector<datatype>v3(2);
            v3[0]=v1[0]*v2[0];
            v3[1]=datatype();
            return v3;
        }
        vector<datatype> v1low(v1.begin(),v1.begin()+N/2);
        vector<datatype> v1high(v1.begin()+N/2,v1.begin()+N);
        vector<datatype> v2low(v2.begin(),v2.begin()+N/2);
        vector<datatype> v2high(v2.begin()+N/2,v2.begin()+N);
        vector<datatype>v1l2l(N);
        vector<datatype>v1h2h(N);
        v1l2l=karastuba(v1low,v2low,(N/2));
        v1h2h=karastuba(v1high,v2high,(N/2));
        vector<datatype>v1add(N/2);
        vector<datatype>v2add(N/2);
        for(int i=0;i<N/2;i++)
        {
            v1add[i]=v1low[i]+v1high[i];
            v2add[i]=v2low[i]+v2high[i];
        }
        vector<datatype>vhl(N/2);
        vhl=karastuba(v1add,v2add,(N/2));
        vector<datatype>v3(2*N);
        for(int i=0;i<N;i++)
        {
            vhl[i]=vhl[i]-v1l2l[i]-v1h2h[i];

        }
        for(int i=0;i<N;i++)
        {
            v3[i]=v3[i]+v1l2l[i];
            v3[i+N]=v3[i+N]+v1h2h[i];
            v3[i+N/2]=v3[i+N/2]+vhl[i];

        }
        return v3;
    }
    void evaluate(int x)
    {
        datatype ans ;
        int power=1;
        for(int i=0;i<n;i++)
        {
             datatype ans1=v[i]*power;
            ans=ans1+ans;
            power=power*x;
        }
        cout<<ans<<endl;

    }
    void differntiate()
    {
        vector<datatype>ans;
        for(int i=1;i<n;i++)
        {
            datatype g ;
            g=v[i]*i;   
            ans.push_back(g);
        }
        for(int i=0;i<ans.size();i++)
        {
            cout<<ans[i]<<" ";
        }
        cout<<endl;

    }
    


};


int32_t main()
{
    int q;
    cin>>q;
    while(q--)
    {
        int op;
        cin>>op;//1-mul,2-eval,3-diff
        if(op==1)
        {
            string s;
            cin>>s;
            if(s=="integer")
            {
    
                Polynomial<Int>Poly1;
                Polynomial<Int>poly2;
                Poly1*poly2 ;

                

            }
            if(s=="float")
            {
    
                Polynomial<Float>Poly1;
                Polynomial<Float>poly2;
                Poly1*poly2 ;
            }
             if(s=="complex")
            {
    
                Polynomial<Complex>Poly1;
                Polynomial<Complex>poly2;
                Poly1*poly2 ;
            
            }
        }
        else if(op==2)
        {
            string s;
            cin>>s;
            if(s=="integer")
            {
                Polynomial<Int>Poly1;
                int x;
                cin>>x;
                Poly1.evaluate(x);
            }
            if(s=="float")
            {
                Polynomial<Float>Poly1;
                int x;
                cin>>x;
                Poly1.evaluate(x);
            }
             if(s=="string")
            {
    
                Polynomial<String>Poly1;
                int x;
                cin>>x;
                Poly1.evaluate(x);
            }
        
        }
        else 
        {
            string s;
            cin>>s;
            if(s=="integer")
            {
                Polynomial<Int>Poly1;
                Poly1.differntiate();
            }
            else if(s=="float")
            {
                Polynomial<Float>Poly1;
                Poly1.differntiate();
            }
            
        }
    }
        
}   

