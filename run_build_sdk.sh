#!/bin/bash
source ./docker/sdk_version.sh

docker build -t prefix_search_sdk:$SDK_VERSION ./docker/