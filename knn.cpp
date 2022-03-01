#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <array>

int main() {

    std::ifstream myfile;
    std::string aux, atr, value, line;
    
    std::vector<std::array<double, 132>> train, test;
    std::vector<int> classes;
    std::array<double, 132> arr;
    int classe;

    myfile.open("digTrain20k.txt");

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            //myfile >> aux;
            std::stringstream st(line);
            getline(st, aux, ' ');
//            std::cout << aux << "\n";
            classe = stoi(aux);

            while (getline(st, aux, ' ')) {
//                std::cout << aux << "\n";

                std::stringstream sstream(aux);
                std::getline(sstream, atr, ':');
                std::getline(sstream, value, ':');
//                std::cout << atr << " " << value << "\n";
                arr[stoi(atr)-1] = stod(value);


            }
            train.insert(train.end(), arr);
            classes.insert(classes.end(), classe);
        }
    }

    for (auto i: train) {
        std::cout << "[";
        for (int j=0; j<132; j++)
            std::cout << i[j] << ", ";
        std::cout << "]\n";
    }
}
