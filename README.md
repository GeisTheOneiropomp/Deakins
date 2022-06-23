# Deakins

Deakins: A ray tracer simulating the effects of a vintage camera
====================================================================================================

This project implements several vintage camera effects inspired by the work of the cinematographer Roger Deakins, in particular the film _The Assassination of Jesse James by the Coward Robert Ford_, which he lensed. For notes and the mathematical background that explains these models, see the accompanying PDF, tentatively titled "DeakinsDraft.pdf."

## Digest

This program implements some effects identified by Roger Deakins, a director of photography who is regarded as a legend in the world of cinematography. For his film The Assassination of Jesse James by the Coward Robert Ford, Deakins created a camera with a special kind of lens that is used to create shots that have been described as dreamy and etheral for its transitions. Two such shots are shown below:

The dream-like effect is attributed to the following three effects:

	- Tilt-shift lens: Since the Deakinizer can be tilted on the horizontal x-axis, and shifted along the vertical z-axis, it is possible to create different vanishing lines in the image. 

	- Optical vignetting: Since the Deakinizer lens that Lopez and Hammerski made was done by removing a lens element, some of the light that is focused into the camera–particularly around the edges–is darker. This phenomenon is referred to as vignetting and it follows a cosine-fourth power law. 

	- Color diffraction: A Deakinizer lens also produces slight color diffraction due to the light rays diffracting as they hit the edge of the lens barrel. 

This project implements those three effects in an attempt to reproduce the above-effects.

## Usage

1. Clone this repository.
2. Compile to Release with Visual Studio. (Note well, this code project uses some Japanese characters. That may cause some compilation errors.)
3. Run from the command line. (In particular, do not run from the debugger) Note that the output will be a .ppm file. So for example, running 

```bash
./deakins.exe > "test.ppm"
```

will generate a file called test.ppm that contains the ray-traced image.

4. The project comes with a background image. It can be swapped out with one's own background images, or moon textures by changing filenames in the FileResources.h file:

`FileResources.h`:
```c++
#include <string>
using namespace std;
#pragma once

const static string TSURUTA_FILE = "..extern\\img\\Tsuruta.jpg";
```

5. The default setting is to generate an image of spheres. To change the scene to balls randomly distributed throughout the scene, open the `Config.h` file, and change any number of the variables: 

Many parameters related to the camera controls can be tweaked the:

`Config.h`
```c++
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
```

## Image Gallery: Tilt-Shift Lens

The following section displays the effects of a tilt-shift lens:

| ![base][simpleunaltered]     | ![tilt][simpletiltshift]    | 
|:----------------------------:|:---------------------------:|
|          Base Image          |      Tilt-Shift Lens        | 

If one wishes to alter the strength of the tilt-shift effect, one only needs to alter these paramaters:

`Config.h`
```c++
const static double TiltFactor = 0.0;
const static double ShiftFactor = 0.0;
```

## Image Gallery: Optical Vignetting

The following section displays the effects of assuming that the lens barrel causes vignetting in the image:

| ![base][simpleunaltered]     | ![vign][simplevignette]     | 
|:----------------------------:|:---------------------------:|
|          Base Image          |     Optical Vignetting      | 

If one wishes to alter the strength of the vignetting effect, one only needs to alter these paramaters:

`Config.h`
```c++
const static bool UseVignette = false;
const static double vignetteFactor = 2.0;
```

## Image Gallery: Color Diffraction

The following section compares post-Lambertian models of the Moon with the standard Lambertian model:

| ![base][simpleunaltered]     | ![diff][simplediffraction]  | 
|:----------------------------:|:---------------------------:|
|          Base Image          |      Simple Diffraction     | 

The diffraction ratio parameter in the config file specifies the proportion of rays to be dedicated to diffraction. To increase the contribution of diffraction to the overall image one only needs to increase the ratio.

`Config.h`
```c++
const static double DiffractionRatio = .1f;
```

## Image Gallery: Overall Deakins Effect

The following section compares post-Lambertian models of the Moon with the standard Lambertian model:

| ![base][simpleunaltered]     | ![deakins][simpledeakins]   | 
|:----------------------------:|:---------------------------:|
|          Base Image          |       Overall Deakins       | 

## In what situations is the Deakins effect applicable?
    
  * Situations in which an overall effect is to create a dream-like quality, in which a memory is fuzzily recalled, but perhaps not perfectly remembered/
  
  * Situations in which one wishes to simulate the past. The original Deakinzer lens was made after the artist was asked to simulate the effects of recreating 19th-century photographs.
  
  * Situations in which one wishes to highlight the grandeur of a landscape, a cloudscape, etc.

  * Etc. The possibilities are endless!

## How does Deakins perform?

  * The most costly part of the application compared to standard ray tracing is the use of a monochromatic ray class. However the cost of this can be amortized if one is using a monochromatic ray class to simulate other optical quantum phenomenon other than diffraction.

## Can you briefly summarize the technical implementation?

  * Tilt-Shift Lens: This particular ray tracer simply performs the calculation by randomly sampling from all possible tilt-shift offsets to generate the blur. One may conceptualize this implemention of code as a way of simulating motion blur, except instead of moving the objects, the camera itself is moved.

  * Optical Vignetting:  Mathematically, the light falloff is proportional to the fourth power of the cosine of the angle at which light impinges the image plane. However, this may cause too much of a darkening effect in the image. Afterall, compared to vintage cameras, our ray-traced camera is so much more clear and has much more detail, so perhaps the cosine-fourth power law is too strong. 

  * Color Diffraction:  The first thing that must be done is to sample across the spectrum of possible colors. To that end, we created a Monochromatic Ray class, that gives each ray a wavelength and intensity. There is also a helper function to convert a chromatic wavelength into its appropriate RGB value. There are many treatments of diffraction. In this paper, we shall only be concerned with far-field diffraction, (Fraunhoffer). Near-field effects, (Fresnel) are ignored, since the only diffraction that we are interested in is the diffraction occuring at the lens aperture, which is a significant distance away from the image plane. 

[simpleunaltered]:          OutputGallery/SimpleUnaltered.png
[simpletiltshift]:          OutputGallery/SimpleTiltShift.png
[simplevignette]:          OutputGallery/SimpleVignette.png
[simplediffraction]:          OutputGallery/SimpleDiffraction.png
[simpledeakins]:          OutputGallery/SimpleDeakins.png