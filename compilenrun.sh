#!/bin/bash

read file_name
if ["${file_name: -1}" -eq "p"]; then
	g++ $file_name
	./a.out
else
	gcc $file_name
	./a.out
fi
