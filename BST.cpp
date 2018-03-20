#include <iostream>
#include <queue>
#include <stdlib.h>
#include <time.h>

using namespace std;

class BST
{
public:
    struct Node
    {
        Node* L;
        Node* R;
        int data;

        Node(){
        L=NULL;
        R=NULL;
        }
        
        Node(int x){
            L=NULL;
            R=NULL;
            data=x;
        }
    };
    
private:
    Node* root;
    int s;
    
    int private_search(Node* &t,int key){
        if(t==NULL){
            cout<<key<<" not found\n";
            return false;}
        else if(key==t->data){
            cout<<key<<" found\n";
            return true;}
        else if(key<t->data){
            private_search(t->L,key);}
        else if(key>t->data){
            private_search(t->R,key);}
    }

    bool private_insert(Node* &t, int key){
        if(t==NULL){
            t=new Node(key);
            s++;
            cout<<key<<" inserted\n";
            return true;}
        else if(t->data==key){
            cout<<key<<" already exists\n";
            return false;}
        else if(key<t->data){
            private_insert(t->L,key);    
        }
        else if(key>t->data){
            private_insert(t->R,key);
        }
    }
    bool private_delete(Node* &t,int key){
            if(t==NULL){
                cout<<key<<" was not in tree\n";
                return false;}
            else{
                if(t->data==key){
                    cut(t);
                    s--;
                    cout<<key<<" deleted\n";
                    return true;}
                else if(key<t->data){
                    private_delete(t->L,key);}
                else if(key>t->data){
                    private_delete(t->R,key);}
                }
    }
    void cut(Node * &t){
        if(t->L==NULL && t->R==NULL){
            delete t;
            t=NULL;}
        else if(t->L!=NULL && t->R!=NULL){
            cut_both(t);}
        else if(t->L!=NULL){
            Node * temp=t->L;
            delete t;
            t=temp;
        }
        else if(t->R!=NULL){
            Node * temp=t->R;
            delete t;
            t=temp;}
    }
    void cut_both(Node * t){
        Node* temp= t->L;
        Node* parrent;
        while(temp->R!=NULL){
            temp=temp->R;
            parrent=temp;}
        t->data=temp->data;
        delete temp;
        parrent=NULL;
    }
    
    void private_show(Node * &t){
        queue<Node*> level;
        queue<Node*> by;
        Node* temp;
        level.push(t);
        while(level.size()>0){
            for(int i=level.size();i>0;i--){
                by.push(level.front());
                level.pop();}
            for(int i=by.size();i>0;i--){
                temp=by.front();
                if (temp!=NULL){
                    cout<<temp->data<<" ";
                    level.push(temp->L);
                    level.push(temp->R);
                    }
                else
                    cout<<"/ ";
                by.pop();}
            cout<<endl;
            }    
    }
    void pre_order(Node* &t){
        cout<<t->data<<" ";
        if(t->L!=NULL){
            pre_order(t->L);}
        if(t->R!=NULL){
            pre_order(t->R);}
    }
    
    void post_order(Node* &t){
        if(t->L!=NULL){
            post_order(t->L);}
        if(t->R!=NULL){
            post_order(t->R);}
        cout<<t->data<<" ";
    }
    bool check(Node* &temp){
        queue<Node*> C;
        C.push(temp);
        for(int i=C.size();i>0;i--){
            temp=C.front();
            if (temp!=NULL){
                if(temp->L != NULL && temp->data < temp->L->data){
                    cout<<"Left child "<<temp->L->data<<" is greater than parent "<<temp->data<<"; invalid tree.\n";
                    return false;}
                if(temp->R != NULL && temp->data > temp->R->data){
                    cout<<"Right child "<<temp->R->data<<" is smaller than parent "<<temp->data<<"; invalid tree.\n";
                    return false;}
                C.push(temp->L);
                C.push(temp->R);
                }
            C.pop();}
        cout<<"Tree structure valid\n";
        return true;
    }
    
public:
    BST(){
        root=NULL;
        s=0;}
        
    int size(){
        return s;}
        
    int height(){
        int height=-1;
        queue<Node*> level;
        queue<Node*> by;
        Node* temp;
        level.push(root);
        while(level.size()>0){
            for(int i=level.size();i>0;i--){
                by.push(level.front());
                level.pop();}
            for(int i=by.size();i>0;i--){
                temp=by.front();
                if (temp!=NULL){
                    level.push(temp->L);
                    level.push(temp->R);
                    }
                by.pop();}
            height++;
            }
        return height;
        }
        
    bool insert(int x){
        if(root==NULL){
            root=new Node(x);
            cout<<"A seed has been planted.\n";
            s++;
            return true;
        }
        return private_insert(root, x);
    }

    bool search(int x){
        if(root==NULL){
            cout<<"the tree is empty\n";
            return false;
        }    
        return private_search(root, x);
    }
    
    bool remove(int x){
        if(root==NULL){
            cout<<"the tree is already empty\n";
            return false;
        }
        return private_delete(root,x);
    }
    
    void show(){
        cout<<"---------------------------------\nTree: size="<<size()<<" height="<<height()<<endl;
        if(root==NULL){
            cout<<"\nThe tree is empty\n---------------------------------\n";}
        else{
            cout<<"pre-order: ";
            pre_order(root);
            cout<<"\npost-order: ";
            post_order(root);
            cout<<endl;
            private_show(root);
            cout<<"\n---------------------------------\n"<<endl;
            }
    }
    
    bool check(){
        if(root==NULL){
            cout<<"Tree structure valid\n---------------------------------\n";
            return true;}
        return check(root);
    }
    
};

int main(){
    srand(time(NULL));
    BST* t=new BST();
    t->show();
    t->check();
    int x=50;
    for(int i=0;i<x;i++){
        int x=rand()%100+1;
        t->insert(x);
        t->show();
        t->check();
        if(rand()%5==1){
            cout<<"deleting "<<x<<endl;
            t->remove(x);
            t->show();
            t->check();
        }
    }
    cout<<x<<" inserts with random deletes successful.\n";
    return 0;
}
