#pragma once

#include "CoreMinimal.h"
#include "RGBaseProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARGBaseProjectile : public AActor
{
	GENERATED_BODY()

protected:

	/** Sphere component used for collision. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* SphereComponent;

	/** Movement component for the trajectory of the magic projectile. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UProjectileMovementComponent* MovementComponent;

	/** Effects particle system. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UParticleSystemComponent* EffectComponent;

	/** Explosion effect. */
	UPROPERTY(EditAnywhere, Category = Particles)
	class UParticleSystem* HitExplosionEffect;

public:

	ARGBaseProjectile();

protected:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode(AActor* HitActor);

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};