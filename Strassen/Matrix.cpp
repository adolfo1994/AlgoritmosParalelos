#include <iostream>
#include <random>
#include <pthread.h>
#include <algorithm>

using namespace std;

class Matrix
{
public:
	Matrix(int dim_, bool rand_, bool normalize){
		dim = dim_;
		if(normalize){
			int n_dim = 2;
			while(n_dim < dim_)
				n_dim *= 2;
			dim = n_dim;
		}

		mat = new int[dim * dim];
		if(rand_){
			random_device rd;
    		mt19937 gen(rd());
    		uniform_int_distribution<> dis(1, 100);
    		for (int i = 0; i < dim*dim; ++i)
    		{    		
	    		mat[i] = dis(gen);    		
    		}	
		}
	}	
	inline int& operator()(int i, int j){
		return mat[i*dim + j];
	}
	inline int operator()(int i, int j) const{
		return mat[i*dim + j];
	}
	Matrix operator + (Matrix b){
		Matrix c(dim, false, false);
		for (int i = 0; i < dim; ++i)
		{
			for (int j = 0; j < dim; ++j)
			{
				c(i,j) = (*this)(i, j) + b(i, j);
			}
		}
		return c;
	}
	Matrix operator - (Matrix b){
		Matrix c(dim, false, false);
		for (int i = 0; i < dim; ++i)
		{
			for (int j = 0; j < dim; ++j)
			{
				c(i,j) = (*this)(i, j) - b(i, j);
			}
		}
		return c;
	}

	void print(){
		for (int i = 0; i < dim; ++i)
		{
			for (int j = 0; j < dim; ++j)
			{
				cout << (*this)(i, j) << "\t";
			}
			cout<<endl;
		}
	}	

	~Matrix(){		
	}

	int dim;	
	int *mat;	
};

Matrix reg_mult(Matrix a, Matrix b) {
        Matrix c(a.dim, false, false);
        for (int i = 0; i < a.dim; i++){
            for (int j = 0; j < a.dim; j++){
            	c(i,j) = 0;
            	for (int k = 0; k < a.dim; k++)
                    c(i,j) += a(i,k) * b(k,j);       
            }
        }
        return c;
}

Matrix parte(int pi, int pj, Matrix m){
	Matrix p(m.dim/2 , false, true);
	pi = pi * p.dim;
	pj = pj * p.dim;
	for (int i = 0; i < p.dim; ++i)
	{
		for (int j = 0; j < p.dim; ++j)
		{
			p(i,j) = m(i + pi, j + pj);
		}
	}	
	return p;
}

void unir(int pi, int pj, Matrix* m, Matrix p){
	pi = pi * p.dim;
	pj = pj * p.dim;
	for (int i = 0; i < p.dim; ++i)
	{
		for (int j = 0; j < p.dim; ++j)
		{
			(*m)(i + pi, j + pj) = p(i, j);
		}
	}	
}

Matrix strassen(Matrix a, Matrix b){
	if (a.dim < 8){
		return reg_mult(a, b);
	}
	Matrix a11 = parte(0, 0, a);
	Matrix a12 = parte(0, 1, a);
	Matrix a21 = parte(1, 0, a);
	Matrix a22 = parte(1, 1, a);

	Matrix b11 = parte(0, 0, b);
	Matrix b12 = parte(0, 1, b);
	Matrix b21 = parte(1, 0, b);
	Matrix b22 = parte(1, 1, b);

	Matrix m1 = strassen(a11+a22, b11+b22);
	Matrix m2 = strassen(a21+a22, b11);
	Matrix m3 = strassen(a11, b12-b22);
	Matrix m4 = strassen(a22, b21-b11);
	Matrix m5 = strassen(a11+a22, b22);
	Matrix m6 = strassen(a21-a11, b11+b12);
	Matrix m7 = strassen(a12-a22, b21+b22);

	Matrix ans(a.dim, false, true);
	unir(0, 0, &ans, m1+m4 - m5+m7);
	unir(0, 1, &ans, m3+m5);
	unir(1, 0, &ans, m2+m4);
	unir(1, 1, &ans, m1-m2+m3+m6);
	return ans;
}

int main(int argc, char const *argv[])
{	
	Matrix a(512, true, false);
	a.print();
    cout<<endl;
    Matrix b(512, true, false);
    b.print();
    cout<<endl;
    Matrix c = strassen(a, b);
    c.print();
	return 0;
}