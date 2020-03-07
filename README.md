# Texture manager 

## Introduction :

This is a management support class, making it easier and more effective to textures.

##### Advantages:

- Manage by name (string)

- Simple creation manipulation

- Collision support (normal , cricle , pixel perfect)

- Load texture from file (.xml) <br>
	```xml 
	<textureatlas>
		<texture name={name} path={path_image_source} createmask={sp_collision_perfect} 
			spritesheet={path_data_sprite}>
		</texture>
	</textureatlas>
	```
	Ex: [d_texture.xml](TextureManager/TextureManager/assets/d_texture.xml)<br>

**PS**: These are just my subjective opinions in the process of capturing and handling events with SFML
## Version :
+ v1.0 
+ v1.1.2
## Content:
##### Version 1.0
	-> Create
	-> Collision

##### Version 1.1.2
	-> Load data texture from the xml file
	-> Update texturemanger
	-> Load spritesheet
	-> Fix collision cricle 

## Update : 

## Conclude :
I am not sure it is a good solution. I look forward to contributing to development. Thanks

## References :
- [SFML Game Development By Example](https://www.amazon.com/SFML-Development-Example-Raimondas-Pupius/dp/1785287346)



