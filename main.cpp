//
//  Project 1 Starter Code - Gerrymandering
//  TODO:  Replace this comment with your header info.
//  Plan so far
//  //1. greetings
    //2. prompt with a command, 4 available functions (load, search, plot, stats)
    //3. read the command line, figure out which command user wants
    //4. do the function
    //5. prompt with a command again.
    //for load, need to input filestream, read, get data, 
    // and put into an array
    // for search use binary search 
    // 

//

#include <ctype.h>
#include <cctype>
#include <cstring>
#include "ourvector.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <vector>


ourvector<string> states;

ourvector<ourvector<string>> districts;
ourvector<ourvector<string>> rVotes;
ourvector<ourvector<string>> dVotes;

ourvector<string> eligibleStates;
ourvector<string> eligibleVoters;
bool dataloaded;
string currentStateForGreetings = "N/A";

using namespace std;

void greetings(bool loaded1, string state1) {
    
    string loaded2;
    string state2;
    loaded2 = "No";
    if (loaded1) {
        loaded2 = "Yes";
    } 
    state2 = state1;
    
        
    
    cout << endl << "Data Loaded? " << loaded2 << endl;
    cout << "State: " << state2 << endl << endl;
    
    
}

void plot (string stateName) {
    string finalString;
    int repVotes;
    int demVotes;
    int stateIndex;
    string plotString;
    if (!dataloaded) {
        cout << "No data loaded, please load data first." << endl;
        greetings(dataloaded,currentStateForGreetings);
    } else {
        if (currentStateForGreetings == "N/A") {
            cout << "State Not Found, try again" << endl;
        } else {

            for (int x = 0; x < states.size(); x++) {
                
                if (states.at(x) == stateName) {
                    stateIndex = x;
                }
            }

            for (int x = 0; x < districts.at(stateIndex).size(); x++) {
                repVotes = 0;
                demVotes = 0;
                plotString = "";
                repVotes = stoi(rVotes.at(stateIndex).at(x));
                demVotes = stoi(dVotes.at(stateIndex).at(x));
                cout << "District: " << districts.at(stateIndex).at(x) << endl;
                
                int proportionD = int((float(demVotes) / float(repVotes + demVotes)) * 100.0);
                int proportionR = 100 - proportionD;
                for (int x = 0; x < proportionD; x++) {
                    plotString += "D";
                }
                 for (int x = 0; x < proportionR; x++) {
                    plotString += "R";
                }


                cout << plotString << endl;


            }
            
        }
    }
     greetings(dataloaded, currentStateForGreetings);
}
void statsFunc(string stateName) {
    string gerry;
    string totalEVoters;
    int WastedDemocraticVotes;
    int WastedRepublicanVotes;
    int stateIndex;
    int difference;
    int totalVotesCast;
    float eGap;
    string whoWon;
    if (!dataloaded) {
        cout << "No data loaded, please load data first." << endl;
        greetings(dataloaded,currentStateForGreetings);
    } else {
        if (currentStateForGreetings == "N/A") {
            cout << "State Not Found, try again" << endl;
        } else {
            




            for (int x = 0; x < states.size(); x++) {
                if (states.at(x) == stateName) {
                    stateIndex = x;
                
                }
            }

            
            int totalOverHalf = 0;
            totalVotesCast = 0;
            WastedDemocraticVotes = 0;
            WastedRepublicanVotes = 0;
            for (int x = 0; x < rVotes.at(stateIndex).size(); x++) {
                totalVotesCast += (stoi(rVotes.at(stateIndex).at(x)) + stoi(dVotes.at(stateIndex).at(x)));
                totalOverHalf = ((stoi(rVotes.at(stateIndex).at(x)) + stoi(dVotes.at(stateIndex).at(x))) / 2) + 1;

                
                

                if (stoi(rVotes.at(stateIndex).at(x)) > stoi(dVotes.at(stateIndex).at(x))) {
                    whoWon = "Republicans";
                    
                    WastedRepublicanVotes += (stoi(rVotes.at(stateIndex).at(x)) - totalOverHalf);
                    WastedDemocraticVotes += stoi(dVotes.at(stateIndex).at(x));
                    
                } else if (stoi(rVotes.at(stateIndex).at(x)) < stoi(dVotes.at(stateIndex).at(x))) {
                    whoWon = "Democrats";
                    
                    WastedDemocraticVotes += (stoi(dVotes.at(stateIndex).at(x)) - totalOverHalf);
                    WastedRepublicanVotes += stoi(rVotes.at(stateIndex).at(x));
                } else {
                    whoWon = "None";
                 
                }

                
            }
            if(WastedRepublicanVotes > WastedDemocraticVotes) {
                    difference = WastedRepublicanVotes - WastedDemocraticVotes;
                } else {
                    difference = WastedDemocraticVotes - WastedRepublicanVotes;
                }
                eGap = (float(difference) / float(totalVotesCast)) * 100.0;
               
                if (eGap >= 7.00) {
                    gerry = "Yes";
                } else {
                    gerry = "No";
                }

                if (rVotes.at(stateIndex).size() < 3) {
                gerry = "No";
                }

            totalEVoters = "";
            

            
            //3,157
            

            cout << "Gerrymandered: " << gerry << endl;
            if (gerry == "Yes") {
                if (whoWon == "Democrats") {
                    cout << "Gerrymandered against: " << "Republicans" << endl;
                } else if (whoWon == "Republicans") {
                    cout << "Gerrymandered against: " << "Democrats" << endl;
                } else {
                    //error
                }
                
                cout << "Efficiency Factor: " << eGap << "%" << endl;
            }
            cout << "Wasted Democratic votes: " << WastedDemocraticVotes << endl;
            cout << "Wasted Republican voters: " << WastedRepublicanVotes << endl;
            for (int x = 0; x < eligibleStates.size(); x++) {
                if (eligibleStates.at(x) == stateName) {
                    cout << "Eligible voters: " << eligibleVoters.at(x) << endl;
                    break;
                }
                if (x == eligibleStates.size() - 1) {
                    cout << "Eligible voters: Unknown" << endl;
                    break;
                }
            }
            

            greetings(dataloaded, currentStateForGreetings);

        }

    }
}
void search (string stateName1) {
    string stateName2 = stateName1;
    string currentStateInVector;
    ourvector<string> states2 = states;
    int index1;
    bool stateFound = false;
    if (!dataloaded) {
        cout << "No data loaded, please load data first." << endl;

        greetings(dataloaded,currentStateForGreetings);
    } else {


        for (int x = 0; x < states2.size(); x++) {
            
            
            for (auto& state5:states2[x]) {

                state5 = tolower(state5);
            }
            currentStateInVector = states2.at(x);

            for (int z = 0; z < stateName2.size(); z++) {
                stateName2.at(z) = tolower(stateName2.at(z));

                
            }
            if (currentStateInVector == stateName2) {
                stateFound = true;
                index1 = x;
                break;
            }
           
           
        }
        if (stateFound) {
            currentStateForGreetings = states.at(index1);
            greetings(dataloaded, currentStateForGreetings);
        } else {
            cout << "State does not exist, search again." << endl << endl;
            greetings(dataloaded, currentStateForGreetings);
            
        }
       
    }
}
void load(string filename) {
    if(dataloaded) {
        cout << "Already read data in, exit and start over." << endl << endl;
        greetings(dataloaded,currentStateForGreetings);
    } else {

    
    
    
    string districtsFile;
    string eligibilityFile;
    size_t found = filename.find(" ");
    if (found != string::npos && found != filename.size() - 1) {
        districtsFile = filename.substr(0, found);
        eligibilityFile = filename.substr(found+1, filename.size() - found - 1);
        cout << endl;
    }
    
    //open districts.txt
    ifstream filestream;
    string fileContent;
    string stateName;
    
    filestream.open(districtsFile);
    cout << "Reading: " << districtsFile << endl;
    getline(filestream,fileContent);
    if (!filestream.is_open()) {
        cout << "Invalid first file, try again." << endl;
    } else {
        
        while (!filestream.eof()) {
            int commaCounter = 0;
            size_t foundComma = fileContent.find(",");
            size_t currentCommaIndex;
            size_t nextCommaIndex;
            
            //find state Name
            if (foundComma != string::npos) {
                
                stateName = fileContent.substr(0,foundComma);
                states.push_back(stateName);
                cout << "..."<< stateName << "...";

            }
            //find districts
            //find number of commas
            int distinguish = 1;
            ourvector<string> districtsWithin;
            ourvector<string> rVotesWithin;
            ourvector<string> dVotesWithin;
            int totalDistricts = 0;
            while (foundComma != string::npos) {
                
                currentCommaIndex = foundComma;
                commaCounter++;
                nextCommaIndex = fileContent.find(",", foundComma + 1);
                string districtNumber;
                size_t foundAL = fileContent.find("AL");
                
                
                districtNumber = fileContent.substr(foundComma+1,nextCommaIndex-currentCommaIndex-1);
                
                
                if (distinguish % 3 == 1) {
                    if (districtNumber == "AL") {
                        districtsWithin.push_back("1");
                        totalDistricts++;
                    } else {
                        districtsWithin.push_back(districtNumber);
                        totalDistricts++;
                    }
                  
                } else if (distinguish % 3 == 2) {
                    dVotesWithin.push_back(districtNumber);
                  
                } else if(distinguish % 3 == 0) {
                    rVotesWithin.push_back(districtNumber);
                  
                } else {
                    //error
                    cout << "ERROR FOUND" << endl;
                }

                distinguish++;
                
                
                foundComma = fileContent.find(",", foundComma + 1);

            } 
            cout << totalDistricts << " districts total" << endl;
           
            districts.push_back(districtsWithin);
            dVotes.push_back(dVotesWithin);
            rVotes.push_back(rVotesWithin);
            
            



            getline(filestream,fileContent);
    }
        filestream.close();
    }
    cout << endl;
    cout << "Reading: " << eligibilityFile << endl;
    //opens eligibility file
    filestream.open(eligibilityFile);
    getline(filestream,fileContent);
     if (!filestream.is_open()) {
        cout << "Invalid second file, try again." << endl;
        
    } else {
        
        while (!filestream.eof()) {
            
            size_t foundComma = fileContent.find(",");
            size_t foundState;
            string stateName;
            string votersNumber;

            if(foundComma != string::npos) {
                stateName = fileContent.substr(0,foundComma);
                votersNumber = fileContent.substr(foundComma+1,fileContent.size() - foundComma - 1);
                bool found1 = false;
                for (int x = 0; x < states.size(); x++) {
                    if (states.at(x) == stateName) {
                        found1 = true;
                        break;
                    }
                }




                if (found1) {
                    
                    eligibleStates.push_back(stateName);
                    eligibleVoters.push_back(votersNumber);
                    cout << "..." << stateName << "..." << votersNumber << " eligible voters"<< endl;
                } else {
                    //state not found in districts.txt
                    
                }

            }

            


            
            getline(filestream,fileContent);
    }
        filestream.close();
    }
    
    dataloaded = true;

    greetings(dataloaded,currentStateForGreetings);


    }


}


void getCommand() {
    string command1;
    string commandContent;
    cout << "Enter command: ";
    getline(cin,command1);
    cout << endl;
    cout << "-----------------------------" << endl << endl;
    string load1 = "load";
    string search1 = "search";
    string stats1 = "stats";
    string plot1 = "plot";

    size_t found = command1.find(load1);
    size_t foundSpace = command1.find(" ");
   
    if (found != string::npos && found == 0 && foundSpace == 4){
        
        commandContent = command1.substr(5, command1.size() - 5);
        load(commandContent);

    } 
    found = command1.find(search1);
    if (found != string::npos && found == 0 && foundSpace == 6) {
        commandContent = command1.substr(7, command1.size() - 7);
        search(commandContent);

    } 
    found = command1.find(stats1);
    if (found != string::npos && found == 0 && command1.size() == 5) {
       statsFunc(currentStateForGreetings);

    } 
    found = command1.find(plot1);
    if (found != string::npos && found == 0 && command1.size() == 4) {
        plot(currentStateForGreetings);

    } 
    // error try again
    

    //string parsing (CHECK)
    //do command
    //then print out loading
    found = command1.find("exit");
    if (found != string::npos && found == 0 && command1.size() == 4) {

    }  else {
        getCommand();
    }
    
}




int main() {
    //TODO:  Write your code here.  
    // You should have LOTS of function decomposition.
    
    
    dataloaded = false;
    cout << "Welcome to the Gerrymandering App!" << endl;
    greetings(dataloaded,currentStateForGreetings);
    getCommand();

    
    // ourvector<int> vec1;
    
    
    // vec1._stats();


    return 0;
}