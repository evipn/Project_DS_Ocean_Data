#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

struct ocean 
{
char date[12];
float temp;
float phosphate;
float silicate;
float nitrite;
float nitrate;
float salinity;
float oxygen;
} typedef OCEAN;

// function to swap elements
void swap(OCEAN *a, OCEAN *b) {
  OCEAN t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
int partition(OCEAN *array, int low, int high) 
{

  // select the rightmost element as pivot
  float pivot = array[high].temp;

  // Index of smaller element and indicates the right position of pivot found so far
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j <= high - 1; j++) 
  {
    if (array[j].temp < pivot) 
    {
      // increment index of smaller element
      i++;

      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);

  // return the partition point
  return (i + 1);
}

void quickSort(OCEAN *array, int low, int high) {
  if (low < high) 
  {

    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);

    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);

    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}

void insertionSort(OCEAN *arr, int n)
{
    int i, j;
    float key;
    for (i = 1; i < n; i++) 
    {
        key = arr[i].temp;
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j].temp > key) 
        {
            arr[j + 1].temp = arr[j].temp;
            swap(&arr[j+1], &arr[j]);
            j = j - 1;
        }
        arr[j + 1].temp = key;
    }
}

// A utility function to print an array of size n
void printArray(OCEAN *OCEAN, int n)
{

    for(int r=0; r<n; r++)
    { 
        printf("Date:%s  Temp:%.2f  \n", OCEAN[r].date, OCEAN[r].temp); 
    }
}

int main()
{
    FILE* fp = fopen("ocean.csv", "r");

    if (!fp)
    {
        printf("Can't open file\n");
    }
    
    OCEAN *dat;
    int n = 1405;
    dat = malloc(sizeof(OCEAN) * n);

    if(dat == NULL)
    {
        printf("Memory is not allocated!");
        return 1;
    }
  
    char buffer[1024];

    int row = 0;
    int column = 0;
    
    int r=0;
    while (fgets(buffer, 1024, fp)) 
    {
        column = 0;
        row++;

        // To avoid printing of column
        // names in file can be changed
        // according to need
        if (row == 1)
            continue;
        // Splitting the data
        char* value = strtok(buffer, ", ");

        while (value) 
        {
            if (column == 0) 
            {
                strcpy(dat[r].date, value);
            }

            if (column == 1) 
            {
                dat[r].temp = atof(value);
            }

            if (column == 2) 
            {
                dat[r].phosphate = atof(value);
            }

            if (column == 3) 
            {
                dat[r].silicate = atof(value);
            }

            if (column == 4) 
            {
                dat[r].nitrite = atof(value);
            }

            if (column == 5) 
            {
                dat[r].nitrate = atof(value);
            }

            if (column == 6) 
            {
               dat[r].salinity = atof(value);
            }

            if (column == 7) 
            {
                dat[r].oxygen = atof(value);
            }

            value = strtok(NULL, ", ");
            column++;
        }
        r++;
    }
    
    // Close the file
    fclose(fp);

    clock_t start, end;
    int  choice;

    do
    {
        printf("Select the sorting method of your choice (1 or 2):\n");
        printf("1. Selection Sort\n2.Quick Sort\n");
        scanf("%d" ,&choice);
    }while(choice != 1 && choice != 2);

    if(choice == 1)
    {
        printf("Selection Sort:\n");
        start = clock();
        printf("Clock ticks at starting time: %ld\n", start);
        insertionSort(dat, n);
        end = clock();
    }
    else
    {
        printf("Quick Sort:\n");
        start = clock();
        printf("Clock ticks at starting time: %ld\n", start);
        quickSort(dat, 0, n-1);
        end = clock();
    }

    printArray(dat, n);
    printf("Clock ticks at end time: %ld\n", end);
    printf("CLOCKS_PER_SEC: %ld\n", CLOCKS_PER_SEC);
    printf("The duration in seconds since the program was launched: %ld\n\n", (end-start)/CLOCKS_PER_SEC);

    free(dat);  //Free memory

    return 0;
}
