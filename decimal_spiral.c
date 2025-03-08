// z5687139, Hoang Lan Vu, 06/03/25
// Reads integer n
// Prints n x n pattern of '*' & '-' in spiral shape
// Note: n is ood and n>= 5


#include <stdio.h>

int find_first_number(int, int);
int find_last_number(int, int, int);
int left_pyramid(int, int, int, int, int);
int count_right_pyramid(int, int);
int fill_gaps(int, int, int, int, int);
void right_pyramid(int, int, int, int, int, int);
int keep_in_range(int);
int left_column(int, int, int);

int main(void) {

    int size;
    printf("Enter size: ");
    scanf("%d", &size);


    

    // How many times column has been iterated through
    int start_digit_column_counter = 0;

    // Value of starting digit of column series
    int start_digit_column = 0;

    for (int row = 0; row < size; row++) {
        // Find starting digit for 1st column, row 2
        if (row % 2 == 0 && row == 2) {
            start_digit_column = find_first_number(size, row);
        }

        int last_number;
        int first_number = find_first_number(size, row);
        if (row % 2 == 0) {
            last_number = find_last_number(size, row, first_number);
        }



        if (row == 0) {
            // Do nothing to first_number
            ;
        }
        else if (row <= size / 2 && row != 0) {
            first_number -= 1;
        }
        else {
            first_number += 1;
        }

        int left_used = left_pyramid(size, row, first_number, start_digit_column, start_digit_column_counter);
        int right_used = count_right_pyramid(size, row);
        fill_gaps(row, size, left_used, right_used, first_number);

        right_pyramid(size, row, first_number, start_digit_column, start_digit_column_counter, last_number);
        printf("\n");
        start_digit_column_counter++;
    }

}


// Finds starting number for each row sequence
int find_first_number(int size, int row) {
    int total_count = 0;
    int pattern_count = row / 2;

    if (row % 2 == 0) {
        if (row == 0) {
            for (int i = 2; i < size - row - 2 * pattern_count; i += 2) {
                total_count += 2 * i;
            }
            total_count += size - 1;
        }
        else if (row <= size / 2) {
            for (int i = 2; i < size - row - 2 * pattern_count; i += 2) {
                total_count += 2 * i;
            }
            total_count += size - row - 2 * pattern_count + 1;
        }
        else {
            pattern_count = size - row / 2;
            // Get lower half digits
            for (int i = 2; i < size + row - 2 * pattern_count; i += 2) {
                total_count += 2 * i;
            }
        }
    
        // Return 2nd digit
        total_count = total_count % 10;
    }


    return total_count;
}

// Find last number in the same sequence of first number
int find_last_number(int size, int row, int first_num) {
    int last_num = first_num;
    if (row == 0) {
        for (int i = 0; i < size - 1; i++) {
            last_num--;
            last_num = keep_in_range(last_num);
        }
    }
    else if (row == 2) {
        for (int i = 0; i < size - 3; i++) {
            last_num--;
            last_num = keep_in_range(last_num);
        }
    }
    // For each 2nd row after row == 2, length of sequence decreases by 4
    else if (row < size / 2) {
        // (2(Row - 2)) + 2
        for (int i = 0; i < size - 2 * (row - 2) - 3; i++) {
            last_num--;
            last_num = keep_in_range(last_num);
        }
    }

    return last_num;

}

int keep_in_range(int num) {
    if (num == -1) {
        return 9;
    }
    else if (num == 10) {
        return 0;
    }
    return num;
}

// Print left pyramid pattenr
int left_pyramid(int size, int row, int first_number, int start_digit_column, int start_digit_column_counter) {
    int left_char_used = 0;
    int col = row - 2;

    int middle_row = size / 2;
    
    // Since column series starts at row 2, we - 2
    int new_start_digit_column = start_digit_column - 2;

    // Print initial column 1st digit
    if (row == 2) {
        printf("%d", start_digit_column);
        left_char_used += 1;
    }
    // Print remaining 1st column in incrementing order
    else if (row >= 2) {
        for (int i = 0; i < start_digit_column_counter; i++) {

            new_start_digit_column ++;
            new_start_digit_column = keep_in_range(new_start_digit_column);
        }
        printf("%d", new_start_digit_column);
        left_char_used += 1;

        
        // How to account for only first column digits considering first_num for first index of sequence?
        // Maybe pass in variable that keeps track of starting digit for each column

    }
    if (row <= middle_row) {
        int iteration_count = 1;
        int col_shift = 2;
        for (int i = 3; i < row; i += 2) {
            first_number = first_number % 10;

            // On last repeat, print out last digit
            if (i >= row - 2 && row % 2 == 0) {
                printf("-%d", first_number + 1);
                left_char_used += 2;
            }
            else {
                // Every 2nd iteration of i for loop, move column over by 2
                if (iteration_count % 2 == 0) {
                    col_shift += 2;
                }
                left_char_used += left_column(size, row, col_shift);
                
            }
            iteration_count++;
            
        }
    }
    else {
        int iteration_count = 1;
        int col_shift = 2;
        for (int i = size / 2 - 2; i >= row - middle_row; i -= 2) {
            if (first_number - 1 == -1) {
                first_number = 9;
            }

            // Handle numbers before, maybe focus on pure column descending

            // Handles last number printed

            if (i <= row - middle_row + 1 && row % 2 == 0) {
                printf("-%d", first_number - 1);
                left_char_used += 2;
            }
            else {
                // Every 2nd iteration of i for loop, move column over by 2
                if (iteration_count % 2 == 0) {
                    col_shift += 2;
                }
                left_char_used += left_column(size, row, col_shift);
            }
            iteration_count++;

        }
    }
    return left_char_used;
}


int left_column(int size, int row, int col_shift) {
    int left_char_used = 0;
    int start_row = 2 + col_shift;
    // When left_column is called again with new col_shift value
    // e.g. col_shift == 2
    // Need to get find_first_number for that respective column as the base
    
    // Find first number for each respective column
    // e.g. return first number for col 2, col 4...
    // We know col = row - 2 where row % 2 == 0
    // i.e. row = 2 + col where row % 2 == 0
    // get the starting row of each column so
    // we can find starting num with our formula above
    // using size 15
    // if col_shift = 0 -> starting row is 2
    // if col_shift = 2 -> starting row is 4

    if (row >= start_row) {
        // Formula to find first_number for respective column
        // e.g. if column 0 then get first_number for col 0 only
        // then if column 1, then get first_number for col 1 only
        int start_num = find_first_number(size, start_row);


        int offset = row - start_row;
        int current_num = (start_num + offset) % 10;
        printf("-%d", current_num);
        left_char_used += 2;
    }
    return left_char_used;
}

int count_right_pyramid(int size, int row) {
    int right_char_used = 0;
    int middle_row = size / 2;
    // Amount of times right pattern has increased until middle row
    if (row <= middle_row) {
        for (int i = 1; i < row; i += 2) {

            // printf("*-");
            right_char_used += 2;
        }
    }

    else {
        // Print decrementing remaining rows
        for (int i = size / 2 - 2; i >= row - middle_row; i -= 2) {
            // printf("*-");
            right_char_used += 2;
            
        }
    }
    // printf("*");
    right_char_used += 1;

    return right_char_used;
}

// Need fill_gaps to get starting number from find_first_number
// Then start incrementing/decrementing if <= middlerow or not
int fill_gaps(int row, int size, int left_used, int right_used, int first_number) {
    int total_used = left_used + right_used;

    int first_num;
    int last_num;

    
    if (row % 2 != 0) {
        for (int j = 0; j < size - total_used; j++)
            {
                printf("-");
            }
    }
    else {
        // Fill gaps for even rows
        for (int j = 0; j < size - total_used; j++)
        {
            first_number = keep_in_range(first_number);
            printf("%d", first_number);

            if (row <= size / 2) {
                first_number--;
                first_number = keep_in_range(first_number);
            }
            else {
                first_number++;
                first_number = keep_in_range(first_number);
            }

        }
    }
    return first_num;
}

void right_pyramid(int size, int row, int first_number, int start_digit_column, int start_digit_column_counter, int last_number) {
    int middle_row = size / 2;
    // Since column series starts at row 0
    int new_start_digit_column = last_number;

    // Since column starts at row 1
    // Print last digit of 1st row
    if (row == 0) {
        printf("%d", last_number);
    }

    // Note: find way to get last digit and decrement
    // Maybe loop pattern to get each column?

    // Amount of times right pattern has increased until middle row
    if (row <= middle_row) {
        for (int i = 1; i < row; i += 2) {
            printf("*-");
        }
    }

    else {
        // Print decrementing remaining rows
        for (int i = size / 2 - 2; i >= row - middle_row; i -= 2) {
            printf("*-");
            
        }
    }

    

    // Print remaining column in decrementing order
    if (row >= 1) {
        for (int i = 0; i <= start_digit_column_counter; i++) {

            new_start_digit_column --;
            if (new_start_digit_column == -1) {
                new_start_digit_column = 9;
            }
        }
        
        printf("%d", new_start_digit_column);
    }
    return;
}

