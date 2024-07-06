#!/bin/bash

source ./docker/sdk_version.sh

docker run --net host --rm -v $PWD:/prefix_search/ -w /prefix_search/ -it prefix_search_sdk:$SDK_VERSION  /bin/bash