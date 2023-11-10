#pragma once

#include "CoreMinimal.h"
#include "RGExplodingBarrel.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARGExplodingBarrel : public AActor
{
	GENERATED_BODY()

protected:

	/** Static mesh of the barrel. */
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;

	/** Radial force of the explosion. */
	UPROPERTY(VisibleAnywhere)
	class URadialForceComponent* RadialForceComponent;

	/** Explosion effect. */
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* EffectComponent;

public:

	ARGExplodingBarrel();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHitCallback(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};