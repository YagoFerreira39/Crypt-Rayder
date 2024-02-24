// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent(){
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay() {
    Super::BeginPlay();

    UE_LOG(LogTemp, Display, TEXT("Trigger Component Alive"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (Mover == nullptr) {
        return;
    }

    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);

    AActor* AcceptableActor = GetAcceptableActor();
    if (AcceptableActor != nullptr) {
            Mover->SetShouldMove(true);
    }
    else {
        Mover->SetShouldMove(false);
    }
}

void UTriggerComponent::SetMover(UMover* NewMover) {
    Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const {
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);

    for (AActor* Actor : Actors) {
        if (Actor->ActorHasTag(AcceptableActorTag)) {
            return Actor;
        }
    }

    return nullptr;
}