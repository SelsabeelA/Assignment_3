/***************************************************************
Purpose: Invert, rotate (90,180,270), Flip, Merge, Enlarge,
 Shuffle, Shrink(1/2 dimension,1/3 dimension, 1/4 dimension), Blur, Darken&lighten, Detect Edges, Black&White RGB images.
 The program loads a gray image image, gives the user an option of
 12 functions, each that gives a different filter effect, and then saves it 
 to a new image (in the same program's file directory) that the user chooses the name of.

 Author:  Abdullah Mohammed Abdullah Farg
 ID: 20210541

 Author:  Adham Mohamed sayed Allam
 ID: 20210053

 Author:  Selsabeel Asim Ali Elbagir
 ID: 20210714

 Section: S1 & S2
 Date:    17 April 2022
 Version: 2.0
****************************************************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image [SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char newimage2[128][128];
unsigned char newimage3[86][86];
unsigned char newimage4[64][64];



void loadImage ();
void saveImage ();
void saveImage2 ();
void Invert_Filter();
void Rotate_Image ();
void merger ();
void darkLight ();
void Black_White_Image () ;
void Flip ();
void FlipHrizontal();
void FlipVertical();
void selection_menu();
void shrink();
void blur();
void Mirror();
void EdgeDetective();
void Enlarge_Image();
void the_order (int& a , int& b  ,char q);
void Shuffle_Filter();
//_________________________________________

int main()
{
    selection_menu();
}

//_________________________________________

void selection_menu()
{


    char filter = '1'; // this ensures the selection menu loops for the user from the start


    while (filter != '0') {
        loadImage();

        cout <<"Please select a filter to apply or 0 to exit:" << endl;
        cout << "1.Black & White Image.\n" << "2.Invert Image.\n"
             << "3.Merge Images.\n"        << "4.Flip Image.\n"
             << "5.Rotate Image.\n"        << "6.Darken and Lighten Image.\n"
             << "7.Detect Image Edges.\n"  << "8.Enlarge Image.\n"
             << "9.Shrink Image.\n"        << "a.Mirror Image.\n"
             << "b.Shuffle Image.\n"       << "c.Blur Image.\n"
             <<"0.exit.\n";
        cin >> filter;

        if (filter == '1')
            Black_White_Image ();
        else if (filter == '2')
            Invert_Filter();
        else if (filter == '3')
            merger();
        else if (filter == '4')
            Flip();
        else if (filter == '5')
            Rotate_Image();
        else if (filter == '6')
            darkLight();
        else if (filter == '7')
            EdgeDetective();
        else if (filter == '8')
             Enlarge_Image();
        else if (filter == '9')
            shrink();
        else if (filter == 'a')
            Mirror();
        else if (filter == 'b')
            Shuffle_Filter();
        else if (filter == 'c')
            blur();
        else if (filter == '0') {
            cout << "M3 elsalamh ya user ya habibi \n";
            break;
        }
        if ((filter == '7')||(filter == '8')||(filter == 'b'))
            continue;
        else
            saveImage();


    }


}

//_________________________________________
void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Ahlan ya user ya habibi \n""Please enter file name of the image to process \n";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_________________________________________
void Rotate_Image()


{
    char choose ;
    cout <<  "choose the degree of rotate please : "<< endl;
    cout << "a.90"<<endl<<"b.180"<<endl<<"c.270"<<endl;
    cin >> choose ;
    if (choose == 'a' )//Rotate 90
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j< SIZE; j++)
            {

                image[i][j] =  image[j-256][i-32];


            }

        }
    }
    else if (choose == 'b') //Rotate 180
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j< SIZE; j++)
            {

                image[i][j] =  image[i-256][-j-64];




            }

        }
    }
    else if (choose == 'c')  //Rotate 270
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j< SIZE; j++)
            {


                image[i][j] =  image[-j][-i-64];
            }
        }

    }

}
//_________________________________________
void Invert_Filter()
{

    for (int i = 0; i < SIZE; i++)//Invert image
    {
        for (int j = 0; j< SIZE; j++)
        {

            image[i][j] = 256 - image[i][j];

        }

    }
}
//_________________________________________
void merger() {
    char imageFileName2[100];
    // Get gray scale image file name
    cout << "Enter the source image file name of what you'd like to merge with: ";
    cin >> imageFileName2;

    // Add to it .bmp extension and load image
    strcat (imageFileName2, ".bmp");
    readGSBMP(imageFileName2, image2);
// since we need two images for merge to occur, we ask the user to input a file name and then read the filename.bmp


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j] = 0.5*( image[i][j] + image2[i][j] );
		// this takes the average of both images

        }
    }

}
//_________________________________________
void darkLight() {
    char choice;
    cout << "Do you want to (d)arken or (l)ighten?\n";
    cout << "Please enter d or l.\n";
    cin >> choice;
    if (choice=='d'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                image[i][j] *= 0.5; // halving the value of each pixel to make it closer to 0 (black)
            }
        }
    }
    else if (choice=='l'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                image[i][j] = 0.5*(image[i][j]+SIZE);
		    // taking the average of the value of each pixel with white (255/SIZE) to make it closer to 255 (white)
		    // we can't multiply by 2 because that would give a value greater than 255 at times.
            }

        }
    }
    else{
        cout << "Invalid entry.";
    }

}
//_________________________________________
void Black_White_Image ()
{
    long sum = 0;
    double avg = 0;
    //average of the pixels
    for(int k = 0; k < SIZE; k++){
        for(int l = 0; l < SIZE; l++){
            sum += image[k][l];
        }
    }
    avg = sum / (SIZE * SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {



            if (image[i][j] > avg)
                image[i][j] = 255;
            else
                image[i][j] = 0;

        }
    }
}
//_________________________________________
void FlipHrizontal() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< (SIZE/2); j++) {
            swap(image[i][j] , image[i][SIZE - j]);

        }
    }
}
//_________________________________________
void FlipVertical(){
    for (int i = 0; i < (SIZE/2); i++) {
        for (int j = 0; j< SIZE; j++) {
            swap(image[i][j] , image[SIZE - i][j]);

        }
    }
}
//_________________________________________
void Flip (){
    cout << "Flip (h)orizontally or (v)ertically ? " << endl;
    char option;
    cin >> option;
    if(option == 'h'){
        FlipHrizontal();
    }
    else if(option == 'v'){
        FlipVertical();
    }
}
//_________________________________________
void shrink() {
    int choice;
    cout << "Would you like to shrink the image by a factor of 2, 3, or 4?\n";
    cout << "Please input your choice as 2 if you want the dimensions to be 1/2, \n";
    cout << "Please input your choice as 3 if you want the dimensions to be 1/3, \n";
    cout << "Please input your choice as 4 if you want the dimensions to be 1/4, \n";
    cin >> choice;
    if ((choice != 2) && (choice != 3) && (choice != 4)) {
        cout << "Invalid entry.";
    }
    else {
            int x=0,y=0;
            for (int i = 0; i < SIZE; i+=choice) {
                for (int j = 0; j < SIZE; j+=choice) { // this loops through the entire image pixel by pixel, skipping every 2/3/4 pixels
                    if (choice==2){
                        newimage2[x][y] = image[i][j]; //saves the original image to an image half the original size
                    }
                    if (choice==3){
                        newimage3[x][y] = image[i][j]; //saves the original image to an image one third the original size
                    }
                    if (choice==4){
                        newimage4[x][y] = image[i][j]; //saves the original image to an image quarter the original size
                    }
                    y++;
                }
            }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) { // this loops through the entire image pixel by pixel
                image[i][j]=255; // makes the original image all white so that we can overwrite the smaller image on top of it

            }
        }
            for (int i = 0; i < SIZE/choice; i++) {
                for (int j = 0; j < SIZE/choice; j++) { // this loops through the entire image pixel by pixel
                    if (choice==2){
                        image[i][j] = newimage2[i][j]; //overwriting the smaller image half the original size on top
                    }
                    if (choice==3){
                        image[i][j] = newimage3[i][j]; // also overwriting here but for 1/3 dimension
                    } 
                    if (choice==4){
                        image[i][j] = newimage4[i][j]; // also overwriting here but for 1/4 dimension
                    }
                }
            }
    }
    }

void blur() {
    for (int i = 1; i < SIZE-1; i++) {
        for (int j = 1; j < SIZE-1; j++) { // loops through each image pixel by pixel
            image[i][j] = ( image[i][j] + image[i][j+1] + image[i][j-1] + image[i+1][j] +image[i+1][j+1] +
                    + image[i+1][j-1] + image[i-1][j+1] + image[i-1][j-1] + image[i-1][j] ) / 9;
		// takes the average of all the pixels around the pixel itself, including the pixel itself

        }
    }
}
//_________________________________________
void Mirror(){
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?" << endl;
    char option;
    cin >> option;
    if(option == 'l'){
      for (int i = 0; i < (SIZE); i++) {
        for (int j = 0; j< SIZE/2; j++) {
          image[i][j] = image[i][SIZE - j];
        }
      }
    }
    else if(option == 'r'){
      for (int i = 0; i < (SIZE); i++) {
        for (int j = 0; j< SIZE/2; j++) {
          image[i][SIZE - j] = image[i][j];
        }
      }
    }
    else if(option == 'u'){
      for (int i = 0; i < (SIZE/2); i++) {
        for (int j = 0; j< SIZE; j++) {
          image[i][j] = image[SIZE - i][j];
        }
      }
    }
    else if(option == 'd'){
      for (int i = 0; i < (SIZE/2); i++) {
        for (int j = 0; j< SIZE; j++) {
          image[SIZE - i][j] = image[i][j];
        }
      }
    }

}
//_________________________________________
void EdgeDetective (){
    long sum = 0;
    double avg = 0;
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j< SIZE; j ++) {
        if (image[i][j] > 128)
            image[i][j] = 255;
        else
            image[i][j] = 0;
        }
      }
    for(int i = 0; i < SIZE; i++){
      for(int j = 0; j < (SIZE - 1); j++){
        if(image[i][j] == 255){
          if(image[i][j] != image[i][j + 1]){
            image2[i][j] = 255;
            image2[i][j + 1] = 0;
            j += 1;
          }
          else if(image[i][j] == image[i][j + 1])
            image2[i][j] = 255;
        }
        else if(image[i][j] == 0){
          if((image[i][j] == image[i][j + 1]) && (image[i][j] == image[i - 1][j]) && (image[i][j] == image[i + 1][j])){
            image2[i][j] = 255;
          }
          else
            image2[i][j] = 0;
        }
      }
    }
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image2);
}
//_________________________________________
void Enlarge_Image()
{
    char choice ;
    cout << "please enter the number of the quarter to enlarge(1,2,3,4) :";
    cin >> choice ;
   // first quarter
  if (choice == '1')
  {
      for (int i = 0 , x = 0  ; i< SIZE; x++ , i+=2)
	{ for (int j = 0 ,y = 0  ;j< SIZE; y++ , j +=2)
		{
                image2[i][j] =  image[x][y];
                image2[i+1][j] = image[x][y];
                image2[i][j+1] = image[x][y];
                image2[i+1][j+1] = image[x][y];
		}
    }
  }
  // second quarter
  else if (choice == '2')
  {
      for (int i = 0 , x = 0  ; i< SIZE; x++ , i+=2)
	{ for (int j = 0 ,y = 128  ;j< SIZE; y++ , j +=2)
		{
                image2[i][j] =  image[x][y];
                image2[i+1][j] = image[x][y];
                image2[i][j+1] = image[x][y];
                image2[i+1][j+1] = image[x][y];
		}
    }
  }



    // third quarter
  else if (choice == '3')
  {
      for (int i = 0 , x = 128  ; i< SIZE; x++ , i+=2)
	{ for (int j = 0 ,y = 0  ;j< SIZE; y++ , j +=2)
		{
                image2[i][j] =  image[x][y];
                image2[i+1][j] = image[x][y];
                image2[i][j+1] = image[x][y];
                image2[i+1][j+1] = image[x][y];
		}
    }
  }

    // forth quarter
    else if (choice == '4')
    {
       for (int i = 0 , x = 128 ; i< SIZE; x++ , i+=2)
        { for (int j = 0 ,y = 128  ;j< SIZE; y++ , j +=2)
            {
                image2[i][j] =  image[x][y];
                image2[i+1][j] = image[x][y];
                image2[i][j+1] = image[x][y];
                image2[i+1][j+1] = image[x][y];
            }
        }
    }
 saveImage2 ();
}
//_________________________________________
void the_order (int& a , int& b  ,char q)
{
        if (q == '1')
        a = 0 , b = 0 ;
    else if (q == '2')
        a = 0 , b = 128;
    else if (q == '3')
        a = 128 , b = 0 ;
    else if (q == '4')
        a = 128 , b = 128 ;

}
//_____________________________________________________
void Shuffle_Filter()
{
    char q1 , q2 ,q3 ,q4 ;
    int a = 0 , b = 0 ;
    cout << "what is the order wold you like : ";
    cin  >> q1 >> q2 >> q3 >> q4 ;
//--------------------

    the_order(a,b,q1);//chose the number of the first quarter
	for (int i = 0  , x = a; i < SIZE/2; x++ , i++)//wright the first quarter
        {
            for (int j =0 , y = b ; j< SIZE/2 ; y++ , j++)
							(image2[i][j]=image[x][y]);
        }
//--------------------
    the_order(a,b,q2);//chose the number of the first quarter
	for (int i = 0  , x = a; i < SIZE/2; x++ , i++)//wright the first quarter
        {
            for (int j =128 , y = b ; j< SIZE ; y++ , j++)
							(image2[i][j]=image[x][y]);
        }
//--------------------

    the_order(a,b,q3);//chose the number of the third quarter
	for (int i = 128  , x = a; i < SIZE; x++ , i++)//wright the third quarter
        {
            for (int j =0 , y = b ; j< SIZE/2 ; y++ , j++)
							(image2[i][j]=image[x][y]);
        }
//--------------------

    the_order(a,b,q4);//chose the number of the forth quarter
	for (int i = 128  , x = a; i < SIZE; x++ , i++)//wright the forth quarter
        {
            for (int j =128 , y = b ; j< SIZE ; y++ , j++)
							(image2[i][j]=image[x][y]);
        }
   saveImage2 ();
}
//_________________________________________________________

void saveImage2 () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image2);

}
//_________________________________________________________

