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

namespace {
    TArray<float> calculateDistribution(const MatrixCalculator& tensorProduct,const MatrixCalculator& res2, TArray<float>values) {
        TArray<float> returnValues;
            const int nrolls = 10000; // number of experiments
            std::default_random_engine generator;
            std::bernoulli_distribution distribution(pow(abs(tensorProduct[1][0]), 2));
            float posibility = 0;

            std::srand(time(NULL));
            generator.seed(rand());

            for (int i2 = 0; i2 < nrolls; ++i2) if (distribution(generator)) ++posibility;
            posibility = 1 - posibility / 10000;
            UE_LOG(LogTemp, Warning, TEXT("%f"), posibility);

            returnValues.Add(tensorProduct[1][0].real());
            returnValues.Add(res2[0][0].real());
            returnValues.Add(res2[0][0].imag());
            returnValues.Add(res2[1][0].real());
            returnValues.Add(res2[1][0].imag());
            returnValues.Add(values[5]);
            returnValues.Add(res2[2][0].real());
            returnValues.Add(res2[2][0].imag());
            returnValues.Add(res2[3][0].real());
            returnValues.Add(res2[3][0].imag());

            return returnValues;

    }
}



//int UCCalculatorMain::CalculateMatrix(float phase, float& posibility)
TArray<float> UCCalculatorMain::CalculateMatrix(TArray<float>values, int gateID, float phase, TArray<float>parameters)

{
    TArray<float> returnValues;
    double pH = 3.141592 / parameters[0];
    const double e = 2.71828;
    int tmp = 3;
    MatrixCalculator hadamardGate(2, 2, std::vector<std::vector<std::complex<double>>>{ {1 / sqrt(2), 1 / sqrt(2)}, { 1 / sqrt(2), -1 / sqrt(2) } });
    MatrixCalculator phaseGate(2, 2, std::vector<std::vector<std::complex<double>>>{ {1, 0}, { 0, exp(pH * 1i) } });
    //Matrix mult(2, 2, std::vector<std::vector<std::complex<double>>>{ {0, 0}, {0, 0} });
    MatrixCalculator slope(2, 1, std::vector<std::vector<std::complex<double>>>{ {1}, { 0 } });
    MatrixCalculator slope2(2, 1, std::vector<std::vector<std::complex<double>>>{ {1}, { 0 } });
    MatrixCalculator controlledPhaseGate(4, 4, std::vector<std::vector<std::complex<double>>>{ {1, 0, 0, 0}, { 0,1,0,0 }, { 0,0,1,0 }, { 0,0,0,pH } });
    MatrixCalculator tensorProduct(4, 1);
    MatrixCalculator qNotGate(2, 2, std::vector<std::vector<std::complex<double>>>{ {0, 1}, { 1, 0 } });
    MatrixCalculator controlledqNotGate(4, 4, std::vector<std::vector<std::complex<double>>>{ {1, 0, 0, 0}, { 0,1,0,0 }, { 0,0,0,1 }, { 0,0,1,0 } });
    MatrixCalculator res(2, 1);
    MatrixCalculator res2(4, 1);
    MatrixCalculator tmpMatrix(2, 1);
    //double imag = res[0][1].imag();
        res2[0][0].real(values[1]);
        res2[0][0].imag(values[2]);
        res2[1][0].real(values[3]);
        res2[1][0].imag(values[4]);
        res2[2][0].real(values[6]);
        res2[2][0].imag(values[7]);
        res2[3][0].real(values[8]);
        res2[3][0].imag(values[9]);
        //-------------------------
        res[0][0].real(values[1]);
        res[0][0].imag(values[2]);
        res[1][0].real(values[3]);
        res[1][0].imag(values[4]);

        tmpMatrix[0][0].real(values[6]);
        tmpMatrix[0][0].imag(values[7]);
        tmpMatrix[1][0].real(values[8]);
        tmpMatrix[1][0].imag(values[9]);

        bool resUsed = false;

     UE_LOG(LogTemp, Warning, TEXT("%f"), values[0]);
     UE_LOG(LogTemp, Warning, TEXT("liczba bramek: %d"), values.Num());
     //UE_LOG(LogTemp, Warning, TEXT("%f"), 1-oneProbability[0]);
    //Algo::Reverse(GatesIDs);
        switch (gateID) {
        case 1:
                res = hadamardGate * res; 
                resUsed = true;
                UE_LOG(LogTemp, Warning, TEXT("Hadamard"));
            break;
        case 2:
                res = phaseGate * res;
                resUsed = true;
                UE_LOG(LogTemp, Warning, TEXT("Fazy"));
            break;
        case 3:
                tensorProduct = tmpMatrix.tensorProduct(res);
                tensorProduct = controlledqNotGate * tensorProduct;
                UE_LOG(LogTemp, Warning, TEXT("CNOT"));
                return calculateDistribution(tensorProduct, res2, values);
            break;
        case 4:
                res2 = qNotGate * res2;
                UE_LOG(LogTemp, Warning, TEXT("NOT"));
            break;        
        default:
            break;
        }
        UE_LOG(LogTemp, Warning, TEXT("00: %f"), res[0][0].real());
        UE_LOG(LogTemp, Warning, TEXT("01: %f"), res[0][1].imag());
        UE_LOG(LogTemp, Warning, TEXT("11: %f"), res[1][1].real());
        UE_LOG(LogTemp, Warning, TEXT("10: %f"), res[1][0].imag());

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
    posibility = 1 - posibility/10000;
    UE_LOG(LogTemp, Warning, TEXT("%f"), posibility);

    if (resUsed) {
        res2[0][0].real(res[0][0].real());
        res2[0][0].imag(res[0][0].imag());
        res2[1][0].real(res[1][0].real());
        res2[1][0].imag(res[1][0].imag());
    }
    returnValues.Add(posibility);
    returnValues.Add(res2[0][0].real());
    returnValues.Add(res2[0][0].imag()); 
    returnValues.Add(res2[1][0].real());
    returnValues.Add(res2[1][0].imag());
    returnValues.Add(values[5]);
    returnValues.Add(res2[2][0].real());
    returnValues.Add(res2[2][0].imag());
    returnValues.Add(res2[3][0].real());
    returnValues.Add(res2[3][0].imag());

	return returnValues;
}


//UE_LOG(LogTemp, Warning, TEXT("Real: %f Img: %f"), res[0][0].real(), res[0][0].imag());
//UE_LOG(LogTemp, Warning, TEXT("Real: %f Img: %f"), res[1][0].real(), res[1][0].imag());
//UE_LOG(LogTemp, Warning, TEXT("Real: %f Img: %f"), res[1][1].real(), res[1][1].imag());
//UE_LOG(LogTemp, Warning, TEXT("Real: %f Img: %f"), res[0][1].real(), res[0][1].imag());
////res = phaseGate * res;
//res[0][0].real(0.707107);
//res[0][0].imag(0);
//res[1][0].real(0.5);
//res[1][0].imag(0.5);
//UE_LOG(LogTemp, Warning, TEXT("Real: %f Img: %f"), res[0][0].real(), res[0][0].imag());
//UE_LOG(LogTemp, Warning, TEXT("Real: %f Img: %f"), res[1][0].real(), res[1][0].imag());
//UE_LOG(LogTemp, Warning, TEXT("Real: %f Img: %f"), res[1][1].real(), res[1][1].imag());
//UE_LOG(LogTemp, Warning, TEXT("Real: %f Img: %f"), res[0][1].real(), res[0][1].imag());
//res = hadamardGate * res;
//UE_LOG(LogTemp, Warning, TEXT("Real: %f Img: %f"), res[0][0].real(), res[0][0].imag());
//UE_LOG(LogTemp, Warning, TEXT("Real: %f Img: %f"), res[1][0].real(), res[1][0].imag());
//UE_LOG(LogTemp, Warning, TEXT("Real: %f Img: %f"), res[1][1].real(), res[1][1].imag());
//UE_LOG(LogTemp, Warning, TEXT("Real: %f Img: %f"), res[0][1].real(), res[0][1].imag());
//UE_LOG(LogTemp, Warning, TEXT("Hadamard"));