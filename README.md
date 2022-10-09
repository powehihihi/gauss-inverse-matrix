# Inversing matrix with Gaussian elimination.

## Introduction

[Gaussian implementation](https://en.wikipedia.org/wiki/Gaussian_elimination) is an algorithm for solving systems of linear equations.
For square matrix it consists of two steps: 
* make an upper triangular matrix
* make an Identity matrix

Each step is realised by elementery row operations.
To inverse the invertible matrix you should repeat every single operation for an identity matrix. [Wiki](https://en.wikipedia.org/wiki/Invertible_matrix#Gaussian_elimination).

## Details

How can we know if algorithm gave us a correct answer? Let's assume $A$ is our matrix. $B$ is matrix we got from algorithm. Let's calculate two values:


<img src="https://latex.codecogs.com/svg.image?res1=||AB-E||_1" />
<img src="https://latex.codecogs.com/svg.image?res1=||BA-E||_1" />
where <img src="https://latex.codecogs.com/svg.image?||C||_1=\max_{1\leqslant&space;j&space;\leqslant&space;n}\sum_{i=1}^{n}|y_{ij}|"

If B is an inversed matrix res1=res2=0. However, due to inaccuracy of floating-point arithmetic, we will assume that $B$ is inversed $A$ if res1 or res2 is less than 1 (random number to be honest).

## Simple Implementation

### Idea
Let's not swap rows or columns - so the leading elements will be on diagonal. Code for this implementation is in GaussSimple.c.
### Problems
This algorithm won't work for some matrice. For example:

<img src="https://latex.codecogs.com/svg.image?\begin{pmatrix}0&space;&&space;1\\1&space;&&space;0\end{pmatrix}" /> 


In this particular case first leading element is 0, so we have to divide by zero. To avoid undefined behaviour, if the modulus of a leading element is too small let's quit the function and say that method is not applicable.

## New implementation

### Idea
Now let's swap rows and columns according to the following rule: the leading element should be a maximum (by modulus) in the submatrix. Again if its modulus is too small we say that method is not applicable. This implementation is realised in Gauss.c.

### Problems
If the simple implementation is applicable, it gives better results in time aand accuracy than new implementation.

### Is new implementation always applicable?
No. Let's try to inverse [Hilbert Matrix](https://en.wikipedia.org/wiki/Hilbert_matrix). 
Method gives completely inaccurate answer for matrix of size 13 and is not apliccable for size 14.
The first implementation is inaccurate if size is more than 12 and is not applicable if size is more than 17.

## Which implementation is better?

It depends on the matrix. Simple solution is faster without a doubt. Also usually it's more accurate. However, it's easy to completely break it by putting zero in the top left corner.

## Tests and code structure

Both implementations are provided with main function and a few other functions - to print matrix, initialize it with formula or read it from file.
Run both executables this way: 
**"./a.out n p k"** or **"./a.out n p 0 filename"**
where n>0 - size of matrix (so there are n×n elements), p - size of printed matrix (p×p elements will be printed), 0<k<5 - number of formula to initialize matrix, filename - name of the file with elements of matrix.

Formulae:
* k=1. $a_{ij} = n - max(i, j)+1$
* k=2. $a_{ij} = max(i, j)$
* k=3. $a_{ij} = |i-j|$
* k=4. $a_{ij} = \frac{1}{i+j-1}$ (Hilbert Matrix)

