#pragma once

enum SCENEPATH { BASESCENE };

const static SCENEPATH ScenePath = BASESCENE;
const static double AspectRatio = (16.0 / 9.0);
const static int ImageWidth = 1600;
const static int ImageHeight = static_cast<int> (ImageWidth / AspectRatio);
const static int SamplesPerPixel = 100;
const static int MaxDepth = 30;

const static int DistToFocus = 10;
const static double Aperture = 0.0;
const static double FieldOfView = 100;
const static double TiltFactor = 0.0;
const static double ShiftFactor = 0.0;
const static double DiffractionRatio = .1f;
const static bool UseVignette = 0.0f;