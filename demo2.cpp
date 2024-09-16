#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <ratio>
#include <chrono>
#include <vector>
#include "block2.cpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;
using namespace std::chrono;

Blockchain myChain;


vector<string> processData(vector<string>& newData) {
    // Perform operations on new data here
    for(int i=0;i<4;i++)
    cout<<newData[i]<<endl;
    myChain.AddBlock(Block(newData));
}


void readNewLines(const string& filename, streampos& lastPosition) {
    ifstream file(filename, ios::ate);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }

    streampos endPosition = file.tellg();
    file.seekg(lastPosition);

    string line;
  
    
    while (getline(file, line)) {
          vector<string> data;
        if (line.find("Light Intensity 1:") != string::npos) {
            data.push_back(line);
           // cout<<line<<endl;
            getline(file, line); // Read next line for Intensity 2
            data.push_back(line);
           // cout<<line<<endl;
            getline(file, line); // Read next line for Intensity 3
            data.push_back(line);
         //   cout<<line<<endl;
            getline(file, line); // Read next line for Present Time
            data.push_back(line);
         //   cout<<line<<endl;
            myChain.AddBlock(Block(data));
            // for(int i=0;i<4;i++)
            // cout<<data[i]<<endl;
            data.clear(); // Clear the data vector for the next set
        }
    }

    lastPosition = endPosition;

    file.close();
}


int main() {
    string filename = "DATA.txt";
    streampos lastPosition = 0;

    while (true) {
        readNewLines(filename, lastPosition);

        #ifdef _WIN32
        Sleep(5000);
        #else
        sleep(5);
        #endif
    }

    return 0;
}