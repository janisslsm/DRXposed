# DRXposed
Xposed Module for Day R Survival.<br>
Allows to execute custom script from external storage to the game.

## Installation
Download the module and install it as normal.<br>
To use the module you'll need to hooks this module using Xposed Module or LSPosed.

## Scripts Installation
All `scripts` must go to `/sdcard/Android/data/{package.name}/files/scripts/` and must ends with `.lua` extension. <br>
For `{package.name}` refer to table below *(This is used to make the scripts usabled in different versions)*

## Supported `package.name`
| Package Name                | Game Name           | Variation                   |
|-----------------------------|---------------------|-----------------------------|
| `com.gm_shaber.dayr`        | Day R Survival      | Free Version (Original)     |
| `com.gm_shaber.dayrpremium` | Day R Premium       | Paid Version (Original)     |
| `app.angelmod.dayr`         | Day R Reimagine Dev | Development Build           |
| `app.dxvmod.dayr`           | Day R DxV Dev       | Development Build           |
| `app.angel_mod.dayr`        | Day R Reimagine Mod | Stable Build                |
| `app.dxv_mod.dayr`          | Day R DxV Mod       | Stable Build                |

_Example: `/sdcard/Android/data/com.gm_shaber.dayrpremium/files/scripts/some_script.lua`_

## Example Scripts
Example of a scripts to multiply items in inventory.
```lua
-- item_multiplier.lua
while not main.character:get("inventory") do
    wait(1)
end

for idx = 1, #main.character:get("inventory") do
    main.character:get("inventory")[idx][3] = main.character:get("inventory")[idx][3] * 4
end
```
