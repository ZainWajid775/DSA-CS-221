#include <iostream>
using namespace std;


//Structure for universe coordinate
struct Universe_Coordinate
{
    int s_number , x_position , y_position;
    bool is_snake;
    
};

//New array creation
Universe_Coordinate** new_array(int r , int c)
{
    Universe_Coordinate** arr = new Universe_Coordinate*[r];

    for(int i = 0 ; i < r ; i ++)
    {
        //Co-ordinates are assigned as array is made
        arr[i] = new Universe_Coordinate[c];
        for(int j = 0 ; j < c ;j++)
        {
            int s_amount = 0;
            arr[i][j].x_position = i;
            arr[i][j].y_position = j;
            cout << "Enter number of snake at (" << i << "," << j << ") :";
            cin >> s_amount;
            cout << endl;
            arr[i][j].s_number = s_amount;

            if(s_amount > 0)
            {
                arr[i][j].is_snake = true;
            }
            else
            {
                arr[i][j].is_snake = false;
            }

        }
    }

    return arr;
}

//Array Resize
Universe_Coordinate** resize(Universe_Coordinate** arr , int old_r , int old_c , int new_r, int new_c)
{
    Universe_Coordinate** new_arr = new_array(new_r , new_c);
    cout << "New map created\n\n";
    
    //Delete old array
    for(int i = 0 ; i < old_r ; i++)
    {
        delete arr[i];
    }
    delete arr;

    return new_arr;
}

//Array traversal
//I runs backwards from max index in order to print co-ordinates in sequence
void map(Universe_Coordinate** arr , int r , int c)
{
    for (int i = r - 1 ; i >= 0 ; i--)
    {
        for(int j = 0 ; j < c ; j++)
        {
            cout << "[" << arr[i][j].x_position << "," << arr[i][j].y_position << " Snakes " << arr[i][j].s_number << " ]  ";
        }
        cout << endl;
    }
}

int main()
{
    //Array Creation
    Universe_Coordinate** arr = new_array(3,3);

    //Printing the array
    map(arr ,3,3);
    cout << endl;

    //Resizing the array
    arr = resize(arr , 3,3,4,4);

    //Printing new array
    map(arr , 4 ,4);
}