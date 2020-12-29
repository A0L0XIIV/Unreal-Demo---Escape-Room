// Baran Kaya 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.h" 	

#include "OpenDoorUpwards.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoorUpwards : public UActorComponent, public OpenDoor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoorUpwards();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

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
