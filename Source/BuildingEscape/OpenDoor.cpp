// Baran Kaya 2020

#include "OpenDoor.h" 	
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	initialYaw = GetOwner()->GetActorRotation().Yaw;
	currentYaw = initialYaw;
	OpenAngle += initialYaw;

	// Check pressure plate
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s object's Pressure Plate is Not Defined! (NULL)"), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Open door if the mass is greater or equal to MassToOpenDoor
	if (PressurePlate && TotalMassOfActors() >= MassToOpenDoor) {
		// Call Open Door Function
		OpenDoor(DeltaTime);
		// Get opened time
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else if (PressurePlate && TotalMassOfActors() < MassToOpenDoor) {
		// Check time
		if(DoorLastOpened + DoorCloseDelay <= GetWorld()->GetTimeSeconds())
			// Call Close Door Function
			CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime) {
	// Calculate current yaw with linear int.
	currentYaw = FMath::Lerp(currentYaw, OpenAngle, DeltaTime * DoorOpenSpeed);
	// Get door's rotation
	FRotator DoorOpen = GetOwner()->GetActorRotation();
	// Set new yaw for the door
	DoorOpen.Yaw = currentYaw;
	GetOwner()->SetActorRotation(DoorOpen);
}

void UOpenDoor::CloseDoor(float DeltaTime) {
	// Calculate current yaw with linear int.
	currentYaw = FMath::Lerp(currentYaw, initialYaw, DeltaTime * DoorCloseSpeed);
	// Get door's rotation
	FRotator DoorClose = GetOwner()->GetActorRotation();
	// Set new yaw for the door
	DoorClose.Yaw = currentYaw;
	GetOwner()->SetActorRotation(DoorClose);
}

float UOpenDoor::TotalMassOfActors() const {
	float TotalMass = 0.f;

	// Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Add up their masses
	for (AActor* actor : OverlappingActors) {
		TotalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	
	return TotalMass;
}