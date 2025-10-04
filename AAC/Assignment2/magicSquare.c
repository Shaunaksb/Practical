#include <stdio.h>
#include <string.h> // For memset
#include <stdlib.h> // For exit

// Function to print the magic square in a formatted grid
void printMagicSquare(int size, int square[100][100]) {
    printf("The Magic Square of size %d x %d is:\n\n", size, size);
    
    // Calculate the magic constant to display it
    int magic_constant = size * (size * size + 1) / 2;
    printf("(The Magic Constant is %d)\n\n", magic_constant);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Use %4d to format the numbers neatly in columns
            printf("%4d ", square[i][j]);
        }
        printf("\n");
    }
}

// Function to generate the magic square for a given odd size
void generateMagicSquare(int n) {
    // The algorithm only works for odd-sized squares.
    // We validate the input first.
    if (n <= 0) {
        printf("Error: Size must be a positive number.\n");
        return;
    }
    if (n % 2 == 0) {
        printf("Error: This algorithm only works for odd-sized magic squares.\n");
        printf("Please enter an odd number (e.g., 3, 5, 7).\n");
        return;
    }

    // Dynamically declare the 2D array for the magic square
    int magicSquare[100][100];

    // Initialize all cells of the square to 0
    memset(magicSquare, 0, sizeof(magicSquare));

    // --- Start of the Siamese Method Algorithm ---

    // 1. Start position: middle of the top row
    int row = 0;
    int col = n / 2;

    // Loop to place all numbers from 1 to n*n
    for (int num = 1; num <= n * n; num++) {
        // Place the current number in the calculated position
        magicSquare[row][col] = num;

        // Calculate the next position (one step up, one step right)
        int next_row = (row - 1 + n) % n; // Wrap around for row
        int next_col = (col + 1) % n;     // Wrap around for column

        // 2. Check the special conditions
        // If the next position is already occupied, move one step down instead
        if (magicSquare[next_row][next_col] != 0) {
            row = (row + 1) % n; // Move down, wrap if necessary
            // Column stays the same
        } else {
            // Otherwise, move to the new position
            row = next_row;
            col = next_col;
        }
    }

    // Print the completed magic square
    printMagicSquare(n, magicSquare);
}

int main() {
    int n;

    printf("--- Magic Square Generator (for odd sizes) ---\n");
    printf("Enter the size of the magic square (must be an odd number): ");
    scanf("%d", &n);
    printf("\n");

    generateMagicSquare(n);

    return 0;
}