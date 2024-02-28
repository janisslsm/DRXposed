## DRXposed

Allows executing lua code from external storage in Day R Premium

Example of multiplying items in inventory (all scripts go in /sdcard/Android/data/com.gm_shaber.dayrpremium/files/scripts/ and have to end with .lua)
```lua
while not main.character:get("inventory") do
    wait(1)
end

for idx = 1, #main.character:get("inventory") do
    main.character:get("inventory")[idx][3] = main.character:get("inventory")[idx][3] * 4
end
```