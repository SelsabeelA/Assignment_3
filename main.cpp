#include <iostream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include<algorithm>
#include <string>

using namespace std;

unsigned char img[SIZE][SIZE];
unsigned char temp[4][SIZE/2][SIZE/2] = {};    // The use of 3D array here is for organizing        q1
unsigned char quarter[(SIZE/2)*(SIZE/2)] = {}; // memory, so quarters get stored squentially:       q2
// this makes appending elements in the memory       q3
// is surely going to finish a quarter entirely      q4
// before moving to the next quarter.

void readImage();
void writeImage();
void shuffleFilter();
void extractQuarter(unsigned char* &, int);


int main() {
    readImage();
    shuffleFilter();
    writeImage();
}




void readImage() {
    char imageName[100];
    printf("Please enter name of the image to process: ");
    cin >> imageName;
    strcat(imageName, ".bmp");
    readGSBMP(imageName, img);
}

void writeImage() {
    char imageName[100];
    printf("Please enter name of the new image: ");
    cin >> imageName;
    strcat(imageName, ".bmp");
    writeGSBMP(imageName, img);
}


void extractQuarter(unsigned char * & ptr, int quarter) {
    int startRow = 0, endRow = SIZE/2, startCol = 0, endCol = SIZE/2;
    // Determine boundries according to quarter
    if (quarter == 2) {
        startCol = SIZE / 2;
        endCol = SIZE;
    }
    else if (quarter == 3) {
        startRow = SIZE / 2;
        endRow = SIZE;
    }
    else if (quarter == 4) {
        startRow = SIZE / 2;
        startCol = SIZE / 2;
        endRow = SIZE;
        endCol = SIZE;
    }
    if (quarter < 1 or quarter > 4)
        cout << "Unrecognized quarter!\n";

    int k = 0;
    for (int i = startRow; i < endRow; i++) {
        for (int j = startCol; j < endCol; j++) {
            ptr[k++] = img[i][j];
        }   // Due to the squential organization of memory we can
    }       // store the image row-by-row with a single iterator(k)
}



void shuffleFilter() {
    string order;
    unsigned char * pQuarter = quarter; // Point at a quarter-sized 2D array to store a quarter into.
    unsigned char * pTemp = &temp[0][0][0]; // Point at temp 3D array (divided into 4 quarters)
    int k = 0;
    cout << "New order of quarters ?\n";
    cin.ignore(); // For getline() to work properly
    getline(cin, order);
    // Shuffle process:
    for (int i = 0; i < order.length(); i++) { // Fill a temp. array with the shuffled image
        if (order[i] == ' ') {                 // a quarter per iteration
            continue;
        }
        extractQuarter(pQuarter, (int) (order[i] - '0'));
        for (int j = 0; j < ((SIZE * SIZE) / 4); j++) {
            pTemp[k] = pQuarter[j]; // Store extracted-quarter[original] inside current quarter[temp]
            k++;
        }
    }
    // Transfer temp. array into original image.
    int qrtr = 0, row = 0, col = 0;
    for (int i = 0; i < SIZE; i++) { // Store a 3D array into a 2D array
        if (i == SIZE / 2) {
            qrtr += 2; // Go to next half (Vertically)
            row = 0;
        }
        col = 0;
        for (int j = 0; j < SIZE; j++) {
            if (j == SIZE / 2) {
                qrtr++; // Go to next quarter(Horizontally), same row
                col = 0;
            }
            img[i][j] = temp[qrtr][row][col];
            col++;
        }
        qrtr--; // Go back to previous quarter(Horizontally), new row
        row++;
    }
}