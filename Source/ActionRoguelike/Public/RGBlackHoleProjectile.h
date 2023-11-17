#pragma once

#include "CoreMinimal.h"
#include "RGBaseProjectile.h"
#include "RGBlackHoleProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARGBlackHoleProjectile : public ARGBaseProjectile
{
	GENERATED_BODY()
	
protected:

	/** Radial force of the black hole. */
	UPROPERTY(VisibleAnywhere)
	class URadialForceComponent* RadialForceComponent;

public:

	ARGBlackHoleProjectile();
};