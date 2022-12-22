// Fill out your copyright notice in the Description page of Project Settings.

#include <iostream>
#include <cmath>
#include <complex>
#include <random>
#include <time.h>
using namespace std::complex_literals;
using namespace std;
#include "CCalculatorMain.h"

// Sets default values for this component's properties
UCCalculatorMain::UCCalculatorMain()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCCalculatorMain::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCCalculatorMain::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

complex<float>** UCCalculatorMain::multiplication(int i, int j, int k, int r1, int r2, int c1, int c2, complex<float> mult[2][2], complex<float> first[2][2], complex<float> second[2][2]) {

    complex<float>** tab = new complex<float>*[2];

    printf("multiply of the matrix=\n");
    for (i = 0; i < 2; i++)
    {
        tab[i] = new complex<float>[2];
    }
    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c1; j++)
        {
            tab[i][j] = 0;
            for (k = 0; k < c1; k++)
            {
                tab[i][j] += first[i][k] * second[k][j];
            }
        }
    }
    //for printing result    
    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c1; j++)
        {
            cout << tab[i][j] << " ";
        }
        printf("\n");
    }
    return tab;


}


int UCCalculatorMain::CalculateMatrix(float phase, float& posibility)
{
    float pi = 3.141593;
    complex<float> h[2][2] = { {1 / sqrt(2), 1 / sqrt(2)}, {1 / sqrt(2), -1 / sqrt(2)} };
    complex<float> p[2][2] = { {1, 0}, {0, exp(pi/phase * 1if) } };
    complex<float> mult[2][2] = { {0, 0}, {0, 0} };
    complex<float> slope[2][2] = { {0}, {1} };
    complex<float>** res;
    complex<float>** res2;
    int r1 = 2,
        c1 = 2,
        r2 = 2,
        c2 = 2,
        i = 0,
        j = 0,
        k = 0;

    res = multiplication(i, j, k, r1, r2, c1, c2, mult, h, slope);
    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c1; j++)
        {
            mult[i][j] = res[i][j];
        }
    }
    res2 = multiplication(i, j, k, r1, r2, c1, c2, mult, p, mult);

    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c1; j++)
        {
            mult[i][j] = res2[i][j];
        }

    }

    complex<float>** res3 = multiplication(i, j, k, r1, r2, c1, c2, mult, h, mult);
    const int nrolls = 10000; // number of experiments
    std::default_random_engine generator;
    std::bernoulli_distribution distribution(res3[1][0].real());
    posibility = 0;

    srand(time(NULL));
    generator.seed(rand());

    for (int i2 = 0; i2 < nrolls; ++i2) if (distribution(generator)) ++posibility;

	return 0;
}


