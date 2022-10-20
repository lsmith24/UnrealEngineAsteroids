// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SoundDefinitions.h" 
#include "Sound/SoundCue.h" 
#include "Bullet.h"
#include "Components/BoxComponent.h" 
#include "Materials/Material.h" 
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

DECLARE_DYNAMIC_DELEGATE(FDelegate);

UCLASS()
class ROIDS_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UBoxComponent* AsteroidBoxComponent;
	UMaterial* AsteroidMaterial;
	TSubclassOf<class AActor> Explosion;
	USoundCue* explosionSoundCue;

	UPROPERTY(EditAnywhere)
	FDelegate HitDelegate;

	UFUNCTION()
	void onHit(AActor* SelfActor, class AActor* OtherActor, FVector NormalImpulse,const FHitResult& Hit);
};
