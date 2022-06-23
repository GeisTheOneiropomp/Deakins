#pragma once

enum SCENEPATH { BASESCENE };

const static SCENEPATH ScenePath = BASESCENE;
const static double AspectRatio = (16.0 / 9.0);
const static int ImageWidth = 1600;
const static int ImageHeight = static_cast<int> (ImageWidth / AspectRatio);
const static int SamplesPerPixel = 50;
const static int MaxDepth = 30;

const static int DistToFocus = 10;
const static double Aperture = 0.0;
const static double FieldOfView = 100;

const static double TiltFactor = 0;
const static double ShiftFactor = 3.5;
const static bool UseVignette = true;
const static double VignetteFactor = .2;
const static double DiffractionRatio = .1;
