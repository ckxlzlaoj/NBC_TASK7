// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"

#include "MyPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class APawn;
/**
 * 
 */
UCLASS()
class MYPROJECT3_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    AMyPlayerController();
    // �Է� ����(�ڵ�� �ε��ϰų� BP���� ����)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* LookAction;

protected:
    virtual void BeginPlay() override;

private:
    APawn* PlayerPawn = nullptr;

};
