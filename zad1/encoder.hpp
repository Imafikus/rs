#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


class encoder {
public:

    encoder(int step) : m_step(step)
    {};

    int getStep() {
        return m_step;
    }


    string operator()(string line) {
        if(line == "" || m_step == 0) {
            return line;
        }
        string encodedLine = "";
        for(auto c : line) {
            encodedLine += determineEncoding(c);
        }
        return encodedLine;
    }

private:

    char determineEncoding(char c) {
        if(isUpper(c)) {
            int newStep = calculateNewStep(upper.size());
            int pos = findPos(c, upper);
            
            string rotatedString = upper;
    
            rotate(rotatedString.begin(), rotatedString.begin() + newStep, rotatedString.end());
            return rotatedString[pos];
            
        }
        
        if(isLower(c)) {
            int newStep = calculateNewStep(lower.size());
            int pos = findPos(c, lower);
            string rotatedString = lower;
            
            rotate(rotatedString.begin(), rotatedString.begin() + newStep, rotatedString.end());
            
            return rotatedString[pos];
        }
        if(isNumber(c)) {
            int newStep = calculateNewStep(number.size());
            int pos = findPos(c, number);
            string rotatedString = number;
            rotate(rotatedString.begin(), rotatedString.begin() + m_step, rotatedString.end());
            return rotatedString[pos];
        }
        return '#';

    }

    int calculateNewStep(int size) {
        int newStep = m_step;

        if(newStep < 0) {
            while(newStep < 0) {
                newStep += size;
            }
        }
        if(newStep > size) {
            while(newStep > size) {
                newStep -= size;
            }
        }
        return newStep;
    }

    bool isUpper(char a) {
        for(auto c : upper) {
            if (c == a) {
                return true;
            }
        }
        return false;
    }
    bool isLower(char a) {
        for(char c : lower) {
            if (c == a) {
                return true;
            }
        }
        return false;
    }
    bool isNumber(char a) {
        
        for(char c : number) {            
            if (c == a) {
                return true;
            }
        }
        return false;
    }

    int findPos(char c, string s) {
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == c) {
                return i;
            }
        }
        return -1;
    }

    int m_step;
    string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lower = "abcdefghijklmnopqrstuvwxyz";
    string number = "0123456789";

};