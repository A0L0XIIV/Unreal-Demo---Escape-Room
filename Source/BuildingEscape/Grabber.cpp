// Baran Kaya 2020

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#include "Grabber.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Grab that shit"));
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Release that shit"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const{
	// Get player's viewpoint
	FVector PlayerViewPointLocation{ 0,0,0 };
	FRotator PlayerViewPointRotation{ 0,0,0 };

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	/*DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0, 0),
		false,
		0.f,
		0,
		5.f
	);*/

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* ActorHit = Hit.GetActor();

	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("HIT: %s"), *ActorHit->GetName());
	}

	return Hit;

	//UE_LOG(LogTemp, Warning, TEXT("Loc: %s, Rot: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
}

