// Baran Kaya 2020

#pragma once

#include "CoreMinimal.h"
#include "OpenDoor.h"
#include "OpenDoorUpwards.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoorUpwards : public UOpenDoor
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoorUpwards();
	void OpenDoor(float DeltaTime) override;
	void CloseDoor(float DeltaTime) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Door initial Z Position
	float initialZPosition = 0.f;
	// Door current Z Position
	float currentZPosition = 0.f;
	// Door max Z Position
	UPROPERTY(EditAnywhere)
	float OpenZPosition = 100.f;
};
