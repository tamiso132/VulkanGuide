#!/bin/bash

# Specify the directory containing the shader files
shader_dir="/home/tom/projects/c++/vulkan-guide/shaders"

# Use find to get all GLSL files in the directory
find "$shader_dir" -type f \( -name "*.vert" -o -name "*.frag" -o -name "*.comp" \) -print0 | while IFS= read -r -d '' shader_file; do
    # Extract the base name without extension
    base_name=$(basename "$shader_file" .vert)
    base_name=$(basename "$base_name" .frag)
    base_name=$(basename "$base_name" .comp)

    # Print the file being processed (optional)
    echo "Processing $shader_file"

    # Determine the shader stage based on the file extension
    case "$shader_file" in
        *.vert) stage="vertex";;
        *.frag) stage="fragment";;
        *.comp) stage="compute";;
    esac

    # Compile each shader to SPIR-V using glslangValidator
    glslangValidator -V "$shader_file" -o "${shader_dir}/${base_name}_${stage}.spv"
done
