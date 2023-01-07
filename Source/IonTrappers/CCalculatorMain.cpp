// Fill out your copyright notice in the Description page of Project Settings.
#include "CCalculatorMain.h"
#include "MatrixCalculator.h"
#include <iostream>
#include <cmath>
#include <complex>
#include <random>
#include <time.h>
#include "Algo/Reverse.h"
using namespace std::complex_literals;
using namespace std;



struct hadamard {
    complex<float> h[2][2] = { {1 / float(sqrt(2)), 1 / float(sqrt(2))}, {1 / float(sqrt(2)), -1 / float(sqrt(2))} };
    bool bHasParameter = false;
    int id = 1;
};

struct physeShift {
    physeShift(float phase_) {
        phase = phase_;
    };
    float phase = 1;
    complex<float> pS[2][2] = { {1, 0}, {0, exp(PI / phase * 1if) } };
    bool bHasParameter = true;
    int id = 2;
};

struct slope {
    complex<float> s[2][2] = { {0}, {1} };
    bool bHasParameter = false;
    int id = 3;
};

struct ionState {
    complex<float> iS[2][2] = { {0,0}, {0,0} };
    bool bHasParameter = false;
    int id = -1;
};

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




//int UCCalculatorMain::CalculateMatrix(float phase, float& posibility)
int UCCalculatorMain::CalculateMatrix(TArray<int>GatesIDs, TArray<int>Parameters)

{

    double pH = 3.141592 / 3;
    const double e = 2.71828;
    int tmp = 3;
    MatrixCalculator h(2, 2, std::vector<std::vector<std::complex<double>>>{ {1 / sqrt(2), 1 / sqrt(2)}, { 1 / sqrt(2), -1 / sqrt(2) } });
    MatrixCalculator p(2, 2, std::vector<std::vector<std::complex<double>>>{ {1, 0}, { 0, exp(pH * 1i) } });
    MatrixCalculator mult(2, 2, std::vector<std::vector<std::complex<double>>>{ {0, 0}, { 0, 0 } });
    MatrixCalculator slope(2, 1, std::vector<std::vector<std::complex<double>>>{ {1}, { 0 } });
    MatrixCalculator slope2(2, 1, std::vector<std::vector<std::complex<double>>>{ {1}, { 0 } });
    MatrixCalculator cp(4, 4, std::vector<std::vector<std::complex<double>>>{ {1, 0, 0, 0}, { 0,1,0,0 }, { 0,0,1,0 }, { 0,0,0,exp(pH * 1i) } });
    MatrixCalculator tp(4, 1);
    MatrixCalculator qnot(2, 2, std::vector<std::vector<std::complex<double>>>{ {0, 1}, { 1, 0 } });

    MatrixCalculator res(2, 1);
    MatrixCalculator res2(2, 1);



    Algo::Reverse(GatesIDs);
    for (int l = 0; l < GatesIDs.Num(); l++) {
        switch (GatesIDs[l]) {
        case 1:
            if (l == 0) res = h * slope;
            else res = h * res;
            break;
        case 2:
            if (l == 0) res = p * slope;
            else res = p * res;
            break;
        default:
            break;
        }
    }


    //slope = h * slope;

    //slope2 = qnot * slope2;

    //tp = slope2.tensorProduct(slope);

    //tp = cp * tp;

    //auto phase = log(tp[3][0] / tp[1][0].real()).imag();
    //auto prob = tp;
    //UE_LOG(LogTemp, Warning, TEXT("%f"), phase);


    const int nrolls = 10000; // number of experiments
    std::default_random_engine generator;
    std::bernoulli_distribution distribution(pow(abs(res[1][0]), 2));
    //std::bernoulli_distribution distribution(pow(abs(tp[1][0]), 2));
    float posibility = 0;

    std::srand(time(NULL));
    generator.seed(rand());

    for (int i2 = 0; i2 < nrolls; ++i2) if (distribution(generator)) ++posibility;
    
	return posibility;
}


