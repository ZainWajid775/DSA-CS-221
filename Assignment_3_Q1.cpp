#include <iostream>

using namespace std;

void count_sort(int arr[] , int size)
{

    // Find max element
    int max = arr[0];
    for(int i = 1 ; i < size ; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
        }
    }

    // Initliase count array with 0
    int count[max + 1];
    for(int i = 0 ; i <= max ; i++)
    {
        count[i] = 0;
    }

    // Count the frequency of each element
    // Index in count array is the value of the element in the input array
    for(int i = 0 ; i < size ; i++)
    {
        count[arr[i]]++; 
    }

    // Calculate the prefix sum
    for(int i = 1 ; i <= max ; i++)
    {
        count[i] += count[i - 1];
    }

    // Create a temporary array to store the sorted array
    int temp_sorted[size];

    // Loop over the input array in reverse order
    for(int i = size - 1 ; i >= 0 ; i--)
    {
        temp_sorted[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy the sorted elements back into the original array
    for (int i = 0; i < size; i++)
    {
        arr[i] = temp_sorted[i];
    }

}
void count_sort(int arr[], int size, int pos)
{

    // Create digit counting array
    int count[10] = { 0 };

    // Count frequencies of each digit
    for (int i = 0;  i < size ; i++) 
    {
        count[(arr[i] / pos) % 10]++;
    }

    // Calculate prefix sum
    for (int i = 1; i < 10; i++) 
    {
        count[i] = count[i] + count[i - 1];
    }

    // Store answer in ans array
    int ans[size];
    for (int i = size - 1 ; i >= 0 ; i--) 
    {
        ans[--count[(arr[i] / pos) % 10]] = arr[i];
    }

    // Copy over the answer to the original array
    for (int i = 0 ; i < size ; i++) 
    {
        arr[i] = ans[i];
    }
}

void radix_sort(int arr[] , int size)
{
    // Find max element
    int k = *max_element(arr , arr + size);

    // Perform counting sort for every digit
    for (int pos = 1; (k / pos) > 0; pos *= 10) 
    {
        count_sort(arr , size , pos);
    }
}

int main()
{   
    int arr[] = {10 , 9 , 8 , 7 , 6 , 5 , 4 , 3 , 2 , 1};
    int size = sizeof(arr)/sizeof(arr[0]);
    count_sort(arr , size);

    for(int i = 0 ; i < size ; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    int arr2[] = {170 , 45 , 75 , 90 , 802 , 24 , 2 , 66};
    int size2 = sizeof(arr2)/sizeof(arr2[0]);
    radix_sort(arr2 , size2);
    for(int i = 0 ; i < size2 ; i++)
    {
        cout << arr2[i] << " ";
    }
}   