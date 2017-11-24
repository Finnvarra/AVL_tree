#include <iostream>
#include <string>
#include <fstream>
using namespace std;
template <typename value>
class List
{
private:
    struct Node
    {
        value item;
        Node* prev;
        Node* next;
    };
    int count;
    int e;
    Node* head;
    Node* tail;
   // ofstream out;
    value stuff;
public:
List()
    {
        head=NULL;
        tail=NULL;
        stuff=NULL;
        e=0;
        count=0;
    }
~List()
    {
        e=1;
        clear();
        //out.close();
    }
void clear()
    {
        if(e == 0)
        {
            //out<<"clear"<<endl;
        }
        e=1;
        while (count != 0)
        {
            remove(0);
        }
        e=0;
    }
void insert(int i, value n)
    {
        Node* node=new Node();
        node->item=n;
        if (tail == NULL && head == NULL)
        {
            head=node;
            tail=node;
        }
        else if (i>count || i < 0)
        {
        }
        else
        {
            if (i == 0)
            {
               // cout<<"head insert "<<node->item<<endl;
                head->prev=node;
                node->next=head;
                node->prev=NULL;
                head=node;
            }
            else if (i == count)
            {
               // cout<<"tail insert "<<node->item<<endl;
                tail->next=node;
                node->prev=tail;
                node->next=NULL;
                tail=node;
            }
           else
           {
               interInsert(i, n, node);
           }
        }
        //out<<"insert "<<i<<" "<<n<<endl;
        count++;
    }
    
void interInsert(int i, value n, Node* node)
{
    int med=count/2;
        if (i>med)
            {
                int num = count-1;
                Node* temp2=tail->prev;
                Node* temp=tail;
                while(num != i)
                {
                    temp2=temp2->prev;
                    temp=temp->prev;
                    num--;
                }
                temp2->next=node;
                node->prev=temp2;
                temp->prev=node;
                node->next=temp;
               // delete temp;
                //delete temp2;//how do I delete these without causing more problems
                //node->next=temp->next;
            }
            else if (i<=med)
            {
                int num =1;
                Node* temp2=head->next;
                Node* temp=head;
                while(num != i)
                {
                    temp2=temp2->next;
                    temp=temp->next;
                    num++;
                }
                node->next=temp2;
                temp2->prev=node;
                node->prev=temp;
                temp->next=node;
            }
           // out<<"insert "<<i<<" "<<n<<endl;
}

void print()
    {
       // out<<"print"<<endl;
        Node* temp=head;
        for(int i =0; i<count; i++)
        {
         //   out<<"node "<<i<<":"<<" "<<temp->item<<endl;
            if (temp->next != NULL)
            {
            temp=temp->next;
            }
        }
    }
value find(value n)
    {
        Node* temp =head;
        for (int i=0; i<count; i++)
        {
            if (temp->item == n)
            {
               // out<<"find "<<n<<" "<<i<<endl;
                return temp->item;
            }
            temp=temp->next;
        }
        return NULL;
       // out<<"find "<<n<<" "<<-1<<endl;
    }
    
    value iter(int n)
    {
        Node* temp =head;
        for (int i=0; i<count; i++)
        {
            if (i == n)
            {
                // out<<"find "<<n<<" "<<i<<endl;
                return temp->item;
            }
            temp=temp->next;
        }
        return NULL;
        // out<<"find "<<n<<" "<<-1<<endl

    }
value remove(int i)
    {
        Node* temp;
        if (i<0 || i > count || count == 0)
        {
        }
        else if (count ==1)
        {
            temp=head;
            temp->prev=NULL;
            temp->next=NULL;
            stuff=head->item;
            delete temp;
            head=NULL;
            tail=NULL;
        }
        else if (i == 0)
        {
            temp=head->next;
            stuff=head->item;
            delete head;
            temp->prev=NULL;
            head=temp;
            //out<<"remove "<<i<<" "<<stuff<<endl;
        }
        else if (i== count-1)
        {
            temp=tail->prev;
            stuff=tail->item;
            delete tail;
            temp->next=NULL;
            tail=temp;
           // out<<"remove "<<i<<" "<<stuff<<endl;
        }
        else
        {
            interRemove(i);
        }
        if (e == 0)
        {
        //out<<"remove "<<i<<" "<<stuff<<endl;
        }
        count--;
        return stuff;
    }
    
    void interRemove(int i)
    {
        int med= count/2;
        Node* temp;
        Node* temp2;
        Node* gone;
         if(i > med)
            {
                temp2=tail->prev->prev;
                temp =tail;
                gone=tail->prev;
                int num =count-2;
                while(num != i)
                {
                    temp2=temp2->prev;
                    temp=temp->prev;
                    gone=gone->prev;
                    num--;
                }
                temp2->next=temp;
                temp->prev=temp2;
                gone->next=NULL;
                gone->prev=NULL;
                stuff=gone->item;
                delete gone;
                //out<<"remove "<<i<<" "<<stuff<<endl;
            }
            else if (i <= med)
            {
                temp2=head->next->next;
                temp=head;
                gone=head->next;
                int num=1;
                while (num != i)
                {
                    temp2=temp2->next;
                    temp=temp->next;
                    gone=gone->next;
                    num++;
                }
                //cout<<temp2->item<<endl;
                temp2->prev=temp;
                temp->next=temp2;
                gone->prev=NULL;
                gone->next=NULL;
                stuff=gone->item;
                delete gone;
                //out<<"remove "<<i<<" "<<stuff<<endl;
            }
    }
    int size()
    {
        return count;
    }
};