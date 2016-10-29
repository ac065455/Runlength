#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class runLength{
private:
public:
    int numRows, numCols, minVal, maxVal, color, pixel, currentColor, length;
    int** img;
    
    runLength(int numRows, int numCols, int minVal, int maxVal){
        this->numRows = numRows;
        this->numCols = numCols;
        this->minVal = minVal;
        this->maxVal = maxVal;
        
        //create size of img 2D array
        img = new int*[numRows];
        for(int i=0; i<numRows; i++){
            img[i] = new int[numCols];
        }//for i
        
        //initialize img 2D array to 0
        for(int i=0; i<numRows; i++){
            for(int j=0; j<numCols; j++){
                img[i][j] = 0;
            }//for j
        }//for i
    }//constructor
    
    void loadImage(ifstream& inFile){
        int data;
        for(int i=0;i<numRows;i++){
            for(int j=0;j<numCols;j++){
                while(!inFile.eof()){
                    inFile >> data;
                    img[i][j] = data;
                    break;
                }//while
            }//for j
        }//for i
        inFile.close();
    }//loadImage
    
    void findRun(ofstream& outFile){
        currentColor = 0;
        length = 0;
        for(int i=0; i<numRows; i++){
            for(int j=0; j<numCols; j++){
                if(img[i][j] != currentColor){
                    currentColor = img[i][j];
                    length = 1;
                    if(img[i][j] == 0){
                        continue;
                    }//if
                    outFile << i << " " << j << " " << currentColor;
                }//if
                else if(j%numCols == 0){
                    if(currentColor == 0){
                        continue;
                    }
                    outFile << " " << length;
                    outFile << "\n";
                    if(img[i][j] == 0){
                        continue;
                    }//if
                    outFile << i << " " << j << " " << currentColor;
                    length = 1;
                }//else if
                else{
                    if(img[i][j+1] != img[i][j]){
                        if(img[i][j] == 0){
                            continue;
                        }//if
                        else{
                            currentColor = 0;
                            outFile << " " << length+1 << "\n";
                        }//else
                    }//if
                    else{
                        length++;
                    }//else
                }//else
            }//for j
        }//for i
    }//findRun
};//runlength


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
    
    runLength myRun(numRows,numCols,minVal,maxVal);
    outFile << numRows << " " << numCols << " " << minVal << " " << maxVal << "\n";
    myRun.loadImage(inFile);
    myRun.findRun(outFile);
    
    outFile.close();
    return 0;
}//main
