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

	FHitResult GetFirstPhysicsBodyInReach();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	// Reach length
	UPROPERTY(EditAnywhere)
	float Reach = 100.f;
	// Physics Handle Component
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	// Input Component
	UInputComponent* InputComponent = nullptr;
	// Functions
	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetupInputComponent();
	// Return the first Actor within reach physics body
	FHitResult GetFirstPhysicsBodyInReach() const;
};
