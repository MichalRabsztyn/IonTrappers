// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <cmath>
#include <complex>
#include <random>
#include <time.h>
#include "CCalculatorMain.generated.h"
using namespace std::complex_literals;
using namespace std;





UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IONTRAPPERS_API UCCalculatorMain : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCCalculatorMain();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	TArray<float> CalculateMatrix(TArray<float>oneProbability, int gateID, float phase, TArray<float>parameters);
	complex<float>** multiplication(int r1, int r2, int c1, int c2, complex<float> first[2][2], complex<float> second[2][2]);
};
