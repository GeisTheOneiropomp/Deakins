# Deakins
This project implements several vintage camera effects inspired by the work of the cinematographer Roger Deakins, in particular the film _The Assassination of Jesse James by the Coward Robert Ford_, which he lensed. For notes and the mathematical background that explains these models, see the accompanying PDF, tentatively titled "DeakinsDraft.pdf."

To run the project: download the project, open the Visual Studio Solution, and compile to "Release" from Visual Studio, and then run from the command line. The format of the output will be .ppm file. So for example, calling ./Deakins.exe > "test.ppm" will generate the ray traced image into a file named "test.ppm."

The project comes with several images, they can be swapped out with one's own background images by changing filenames in the Resources.h file.

For the time being, the parameters of the actual image (such as the dimensions of the output), can be changed in the main.cpp file. It is here where one can tweak the diffraction strength, the tilt-shift strength, and whether or not to use optical vignetting.

No copyright infringement intended.
