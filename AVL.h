#include "LinkedList.h"
#include <cmath>
template <typename info>
class AVL
{
private:
    struct Node
    {
        info item;
        Node* left;
        Node* right;
        int height;
    };
    List <Node*> queue;
    Node* root;
    int high;
    int e;
   // int bole;
    ofstream out;
public:
    AVL(string file)
    {
        out.open(file);
        root=NULL;
        e=0;
    }
    ~AVL()
    {
        e=1;
        clear();
        out.close();
    }
    void clear()
    {
        if (e== 0)
        {
            out<<"clear"<<endl;
        }
        while (root != NULL)
        {
            remove(root->item);
        }
        
    }
    
    void add(info name)
    {
        out<<"add "<<name<<endl;
        rec_add(name, root);
       // cout<<"balanced"<<endl;
    }
    
    void rec_add(info name, Node*&temp)
    {
        if(temp == NULL)
        {
            Node* node= new Node();
            node->item=name;
            //cout<<"add "<<name<<endl;
            node->height=1;
            node->left=NULL;
            node->right=NULL;
            temp = node;
            return;
        }
        else if (name < temp->item)
        {
            rec_add(name, temp->left);
           // balance(temp);
        }
        else if (name > temp->item)
        {
            rec_add(name, temp->right);
            //balance(temp);
        }
        else
        {
            return;
        }
        updateheight(temp);
       // cout<<temp->item<<endl;
       balance(temp);
    }
    
    void print()
    {
        out<<"print"<<endl;
        Node* temp= root;
        if (temp != NULL)
        {
        queue.insert(0, temp);
        }
        int count =0;
        while (queue.size() != 0)
        {
            int size= queue.size();
            out<<"level "<<count<<":";
            for (int i=0; i<size; i++)
            {
                Node* n= queue.remove(0);
                if (n->left != NULL)
                {
                queue.insert(queue.size(), n->left);
                }
                if (n->right != NULL)
                {
                queue.insert(queue.size(), n->right);
                }
                out<<" "<<n->item<<"("<<updateheight(n)<<")";
            }
            out<<endl;
            count++;
        }
    }
    
    void find(string name)
    {
       // if (root == NULL)
        //{
          //  cout<<"find "<<name<<" false"<<endl;
            //return NULL;
        //}
        Node* temp=root;
        rec_find(name, temp);
    }
    
    void rec_find(string name, Node* &cur)
    {
        if (cur == NULL)
        {
            out<<"find "<<name<<" false"<<endl;
            return;
        }
        else if (name <  cur->item)
        {
            rec_find(name, cur->left);
        }
        else if (name > cur->item)
        {
            rec_find(name, cur->right);
        }
        else
        {
        out<<"find "<<name<<" true"<<endl;
        }
    }
    
    void remove(info name)
    {
        if (e==0)
        {
            out<<"remove "<<name<<endl;
        }
        rec_rem(root, name);
    }
    
   void rec_rem (Node*& cur, info name)
    {
        if (cur == NULL)
        {
            return;
        }
        else if (name > cur->item)
        {
            rec_rem(cur->right, name);
            updateheight(cur);
        }
        else if (name < cur-> item)
        {
            rec_rem(cur->left, name);
            updateheight(cur);
        }
        else
        {
            if (cur->left == NULL && cur->right == NULL)
            {
                delete cur;
                //balance(temp);
                cur=NULL;
                //updateheight(cur);
                return;
            }
            else if (cur->left != NULL && cur->right == NULL)
            {
                Node* temp= cur->left;
                delete cur;
                cur= temp;
                updateheight(cur);
                //cout<<cur->item<<" "<<getheight(cur)<<endl;
                return;
            }
            else if (cur->right != NULL && cur->left == NULL)
            {
                Node* temp = cur->right;
                delete cur;
                cur= temp;
                updateheight(cur);
                return;
            }
            else if (cur->left != NULL && cur->right != NULL)
            {
                Node* temp= cur->right;
                while (temp->left != NULL)
                {
                    temp=temp->left;
                }
                //Node* child=temp->right;
                cur->item=temp->item;
                rec_rem(cur->right, temp->item);
                //updateheight(cur);
                //balance(cur);
                //return;
            }
            //updateheight(cur);
            //balance(cur);
        }
        updateheight(cur);
        balance(cur);
        return;
    }
    
    int getheight (Node* n)
    {
        if (n != NULL)
        {
        return n->height;
        }
        else
        {
            return 0;
        }
    }
    
    int updateheight (Node*& n)
    {
        //cout<<n->item<<" "<<getheight(n->left)<<" "<<getheight(n->right) <<endl;
       return n->height = max(getheight(n->left), getheight(n->right))+1;
    }
    
    int max (int l, int r)
    {
        if (l > r)
        {
            return l;
        }
        return r;
    }
    
    void balance (Node*& cur)
    {
        int diff=getheight(cur->right)-getheight(cur->left);
       // cout<<cur->item<<" balance "<<diff<<endl;
        if (diff > 1)//left rotation
        {
            Node* temp= cur->right;
            int lrot=getheight(temp->right)-getheight(temp->left);
            //cout<<"second balance "<<lrot<<endl;
            if (lrot >= 0)
            {
                //lr
                leftr(cur);
            }
            else
            {
                //cout<<"rlr"<<endl;
                //rlr
                rightleftr(cur);
            }
        }
        else if (diff < -1)//right rotation
        {
            Node* temp= cur->left;
            int rrot=getheight(temp->right)-getheight(temp->left);
            //cout<<"second balance "<<rrot<<endl;
            if (rrot > 0)
            {
                leftrightr(cur);
            }
            else
            {
                rightr(cur);
            }
        }
    }
    
    void rightr (Node*& p)
    {
      
        Node* n=p->left;//mom
        p->left=n->right;//mom right
        n->right=p;//mom right tom
        p=n;//tom becomes mom
        updateheight(p->right);
        updateheight(p);
    }
    void leftr(Node*&p)
    {
        //cout<<p->item<<endl;
        Node* n=p->right;
        p->right=n->left;
        n->left=p;
        p=n;
        updateheight(p->left);
        updateheight(p);

    }
    
    void leftrightr(Node*&p)
    {
        leftr(p->left);
        rightr(p);
    }
    
    void rightleftr(Node*&p)
    { //cout<<"p data"<<p->item<<endl;
        rightr(p->right);
        leftr(p);
    }
};