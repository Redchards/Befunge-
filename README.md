# Befunge-
Simplistic Befugne 93 compliant befunge interpreter written in C++. Mainly a study project, to have fun with the Befunge language, and see how short writing an interpreter for it could be.

# How to build
Simply run the provided makefile, with the desired platform and compilation mode, like this :
```make mode-platform```

Here are the different possibility for the 'mode-platform' parameter :
|Parameter  |Effect                 							|
|---------- |---------------------------------------------------|
|debug      |Build the debug version for your current platform  |
|release    |Build the release version for your current platform|
|debug-x86  |Build the debug version for x86					|
|release-x86|Build the release version for x86				 	|
|debug-x64  |Build the debug version for x64				    |
|release-x64|Build the release version for x64					|

The resulting file will be in 'bin/platform/mode'

The makefile got some more options, like compiling to LLVM bitcode. If you want to know more, please refer to the documentation written at the top of it.

# How to use
Before writing your own befunge programs, you can try many of the examples provided, by using this command :
```Befunge- pathToTheExample```

The befunge syntax can be found here :
https://fr.wikipedia.org/wiki/Befunge
