#!/bin/bash

# Simple script to render websites using the modern renderer

set -e

echo "=== Modern Blink Renderer - Website Rendering Tool ==="
echo ""

if [ $# -eq 0 ]; then
    echo "Usage: $0 <html_file> [output_file]"
    echo ""
    echo "Examples:"
    echo "  $0 page.html"
    echo "  $0 page.html output.html"
    exit 1
fi

INPUT_FILE="$1"
OUTPUT_FILE="${2:-rendered_output.html}"

if [ ! -f "$INPUT_FILE" ]; then
    echo "Error: File not found: $INPUT_FILE"
    exit 1
fi

echo "Input: $INPUT_FILE"
echo "Output: $OUTPUT_FILE"
echo ""

# Compile and run renderer
BUILD_DIR="$(cd "$(dirname "$0")/../build" && pwd)"

if [ ! -f "$BUILD_DIR/headless_renderer" ]; then
    echo "Building renderer..."
    cd "$(dirname "$0")/.."
    ./build.sh
fi

echo "Rendering..."
$BUILD_DIR/headless_renderer "$INPUT_FILE" "$OUTPUT_FILE"

echo ""
echo "✓ Done! Check $OUTPUT_FILE"
