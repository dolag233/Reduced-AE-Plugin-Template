# AE Plugin Template

This is a reduced AE plugin template to replace the Skeleton in the AE SDK. You can develop your plugin based on this project on Windows instead of Skeleton.

---

## Features

+ Remove redundant code and just keep only the core code.
+ Support MFR by default.
+ More organized and portable project structure.
+ Compile it in one click without tedious configuration.
+ Standalone in one folder, no weird dependencies.

## Notes

+ Windows only!
+ Use May2023 SDK.
+ Use Visual Studio 2022.
+ Use Clang by default.
+ If you want to change the plugin and project name, you should pay attention to Name and AE_Effect_Match_Name in PiPL, name of the source file and #include statement, name of the vcxproj and configuration, name of the solution, project and solution name within .sln file.