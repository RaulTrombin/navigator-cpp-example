#!/bin/bash

# You can add you ssh-key to BlueOS, no password required during the scripts.
# ssh-copy-id -i ~/.ssh/id_rsa.pub pi@192.168.15.192

# Enable strict error handling
set -o errexit
# Treat unset variables as errors
set -o nounset
# Consider the last non-zero exit code in a pipeline as the script's exit code
set -o pipefail
# Print each command and its expanded arguments as they are executed
set -o xtrace

# Define the target host, path, and architecture
readonly TARGET_HOST="pi@192.168.15.192"
readonly TARGET_PATH="/home/pi/deploy"
readonly TARGET_ARCH="armv7-unknown-linux-gnueabihf"
readonly SOURCE_PATH="./source/${TARGET_ARCH}/libbluerobotics_navigator.so"
readonly BINDINGS_PATH="./source/bindings.h"
readonly CPP_PATH="./"

ssh -t "${TARGET_HOST}" rm -rf deploy
ssh -t "${TARGET_HOST}" mkdir -p deploy/source/

# Transfer the built binary to the target host
rsync "${SOURCE_PATH}" "${TARGET_HOST}:${TARGET_PATH}/source"
rsync "${BINDINGS_PATH}" "${TARGET_HOST}:${TARGET_PATH}/source"

rsync -r "${CPP_PATH}/project" "${TARGET_HOST}:${TARGET_PATH}"

# SSH into the target host, navigate to the target path, list the contents, and execute the binary
ssh -t "${TARGET_HOST}" "cd ${TARGET_PATH}/project/ && cmake -B build -DCMAKE_BUILD_TYPE=Debug && cmake --build build --config Debug --parallel && build/example"
