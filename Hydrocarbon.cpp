// Author: Matthew Nunez
// The goal of this code is to maintain one entry for each unique molecular formula along 
// with all the names for that formula. After they have all been read in, 
// we will sort the vector by carbon and hydrogen, 
// and finally display all the entries in the sorted vector.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

// Hydrcarbon struct contains
// vector of names
// number of carbons
// number of hydrogens
struct Hydrocarbon {
    vector<string> name;
    int carbon,hydrogen;
};

// Prototypes
void open_file(ifstream& file);
void fill_vector(ifstream& file, vector<Hydrocarbon>& HC);
void add_name(vector<Hydrocarbon>& HC, const string& name, int carbon, int hydrogen);
void insert_info(vector<Hydrocarbon>& HC, const string& name, int carbon, int hydrogen);
void sort_vector(vector<Hydrocarbon>& HC);
void dis_single(const vector<Hydrocarbon>& HC, size_t idx);
void display(const vector<Hydrocarbon>& HC);

int main() {
    ifstream file;
    vector<Hydrocarbon> HC;

    open_file(file);
    fill_vector(file,HC);
    file.close();
    sort_vector(HC);
    display(HC);

    return 0;
}

void open_file(ifstream& file){
    // attempts to open stream, if user provides invalid filename then ask again
    // will ask until the stream successfully opens
    string file_name;
    do{
        cout << "Please enter the file name: ";
        cin >> file_name;
        file.open(file_name);
        if (!file) {
            cerr << "Could not open the file." << endl;
            file.clear();
            file.open(file_name);
        }
    } while (!file);
}

void insert_info(vector<Hydrocarbon>& HC, const string& name, int carbon, int hydrogen) {
    // creates new Hydrocarbon then pushes back into HC vector
    Hydrocarbon new_HC;
    new_HC.name.push_back(name);
    new_HC.carbon = carbon;
    new_HC.hydrogen = hydrogen;
    HC.push_back(new_HC);
}

void add_name(vector<Hydrocarbon>& HC, const string& name, int carbon, int hydrogen){
    // finds if the formula is in the vector HC
    // if the formula is in HC, add name
    // if not then create new hydrocarbon
    bool form_not_found = true;

    for (size_t index = 0; index < HC.size(); ++index){
        if ((carbon == HC[index].carbon) && (hydrogen == HC[index].hydrogen)) {
            HC[index].name.push_back(name);
            form_not_found = false;
        }
    }
    if (form_not_found){
        insert_info(HC,name,carbon,hydrogen);
    }
}

void fill_vector(ifstream& file, vector<Hydrocarbon>& HC) {
    // fills the vector from file
    string name;
    int carbon;
    char C,H;
    int hydrogen;
    while (file >> name >> C >> carbon >> H >> hydrogen) {
        add_name(HC,name, carbon, hydrogen);
    }
    file.close();
};

void sort_vector(vector<Hydrocarbon>& HC) {
    Hydrocarbon temp;
    //bubble sort
    for (size_t idx = 0; idx < HC.size(); ++idx){
        for (size_t curr_idx = 0; curr_idx < HC.size()-1; ++curr_idx){
            if (HC[curr_idx].carbon > HC[curr_idx+1].carbon){
                temp = HC[curr_idx];
                HC[curr_idx] = HC[curr_idx+1];
                HC[curr_idx+1] = temp;
            } else if (HC[curr_idx].carbon == HC[curr_idx+1].carbon){
                if (HC[curr_idx].hydrogen > HC[curr_idx+1].hydrogen){
                    temp = HC[curr_idx];
                    HC[curr_idx] = HC[curr_idx+1];
                    HC[curr_idx+1] = temp;
                }
            }
        }
    }
}

void dis_single(const vector<Hydrocarbon>& HC, size_t idx){
    // print hydrogen's and carbon's of specified HC
    cout << " C"<< HC[idx].carbon << " H" <<  HC[idx].hydrogen;
}

void display(const vector<Hydrocarbon>& HC) {
    // prints the vector of names and the corresponding carbon's and hydrogen's
    for (size_t idx = 0; idx < HC.size(); idx++) {
        dis_single(HC,idx);
        for (size_t n = 0; n < HC[idx].name.size(); n++) {
            cout << " " << HC[idx].name[n];
        }
        cout << endl;
    }
}