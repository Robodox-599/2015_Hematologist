#2015_Hematologist
Code for the Hematologist, team 599's FRC Recycle Rush robot.
___
####System Checklist
1. Robot turns on
2. Robot has robot code
3. Joysticks plugged in
4. Smart Dashboard + Default Dashboard
5. Limit switches turn green when pressed
6. Lift moves up and down
7. Lift doesn't move when top limit switch pressed
8. Lift doesn't move when bottom limit switch pressed
9. Compressor can turn on/off
10. Compressor stops at 120 psi
11. Motors can drive forward/back with R joystick
12. Motors can turn with R joystick
13. Motors can strafe L joystick
14. Forklift opens and closes
15. Second tier opens and closes
16. Bin hugger opens and closes
17. Autonomous modes work
	- Do nothing
	- Strafe right
	- Extend long arms
___
#####2015-09-26 (Fall Classic 2015 Day 1)
Curretly in the process of cleaning up the code and organizing it to make it readable and easy to navigate. So far, I've set up folders for each subsystem.

**Folder Hierarchy**:
`\src`
- Main robot file (Hematologist.cpp)
- Limit switch .h and .cpp files
- Macros file
- Operator interface .h and .cpp files

`\src\Autonomous`
- Autonomous header and cpp files


`\src\Drive`
- Drive header and cpp files

`\src\Manipulator`
- Manipulator header and cpp files

**TODO**
- Organize and split autonomous files
- Rename files and functions for simplicity
- Organize macros file and make it readable
- Idk




