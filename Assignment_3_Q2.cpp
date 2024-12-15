#include <iostream>

using namespace std;

// Structure for linked list nodes
struct List_Node
{
    List_Node* next;
    int id;
    string description;

    List_Node(int id , string description)
    {
        next = nullptr;
        this->id = id;
        this->description = description;
    }
};

// Structure for AVL tree nodes
struct AVL_Node
{
    int loc_id;
    string area;
    string city;
    List_Node* head;
    AVL_Node* right;
    AVL_Node* left;
    int height;


    AVL_Node(int loc_id , string area , string city )
    {
        this->loc_id = loc_id;
        this->area = area;
        this->city = city;
        this->right = nullptr;
        this->left = nullptr;
        this->height = 1;
        head = nullptr;
    }
};

// AVL Tree 

void add_to_list(List_Node*& head, string description) 
{
    int new_id = 1;


    List_Node* current = head;
    while (current) 
    {
        new_id = current->id + 1;
        current = current->next;
    }

    List_Node* new_node = new List_Node(new_id, description);

    if (!head) 
    {
        head = new_node;
    } 
    else 
    {
        current = head;
        while (current->next) 
        {
            current = current->next;
        }

        current->next = new_node;
    }
}

int get_height(AVL_Node* root)
{
    if(root == NULL)
    {
        return 0;
    }

    return root->height;
}

int get_balance(AVL_Node* root)
{
    if(root == NULL)
    {
        return 0;
    }

    return get_height(root->left) - get_height(root->right);
}


AVL_Node* right_rotate(AVL_Node* y) 
{
    AVL_Node* x = y->left;
    AVL_Node* T = x->right;

    x->right = y;
    y->left = T;

    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;

    return x;
}

AVL_Node* left_rotate(AVL_Node* x) 
{
    AVL_Node* y = x->right;
    AVL_Node* T = y->left;

    y->left = x;
    x->right = T;

    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;

    return y;
}

AVL_Node* insert_avl_node(AVL_Node* root, int loc_id, string area, string description) {
    if (root == nullptr) {
        AVL_Node* new_node = new AVL_Node(loc_id, area, "Isb");
        add_to_list(new_node->head, description); // Automatically assign ID
        return new_node;
    }

    if (loc_id < root->loc_id) {
        root->left = insert_avl_node(root->left, loc_id, area, description);
    } else if (loc_id > root->loc_id) {
        root->right = insert_avl_node(root->right, loc_id, area, description);
    } else {
        // Location exists, add incident to linked list
        add_to_list(root->head, description);
        return root;
    }

    // Update height and balance
    root->height = 1 + max(get_height(root->left), get_height(root->right));
    int balance = get_balance(root);

    if (balance > 1 && loc_id < root->left->loc_id) {
        return right_rotate(root);
    }

    if (balance < -1 && loc_id > root->right->loc_id) {
        return left_rotate(root);
    }

    if (balance > 1 && loc_id > root->left->loc_id) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (balance < -1 && loc_id < root->right->loc_id) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}




void delte_list(List_Node* head) 
{
    while (head) 
    {
        List_Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Delete a node from the AVL tree
AVL_Node* delete_avl_node(AVL_Node* root, int loc_id) 
{
    if (!root) 
    {
        return nullptr;
    }

    if (loc_id < root->loc_id) 
    {
        root->left = delete_avl_node(root->left, loc_id);
    } 
    else if (loc_id > root->loc_id) 
    {
        root->right = delete_avl_node(root->right, loc_id);
    } 
    else 
    {
        delte_list(root->head);

        if (!root->left || !root->right) 
        {
            AVL_Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }

        AVL_Node* temp = root->right;
        while (temp->left) temp = temp->left; 

        root->loc_id = temp->loc_id;
        root->area = temp->area;
        root->city = temp->city;
        root->head = temp->head; 
        
        root->right = delete_avl_node(root->right, temp->loc_id);
    }

    root->height = 1 + max(get_height(root->left), get_height(root->right));
    int balance = get_balance(root);

    if (balance > 1 && get_balance(root->left) >= 0) 
    {
        return right_rotate(root);
    }
    if (balance > 1 && get_balance(root->left) < 0)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (balance < -1 && get_balance(root->right) <= 0) 
    {
        return left_rotate(root);
    }
    if (balance < -1 && get_balance(root->right) > 0) 
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

void add_incident(AVL_Node* root, int loc_id, string description) {
    if (!root) {
        cout << "Location " << loc_id << " not found!" << endl;
        return;
    }

    if (loc_id < root->loc_id) {
        add_incident(root->left, loc_id, description);
    } else if (loc_id > root->loc_id) {
        add_incident(root->right, loc_id, description);
    } else {
        // Location found, add incident with auto-incremented ID
        add_to_list(root->head, description);
        cout << "Incident added to location " << loc_id << endl;
    }
}


void delete_incident(AVL_Node* root, int loc_id, int incident_id) 
{
    if (!root) 
    {
        cout << "Location " << loc_id << " not found!" << endl;
        return;
    }

    if (loc_id < root->loc_id) 
    {
        delete_incident(root->left, loc_id, incident_id);
    } 
    else if (loc_id > root->loc_id) 
    {
        delete_incident(root->right, loc_id, incident_id);
    } 
    else 
    {
        // Location found, delete the incident from linked list
        List_Node* current = root->head;
        List_Node* prev = nullptr;

        while (current && current->id != incident_id) 
        {
            prev = current;
            current = current->next;
        }

        if (!current) 
        {
            cout << "Incident ID " << incident_id << " not found at location " << loc_id << endl;
            return;
        }

        if (prev) 
        {
            prev->next = current->next;
        } else 
        {
            root->head = current->next;
        }

        delete current;

        cout << "Incident ID " << incident_id << " deleted from location " << loc_id << endl;
    }
}

void print_avl_tree(AVL_Node* root) 
{
    if (!root) 
    {
        return;
    }

    print_avl_tree(root->left);

    cout << "Location ID: " << root->loc_id 
         << ", Area: " << root->area 
         << ", City: " << root->city 
         << "\nIncidents:\n";

    List_Node* current = root->head;
    while (current) {
        cout << "  - Incident ID: " << current->id << ", Description: " << current->description << endl;
        current = current->next;
    }
    cout << "----------------------------" << endl << endl;

    print_avl_tree(root->right);
}


int main() {
    AVL_Node* root = NULL;

    // 1. Add new locations
    root = insert_avl_node(root, 120 , "Zero Point" , "Fire near bank");
    root = insert_avl_node(root, 115 , "F-7" , "Main road attack");
    root = insert_avl_node(root, 125 , "F-8" , "Car blast near centaurus");
    root = insert_avl_node(root, 225 , "F-10" , "TEMPORARY");

    // 2. Add incidents to locations
    add_incident(root , 120 , "Traffic Accident");
    add_incident(root , 120 , "Figth at street 3");
    add_incident(root , 115 , "Gun fire");

    // 3. Display all locations and their incidents
    cout << endl;
    cout << "Initial AVL tree:" << endl;
    print_avl_tree(root);

    // 4. Delete an incident
    delete_incident(root , 120 , 1);

    // 5. Remove a location
    root = delete_avl_node(root , 225);

    // Final display
    cout << endl;
    cout << "\nFinal state of AVL tree:\n";
    print_avl_tree(root);

    return 0;
}




