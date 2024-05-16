//FCI - programming 1 - 2022 - Assignment 3
// Group task
//Program Name:photoshop program.cpp
// Names and IDs:
// Ahmed Shaaban Ahmed Refaei - 20210022 - S17,S18-B
// Abdulrahman Ibrahim Mahmoud Mohamed - 20210193 - S17,S18-B
// Mohamed Basim Sarhan Alkaabi - 20210711 - S17,S18-B
// Teaching Assistant: Eng. Hager Ali



#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.h"
#include "bmplib.cpp"

using namespace std;

unsigned char originalImage[SIZE][SIZE];
unsigned char secondImage[SIZE][SIZE];
unsigned char temp[4][SIZE/2][SIZE/2] = {};
unsigned char quarter[(SIZE/2)*(SIZE/2)] = {};
unsigned char detectimage[SIZE][SIZE];
unsigned char Leftimg[SIZE][128];
unsigned char Upperimg[128][SIZE];

void loadImage();
void saveImage();
void rotateImage();
void filterImage();
void blackAndWhiteImage();
void flipVerticallyImage();
void flipHorizontallyImage();
void InvertImage();
void darkenImage();
void lightenImage();
void mergeImages();
void loadSecondImage();
void shrinkImage();
void shrinkImageToHalf();
void shrinkImageToOneThird();
void shrinkImageToQuarter();
void shuffleFilter();
void extractQuarter(unsigned char* &, int);
void blurImage();
void edgeDetect();
void Rotate();
void flipping();
void EnlargeImage();
void flipHorizontallyImage(unsigned char m_img[SIZE][128]);
void flipVerticallyImage(unsigned char Upperimg[128][SIZE]);
void Mirrorimagefilter();
string response();
int main() {
    char choice;
    cout << "Welcome to our program \n Please enter file name of the image to process :" << endl;
    loadImage();
    cout <<"Please select a filter to apply or 0 to exit:"<< endl <<
         "1- Black & White Filter" << endl
         << "2- Invert Filter" << endl
         << "3- Merge Filter" << endl
         << "4- Flip Image"  << endl
         << "5- Darken and Lighten Image" << endl
         << "6- Rotate Image" << endl
         << "7- Detect Image Edges" << endl
         << "8- Enlarge Image" << endl
         << "9- Shrink Image " << endl
         << "a- Mirror Image" << endl
         << "b- Shuffle Image" << endl
         << "c- Blur Image" << endl;

    cin >> choice;
    switch(choice)
    {
        case '1':
            blackAndWhiteImage();
            saveImage();
            break;
        case '2':
            InvertImage();
            saveImage();
            break;
        case '3':
            cout << "Please enter name of image file to merge with : " << endl;
            mergeImages();
            saveImage();
            break;
        case '4':
            char verticalOrHorizontal;
            while (true) {
                cout << "Flip (h)orizontally or (v)ertically ? " << endl;
                cin >> verticalOrHorizontal;
                if (verticalOrHorizontal == 'v') {
                    flipVerticallyImage();
                    saveImage();
                    break;
                }
                else if (verticalOrHorizontal == 'h')
                {
                    flipHorizontallyImage();
                    saveImage();
                    break;
                }
                else
                    cout << "Please enter only (v) for flipping image vertically or (h) for flipping image horizontally " << endl;
            }
            break;
        case '5':
            char darkenOrLighten;
            cout << "Do you want to (d)arken or (l)ighten";
            while (true)
            {
                cin >> darkenOrLighten;
                if (darkenOrLighten == 'd')
                {
                    darkenImage();
                    saveImage();
                    break;

                }
                else if (darkenOrLighten == 'l')
                {
                    lightenImage();
                    saveImage();
                    break;
                }
                else
                    cout << "Please enter (d) for darken image or (l) for lighten image only " << endl;
            }
            break;
        case '6':
            filterImage();
            saveImage();
            break;
        case '7':
            edgeDetect();
            saveImage();
            break;
        case '8':
            EnlargeImage();
            saveImage();
            break;
        case '9':
            shrinkImage();
            saveImage();
            break;
        case 'a':
            Mirrorimagefilter();
            saveImage();
            break;
        case 'b':
            shuffleFilter();
            saveImage();
            break;
        case 'c':
            blurImage();
            saveImage();
            break;


    }


    return 0;
}

void loadImage() {
    char imageFileName[100];

    cout << "Enter the source image file name:";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, originalImage);
}

void saveImage() {
    char imageFileName[100];

    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    //
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, originalImage);


}
// Function of Rotate
void rotateImage() {
    int newimage;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = i; j < SIZE; j++)
        {
            newimage = originalImage[i][j];
            originalImage[i][j] = originalImage[j][i];
            originalImage[j][i] = newimage;
        }
    }


    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < (SIZE / 2); j++)
        {
            newimage = originalImage[i][j];
            originalImage[i][j] = originalImage[i][3 - 1 - j];
            originalImage[i][3 - 1 - j] = newimage;
        }
    }



}
void filterImage() {

    int choose = 0;
    cout << "please choose type of rotate" << endl << "1-(90 degree)" << endl << "2-(180 degree)" << endl << "3-(270 degree)" << endl;

    while (true) {
        cin >> choose;
        if (choose == 1)
        {
            rotateImage();
            break;

        }
        else if (choose == 2) {
            rotateImage();
            rotateImage();
            break;

        }
        else if (choose == 3) {
            rotateImage();
            rotateImage();
            rotateImage();
            break;

        }
        else
            cout << "please enter valid number" << endl;


    }
}
void InvertImage() {
    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++)

            originalImage[i][j] = 255 - originalImage[i][j]; // subtract pixel of 255 and assign result in original image


    }
}
void darkenImage()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)

            originalImage[i][j] /= 2; // divide every pixel by 2 and assign it.

    }

}
void lightenImage()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)

            originalImage[i][j] = (originalImage[i][j] + 255) / 2; // get the average of adding 255 plus pixel and assign result in original image

    }

}
void mergeImages()
{
    loadSecondImage();
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)

            originalImage[i][j] = (originalImage[i][j] + secondImage[i][j]) / 2; // get the average of every pixel of first image and the second image and assign it in original image
    }
}
void loadSecondImage() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, secondImage);
}

void blackAndWhiteImage()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (originalImage[i][j] > 127)
                originalImage[i][j] = 255;
            else
                originalImage[i][j] = 0;
        }
    }
}

void flipVerticallyImage()
{
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = 0; j < SIZE; j++) {
            int temp = originalImage[i][j];
            originalImage[i][j] = originalImage[SIZE - i][j];
            originalImage[SIZE - i][j] = temp;
        }
    }
}

void flipHorizontallyImage()
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            int temp = originalImage[i] [j] ;
            originalImage[i][j] = originalImage[i][SIZE - j];
            originalImage[i][SIZE - j] = temp;
        }
    }
}
void blurImage()
{
    for(int i=0;i<SIZE;i++)
    {
        for (int j=0;j<SIZE;j++)
        {
            if ( (i != 0 && i != 255) && (j !=0 && j!= 255) )
                originalImage[i][j] = (originalImage[i-1][j-1] + originalImage[i-1][j] + originalImage[i-1][j+1] + originalImage[i][j-1] + originalImage[i][j] + originalImage[i][j+1] + originalImage[i+1][j-1] + originalImage[i+1][j] + originalImage[i+1][j+1])/9;
            else
            if(i == 0)
                originalImage[i][j] = (originalImage[i+1][j] + originalImage[i][j])/2;
            else if (j == 0)
                originalImage[i][j] = (originalImage[i][j] + originalImage[i-1][j] + originalImage[i-1][j+1] + originalImage[i][j+1])/4;
            else if (i == 255)
                originalImage[i][j] = (originalImage[i][j] + originalImage[i-1][j])/2;
            else if (j == 255)
                originalImage[i][j] = (originalImage[i][j] + originalImage[i][j-1] + originalImage[i+1][j-1] + originalImage[i+1][j])/4;


        }

    }
}
void shrinkImageToHalf()
{
    unsigned int temp[SIZE][SIZE];
    int x=0 ,y=0;

    for(int i=0;i<SIZE;i+=2)
    {
        y=0;
        for(int j=0;j<SIZE;j+=2)
        {
            temp[x][y] = (originalImage[i][j]+originalImage[i][j+1] + originalImage[i+1][j] + originalImage[i+1][j+1])/4;
            y+=1;
        }
        x+=1;
    }
    for (int i=0;i < SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
            originalImage[i][j] = temp[i][j];
    }
    for(int i=0;i < SIZE;i++)
    {
        for(int j=0;j<SIZE;j++){
            if (i > SIZE/2 || j > SIZE/2)
                originalImage[i][j] = 255;

        }
    }

}
void shrinkImageToQuarter(){

    unsigned int temp[SIZE][SIZE];
    int x=0 ,y=0;

    for(int i=0;i<SIZE;i+=4)
    {
        y=0;
        for(int j=0;j<SIZE;j+=4)
        {
            temp[x][y] = (
                                 originalImage[i][j]     +
                                 originalImage[i][j+1]   + originalImage[i][j+2]   +
                                 originalImage[i][j+3]   + originalImage[i+1][j]   +
                                 originalImage[i+1][j+1] + originalImage[i+1][j+2] +
                                 originalImage[i+1][j+3] + originalImage[i+2][j]   +
                                 originalImage[i+2][j+1] + originalImage[i+2][j+2] +
                                 originalImage[i+2][j+3] + originalImage[i+3][j]   +
                                 originalImage[i+3][j+1] + originalImage[i+3][j+2] +
                                 originalImage[i+3][j+3]
                         )/16;
            y+=1;
        }
        x+=1;
    }
    for (int i=0;i < SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
            originalImage[i][j] = temp[i][j];
    }
    for(int i=0;i < SIZE;i++)
    {
        for(int j=0;j<SIZE;j++){
            if (i > SIZE/4 || j > SIZE/4)
                originalImage[i][j] = 255;

        }
    }
}
void shrinkImageToOneThird()
{
    unsigned int temp[SIZE][SIZE];
    int x=0 ,y=0;

    for(int i=0;i<SIZE;i+=3)
    {
        y=0;
        for(int j=0;j<SIZE;j+=3)
        {
            temp[x][y] = (
                                 originalImage[i][j]     + originalImage[i][j+1]   +
                                 originalImage[i][j+2]   + originalImage[i+1][j]   +
                                 originalImage[i+1][j+1] + originalImage[i+1][j+2] +
                                 originalImage[i+2][j]   + originalImage[i+2][j+1] +
                                 originalImage[i+2][j+2]
                         )/9;
            y+=1;
        }
        x+=1;
    }
    for (int i=0;i < SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
            originalImage[i][j] = temp[i][j];
    }
    for(int i=0;i < SIZE;i++)
    {
        for(int j=0;j<SIZE;j++){
            if (i > SIZE/3 || j > SIZE/3)
                originalImage[i][j] = 255;

        }
    }
}
void shrinkImage()
{
    int choice;
    while (true)
    {
        cout << " Choose dimension that you want to shrink image to" << endl;
        cout << "1 - to 1/2 " << endl
             << "2 - to 1/3" << endl
             << "3 - to 1/4 " ;
        cin >> choice;
        if (choice == 1){
            shrinkImageToHalf();
            break;
        }
        else if(choice == 2){
            shrinkImageToOneThird();
            break;
        }
        else if (choice == 3){
            shrinkImageToQuarter();
            break;
        }
        else
            cout << "Please enter your choice correctly " << endl ;
    }
}
void extractQuarter(unsigned char * & ptr, int quarter) {
    int startRow = 0, endRow = SIZE/2, startCol = 0, endCol = SIZE/2;

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
            ptr[k++] = originalImage[i][j];
        }
    }
}



void shuffleFilter() {
    string order;
    unsigned char * pQuarter = quarter;
    unsigned char * pTemp = &temp[0][0][0];
    int k = 0;
    cout << "New order of quarters ?\n";
    cin.ignore();
    getline(cin, order);
    // Shuffle process:
    for (int i = 0; i < order.length(); i++) {
        if (order[i] == ' ') {
            continue;
        }
        extractQuarter(pQuarter, (int) (order[i] - '0'));
        for (int j = 0; j < ((SIZE * SIZE) / 4); j++) {
            pTemp[k] = pQuarter[j];
            k++;
        }
    }

    int qrtr = 0, row = 0, col = 0;
    for (int i = 0; i < SIZE; i++) {
        if (i == SIZE / 2) {
            qrtr += 2;
            row = 0;
        }
        col = 0;
        for (int j = 0; j < SIZE; j++) {
            if (j == SIZE / 2) {
                qrtr++;
                col = 0;
            }
            originalImage[i][j] = temp[qrtr][row][col];
            col++;
        }
        qrtr--;
        row++;
    }
}
void edgeDetect() {
    long avarage = 0;
    int x=0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            detectimage[i][j]=255;

        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            avarage += originalImage[i][j];

        }
    }
    avarage /= (SIZE*SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if (originalImage[i][j] > avarage)
                originalImage[i][j] = 255;
            else
                originalImage[i][j] = 0;


        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if(x==1)
            {
                detectimage[i][j]=255;
                if (originalImage[i][j+1]==255)
                {
                    x=0;
                }

            }

            if(x==0)
            {
                if (originalImage[i][j]==0)
                {
                    detectimage[i][j]=0;
                    x=1;
                    if(originalImage[i-1][j]==255 or originalImage[i+1][j]==255 or originalImage[i-1][j+1]==255 or originalImage[i-1][j-1]==255 or originalImage[i+1][j+1]==255 or originalImage[i+1][j-1]==255)
                    {
                        detectimage[i][j]=0;
                        x=0;
                    }
                }
            }
        }

    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            originalImage[i][j]=detectimage[i][j];

        }
    }


}
void Rotate() {
    for (int x = 0; x < SIZE; x++)
        for (int y = x; y < SIZE; y++)
            swap(originalImage[x][y], originalImage[y][x]);
}

void flipping() {
    char FHV;
    cout << "Flip (h)orizontally or (v)ertically?: ";
    cin >> FHV;
    for (int i = 0; i < SIZE; i++)
    {
        int j = 0;
        int k = SIZE - 1;
        while (j < k)
        {
            if (FHV == 'h')
                swap(originalImage[i][j], originalImage[i][k]);
            if (FHV == 'v')
                swap(originalImage[j][i], originalImage[k][i]);
            j++;
            k--;
        }
    }

}
void flipHorizontallyImage(unsigned char m_img[SIZE][128]) {
    for (int i = 0; i < SIZE; i++)
    {
        int j = 0;
        int k = SIZE - 1;
        while (j < k)
        {
            swap(originalImage[i][j], originalImage[i][k]);
            j++;
            k--;
        }
    }
}

void flipVerticallyImage(unsigned char Upperimg[128][SIZE]) {
    for (int i = 0; i < SIZE; i++)
    {
        int j = 0;
        int k = SIZE - 1;
        while (j < k)
        {
            swap(originalImage[j][i], originalImage[k][i]);
            j++;
            k--;
        }
    }
}

void Mirrorimagefilter() {
    char direction;
    cout << "Choose one of these Mirror sides, (l)eft, (r)ight, (u)pper, (d)own: ";
    cin >> direction;
    if (direction == 'l')
    {
        for (int x = 0; x < SIZE; x++)
            for (int y = 0; y < SIZE / 2; y++)
                Leftimg[x][y] = originalImage[x][y];

        flipHorizontallyImage(Leftimg);
        for (int x = 0; x < SIZE; x++)
            for (int y = 0; y < 128; y++)
                swap(Leftimg[x][y], originalImage[x][y]);
    }
    if (direction == 'r')
    {
        for (int x = 0; x < SIZE; x++)
            for (int y = SIZE; y > SIZE / 2; y--)
                Leftimg[x][y] = originalImage[x][y];

        flipHorizontallyImage(Leftimg);
        for (int x = 0; x < SIZE; x++)
            for (int y = SIZE; y > 128; y--)
                swap(Leftimg[x][y], originalImage[x][y]);
    }
    if (direction == 'u')
    {
        for (int x = 0; x < SIZE; x++)
            for (int y = 0; y < SIZE / 2; y++)
                Upperimg[y][x] = originalImage[y][x];

        flipVerticallyImage(Upperimg);
        for (int x = 0; x < SIZE; x++)
            for (int y = 0; y < 128; y++)
                swap(Upperimg[y][x], originalImage[y][x]);
    }
    if (direction == 'd')
    {
        Rotate();
        for (int x = 0; x < SIZE; x++)
            for (int y = SIZE; y > SIZE / 2; y--)
                Leftimg[x][y] = originalImage[x][y];

        flipHorizontallyImage(Leftimg);
        for (int x = 0; x < SIZE; x++)
            for (int y = SIZE; y > 128; y--)
                swap(Leftimg[x][y], originalImage[x][y]);
        Rotate();
    }

}
void EnlargeImage() {
    unsigned char newimage[128][128];
    string choise=response();
    if(choise=="1"){
        for (int i = 0; i <= 128; i++) {
            for (int j = 0; j <= 128; j++) {
                newimage[i][j]= originalImage[i][j];

            }
        }
    }else if (choise=="2"){
        for (int i = 0; i < 128; i++) {
            for (int j = 128; j < 256; j++) {
                newimage[i][j-128]=originalImage[i][j];
            }
        }


    }else if (choise=="3"){
        for (int i = 128; i <256 ; i++) {
            for (int j = 0; j < 128; j++) {
                newimage[i-128][j]=originalImage[i][j];
            }
        }


    }else if (choise=="4"){
        for (int i = 128; i <256 ; i++) {
            for (int j = 128; j < 256; j++) {
                newimage[i-128][j-128]= originalImage[i][j];
            }
        }

    }
    for(int i=0,m=0;i<=256,m<=128;i+=2,m++)
    {
        for(int j=0,n=0;j<=256,n<=128;j+=2,n++)
        {
            originalImage[i][j]=newimage[m][n];
            originalImage[i+1][j]=newimage[m][n];
            originalImage[i][j+1]=newimage[m][n];
            originalImage[i+1][j+1]=newimage[m][n];
        }

    }
}


string response(){
    string choose;

    while(true){
        cout<<" Enter the quarter number from 1 to 4"<<endl;
        cin>>choose;
        if(choose=="1"||choose=="2"||choose=="3"||choose=="4") {
            return choose;
        }
        else{
            cout<<"please Enter an existing number "<<endl;

        }

    }
}
