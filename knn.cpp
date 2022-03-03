#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
#include <algorithm>


int main(int argc, char **argv) {

    if (argc < 4) {
        std::cout << "Por favor informe <base de treinamento> <base de teste> <valor de k>\n";
        return 0;
    }

    std::ifstream myfile;
    std::string aux, atr, value, line;
    
    std::vector<std::array<double, 132>> train, test;
    std::vector<int> classes;
    std::array<double, 132> arr;
    int classe, k, n, tam_treinamento, max_class_neighbor, predicted_class,
    tam_test;
    std::vector<int> min_dist_pos, class_vector;
    std::vector<std::vector<int>> confusao;
    bool done;
    double sum, accuracy;
    std::vector<double> min_dist;

    //lendo treinamento
    tam_treinamento = 0;
    tam_test = 0;

    myfile.open(argv[1]);

    if (myfile.is_open()) {
        while (getline(myfile, line)) {

            std::stringstream st(line);
            getline(st, aux, ' ');
            classe = stoi(aux);

            arr.fill(0);

            while (getline(st, aux, ' ')) {

                std::stringstream string_stream(aux);
                std::getline(string_stream, atr, ':');
                std::getline(string_stream, value, ':');
                arr[stoi(atr)-1] = stod(value);

            }
            train.insert(train.end(), arr);
            classes.insert(classes.end(), classe);
            tam_treinamento++;
        }
    }
    myfile.close();

    n = *max_element(classes.begin(), classes.end()) + 1;
    k = stoi(std::string(argv[3]));
    confusao.resize(n);
    for (int i=0; i<n; i++) {

        confusao.at(i).resize(n);
        std::fill(confusao.at(i).begin(), confusao.at(i).end(), 0);
    }
    min_dist.resize(k);
    min_dist_pos.resize(k);
    class_vector.resize(n);
    //lendo teste e calculando classe
    myfile.open(argv[2]);

    if (myfile.is_open()) {
        while (getline(myfile, line)) {

            std::stringstream st(line);
            getline(st, aux, ' ');
            classe = stoi(aux);

            arr.fill(0);

            while (getline(st, aux, ' ')) {

                std::stringstream string_stream(aux);
                std::getline(string_stream, atr, ':');
                std::getline(string_stream, value, ':');
                arr[stoi(atr)-1] = stod(value);


            }
            tam_test++;
            //arr contem uma entrada da base de teste
            //std::cout << tam_test << "\n";
            fill(min_dist_pos.begin(), min_dist_pos.end(), 0);
            max_class_neighbor = 0;
            for (int i=0; i<k; i++) {
                sum = 0;
                for (int j=0; j<132; j++) {
                    sum += (train.at(i)[j] - arr[j])*(train.at(i)[j] - arr[j]);
                }
                min_dist.at(i) = sum;
                min_dist_pos.at(i) = i;
            }
            for (int i=k; i<tam_treinamento; i++) {
                sum = 0;
                for (int j=0; j<132; j++) {
                    sum += (train.at(i)[j] - arr[j])*(train.at(i)[j] - arr[j]);
                }

                int j=0;
                done = false;
                while ((j<k) && !(done)) {
                
                    if (sum < min_dist.at(j)) {
//                        std::cout << "on if " << j << "\n";
                        min_dist.at(j) = sum;
                        min_dist_pos.at(j) = i;
                        done = true;
                    }
                    j++;
                }
            }
            fill(class_vector.begin(), class_vector.end(), 0);
/*
            for (auto i: min_dist_pos)
                std::cout << i << ", ";
            std::cout << "\n";
*/
            for (int i=0; i<k; i++)
               class_vector.at(classes.at(min_dist_pos.at(i)))++;
//            std::cout << "a\n";
            for (int i=0; i<n; i++) {
                if (class_vector.at(i) > max_class_neighbor) {
                    max_class_neighbor = class_vector.at(i);
                    predicted_class = i;
                }
            }
//            std::cout << "b\n";
            //confusao[real][predita]
            confusao.at(classe).at(predicted_class)++;
//            std::cout << "classe: " << classe << " classe prevista: " << predicted_class << "\n";
        }
    }
    myfile.close();
    for (int i=0; i<n; i++) {
        std::cout << "[";
        for (int j=0; j<n; j++)
            std::cout << confusao.at(i).at(j) << ", ";
        std::cout << "]\n";
    }
    accuracy = 0;
    for (int i=0; i<n; i++)
        accuracy += confusao.at(i).at(i);
    //std::cout << "size: " << (tam_test) << "\n";
    std::cout << "accuracy: " << (accuracy/tam_test) << "\n";
}
