#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> 
#include <ctime> 
#include <sstream>
#include <chrono>
using namespace std;


vector<vector<int>> create_random_of_matrix(const int size) {
    vector<vector<int>> matrix(size, vector<int>(size));
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            matrix[i][j] = rand() % 100;
    return matrix;
}


void write_matrix(const vector<vector<int>>& matrix, const string& filename) {
    ofstream output_file(filename);
    for (const auto& row : matrix) {
        for (int value : row)
            output_file << value << " ";
        output_file << endl;
    }
    output_file.close();
}


vector<vector<int>> read_matrix(const string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<int>> res;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<int> temp;
            std::stringstream ss(line);
            int num;
            while (ss >> num) {
                temp.push_back(num);
            }
            res.push_back(temp);
        }
        file.close();
    }
    return res;
}


vector<vector<int>> multiply_matrix(const vector<vector<int>> matrix1, const vector<vector<int>> matrix2, const int size) {
    vector<vector<int>> result(size, vector<int>(size, 0));
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            for (int k = 0; k < size; ++k)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}


int main()
{
    vector<int> sizes = { 10, 100, 200, 300, 500, 1000 };
    ofstream output_file("res_time.txt");
    for (int size : sizes)
    {
        auto time = chrono::milliseconds(0);
        stringstream ss1;
        stringstream ss2;
        stringstream ss3;
        ss1 << "matrix1." << size << ".txt";
        string filename1 = ss1.str();
        ss2 << "matrix2." << size << ".txt";
        string filename2 = ss2.str();
        vector<vector<int>> mat1 = read_matrix(filename1);
        vector<vector<int>> mat2 = read_matrix(filename2);
        vector<vector<int>> res;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 6; ++i)
        {
            res = multiply_matrix(mat1, mat2, size);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        ss3 << "res." << size << ".txt";
        write_matrix(res, ss3.str());
        output_file <<size<< " - "<< duration.count() / 6 << endl;
    }
    output_file.close();
}