// Author: Matthew Nunez
// This code is an implementation of Conway's Game of Life


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream life_game("life.txt");
    if (!life_game){
        cerr << "Could not open file!.\n";
        exit(1);
    }

    vector<string> cells;
    string line;
    
    cout << "Initial world"<< endl;

    while (life_game >> line){
        cout << line << endl;
        cells.push_back(line);
    }

    cout << string(20, '=') <<  endl;

    life_game.close();
    for (int outputs = 1; outputs < 11; outputs++){

        cout << "Generation: " << outputs << endl;
        
        vector<string> new_gen;
        for (size_t r = 0; r < cells.size(); ++r) {
            string nextline;
            for (size_t c = 0; c < cells[0].size(); ++c) {
                nextline.push_back('-');
            }
            new_gen.push_back(nextline);
        }

        for (size_t r = 0; r < cells.size(); ++r) {
            for (size_t c = 0; c < cells[0].size(); ++c) {
                int alive_n = 0;

                if (r > 0 && c > 0 && cells[r-1][c-1] == '*'){
                    alive_n++;
                }
                if (r > 0 && cells[r-1][c] == '*'){
                    alive_n++;
                }
                if (r > 0 && c < cells[0].size()-1 && cells[r-1][c+1] == '*'){
                    alive_n++;
                }
                if (c > 0 && cells[r][c-1] == '*'){
                    alive_n++;
                }
                if (c < cells[0].size()-1 && cells[r][c+1] == '*'){
                    alive_n++;
                }
                
                if (r < cells.size()-1 && c > 0 && cells[r+1][c-1] == '*'){
                    alive_n++;
                }
                if (r < cells.size()-1 && cells[r+1][c] == '*'){
                    alive_n++;
                }
                if (r < cells.size()-1 && c < cells[0].size()-1 && cells[r+1][c+1] == '*'){
                    alive_n++;
                }
                if (cells[r][c] == '*'){
                    if (alive_n == 2 || alive_n == 3){
                        new_gen[r][c] = '*';
                    }
                    else if (alive_n < 2 || alive_n > 3){
                        new_gen[r][c] = '-';
                    }
                }
                else if (cells[r][c] == '-'){
                    if (alive_n == 3){
                        new_gen[r][c] = '*';
                    }
                }
            }
        }
        cells = new_gen;
        for (size_t i = 0; i < new_gen.size(); i++){
            cout << new_gen[i] << endl;
        }
        cout << string(20, '=') <<  endl;
    }
}