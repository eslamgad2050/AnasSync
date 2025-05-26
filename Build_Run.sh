
set -e 
BUILD_DIR="CmakeBuild"
TARGET_NAME="main"  # Must match CMake target name

echo "=== Building $TARGET_NAME ==="

# Clean and create build directory
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"

cmake -S . -B "$BUILD_DIR"
make -C "$BUILD_DIR" 
echo "===Running $TARGET_NAME==="
echo
./CmakeBuild/main
echo
echo
echo "===Done $TARGET_NAME==="
