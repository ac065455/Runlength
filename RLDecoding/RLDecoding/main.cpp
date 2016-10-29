#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class RLDecoding{
private:
public:
    int numRows, numCols, minVal, maxVal, length, currentColor;
    int** img;
    
    RLDecoding(int numRows, int numCols, int minVal, int maxVal){
        this->numRows = numRows;
        this->numCols = numCols;
        this->minVal = minVal;
        this->maxVal = maxVal;
        
        //construct 2D array dynamically
        img = new int*[numRows];
        for(int i=0; i<numRows; i++){
            img[i] = new int[numCols];
        }//for
        
        //initialize to 0
        for(int i=0; i<numRows; i++){
            for(int j=0; j<numCols; j++){
                img[i][j] = 0;
            }//for j
        }//for i
    }//constructor
    
    void loadImage(ifstream& inFile, ofstream& outFile){
        int row, col, pixel, length;
        for(int i=0; i<numRows; i++){
            for(int j=0; j<numCols; j++){
                while(!inFile.eof()){
                    inFile >> row;
                    inFile >> col;
                    inFile >> pixel;
                    inFile >> length;
                    createImage(outFile,i,j,row,col,pixel,length);
                    break;
                }//while
            }//for j
        }//for i
        inFile.close();
    }//findRun
    
    void createImage(ofstream& outFile, int i, int j, int row, int col, int pixel, int length){
        for(int k=0; k<length;k++){
            img[row][col++] = pixel;
        }//for k
    }//createImage
    
    void print(ofstream& outFile){
        for(int i=0; i<numRows; i++){
            for(int j=0; j<numCols; j++){
                outFile << img[i][j] << " ";
            }//for j
            outFile << "\n";
        }//for i
    }//print
    
};//class

int main(int argc, const char * argv[]) {
    ifstream inFile;
    inFile.open(argv[1]);
    ofstream outFile;
    outFile.open(argv[2]);
    
    int numRows, numCols, minVal, maxVal;
    inFile >> numRows;
    inFile >> numCols;
    inFile >> minVal;
    inFile >> maxVal;
    
    RLDecoding RDL(numRows, numCols, minVal, maxVal);
    outFile << numRows << " " << numCols << " " << minVal << " " << maxVal << "\n";
    RDL.loadImage(inFile,outFile);
    RDL.print(outFile);
    outFile.close();
    return 0;
}//main
