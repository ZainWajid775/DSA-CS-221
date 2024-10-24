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

    //Function to check if node exists
    Node* exist(int value)
    {
        Node* temp = head;

        while(temp != nullptr)
        {
            if(temp->val == value)
            {
                return temp;
            }
            temp = temp->next;
        } 
        return nullptr;
    }

    // Function to swap nodes
    void swap_nodes(int val_1, int val_2) 
    {
        // Checking if the nodes exist and getting their address
        Node* node_1 = exist(val_1);
        Node* node_2 = exist(val_2);

        if (node_1 != nullptr && node_2 != nullptr) 
        {
            // If the nodes are adjacent, handle the special case
            if (node_1->next == node_2) 
            {
                // node_1 is before node_2
                node_1->prev = node_2;
                node_2->prev = node_1->prev; // node_1's previous remains unchanged
                node_1->next = node_2->next;

                if (node_2->next != nullptr) 
                {
                    node_2->next->prev = node_1;
                } 
                else 
                {
                    tail = node_1; // Update tail if needed
                }
                
                node_2->next = node_1;
                if (node_1->prev != nullptr) 
                {
                    node_1->prev->next = node_2;
                } else 
                {
                    head = node_2; // Update head if needed
                }
                
                node_1->prev = node_2; // Correct the previous pointer
                node_2->prev = nullptr; // node_2 becomes the head
                return;
            } 
            else if (node_2->next == node_1) 
            {
                // node_2 is before node_1
                swap_nodes(val_2, val_1); // Just call the function with reversed parameters
                return;
            }

            // Swapping non-adjacent nodes
            if (node_1->prev != nullptr) 
            {
                node_1->prev->next = node_2;
            } 
            else 
            {
                head = node_2; // node_1 was head
            }

            if (node_2->prev != nullptr) 
            {
                node_2->prev->next = node_1;
            } 
            else 
            {
                head = node_1; // node_2 was head
            }

            // Adjusting the next pointers
            Node* temp_next_1 = node_1->next;
            Node* temp_next_2 = node_2->next;

            node_1->next = temp_next_2;
            node_2->next = temp_next_1;

            // Adjusting the prev pointers
            if (temp_next_1 != nullptr) 
            {
                temp_next_1->prev = node_2;
            }
            if (temp_next_2 != nullptr) 
            {
                temp_next_2->prev = node_1;
            }

            // Swap prev pointers
            Node* temp_prev_1 = node_1->prev;
            Node* temp_prev_2 = node_2->prev;

            node_1->prev = temp_prev_2;
            node_2->prev = temp_prev_1;

            // Connect the previous nodes
            if (temp_prev_1 != nullptr) 
            {
                temp_prev_1->next = node_2;
            }
            if (temp_prev_2 != nullptr) 
            {
                temp_prev_2->next = node_1;
            }

            cout << "Nodes swapped\n";
        } 
        else 
        {
            cout << "Nodes not found\n";
        }
    }
};

int main()
{
    Doubly_Linked_List list;
    list.insertion(5);
    list.insertion(4);
    list.insertion(3);
    list.insertion(2);
    list.insertion(1);
    cout << endl;

    list.display();
    cout << endl;

    list.swap_nodes(2,4);
    list.display();
}