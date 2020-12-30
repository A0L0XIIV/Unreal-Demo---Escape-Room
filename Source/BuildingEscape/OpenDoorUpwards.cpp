// Baran Kaya 2020

#include "OpenDoorUpwards.h"

// Sets default values for this component's properties
UOpenDoorUpwards::UOpenDoorUpwards()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoorUpwards::BeginPlay()
{
	Super::BeginPlay();

	initialZPosition = GetOwner()->GetActorLocation().Z;
	currentZPosition = initialZPosition;
	OpenZPosition += initialZPosition;

	// Check pressure plate
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s object's Pressure Plate is Not Defined! (NULL)"), *GetOwner()->GetName());
	}
	// Find Audio Component
	FindAudioComponent();
}

void UOpenDoorUpwards::OpenDoor(float DeltaTime) {
	// Calculate current yaw with linear int.
	currentZPosition = FMath::Lerp(currentZPosition, OpenZPosition, DeltaTime * DoorOpenSpeed);
	// Get door's location
	FVector DoorOpen = GetOwner()->GetActorLocation();
	// Set new z position for the door
	DoorOpen.Z = currentZPosition;
	GetOwner()->SetActorLocation(DoorOpen);
	// Check Audio Component
	if (!AudioComponent) return;
	CloseDoorSound = false;
	// Sound play only once check
	if (!OpenDoorSound) {
		AudioComponent->Play();
		OpenDoorSound = true;
	}
}

void UOpenDoorUpwards::CloseDoor(float DeltaTime) {
	// Calculate current yaw with linear int.
	currentZPosition = FMath::Lerp(currentZPosition, initialZPosition, DeltaTime * DoorCloseSpeed);
	// Get door's location
	FVector DoorClose = GetOwner()->GetActorLocation();
	// Set new z position for the door
	DoorClose.Z = currentZPosition;
	GetOwner()->SetActorLocation(DoorClose);
	// Check Audio Component
	if (!AudioComponent) return;
	OpenDoorSound = false;
	// Sound play only once check
	if (!CloseDoorSound) {
		AudioComponent->Play();
		CloseDoorSound = true;
	}
}