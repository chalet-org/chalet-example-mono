#!/bin/bash

if [[ $OSTYPE == 'msys' || $OSTYPE == 'win32' ]]; then
	PLATFORM=windows
fi

if [[ $PLATFORM == "windows" ]]; then
	msbuild.exe /property:Configuration=Release
else
	msbuild /property:Configuration=Release
fi
