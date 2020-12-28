// Baran Kaya 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	// Reach length
	UPROPERTY(EditAnywhere)
	float Reach = 100.f;
	// Physics Handle Component
	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	// Input Component
	UPROPERTY()
	UInputComponent* InputComponent = nullptr;
	// Functions
	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetupInputComponent();
	// Return the first Actor within reach physics body
	FHitResult GetFirstPhysicsBodyInReach() const;
	// Return the Line Trace End
	FVector GetPlayersReach() const;
	// Get Player's viewpoint location
	FVector GetPlayersLocation() const;
};
