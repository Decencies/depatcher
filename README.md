# depatcher
A patcher for loading Defiance 2013 written C++.

## Usage
Compile & place `depatcher.dexe` & `libmod.dll` into the `Games\Defiance\Live` directory, then you can run `depatcher.exe` with your usual program arguments. 
Alternatively, you can rename `libmod.dll` to `Telemetry32.dll` and it will be (automatically) loaded by Defiance.

> Note: when using the Telemetry32 method, it is likely to have issues attaching to the console.
