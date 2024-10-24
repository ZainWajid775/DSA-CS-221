#include <iostream>
#include <string>
using namespace std;

//Function to convert a string to lowercase
string to_lower(const string& str)
{
    string lower_str = str;
    for (char &c : lower_str)
    {
        c = tolower(c);
    }
    return lower_str;
}

struct Person
{
    string name;
    int age; 
    string phone_no;

    Person(string name , int age , string phone_no)
    {
        this->name = name;
        this->age = age;
        this->phone_no = phone_no;
    }
};

struct Node
{
    Node* next;
    Person p_data;

    Node(Person p) : p_data(p) , next(nullptr) {}
};

class Linked_List
{
    private:
    Node* head;

    public:
    Linked_List()
    {
        head = nullptr;
        cout << "Linked List initialised\n";
    }

    bool is_empty()
    {
        return (head == nullptr);
    }

    void insertion(Person p_input)
    {
        Node* new_node = new Node(p_input);

        //Insertion if list is empty ot name is alphabeticall highest
        if(head == nullptr || new_node->p_data.name < head->p_data.name)
        {
            new_node->next = head;
            head = new_node;

            cout << "New node added at start\n";
        }
        else
        {
            Node* temp = head;

            //Traverse the list until right place is found alphabetically
            while(temp->next != nullptr && temp->next->p_data.name < new_node->p_data.name)
            {
                temp = temp->next;
            }

            new_node->next = temp->next;
            temp->next = new_node;
        }
    }

    void display()
    {
        if(!is_empty())
        {
            Node* temp = head;

            while(temp != nullptr)
            {
                cout << "Name : " << temp->p_data.name << " | Age : " << temp->p_data.age << " | Phone Number : " << temp->p_data.phone_no << endl;
                temp = temp->next;
            }
            cout << endl;
        }
        else
        {
            cout << "List empty\n";
        }
    }

    void find(const string& name)
    {
        Node* temp = head;

        while(temp != nullptr)
        {
            if(to_lower(temp->p_data.name) == to_lower(name))
            {
                cout << "Person found\n";
                cout << "Name : " << temp->p_data.name << " | Age : " << temp->p_data.age << " | Phone Number : " << temp->p_data.phone_no << endl; 
                return;
            }
            temp = temp->next;
        }

        cout << "Person not found in list\n";
    }


};

//Fucntion to validate phone number
bool number_validation(string phone_number)
{
    if(phone_number.length() != 11)
    {
        return false;
    }
    for(char c : phone_number)
    {
        if(!isdigit(c))
        {
            return false;
        }
    }

    return true;
}

//Function to input person data
Person get_info()
{
    int a = 0;
    string n, p;
    bool check = false;
    bool p_valid = false;

    while(!check)
    {
        while(n == "")
        {
            cout << "Enter name : ";
            cin >> n;

            if(n == "")
            {
                cout << "Invalid name\n";
            }
        }

        while(!(a > 0))
        {
            cout << "Enter " << n << "'s age : ";
            cin >> a;

            if(!(a > 0))
            {
                cout << "Invalid age\n";
            }
        }

        while(!number_validation(p))
        {
            cout << "Enter " << n << "'s phone number : ";
            cin >> p;
            cout << endl;

            if(!number_validation(p))
            {
                cout << "Invalid phone number\n";
                cout << "Phone number must be 11 digits and all numeric characters\n";
            }
        }

        check = true;
    }

    Person temp(n , a , p);
    return temp;
};

int main()
{
    Linked_List list;

    //Inserting new persons in list
    for(int i = 0 ; i < 2 ; i++)
    {
        Person temp = get_info();
        list.insertion(temp);
    }
    cout << endl;

    //Displaying updated list
    list.display();
    cout << endl;

    //Finding a person in list
    string search_name;
    cout << "Enter name to search for : ";
    cin >> search_name;
    cout <<endl;
    list.find(search_name);

}