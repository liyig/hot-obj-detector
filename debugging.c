/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

// Function declaration
static int sum_array(int acc[], int start, int size);
static int contains(int hot_object[], int position);

int contains(int hot_object[], int position) {
    for (int i = 0; i < 4; i++) { // INPUT: SIZE OF ARRAY HERE!!
        if (hot_object[i] == position) {
            return 1;
        }
    }
    return 0;
}

int sum_array(int acc[], int start, int size) {
    int res = 0;
    for (int i = start; i < start + size; i++) {
        res += acc[i];
    }
    return res;
}

int main()
{
    int hot_object[4] = {325, 326, 357, 358};
    
    int acc[768];
    for (int a = 0; a < 768; a++ ) {
      if (contains(hot_object, a)) {
          acc[a] = 250;
      }
      else if (contains(hot_object, a+1) || contains(hot_object, a-1)
               || (a > 32 && contains(hot_object, a-32)) || (a < 32*23 && contains(hot_object, a+32))) {
          acc[a] = 220;
      }
      else if (contains(hot_object, a+2) || contains(hot_object, a-2)
               || (a > 32 && contains(hot_object, a-31)) || (a < 32*23 && contains(hot_object, a+31))
               || (a > 32 && contains(hot_object, a-33)) || (a < 32*23 && contains(hot_object, a+33))
               || (a > 64 && contains(hot_object, a-64)) || (a < 32*22 && contains(hot_object, a+64))) {
          acc[a] = 190;
      }
      else if (contains(hot_object, a+3) || contains(hot_object, a-3) 
               || (a > 32 && contains(hot_object, a-30)) || (a < 32*23 && contains(hot_object, a+30))
               || (a > 32 && contains(hot_object, a-34)) || (a < 32*23 && contains(hot_object, a+34))) {
          acc[a] = 140;
      }
      else if (contains(hot_object, a+4) || contains(hot_object, a-4)) {
          acc[a] = 120;
      }
      else if (contains(hot_object, a+5) || contains(hot_object, a-5)) {
          acc[a] = 50;
      }
      else {
          acc[a] = 0;
      }
    
    }
                  
    int num_row = sizeof(acc)/sizeof(acc[0])/32; // Each row has 32 ele
    int row_counter = 0; // For tracking row in iteration
    
    int right = 0;
    int left = 0;
    int mid = 0;
    
    for (int k = 0; k < num_row; k ++) {
       int start_left = 0 + 32*row_counter;
       int start_mid = 11 + 32*row_counter;
       int start_right = 21 + 32*row_counter;
       int end_right = 32 + 32*row_counter;
       
       left += sum_array(acc, start_left, 11);
       mid += sum_array(acc, start_mid, 10);
       right += sum_array(acc, start_right, 11);
       
       row_counter++;
       
    }
    printf("\n%d\n", left);
    printf("%d\n", mid);
    printf("%d\n", right);
    
    if (left > mid && left > right) {
        return 0;
    } else if (left == mid && left > right) {
        return 1;
    } else if (mid > left && mid > right) {
        return 2;
    } else if (right == mid && right > left) {
        return 3;
    } else if (right > mid && right > left) {
        return 4;
    }
    else {
        return -1;
    }
    
    
    return 0;
}


