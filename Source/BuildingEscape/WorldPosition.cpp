// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	// LOG object name
	FString objName = GetOwner()->GetName();

	FVector objLocation = GetOwner()->GetActorLocation();
	FString objLocationStr = objLocation.ToString();
	FString objLocationCStr = objLocation.ToCompactString();

	UE_LOG(LogTemp, Warning, TEXT("Name: %s, Location: %s, Compact Location: %s"), *objName, *objLocationStr, *objLocationCStr);

}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

