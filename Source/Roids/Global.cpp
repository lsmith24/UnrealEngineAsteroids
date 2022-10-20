// Fill out your copyright notice in the Description page of Project Settings.

#include "Global.h"
#include "UObject/ConstructorHelpers.h" 
#include "Kismet/GameplayStatics.h"

// Sets default values
AGlobal::AGlobal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UBlueprint> Asteroid(TEXT("Blueprint'/Game/AsteroidBP.AsteroidBP'"));
	if (Asteroid.Object) {
		AsteroidClass = (UClass*)Asteroid.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void AGlobal::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(timerHandle, this, &AGlobal::SpawnAsteroids, 5.0f, true);
	Score = 0;
}

// Called every frame
void AGlobal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGlobal::SpawnAsteroids() {
	UWorld* const World = GetWorld();
	if (World) {
		for (int i = 0; i < 3; i++) {
			float random1 = (float)rand() / RAND_MAX;
			float random2 = (float)rand() / RAND_MAX;

			APlayerController* cam = UGameplayStatics::GetPlayerController(GetWorld(), 0);

			FVector actorLoc = cam->GetPawn()->GetActorLocation();

			float xPos = FMath::RandRange(actorLoc[0] - 600, actorLoc[0] + 600);
			float yPos = FMath::RandRange(actorLoc[1] - 600, actorLoc[1] + 600);
			FVector spawn = FVector(xPos, yPos, actorLoc[2]);
			AAsteroid* roid = World->SpawnActor<AAsteroid>(AsteroidClass, spawn, FRotator(0.f));
			roid->HitDelegate.BindDynamic(this, &AGlobal::incrementScore);
		}
	}
}

void AGlobal::incrementScore() {
	Score += 10;
}

