#include<bits/stdc++.h>
using namespace std ;

class Book
{
    public:
    string title;
    string author;
    Book(string t,string a,string i,int c,int to)
    {
        title=t;author=a;isbn=i;copiesavail=c;totalcopies=to;
    }
    Book()
    {
         title="UnknownTitle";author="UnknownAuthor";isbn="ISBN"  ;copiesavail=0;totalcopies=5;
    }
    Book(Book b,string i)
    {
        title=b.title;author=b.author;isbn=i;copiesavail=b.copiesavail ;totalcopies=b.totalcopies;
    }
    string getisbn()
    {
        return isbn;
    }
    int getcopiesavail()
    {
        return copiesavail;
    }
    int gettotalcopies()
    {
        return totalcopies;
    }
    void updatecopies(int count)
    {
        if(count>=0)
        {
            copiesavail+=count;
            totalcopies+=count;
        }
        else
        {
            if(copiesavail+count<0)
            {
                cout<<"Invalid request! Count becomes negative"<<endl;
            }
            else
            {
                copiesavail+=count;
                totalcopies+=count;
            }
        }
    }
    bool borrowbook()
    {
        if(copiesavail==0)
        {
            cout<<"Invalid request! Copy of book not available"<<endl;
            return false;
        }
       
            copiesavail-=1;
            return true;
        
    }
    bool bookstoringlimit()
    {
         if(copiesavail==totalcopies)
        {
            
            return true ;
        }
       
         return false;
    }
    bool returnbook()
    {
        if(copiesavail==totalcopies)
        {
            cout<<"Invalid request! Copy of book exceeds total copies"<<endl;
            return false;
        }
       
            copiesavail+=1;
            return true;
        
    }
    void printdetails()
    {
        cout<<title<<" "<<author<<endl;
    }
    private :
    string isbn;
    int copiesavail;
    int totalcopies;

};
class Member
{
    private:
    string memberid;
    int borrowlimit;
    int booksborrowed;
    map<string,int>borrowedbooks;
    public:
    bool reachedlimit()
    {
         if(booksborrowed==borrowlimit)
        {
           
            return true;
        }
       
            return false;
    }
    string getid()
    {
        return memberid;
    }
    string name;
    Member(string id,string n)
    {
        memberid=id;name=n;borrowlimit=3;booksborrowed=0;
    }
    Member(string id,string n,int b)
    {
        memberid=id;name=n;borrowlimit=b;booksborrowed=0;
    }
    bool borrowBook(string i)
    {
        if(booksborrowed==borrowlimit)
        {
            cout<<"Invalid request! Borrow limit exceeded"<<endl;
            return false;
        }
        
            booksborrowed++;
            borrowedbooks[i]++;
            return true;
    }
    bool nottakenthebook(string i)
    {
         if(borrowedbooks.find(i)==borrowedbooks.end())
        
        {
            
            return true ;
        }
        
            return false;
        
    }
    bool returnBook(string i)
    {
        if(borrowedbooks.find(i)==borrowedbooks.end())
        {
            cout<<"Invalid request! Book not borrowed"<<endl;
            return false;
        }
        
            booksborrowed--;
            borrowedbooks[i]--;
            if(borrowedbooks[i]==0)borrowedbooks.erase(i);
            return true;

        
    }
    void print()
    {
        for(auto it = borrowedbooks.begin();it!=borrowedbooks.end();it++)
        {
            if(it->second!=0)
            {
                cout<<memberid<<" "<<name<<" "<<it->first<<" "<<it->second<<endl;
            }
        }
    }
};
class Library
{
    private:
    vector<Book>books;
    vector<Member>members;
    public:
    Book *  getbookfromisbn(string isbn)
    {
        int i;
        for( i=0;i<(int)books.size();i++)
        {
            if(isbn==books[i].getisbn())
            {
                break;  // check with unknown name books i.e default constructor
            }
        } 
        
            
             return & books[i];
        

    }
    Member * getmemberfromid(string id)
    {
         int j;
        for( j=0;j<(int)members.size();j++)
        {
            if(id==members[j].getid())
            {
                break;  // check with unknown name books i.e default constructor
            }
        }   
       
            return &members[j];  
        
    }
    bool addbook(Book &b)
    {
        string s=b.getisbn(); 
        int i;
        for( i=0;i<(int)books.size();i++)
        {
            if(s==books[i].getisbn())
            {
                break;  // check with unknown name books i.e default constructor
            }
        }
        if(i!=(int)books.size())
        {
            cout<<"Invalid request! Book with same isbn already exists"<<endl;
            return false;
        }
        
            books.push_back(b);
            return true ;
        
    }
    bool addmember(Member &m)
    {
        string s=m.getid(); // need to friend with book
        int i;
        for( i=0;i<(int)members.size();i++)
        {
            if(s==members[i].getid())
            {
                break;  // check with unknown name books i.e default constructor
            }
        }
        if(i!=(int)members.size())
        {
            cout<<"Invalid request! Member with same id already exists"<<endl;
            return false;
        }
        
            members.push_back(m);
            return true ;
        
    }
    bool BorrowBook(string id,string isbn)
    {
      
        {
              Book &b=*getbookfromisbn(isbn) ;
              if(b.getcopiesavail()==0)
              {
                    return b.borrowbook();
              }
              else 
              {
                   
                        {
                            Member &m=*getmemberfromid(id);
                            if(m.reachedlimit())
                            {
                                return m.borrowBook(isbn);
                            }
                            else
                            {
                                b.borrowbook();
                                m.borrowBook(isbn);

                            }

                        }    
                             
              }
        }
        return true;
 
    }
    bool ReturnBook(string id,string isbn)
    {
 
        {
            
              Book &b=*getbookfromisbn(isbn) ;
              if(b.bookstoringlimit())
              {
                    return b.returnbook();
              }
              else 
              {
                
                {
                    Member &m=*getmemberfromid(id);
                    if(m.nottakenthebook(isbn) )
                    {
                        return m.returnBook(isbn);
                    }
                    else
                    {
                        b.returnbook();
                        m.returnBook(isbn);

                    }

                }    
                                                 
              }
        }
        return true ;
      
    }
    void printlibrarydetails()
    {
        int i;
        for( i=0;i<(int)books.size();i++)
        {
           Book b=books[i];
            cout<<b.title<<" "<<b.author<<" "<<b.getcopiesavail()<<endl;
        }  
        int j;
        for( j=0;j<(int)members.size();j++)
        {
                Member m=members[j];
                cout<<m.getid()<<" "<<m.name<<" "<<endl;

        } 
    }

};


int main()
{
//no two books have same isbn
Library lib;
while( 1)
{
    string s;
    cin>>s;
    if(s=="Book")
    {
        string s1;
        cin>>s1;
        if(s1=="None")
        {
            Book b;
            lib.addbook(b);


        }
        else if(s1=="ExistingBook")
        {
             string s2,s3;
             cin>>s2>>s3;
            Book b=*lib.getbookfromisbn(s2) ;
            //Book* c = new Book(b,s3);
            Book c(b,s3);
            lib.addbook(c);
           
        }
        else
        {
            string s2,s3;
            cin>>s2>>s3;
            int x,y;
            cin>>x>>y;
            Book c(s1,s2,s3,x,y);
            lib.addbook(c);
        }
    }
    else if(s=="UpdateCopiesCount")
    {
        string s1;
        int n;
        cin>>s1>>n;
        Book * b=lib.getbookfromisbn(s1) ;
        b->updatecopies(n);


    }
    else if(s=="Member")
    {
        string s1;
        cin>>s1;
        if(s1=="NoBorrowLimit")
        {
            string s2,s3;
            cin>>s2>>s3;
            Member m(s2,s3);
            lib.addmember(m);

        }
        else
        {
            string s2;
            int n;
            cin>>s2>>n;
            Member m(s1,s2,n);
            lib.addmember(m);
        }
    }
    else if(s=="Borrow")
    {
       string s2,s3;
            cin>>s2>>s3;
             lib.BorrowBook(s2,s3);

    }
    else if(s=="Return")
    {
       string s2,s3;
            cin>>s2>>s3;
             lib.ReturnBook(s2,s3);
             
    }
    else if (s=="PrintBook")
    {
         string s1;
        cin>>s1;
        Book b=*lib.getbookfromisbn(s1);
        b.printdetails();
    }
    else if(s=="PrintMember")
    {
        string s1;
        cin>>s1;
        Member m=*lib.getmemberfromid(s1);
        m.print();

    }
    else if(s=="PrintLibrary")
    {
        lib.printlibrarydetails();
    }
    else if(s=="Done")
    {
        break;
    }
    }

}