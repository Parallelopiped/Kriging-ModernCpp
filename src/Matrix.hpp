//
// Created by NaturalVStudio on 2022/6/26.
//

#ifndef KRIGING_MODERNCPP_MATRIX_HPP
#define KRIGING_MODERNCPP_MATRIX_HPP

#include <cmath>
#include <cstdlib>
#include <cassert>
#include <stdexcept>
#include <iomanip>
#include <vector>

#include <iostream>

class Matrix{
private:
    int row, col;
    int *r;
    double *array;

    static constexpr double EPSILON = 0.00001;

public:
    Matrix * L;
    Matrix * U;
    Matrix * I;

    inline Matrix(int Row, int Col);
    explicit inline Matrix(Matrix *m);
    inline Matrix(int Size, bool One, int a);
    inline ~Matrix();

    inline double get(int _row, int _col);
    inline double& operator()(int _row, int _col);
    // Assignation Operator
    inline double& set(int _row, int _col, double value);

    inline void swap(int r1, int r2);
    inline void clearPermutation();
    inline void setRow(int r1, int r2, double s);
    inline void setRow(int _r, double s);
    inline void gaussInversion();
    inline void invert();
    inline Matrix multiply(Matrix m);

    inline void print();
};


Matrix::Matrix(int Row,  int Col){
    this->row = Row;
    this->col = Col;
    array = new double [row*col];

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; ++j){
            array[i*col+j] = 0;
        }
    }

    r = new int[row];
    for(int i = 0; i < row; ++i){
        r[i] = i;
    }
    L = nullptr;
    U = nullptr;
    I = nullptr;
}

Matrix::Matrix(Matrix * m){
    //cout << "COPY CONSTRUCTOR" << endl;
    row = m->row;
    col = m->col;
    array = new double [row*col];
    for(int i = 0; i < row*col; ++i){
        array[i] = m->array[i];
    }

    r = new int[row];
    for(int i = 0; i < row; ++i){
        r[i] = m->r[i];
    }
    if(m->L != nullptr) L = new Matrix(m->L); else L = nullptr;
    if(m->U != nullptr) U = new Matrix(m->U); else U = nullptr;
    if(m->I != nullptr) I = new Matrix(m->I); else I = nullptr;
}

Matrix::Matrix(int Size, bool One, int a) {
    this->row = Size;
    this->col = Size;

    array = new double[row * col];
    for(  int i = 0; i < row; i++){
        for(int j = 0; j < col; ++j){
            array[i*row+j] = 0;
        }
        if(One)
            array[i*row + i] = 1;
    }

    r = new int[row];
    for(int i = 0; i < row; ++i){
        r[i] = i;
    }
    L = nullptr;
    U = nullptr;
    I = nullptr;
}

Matrix::~Matrix(){
    delete(L);
    delete(U);
    delete(I);
}

double Matrix::get(const int _row, const int _col){
    assert(_row >= 0 && _row < this->row && _col >= 0 && _col < this->col);
    return array[r[_row] * this->col + _col];
}

double & Matrix::set(const int _row, const int _col, double value){
    assert(_row >= 0 && _row < this->row && _col >= 0 && _col < this->col);
    double rnd = std::round(value);
    double res = value-rnd;
    if(res < EPSILON && res > -EPSILON){
        value = rnd;
    }
    array[r[_row] * this->col + _col] = value;
    return array[r[_row] * this->col + _col];
}

double & Matrix::operator () (int _row, int _col){
    assert(_row >= 0 && _row < this->row && _col >= 0 && _col < this->col);
    return array[r[_row] * this->col + _col];
}

void Matrix::swap(int r1, int r2){
    size_t t = r[r1];
    r[r1] = r[r2];
    r[r2] = t;
}

void Matrix::clearPermutation(){
    for(int i = 0; i < row; ++i)
    {
        this->r[i] = i;
    }
}

void Matrix::setRow(int r1, int r2, double s){
    //cout << "O: [" << r1 << "]" << " = [" << r1 << "] - [" << r2 << "] * " << s << endl;
    for(int c = 0; c < col; ++c){
        set(r1,c,get(r1,c) - (get(r2,c) * s));
        I->set(r1,c,I->get(r1,c) - (I->get(r2,c) * s));
    }
}

void Matrix::setRow(int _r, double s) {
    for(int c = 0; c < col; ++c){
        set(_r, c, get(_r, c) * s);
        I->set(_r, c, I->get(_r, c) * s);
    }
}

void Matrix::gaussInversion() {
    I = new Matrix(row,true, 233);

    int n = row;
    double q = double(n)/100.0;
    double p = q;

    //Pivoting
    for(int i = 1; i < n; ++i){
        if(get(i,i) == 0){
            swap(i-1,i);
            I->swap(i-1,i);
        }
    }

    for(int i = 0; i < row; ++i){
        if(q != 0 && i > p){
            p += q;
            int prog = p/q;
            //std::cout << "\r" << (prog - 1) << "% completed: ";
            //std::cout.flush();
        }

        try{
            setRow(i,1.0/get(i,i));
        }
        catch(std::runtime_error& e){
            std::cout << "AN ERROR HAS OCURRED: " << e.what();
            exit(0);
        }
        catch(int e){
            std::cout << "AN UNIDENTIFIED ERROR OCURRED: " << e << endl;
            exit(0);
        }

        for(int _r = 0; _r < row; ++_r){
            if(_r != i){
                setRow(_r, i, get(_r, i));
            }
        }
    }

    //std::cout << endl;
}

void Matrix::invert() {
    gaussInversion();
    I->clearPermutation();
}

Matrix Matrix::multiply(Matrix m) {
    assert(col == m.row);

    Matrix K = Matrix(row, m.col);
    for(int i = 0; i < row; ++i){
        for(int j = 0; j < m.col; ++j){
            double v = 0;
            for(int k = 0; k < col; ++k){
                v += get(i, k) * m.get(k, j);
            }
            K.set(i, j, v);
        }
    }
    return K;
}

void Matrix::print()
{
    for(int i = 0; i < this->row; i++)
    {
        std::cout << "[" << r[i] << "] ";
        for(  int j = 0; j < this->col; j++)
        {
            if(get(i,j) >= 0)
                std::cout << " ";
            if(get(i,j) == -0.0)
                set(i,j,0);
            std::cout << get(i,j) << " ";
        }
        std::cout << std::endl;
    }
}

#endif //KRIGING_MODERNCPP_MATRIX_HPP
