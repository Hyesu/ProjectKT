// Fill out your copyright notice in the Description page of Project Settings.

#include "KTButton.h"

TSharedRef<SWidget> UKTButton::RebuildWidget()
{
	WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::NoDrawType;
	WidgetStyle.Hovered.DrawAs = ESlateBrushDrawType::NoDrawType;
	WidgetStyle.Pressed.DrawAs = ESlateBrushDrawType::NoDrawType;
	WidgetStyle.Disabled.DrawAs = ESlateBrushDrawType::NoDrawType;

	return Super::RebuildWidget();
}