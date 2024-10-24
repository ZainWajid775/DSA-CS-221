#include <iostream>
using namespace std;

// Define the struct for Universe_Coordinate
struct Universe_Coordinate
{
    int s_number, x_position, y_position;
    bool is_snake;
};

// Function to create a 2D dynamic array
Universe_Coordinate** create_2d_array(int rows, int cols)
{
    Universe_Coordinate** array = new Universe_Coordinate*[rows];
    for (int i = 0; i < rows; ++i) {
        array[i] = new Universe_Coordinate[cols];
    }
    return array;
}

// Function to delete a 2D dynamic array
void delete_2d_array(Universe_Coordinate** array, int rows)
{
    for (int i = 0; i < rows; ++i) {
        delete[] array[i];
    }
    delete[] array;
}

// Function to resize a 2D dynamic array
Universe_Coordinate** resize_2d_array(Universe_Coordinate** old_array, int old_rows, int old_cols, int new_rows, int new_cols)
{
    // Create a new 2D array with the new size
    Universe_Coordinate** new_array = create_2d_array(new_rows, new_cols);

    // Copy data from old array to new array
    for (int i = 0; i < old_rows && i < new_rows; ++i) {
        for (int j = 0; j < old_cols && j < new_cols; ++j) {
            new_array[i][j] = old_array[i][j];
        }
    }

    // Delete the old array
    delete_2d_array(old_array, old_rows);

    return new_array;
}

int main()
{
    int rows = 2, cols = 2;
    Universe_Coordinate** Universe_Data = create_2d_array(rows, cols); // Initial 2x2 array

    cout << "Main Menu\n";
    cout << "1. Enter new coordinate\n";
    cout << "2. View Map\n";
    cout << "3. Resize Grid\n";

    int option;

    cout << "Type here: ";
    cin >> option;
    cout << endl;

    switch(option)
    {
        case 1:
        {
            int x, y;
            cout << "Enter X-coordinate: ";
            cin >> x;
            cout << endl;

            cout << "Enter Y-coordinate: ";
            cin >> y;
            cout << endl;

            // Check if x and y are within bounds
            if (x < rows && y < cols)
            {
                cout << "Enter sector number (s_number): ";
                cin >> Universe_Data[x][y].s_number;
                cout << "Is there a snake? (1 for yes, 0 for no): ";
                cin >> Universe_Data[x][y].is_snake;

                Universe_Data[x][y].x_position = x;
                Universe_Data[x][y].y_position = y;

                cout << "Coordinate successfully entered!\n";
            }
            else
            {
                cout << "Coordinates out of bounds! Please resize the grid first.\n";
            }
            break;
        }

        case 2:
        {
            cout << "Map View:\n";
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    cout << "(" << Universe_Data[i][j].x_position << "," 
                         << Universe_Data[i][j].y_position << ") Snake: " 
                         << Universe_Data[i][j].is_snake << "\n";
                }
            }
            break;
        }

        case 3:
        {
            int new_rows, new_cols;
            cout << "Enter new number of rows: ";
            cin >> new_rows;
            cout << "Enter new number of columns: ";
            cin >> new_cols;

            // Resize the array
            Universe_Data = resize_2d_array(Universe_Data, rows, cols, new_rows, new_cols);
            rows = new_rows;
            cols = new_cols;

            cout << "Grid resized to " << new_rows << " rows and " << new_cols << " columns.\n";
            break;
        }

        default:
            cout << "Invalid option!\n";
    }

    // Free the dynamically allocated memory
    delete_2d_array(Universe_Data, rows);

    return 0;
}
