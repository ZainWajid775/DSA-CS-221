#include <iostream>
using namespace std;

struct Node
{
    int val;
    Node* next;

    Node(int value) : val(value) , next(nullptr) {}
};

class Linked_List
{
    private:
    Node* head;

    //Length is used to account for an inner loop when printing the list
    int length;

    public:

    //Constuctor
    Linked_List() 
    {
        length = 0;
        head = nullptr;
        cout << "Linked List initialised\n";
    }

    //Check to see if linked_list is empty
    bool is_empty()
    {
        return (head == nullptr);
    }

    void check_length()
    {
        cout << "Current Size : " << length << endl;
    }

    //Insertion at head
    void insertion(int value)
    {
        Node* new_node = new Node(value);
        new_node->next = head;
        head = new_node;
        length++;

        cout << "Node added with value : " << value << endl;
    }

    //Deletion with index 
    int deletion(int index)
    {
        if(!is_empty())
        {
            Node* temp = head;

            if(index == 0)
            {
                int return_val = head->val;
                head = head->next;
                delete temp;
                cout << "Head Node deleted\n";
                length--;
                return return_val;
            }
            else
            {
                //Traversal to node
                for(int i = 0 ; i < index - 1 ; i++)
                {
                    if(temp->next == nullptr)
                    {
                        cout << "Invalid index\n";
                        return -1;
                    }
                    temp = temp->next;
                }

                Node* del_node = temp->next;
                int return_val = del_node->val;
                temp->next = del_node->next;

                delete del_node;
                length--;

                cout << "Node at index " << index << " deleted\n";
                return return_val;
            }
        }
        else
        {
            cout << "List empty\n";
            return -1;
        }
    } 

    //Display functionality
    void display()
    {
        if(!is_empty())
        {
            int index = 0;
            Node* temp = head;
            while(index != length)
            {
                cout << "Index : " << index++ << " Value : " << temp->val << endl;
                temp = temp->next; 
            }

            cout << endl;
        }
        else
        {
            cout << "List empty\n";
        }

    }

    //Fucntionality to create loop within the list
    //To account for a inner loop , length index is used to avoid repitition
    void create_loop(int index)
    {
        if(!is_empty())
        {
            Node* temp = head;
            Node* loop_node = head;

            //Traversal to last node
            while(temp->next != nullptr)
            {
                temp = temp->next;
            }

            //Traversal to node to loop to
            for(int i = 0 ; i < index ; i++)
            {
                if(loop_node == nullptr)
                {
                    cout << "Loop node not found\n";
                    return;
                }
                loop_node = loop_node->next;
            }

            //Linking pointers to create a loop
            temp->next = loop_node;
            cout << "Loop created at index : " << index << endl;
        }
    }

    void remove_loop()
    {
        //As loop will always be at last index , we traverse till there
        Node* last_node = head;

        for(int i = 0 ; i < length - 1 ; i++)
        {
            last_node = last_node->next;
        }

        Node* loop_node = last_node->next;

        //Traversing to looped node to find its index
        Node* temp = head;
        int index = 1;
        while(temp != loop_node)
        {
            temp = temp->next;
            index++;
        }

        //Correcting the loop
        last_node->next = nullptr;

        cout << "Loop removed from node no. " << length << " to node no. " << index << endl;
        cout << "Loop Node value : " << loop_node->val << endl;

    }
};

int main()
{
    //Creating LL and inserting values
    Linked_List list;
    cout << endl;

    list.insertion(1);
    list.insertion(2);
    list.insertion(8);
    list.insertion(3);
    list.insertion(11);
    cout << endl;
    list.display();

    //Changing last nodes next to simulate a loop
    list.create_loop(2);
    cout << endl;

    //Removing the loop
    list.remove_loop();

    cout << endl;
    list.display();



}