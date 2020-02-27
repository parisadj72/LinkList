#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
using namespace std;

string s2;
string s3;
class node
{
    int data ;
    node * next ;
public :
    node ( int data , node * next = 0 )
    {
        this ->data = data ;
        this->next = next ;
    }

    int get_data ( )
    {
        return data ;
    }
    void set_data (int data )
    {
        this->data = data ;
    }
    node * get_next ()
    {
        return next ;
    }
    void set_next ( node * next )
    {
        this->next = next ;
    }
};

class link_list
{
protected:
    node * head ;
    node * tail ;
public:
    link_list ()
    {
        head = 0 ;
        tail = 0 ;
    }

    ~ link_list ()
    {
        node * ptr = head ;
        while ( ptr )
        {
            node * tmp = ptr->get_next() ;
            delete ptr ;
            ptr = tmp ;
        }
        head = 0 ;
        tail = 0 ;
    }

    void add_front ( int d );

    void add_back ( int d );

    void print();

};

void link_list::add_front ( int d )
{
    node * ptr = new node ( d , this->head ) ;

    if ( head == 0 )
        this->tail = ptr ;
    this->head = ptr ;
}

void link_list::print ()
{
    if(head==0 && tail==0)
    {
        cout<<"Empty list!"<<endl;
    }
    node * ptr = this->head ;
    while ( ptr )
    {
        cout << ptr->get_data()<< endl ;
        ptr = ptr ->get_next() ;
    }
}

void link_list::add_back ( int d )
{
    if ( this->head == 0 )
        this->add_front(d);
    else
    {
        node * tmp = new node ( d );
        tail->set_next(tmp);
        this->tail = tmp;
    }
}

class MY_link_list : public link_list
{
private:
    string s;
public:
    MY_link_list(string t)
    {
        head = 0 ;
        tail = 0 ;
        s=t;
    }

    void add_front(int a)
    {
        if(s=="parisa")
        {
           link_list:: add_front(a);
        }
        if(s=="Even")
        {
          if(a%2==0)
             link_list::add_front(a);
          else
              return ;
        }
        else if(s=="Odd")
        {
            if(a%2!=0)
                link_list::add_front(a);
                else
                    return ;
        }
    }

    void add_back(int a)
    {
        if(s=="parisa")
        {
           link_list:: add_back(a);
        }
        if(s=="Even")
        {
            if(a%2==0)
                link_list::add_back(a);
            else
                return ;
        }

        if(s=="Odd")
        {
            if(a%2!=0)
                link_list::add_back(a);
            else
                return ;
        }

    }

    MY_link_list operator + ( MY_link_list & y )
    {
        MY_link_list r("parisa") ;
        node * ptr1=y.head;
        node * tmp = head ;
        while(tmp!=0)
        {
            r.add_back(tmp->get_data());
            tmp = tmp->get_next() ;
        }

        while(ptr1!=0)
        {
            tmp=head;
            while(tmp!=0)
            {
                if(ptr1->get_data()==tmp->get_data())
                {
                    break;
                }
                else if(tmp->get_next()==NULL)
                {
                    r.add_back(ptr1->get_data());
                    tmp=tmp->get_next();
                }
                else
                    tmp = tmp->get_next() ;
            }
            ptr1=ptr1->get_next();
        }
        return r ;
    }

    MY_link_list operator - ( MY_link_list & y )
    {
        MY_link_list r("parisa");
        node * ptr1=y.head;
        node * tmp=head;
        while(tmp)
        {
            ptr1=y.head;
            while(ptr1)
            {
                if(tmp->get_data()==ptr1->get_data())
                {
                    break;
                }
                if(ptr1->get_next()==0)
                {
                    r.add_back(tmp->get_data());
                    break;
                }
                ptr1=ptr1->get_next();
            }
            tmp=tmp->get_next();
        }
        return r;
    }

};

int main()
{
    string s1;
    ifstream parisa;
    parisa.open("par.txt");
    if (!parisa)
    {
        cout << "can't open par.txt" << endl ;
        return 0;
    }
    int i;
    parisa >> s1;
    s3=s1;
    MY_link_list l(s1) ;
    while(!parisa.eof())
    {
        parisa >> s1;
        if (s1 == "AddF")
        {
            parisa >> s1;
            istringstream(s1)>>i;
                l.add_front(i);
        }
        else if (s1 == "AddB")
        {
            parisa >> s1;
            istringstream(s1)>>i;
                l.add_back(i);
        }
        else if(s1=="Odd" || s1=="Even")
        {
            s2=s1;
            break;
        }
    }

    MY_link_list ll(s1);
    while(!parisa.eof())
    {
        parisa >> s1;
        if (s1 == "AddF")
        {
            parisa >> s1;
            istringstream(s1)>>i;
                ll.add_front(i);
        }
        else if (s1 == "AddB")
        {
            parisa >> s1;
            istringstream(s1)>>i;
                ll.add_back(i);
        }
    }


    cout<<s3<<":"<<endl;
    l.print();
    cout<<s2<<":"<<endl;
    ll.print();
    cout<<"Sum:"<<endl;
    (l+ll).print();
    cout<<"Difference:"<<endl;
    (l-ll).print();

    parisa.close();
    l.~link_list();

    return 0;
}
