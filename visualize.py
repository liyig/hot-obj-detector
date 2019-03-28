#!/usr/bin/env python
# coding: utf-8

# In[107]:


from cs103 import *
from typing import *

def convert_num_to_col(size: int, n: int) -> Image:
    """
    Converts a number into a square of the appropriate color
    Variation of colors: white, red, orange, yellow, green, cyan, blue, darkblue, purple, black
    Note: n should be in the range of (0, 255)
    """
    step = 25
    if (n < step):
        return square(size, "solid", "black")
    elif (n < step * 2):
        return square(size, "solid", "purple")
    elif (n < step * 3):
        return square(size, "solid", "darkblue")
    elif (n < step * 4):
        return square(size, "solid", "blue")
    elif (n < step * 5):
        return square(size, "solid", "cyan")
    elif (n < step * 6):
        return square(size, "solid", "lightgreen")
    elif (n < step * 7):
        return square(size, "solid", "yellow")
    elif (n < step * 8):
        return square(size, "solid", "orange")
    elif (n < step * 9):
        return square(size, "solid", "red")
    else:
        return square(size, "solid", "white")
    

def main(size: int, lon: List[int]) -> Image:
    """
    Takes in a list of 32 * 24 ints, converts it into an Image
    """
    #return square(10, "solid", "white")
    row = 1
    acc = square(size, "solid", "white")
    one_row = square(size, "solid", "white")
    for i in range(0, len(lon)):
        if (i < 32 * row):
            one_row = beside(one_row, convert_num_to_col(size, lon[i]))
        if (i == (32 * row)-1): # prep or next row
            acc = above(acc, one_row)
            row = row + 1
            one_row = square(size, "solid", "white") # reset row accumultor

    return acc


# In[124]:


def create_arr(positions: List[int]):
    """
    Takes in a list of ints corresponding to the position of the hot object
    
    """
    acc = []
    for i in range(0, 32*24):
        if (i in positions): # hot objects
            acc.append(250)
        elif (i+1 in positions or i-1 in positions or 
              (i > 32 and i -32 in positions) or (i < 32 *23 and i + 32 in positions)):
            acc.append(220)
        elif (i+2 in positions or i-2 in positions or
              (i > 32 and i-31 in positions) or (i < 32 * 23 and i - 31 in positions)):
            acc.append(190)
        elif (i+3 in positions or i-3 in positions):
            acc.append(140)
        elif (i+4 in positions or i-4 in positions):
            acc.append(120)
        elif (i+5 in positions or i-5 in positions):
            acc.append(50)
        else:
            acc.append(10)
        
            
    return acc


# In[128]:


horizontal = 5
vertical_step = 4
vertical = vertical_step*32

arr_input = [16+vertical-horizontal, 48+vertical-horizontal, 79+vertical-horizontal,
                     110+vertical-horizontal, 141+vertical-horizontal, 173+vertical-horizontal]
main(10, create_arr(arr_input))

#create_arr(arr_input)


# In[ ]:





# In[ ]:




