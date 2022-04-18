//
// Created by Asus on 4/18/2022.
//

/***************************************************************
 Purpose: Invert and rotate (90,180,270) grayscale images.
 Purpose: Merge and darken/ligthen grayscale images.
 Program load a gray image and store in another file

 Author:  Abdullah Mohammed Abdullah Farg
 ID: 20210541

 Author:  Adham Mohamed sayd Alam
 ID: 20210053

 Author:  Selsabeel Asim Ali Elbagir
 ID: 20210714


 Section: S2
 Date:    30 March 2018
 Version: 1.0
****************************************************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];



void loadImage();
void saveImage();
void Invert_Filter();
void Rotate_Image();
void merger();
void darkLight();
void shrinker();

int main()
{


    int filter = 1;


    while (filter != 0)
    {
        loadImage();

        cout << "Please select a filter to apply or 0 to exit:" << endl;
        cout << "1.Invert filter \n" << "2.Rotate image \n";
        cout << "3.Merger image \n" << "4.Darken/Lighten image \n" << "0.exit \n";

        cin >> filter;

        if (filter == 1)
            Invert_Filter();
        else if (filter == 2)
            Rotate_Image();
        else if (filter == 3)
            merger();
        else if (filter == 4)
            darkLight();
        else if (filter == 0)
            return 0;
        saveImage();

    }


}

//_________________________________________
void loadImage() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Ahlan ya user ya habibi \n""Please enter file name of the image to process \n";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_________________________________________
void Rotate_Image()


{
    char choose;
    cout << "choose the degree of rotate please : " << endl;
    cout << "a.90" << endl << "b.180" << endl << "c.270" << endl;
    cin >> choose;
    if (choose == 'a')//Rotate 90
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {

                image[i][j] = image[j - 256][i - 64];
                image[i][j] = image[j - 256][i - 64];

            }

        }
    }
    else if (choose == 'b') //Rotate 180
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {

                image[i][j] = image[i - 256][-j - 64];




            }

        }
    }
    else if (choose == 'c')  //Rotate 270
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {


                image[i][j] = image[-j][-i - 64];
            }
        }

    }

}
//_________________________________________
void Invert_Filter()
{

    for (int i = 0; i < SIZE; i++)//Invert image
    {
        for (int j = 0; j < SIZE; j++)
        {

            image[i][j] = 256 - image[i][j];

        }

    }
}
//_________________________________________
void merger() {
    char imageFileName2[100];
    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName2;

    // Add to it .bmp extension and load image
    strcat(imageFileName2, ".bmp");
    readGSBMP(imageFileName2, image2);


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 0.5 * (image[i][j] + image2[i][j]);
        }
    }

}
//_________________________________________
void darkLight() {
    char choice;
    cout << "Do you want to (d)arken or (l)ighten?";
    cin >> choice;
    if (choice == 'd') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] *= 0.5;
            }
        }
    }
    if (choice == 'l') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = 0.5 * (image[i][j] + SIZE);
            }

        }
    }
    else {
        cout << "Invalid entry.";
    }

}
//_________________________________________

void shrinker() {
    int choice;
    cout << "Would you like to shrink the image by a factor of 2, 3, or 4?\n";
    cout << "Please input your choice as 2 if you want the dimensions to be 1/2, \n";
    cout << "Please input your choice as 3 if you want the dimensions to be 1/3, \n";
    cout << "Please input your choice as 4 if you want the dimensions to be 1/4, \n";
    cin >> choice;
    if (choice != 1) && (choice != 2) && (choice != 3) {
        cout << "Invalid entry.";
    }
    else {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = / choice;
            }
        }
    }

}
