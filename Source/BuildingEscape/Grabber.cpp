// Baran Kaya 2020

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// Find Physics Handle Component
	FindPhysicsHandle();

	// Sey and Bind Input component
	SetupInputComponent();
	
}

void UGrabber::FindPhysicsHandle() {
	// Find Physics Handle by class
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	// Null check
	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("Physics handler component on %s is NULL!"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent() {
	// Checking for Input Component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	// Null check
	if (!InputComponent) {
		UE_LOG(LogTemp, Error, TEXT("Input component on %s is NULL!"), *GetOwner()->GetName());
	}
	// Bind PRESS and RELEASE actions
	else {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab() {
	// Get first object in reach
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	// Get component out of hit result
	UPrimitiveComponent* GrabToComponent = HitResult.GetComponent();
	// Get the actor that hit
	AActor* ActorHit = HitResult.GetActor();
	// If hit the actor
	if (ActorHit) {
		// Check PhysicsHandle
		if (!PhysicsHandle) return;
		// Grab it
		PhysicsHandle->GrabComponentAtLocation(GrabToComponent, NAME_None, GetPlayersReach());
	}
}

void UGrabber::Release() {
	// Check PhysicsHandle
	if (!PhysicsHandle) return;
	// Release the grabbed component
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Check PhysicsHandle
	if (!PhysicsHandle) return;
	// If user grabbed something
	if (PhysicsHandle->GrabbedComponent) {
		// Move object we are holding
		PhysicsHandle->SetTargetLocation(GetPlayersReach());
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const{
	// Hit result
	FHitResult Hit;
	// COllision parameters
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	// Get first physics body in reach
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayersLocation(),
		GetPlayersReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return Hit;
}

FVector UGrabber::GetPlayersReach() const {
	// Player's viewpoint vector variables
	FVector PlayerViewPointLocation{ 0,0,0 };
	FRotator PlayerViewPointRotation{ 0,0,0 };
	// Get player's viewpoint location and rotation
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	// Calculate player's reach and return
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FVector UGrabber::GetPlayersLocation() const {
	// Player's viewpoint vector variables
	FVector PlayerViewPointLocation{ 0,0,0 };
	FRotator PlayerViewPointRotation{ 0,0,0 };
	// Get player's viewpoint location and rotation
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	// Calculate player's reach and return
	return PlayerViewPointLocation;
}

