#!/bin/bash

if [[ $OSTYPE == 'msys' || $OSTYPE == 'win32' ]]; then
	PLATFORM=windows
fi

if [[ $PLATFORM == "windows" ]]; then
	msbuild.exe /clp:ForceConsoleColor /property:Configuration=Debug
else
	msbuild /clp:ForceConsoleColor /property:Configuration=Debug
fi
