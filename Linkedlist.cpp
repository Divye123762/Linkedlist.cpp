#include<iostream>
#include<iterator>
#include<list>
using namespace std;

class Node{
    public:
    int data;
    Node* next;
public:
        Node(int val){
            data = val;
            next = NULL;

        }
        // ~Node(){
        //     cout<<"~Node "<<data<<endl;
        //     if(  next  !=NULL){
        //         delete next;
        //         next = NULL;

        //     }

            
        // }

        
    };
 class List{
    public:
    
    Node* head;
    Node* tail;
     public:
    List(){
        head = NULL;
        tail=NULL;
    }
    // ~List(){
    //     cout<<"~List "<<endl;
    //     if(head!=NULL){
    //         delete head ;
    //         head = NULL;
    //     }
    // }

    void push_front(int val){
        Node* newNode = new Node(val);
        if(head==NULL){
            head=tail=newNode;
        }
        else{
            newNode->next =head;
            head=newNode;

        }

    }
    void printlist(){
        Node* temp= head;
        while(temp!=NULL){
            cout<<temp->data<<" -> ";
            temp = temp->next;
        }
        cout<<" NULL"<<endl;
    }
    void push_back(int val){
        Node* newNode = new Node(val);
        if(head==NULL){
            head=tail=newNode;// no node present initally
        }
        else{
            tail->next =newNode;
            tail=newNode;

        }

    }
    void insert(int val, int pos){
        Node* newNode = new Node( val);
        Node* temp = head;
        for(int i=0; i<pos-1; i++){
            if(temp==NULL){
                cout<<" position is invalid "<<endl;
                return ;
            }
            temp= temp->next;
        }
        newNode->next= temp->next;
        temp->next=newNode;
        

    }
    void pop_front(){
        if (head==NULL){
            cout<<" list is empty"<<endl;
            return;
        }
        Node* temp= head;
        head = head->next;
        temp->next = NULL;
        delete temp;
    }

    void pop_back(){
        Node* temp = head;
        while(temp->next->next !=NULL){
            temp=temp->next;
        }
        temp->next=NULL;// temp= tail prev
        delete tail;
        tail=temp;
    }
    int searchitr(int key){
        Node* temp= head;
        int idx=0;
        while(temp!=NULL){
            if(temp->data==key){
                return idx;
            }
            temp= temp->next;
            idx++;
        }
        return -1;
    }
    int helper(Node*h, int key){
        if(h==NULL){
            return -1;
        }
        if(h->data==key){
            return 0;
        }
        int idx=helper(h->next ,key);
        if (idx==-1)
        {
            return -1;
        }
        return idx+1;
        
    }
    int searchrec(int key){
        return helper(head,key);
    }
    void reverse(){
        Node* curr= head;
        Node* prev= NULL;
        while (curr!=NULL)
        {
            Node* next = curr->next;
            curr->next=prev;
            // updations for next itr
            prev=curr;
            curr=next;
        }
         head= prev;
        
    }
    int getsize(){
        int sz=0;
        Node* temp=head;
        while(temp!=NULL){
            temp= temp->next;
            sz++;
        }
        return sz;
    }
    void removeNth(int n){
        int size= getsize();
        Node* prev= head;
        for(int i=1; i<(size-n); i++){
            prev= prev->next;
        }
        Node* todel= prev->next;
        cout<<"going to delete :"<< todel->data<<endl;
        prev->next=prev->next->next;
    }
    
     
    
    
 } ; 
 void printlist(Node* head){ 
        Node* temp= head;
        while(temp!=NULL){
            cout<<temp->data<<" -> ";
            temp = temp->next;
        }
        cout<<" NULL"<<endl;
    }
 bool iscycle(Node* head){
        Node* slow= head;
        Node* fast = head;
        while(fast!=NULL && fast->next!=NULL){
            slow= slow->next;
            fast=fast->next->next;
            if(slow==fast){
            cout<<"cycle exits"<<endl;
            return true;
        }
        }
        
        cout<<"cycle does not exits"<<endl;
        return false;
     }
     void removecycle(Node* head){
        // step 1- detect cycle
        Node* slow= head;
        Node* fast= head;
        bool iscycle=false;
        while(fast!=NULL && fast->next!=NULL){
            slow=slow->next;
            fast=fast->next->next;
            if(slow==fast){
                cout<<" cycle exists"<<endl;
                iscycle= true;
                break;
            }
            if(!iscycle){
                cout<<"cycle does not exit "<<endl;
            }
            slow=head;// special case tail->head
            if(slow==fast){
                while(fast->next!=slow){
                    fast=fast->next;
                }
                fast->next=NULL;

            }
            else{
                Node* prev= fast;
                while(slow!=fast){
                    slow=slow->next;
                    prev=fast;
                    fast= fast->next;

                }
                prev->next=NULL; // remove cycle
            }
        }
        
     }
    //   void printList(list<int> ll){
    //     list<int>:: iterator itr;
    //     for(itr=ll.begin(); itr!=ll.end();itr++){
    //         cout<<(*itr)<<" -> ";
    //     }
    //     cout<<"NULL"<< endl;
    //   }
      Node* splitAtMid(Node* head){
        Node* slow= head;
        Node* fast= head;
        Node* prev = NULL;
        while(fast!=NULL && fast->next!=NULL){
            prev= slow;
            slow= slow->next;
            fast=fast->next->next;
        }
        if(prev!=NULL){
            prev->next= NULL;
        }
        return slow;// righthead
      }
      Node* merge(Node* left , Node* right){
        List ans;
        Node* i= left;
        Node*j= right;
        while(i!=NULL && j!=NULL){
            if(i->data <= j->data){
                ans.push_back(i->data);
                i=i->next;
            }
            else{
                ans.push_back(j->data);
                j=j->next;
            }
        }
        while(i!=NULL){
            ans.push_back(i->data);
            i=i->next;
        }
        while(j!=NULL){
            ans.push_back(j->data);
            j=j->next;
        }
        return ans.head;

      }


      Node* mergesort(Node* head){
        if(head==NULL || head->next==NULL ){
            return head;
        }
        Node* rightHead =splitAtMid(head);

        Node* left=mergesort(head); // left head
        Node* right = mergesort(rightHead) ;// right head
       return merge(left, right);// head of the sorted list

      }
      Node* reverse(Node* head){
        Node* curr = head;
        Node* next= NULL;
        Node* prev = NULL;
        while(curr!=NULL){
            next= curr->next;
            curr->next= prev;
            prev= curr;
            curr=next;
        }
        return prev ; //  prev is head of reverse linked list
      }
      Node* zigzag(Node* head){
        Node* rightHead =splitAtMid(head);
        Node* rightHeadRev= reverse(rightHead);
        // alternating merging
        Node* left= head;
        Node* right= rightHeadRev;
        Node* tail= right;
        while(left!=NULL && right!=NULL){
            Node* nextleft= left->next;
            Node* nextright= right->next;
            
            left->next=right;
            right->next=nextleft;
            tail= right;
            left= nextleft;
            right=nextright;
        }
        if(right!=NULL){
            tail->next=right;

        }
        return head;
      }

 int main() {
    // List ll;
    // list<int> ll;
    // ll.push_front(4);
    // ll.push_front(3);
    // ll.push_front(2);
    // ll.push_front(1);
    // cout<<" size of list:"<<ll.size()<<endl;
    // cout<<" head: "<<ll.front()<<endl;
    // cout<<" tail: "<<ll.back()<<endl;
    // ll.pop_back();
    // printList(ll);
    
    
    
  //  ll.printlist();
     
  //  ll.printlist();
//   ll.push_front(4);
//     ll.push_front(3);
//     ll.push_front(2);
//     ll.push_front(1);
   // ll.insert(100,2);
   // ll.pop_front();
  // ll.pop_back();
//   cout<<  ll.searchitr(5)<<endl;
//     ll.printlist();
// cout<<ll.searchrec(4); 
// ll.reverse();
// ll.removeNth(2);
// ll.printlist();
//  ll.tail->next= ll.head;
//  iscycle(ll.head);
// removecycle(ll.head);
// printlist(ll.head);
List ll;
ll.push_front(5);
ll.push_front(4);
ll.push_front(3);
ll.push_front(2);
 ll.push_front(1);
 printlist(ll.head);
//  ll.head = mergesort(ll.head);
//  printlist(ll.head);
ll.head=zigzag(ll.head);
printlist(ll.head);


    


    return 0;
 }

