# DRXposed
Xposed Module for game called **Day R Survival.**  
This allows you to execute custom script from external storage *`(Internal  Storage)`* 
to the game and modify how the game will behave by patching it on 
initialization *(`Loading n%`)*.


## Installation
> You'll need to have your phone rooted and have LSPosed or any similiar xpose module managers.
1. Download the module [Here](https://github.com/janisslsm/DRXposed/releases).
2. Install it.
3. Open LSPosed, go to modules, then find `DRXposed`.
4. Enable it, then open its settings
5. Find the Day R Survival game that had these [package names](https://github.com/janisslsm/DRXposed/edit/master/README.md#supported-game-and-mods).

>*This module support official build of the game from play store, but the main purpose of this module was to create mod managers for the modded versions.*

## Supported Game and Mods

|Package Name| Name | Type | Author |
|--|--|--|--|
| `com.gm_shaber.dayr` | Day R Survival | Official | TLTGames / Rmind |
| `com.gm_shaber.dayrpremium` | Day R Premium | Official | TLTGames / Rmind |
| `app.angel_mods.dayr` | Day R Reimagine | Modded | Angel |
| `com.diexievie.dayr` | Day R DXV| Modded | Diexievie |

## Adding Script

There's a requirements to make your script used by the module.
1. It must be placed in `/Android/data/{package.name}/files/scripts/`.
2. It must ends with `.lua` extension.
3. The DRXpose module must be enabled and targets the same app your scripts targets.


> *For `{package.name}` refer to [package names](https://github.com/janisslsm/DRXposed/edit/master/README.md#supported-game-and-mods).*
*Example: `/sdcard/Android/data/com.gm_shaber.dayrpremium/files/scripts/some_script.lua`*

For this example we can make `item_multiplier.lua`
The script will multiply all of our items amount 4 times from original value.
But before that, you need to make **explicit** checks before the script runs, 
since this script will be loaded the moment the module hooks to the game.
> It's simply race with the game. It also can crash your game if there's no explicit checks.

### Setup the checks.
```lua
while not(main and main.character and main.character:get("inventory")) do
    wait(1)
end
```
This checks will check if `main`, `main.character`, and `inventory` of our character does exist,
if not, `wait` for 1 second and recheck again.
> When the loop finds all, it continue to execute anything after it and exit.
#### Code for the multiplier.
```lua
for index = 1, #main.character:get("inventory") do
	local currentItemObject = main.character:get("inventory")[index];
	currentItemObject[3] = currentItemObject[3] * 4
end
```
This code, iterate every items in your inventory then 
replace the key number `3`, which is the `amount` with `current_amount * 4` .

> *Note: You can see the inner working of the game if you **made** a function that basically print to file the table the game uses, example such as **printToFile(main)*** 

### Final Code of `item_multiplier.lua`
```lua
while not(main and main.character and main.character:get("inventory")) do
    wait(1)
end

for index = 1, #main.character:get("inventory") do
	local currentItemObject = main.character:get("inventory")[index];
	currentItemObject[3] = currentItemObject[3] * 4
end
```
> This code will runs every time the game launch, means you might have kkkkkkkk of items.
> as of now, there's no such thing as Enable/Disable script, you can however make an if statement that never become true or just add **.bak** after **.lua** or replace the extension, also the module only read any lua file inside /files folder, if there's subfolder inside /files, it will ignore it *hopefully* (untested).

