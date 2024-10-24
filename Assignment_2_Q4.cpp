#include <iostream>
using namespace std;

struct Node
{
    int val;
    Node* next;
    Node* prev;

    Node(int value) : val(value) , next(nullptr) , prev(nullptr) {} 
};

class Doubly_Linked_List
{
    private:
    Node* head;
    Node* tail;

    public:
    Doubly_Linked_List() : head(nullptr) , tail(nullptr) {}

    //Insertion is done at head
    void insertion(int value)
    {
        Node* new_node = new Node(value);

        if(head == nullptr)
        {
            head = tail = new_node;
            cout << "New node inserted at start\n";
        }
        else
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
            cout << "New node inserted at start\n";
        }
    }

    void display()
    {
        Node* temp = head;
        int index = 0;

        while(temp != nullptr)
        {
            cout << "Index : " << index++ << " Value : " << temp->val << endl;
            temp = temp->next;
        }

        cout << endl;
    }

    //Fucntion to create a new head
    bool position_head(int pos)
    {
        Node* temp = head;

        if(pos == 0)
        {
            return true;
        }

        for(int i = 0 ; i < pos ; i++)
        {
            if(temp->next == nullptr)
            {
                return false;
            }
            temp = temp->next;
        }



        temp->prev->next = nullptr;
        Node* temp_tail = temp->prev;
        temp->prev = nullptr;
         
        tail->next = head;
        head->prev = tail;
        head = temp;
        tail = temp_tail;

        return true;

    }

};

int main()
{
    Doubly_Linked_List list;
    list.insertion(1);
    list.insertion(2);
    list.insertion(8);
    list.insertion(3);
    list.insertion(11);
    cout << endl;

    list.display();
    cout << endl;

    if(list.position_head(2))
    {
        list.display();
    }
    else
    {
        cout << "Error\n";
    }

}