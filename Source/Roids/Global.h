// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Asteroid.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global.generated.h"

UCLASS()
class ROIDS_API AGlobal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGlobal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	TSubclassOf<class AAsteroid> AsteroidClass;
	void SpawnAsteroids();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global") 
	int32 Score;
	FTimerHandle timerHandle;

	UFUNCTION()
	void incrementScore();
};
