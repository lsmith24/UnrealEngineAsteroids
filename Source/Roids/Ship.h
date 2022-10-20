// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "Bullet.h"
#include "GameFramework/Pawn.h"
#include "Ship.generated.h"

UCLASS()
class ROIDS_API AShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	USphereComponent* ShipSphereComponent;

	// Input Functions
	void Move_Forward(float AxisValue);
	void Move_Turn(float AxisValue);
	void Shoot();
	UPROPERTY(EditDefaultsOnly, Category = Projectile) TSubclassOf<class ABullet> ProjectileClass;
};
