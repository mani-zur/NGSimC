#include "Addons.h"

using namespace std;

//givie random sign (-1,1)
int rSign(){
    if (rand()%2) return -1;
    else return 1;
}

//Reading data form config file
Config::Config(char* fName){
    ifstream cFile (fName);
    if (cFile.is_open()){
        string line;
        while(getline(cFile, line)){
            std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
            line.erase(end_pos, line.end());
            if(line[0] == '#' || line.empty())
                continue;
            size_t delimiterPos = line.find("=");
            string name = line.substr(0, delimiterPos);
            double valu = stod(line.substr(delimiterPos + 1));
            param[nParams]=name;
            value[nParams]=valu; 
            nParams++;
        }
    }
    else cerr << "Couldn't open config file for reading.\n";
}

//Returnig value of chosen variable by name
double Config::GetValue(char * para){
    for(int i = 0; i < nParams; i++){
        if (param[i]==para){
            return value[i];
        }
    }
    cerr << "Parametr "<< para <<" not find !" <<endl;
    return -1.;
}