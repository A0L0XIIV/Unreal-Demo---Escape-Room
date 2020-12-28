// Baran Kaya 2020

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

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
	targetYaw += initialYaw;

	// Check pressure plate
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s object's Pressure Plate is Not Defined! (NULL)"), *GetOwner()->GetName());
	}
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ActorThatOpens) {
		UE_LOG(LogTemp, Error, TEXT("%s object's ActorThatOpens is Not Defined! (NULL)"), *GetOwner()->GetName());
	}
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Open door if overlaps
	if (PressurePlate && ActorThatOpens && PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		// Call Open Door Function
		OpenDoor(DeltaTime);
		// Get opened time
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else if (PressurePlate && ActorThatOpens && !PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		// Check time
		if(DoorLastOpened + DoorCloseDelay <= GetWorld()->GetTimeSeconds())
			// Call Close Door Function
			CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime) {
	currentYaw = FMath::Lerp(currentYaw, targetYaw, DeltaTime * DoorOpenSpeed);
	FRotator DoorOpen = GetOwner()->GetActorRotation();
	DoorOpen.Yaw = currentYaw;
	GetOwner()->SetActorRotation(DoorOpen);
	/*float currentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator openDoor( 0.f, targetYaw, 0.f );
	// Current Yaw, Target Yaw, 0-1
	openDoor.Yaw = FMath::FInterpTo(currentYaw, targetYaw, DeltaTime, 2);
	UE_LOG(LogTemp, Warning, TEXT("%f"), openDoor.Yaw);
	// Set new yaw
	GetOwner()->SetActorRotation(openDoor);
	//GetOwner()->SetActorRotation({ 0.f, GetOwner()->GetActorRotation().Yaw + 0.02f, 0.f });*/
}

void UOpenDoor::CloseDoor(float DeltaTime) {
	currentYaw = FMath::Lerp(currentYaw, initialYaw, DeltaTime * DoorCloseSpeed);
	FRotator DoorClose = GetOwner()->GetActorRotation();
	DoorClose.Yaw = currentYaw;
	GetOwner()->SetActorRotation(DoorClose);
}