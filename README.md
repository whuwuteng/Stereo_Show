# A Qt based tool to show Epipolar stereo image

This is a Qt and CMake based project to show stereo image in one window in [Red/Cyan mode](https://en.wikipedia.org/wiki/Anaglyph_3D).
The Red/Cyan mode is also called stereo anaglyph, a [python based implement](https://github.com/miguelgrinberg/anaglyph.py) can be found, and the [algorithm](http://www.3dtv.at/knowhow/anaglyphcomparison_en.aspx) is not complicate, the optimized color is used.

## OVERVIEW
If you want to check parallax error in y(vertic), because this error is important for stereo Matching.

## USAGE
You can use QtCreate to import the porject, also you can use CMake
<center><h2>CMakeLists for Ubuntu 16.04</h2></center>
<UL>
<LI> mkdir build
<LI> cd build
<LI> cmake ..
<LI> make
</UL>

## FEATURE
Can hand both gray and color image.

## EXAMPLE
The gray image from [ETH3D](https://www.eth3d.net/datasets) dataset:
|<img src="im0.png" width="250" alt="left image" />|<img src="im1.png" width="250" alt="right image" />|<img src="eth3d.png" width="250" alt="Red/Cyan image" />|
| :---:         |     :---:      |          :---: |
| *left image* | *right image* | *Red/Cyan mode* | 

The gray image from [Middlebury stereo](https://vision.middlebury.edu/stereo/) dataset:
|<img src="m_im0.png" width="250" alt="left image" />|<img src="m_im1.png" width="250" alt="right image" />|<img src="middlebury.png" width="250" alt="Red/Cyan image" />|
| :---:         |     :---:      |          :---: |
| *left image* | *right image* | *Red/Cyan mode* | 

## MAINTENANCE
If you think you have any problem, contact Teng Wu <teng.wu@ign.fr>
