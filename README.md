# What is this mod?

This mod is intended for the game The Legend of Heroes: Trails in the Sky FC. It changes the hardcoded resolution of the spritesheets for characters and monsters, allowing to use upscaled spritesheets. This can be applied to both DX8 and DX9 executables.
![Hd](https://user-images.githubusercontent.com/69110695/125199738-fa132680-e267-11eb-8a1c-13aa3b3f2c65.PNG)

It also includes a small single threaded texture injector that is only compatible with the DX9 version of the game. I based it on SpecialK injector, but due to my very limited knowledge with DX9, it is not be perfect. If you know how to improve it, please let me know.
 
This injector was made because packing all the DDS of the game inside ED6_DT15.dat gives long loading times. The to-be-injected textures are placed inside a "textures" folder located in the game folder.

It is compatible with the SoraVoice patch if you use the dsound dll instead of the dinput8 dll.

# How to use it

1- Put your ED6_DT04.DAT/DIR, ED6_DT06.DAT/DIR, ED6_DT07.DAT/DIR and ED6_DT09.DAT/DIR containing upscaled spritesheets in the game folder\
2 - (Optional if you set "textureinjection" to false) Create a "textures" folder where you put all the upscaled textures of the game \
3 - Place dinput8.dll inside the game folder\
4 - Fill out the config.ini file. An example below:

[mods]\
hdsprites=true\
textureinjection=true\
upscaling factor=2

The upscaling factor is used to improve the resolution of the sprites only

# How to extract the game textures/adapt them/upscale them
I will write the process later.

# Issues
- Lack of testing (didn't do a full playthrough + only tested with upscale factor of 2)
- Some textures are conveniently not upscaled (textbox, minimap, ...) 
- Loading a savefile that was created using a non HD version of the game can crash it shortly after. However once a new map is loaded, the game should be stable.
