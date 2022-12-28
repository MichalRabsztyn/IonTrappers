// Fill out your copyright notice in the Description page of Project Settings.

#include <iostream>
#include <cmath>
#include <complex>
#include <random>
#include <time.h>
#include "Algo/Reverse.h"
using namespace std::complex_literals;
using namespace std;
#include "CCalculatorMain.h"


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

complex<float>** UCCalculatorMain::multiplication(int r1, int r2, int c1, int c2, complex<float> first[2][2], complex<float> second[2][2]) {

    complex<float>** tab = new complex<float>*[2];
    for (int i = 0; i < 2; i++)
    {
        tab[i] = new complex<float>[2];
    }
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c1; j++)
        {
            tab[i][j] = 0;
            for (int k = 0; k < c1; k++)
            {
                tab[i][j] += first[i][k] * second[k][j];
            }
        }
    }
    return tab;
}


//int UCCalculatorMain::CalculateMatrix(float phase, float& posibility)
int UCCalculatorMain::CalculateMatrix(TArray<int>GatesIDs, TArray<int>Parameters)

{
    struct slope s;
    struct hadamard h;
    
    struct ionState iS;
    //complex<float> h[2][2] = { {1 / sqrt(2), 1 / sqrt(2)}, {1 / sqrt(2), -1 / sqrt(2)} };
    //complex<float> p[2][2] = { {1, 0}, {0, exp(pi/phase * 1if) } };
    complex<float> mult[2][2] = { {0}, {1} };
    //complex<float> slope[2][2] = { {0}, {1} };
   
    complex<float>** res;
    //complex<float>** res2;
    int r1 = 2,
        c1 = 2,
        r2 = 2,
        c2 = 2,
        i = 0,
        j = 0,
        k = 0;


    Algo::Reverse(GatesIDs);
    for (int l = 0; l < GatesIDs.Num(); l++) {
        /*switch (GatesIDs[l]) {
        case 1:
            res = multiplication(r1, r2, c1, c2, mult, h.h);
            break;
        case 2:
            struct physeShift pS(Parameters[l]);
            pS.phase = Parameters[l];
            pS.pS[2][2] = second[2][2];
            UE_LOG(LogTemp, Warning, TEXT("%f"),pS.phase);
            res = multiplication(r1, r2, c1, c2, mult, pS.pS);
            break;

        default:
            struct physeShift pS(1);
            res = {};
            break;
        }*/

        if (GatesIDs[l] == 1) {
            res = multiplication(r1, r2, c1, c2, mult, h.h);
        }
        else if (GatesIDs[l] == 2) {
            complex<float> second[2][2] = { {1, 0}, {0, exp(PI / Parameters[l] * 1if) } };
            //struct physeShift pS(Parameters[l]);
            //pS.phase = Parameters[l];
            //pS.pS[2][2] = second[2][2];
            //UE_LOG(LogTemp, Warning, TEXT("%f"), pS.phase);
            res = multiplication(r1, r2, c1, c2, mult, second);

        }
        else res = {};
        
        for (i = 0; i < r1; i++)
        {
            for (j = 0; j < c1; j++)
            {
                mult[i][j] = res[i][j];
            }
        }
    }

    //res = multiplication(r1, r2, c1, c2, h, Slope);
    //for (i = 0; i < r1; i++)
    //{
    //    for (j = 0; j < c1; j++)
    //    {
    //        //mult[i][j] = res[i][j];
    //    }
    //}
    //res2 = multiplication(r1, r2, c1, c2, p, mult);

    //for (i = 0; i < r1; i++)
    //{
    //    for (j = 0; j < c1; j++)
    //    {
    //       // mult[i][j] = res2[i][j];
    //    }

    //}

    //complex<float>** res3 = multiplication(r1, r2, c1, c2, mult, h.h, mult);
    const int nrolls = 10000; // number of experiments
    std::default_random_engine generator;
    std::bernoulli_distribution distribution(mult[1][0].real());
    float posibility = 0;

    std::srand(time(NULL));
    generator.seed(rand());

    for (int i2 = 0; i2 < nrolls; ++i2) if (distribution(generator)) ++posibility;

	return posibility;
}


