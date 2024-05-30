// Fill out your copyright notice in the Description page of Project Settings.


#include "Spline.h"

#include "Components/SplineComponent.h"


ASpline::ASpline()
{
	mSpline = CreateDefaultSubobject<USplineComponent>("SplineComp");
	RootComponent = mSpline;
}
