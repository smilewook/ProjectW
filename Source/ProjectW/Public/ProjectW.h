// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(ProjectW, Log, All);

#define WLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define WLOG_S(Verbosity) UE_LOG(ProjectW, Verbosity, TEXT("%s"), *WLOG_CALLINFO)
#define WLOG(Verbosity, Format, ...) UE_LOG(ProjectW, Verbosity, TEXT("%s%s"), *WLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define WCHECK(Expr, ...) { if(!(Expr)) { WLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; } }