#include <iostream>
#include <random>
#include <pthread.h>
#include <algorithm>
#include "utils.cpp"

using namespace std;

class Matrix
{
public:
	Matrix(int _f, int _c){
		rows = _f;
		cols = _c;
		mat = new int * [rows];
		for(int i=0; i < rows; i++){
			mat[i] = new int[cols];
		}
		random_device rd;
    	mt19937 gen(rd());
    	uniform_int_distribution<> dis(1, 10001);
    	for (int i = 0; i < rows; ++i)
    	{
    		for (int j = 0; j < cols; ++j)
    		{
    			mat[i][j] = dis(gen);
    		}
    	}
	}
	Matrix (const Matrix &other){
		rows = other.rows;
		cols = other.cols;
		mat = new int * [rows];
		for(int i=0; i < rows; i++){
			mat[i] = new int[cols];
		}
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				mat[i][j] = other.mat[i][j];		
			}
		}
	}
	void print(){
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				cout << mat[i][j] << "\t";
			}
			cout<<endl;
		}
	}
	void normalize(int final){
		int ** n_mat = new int* [final];
		for (int i = 0; i < final; ++i)
		{
			n_mat[i] = new int [final];
		}
		for (int i = 0; i < final; ++i)
		{
			for (int j = 0; j < final; ++j)
			{
				if(i < rows && j < cols){
					n_mat[i][j] = mat[i][j];
				}else{
					n_mat[i][j] = 0;
				}
			}
		}
		mat = n_mat;
		rows = final;
		cols = final;

	}

	~Matrix(){
		for (int i = 0; i < rows; ++i)
		{
			delete mat[i];
		}
		delete mat;
	}

	int rows;
	int cols;
	int ** mat;	
};

Matrix strassen(Matrix a, Matrix b){
	int rows = max(a.rows, b.rows);
	int cols = max(a.cols, b.cols);
	int max_cr = max(rows, cols);
	if(isPowerOfTwo(max_cr)){
		a.normalize(max_cr);
		b.normalize(max_cr);
	}	
	else{
		while(!isPowerOfTwo(max_cr)){
			max_cr++;
		}
		a.normalize(max_cr);
		b.normalize(max_cr);
	}
	a.print();
	cout<<endl;
	b.print();
	cout<< "no pasa nada"<<endl;
	return a;
}

int main(int argc, char const *argv[])
{	
	Matrix * a = new Matrix(14,14);
	Matrix * b = new Matrix(14,12);
	Matrix c = strassen(*a, *b);
	return 0;
}