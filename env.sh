#!/usr/bin/env bash

boot2docker up
eval "$(boot2docker shellinit)"
docker build -t island .
docker run -p 8082:8082 -itd -v $(pwd):/island --name=island island bash
alias island-bash="docker start island && docker attach island"
alias island-kill="docker rm -f island"
