#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <array>



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
    int classe, k, n, tam_treinamento, sum, max_class_neighbor, predicted_class;
    int **confusao, *min_dist, *min_dist_pos, *class_vector;
    bool done;

    //lendo treinamento
    tam_treinamento = 0;

    myfile.open(argv[1]);

    if (myfile.is_open()) {
        while (getline(myfile, line)) {

            std::stringstream st(line);
            getline(st, aux, ' ');
            classe = stoi(aux);

            arr.fill(0);

            while (getline(st, aux, ' ')) {

                std::stringstream sstream(aux);
                std::getline(sstream, atr, ':');
                std::getline(sstream, value, ':');
                arr[stoi(atr)-1] = stod(value);


            }
            train.insert(train.end(), arr);
            classes.insert(classes.end(), classe);
            tam_treinamento++;
        }
    }

    n = *std::max_element(classes.begin(), classes.end()) + 1;
    k = stoi(argv[3]);
    confusao = malloc(n*sizeof(int *));
    for (int i=0; i<n; i++) {

        confusao[i] = malloc(n*sizeof(int));
        confusao[i].fill(0);
    }
    min_dist = malloc(k*sizeof(int));
    min_dist_pos = malloc(k*sizeof(int));
    class_vector = malloc(k*sizeof(int));
    //lendo teste e calculando classe
    myfile.open(argv[2]);

    if (myfile.is_open()) {
        while (getline(myfile, line)) {

            std::stringstream st(line);
            getline(st, aux, ' ');
            classe = stoi(aux);

            arr.fill(0);

            while (getline(st, aux, ' ')) {

                std::stringstream sstream(aux);
                std::getline(sstream, atr, ':');
                std::getline(sstream, value, ':');
                arr[stoi(atr)-1] = stod(value);


            }
            //arr contem uma entrada da base de teste
            sum = 0;
            min_dist_pos.fill(0);
            max_class_neighbor = 0;
            for (int i=0; i<tam_treinamento; i++) {
                for (int j=0; j<132; j++)
                    sum += (train.at(i)[j] - arr[j])*(train.at(i)[j] - arr[j]);
                if (i<k) {
                    min_dist = sum;
                    min_dist_pos = i;
                }
                else {
                    int j=0;
                    done = false
                    while ((j<k) && !(done)) {
                    
                        if (sum < min_dist[j]) {
                            min_dist[j] = sum;
                            min_dis_pos[j] = i;
                            done = true;
                        }
                        j++;
                    }
                }
            }
            class_vector.fill(0);
            for (int i=0; i<k; i++)
               class_vector[classes.at(min_dis_pos[i])]++;
            for (int i=0; i<k; i++) {
                if (class_vector[i] > max_class_neighbor) {
                    max_class_neighbor = class_vector[i];
                    predicted_class = i;
                }
            }
            //confusao[real][predita]
            confusao[classe][predicted_class]++;
        }
    }

    for (int i=0; i<n; i++) {
        std::cout << "[";
        for (int j=0; j<n; j++)
            std::cout << confusao[i][j] << ", ";
        std::cout << "]\n";
    }

}
