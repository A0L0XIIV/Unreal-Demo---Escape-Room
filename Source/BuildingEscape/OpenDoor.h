// Baran Kaya 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

private:
	// Door initial yaw degree
	float initialYaw = 0.f;
	// Door current yaw degree
	float currentYaw = 0.f;
	// Door max yaw degree
	UPROPERTY(EditAnywhere)
	float targetYaw = 90.f;

	// Pressure Plate
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	// Pressure Plate Actor
	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;

	// Door close time parameters
	float DoorLastOpened = 0.f;
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.f;

	// Door open and close speeds
	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 1.0f;
	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 2.f;

};
