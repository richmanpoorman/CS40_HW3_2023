 #! /bin/sh
# This script assumes you are running it from the locality folder

# Possible operations to do on an image
TRANSFORMATIONS=("-rotate 90" "-rotate 180" "-rotate 270"
          "-flip horizontal" "-flip vertical" "-transpose")

# The possible ways to read the image
MAJORS=("-row-major" "-col-major" "-block-major")

# The ppm images to run the tests on, without the .ppm suffix 
IMAGE_PATH="Test/TestImages/"
# IMAGES=("flowers")
IMAGES=("flowers" "animals" "desert" "erosion" "from-wind-cave" \
        "halligan" "in-wind-cave" "rock" "segfault" "wind-cave") 
        
OUTPUT_PATH="Test/OutputTest/"
TIMING_SUFFIX="Timing.txt"
# Default image transform

# imageTransform [imageName] [outputSuffix] [operation1] [operation2]
imageTransform () {
        # jpegtran $3 $IMAGE_PATH$1.jpg | djpeg > $OUTPUT_PATH$1$2test.ppm

        # djpeg $IMAGE_PATH$1.jpg > $IMAGE_PATH$1.jpgToPpm | \
        # valgrind --leak-check=full --show-leak-kinds=all \
        djpeg $IMAGE_PATH$1.jpg | \
        valgrind ./ppmtrans \
                $3 $4 $5 \
                > $OUTPUT_PATH$1$2.ppm

        # diffVal="$(diff $OUTPUT_PATH$1$2test.ppm $OUTPUT_PATH$1$2.ppm)"
        # if [ ! -z "$diffVal" ]; then
        #         # display $OUTPUT_PATH$1$2test.ppm
        #         # display $OUTPUT_PATH$1$2.ppm
                
        #         echo "$IMAGE_PATH$1$3$4$5 has a diff error"
        #         echo $diffVal > $OUTPUT_PATH$1$2.diff
        # else 
        #         echo "Good Match"
        # fi

        # rm $OUTPUT_PATH$1$2test.ppm
        rm $OUTPUT_PATH$1$2.ppm
        # rm $IMAGE_PATH$1.jpgToPpm
        # ./ppmtrans $3 $4 $5 $IMAGE_PATH$1.ppm > \
        #                 $OUTPUT_PATH$1$2.ppm 
        # if [[ -f $IMAGE_PATH$1.jpg ]] && [[ "$#" -ge 3 ]]; then
        #         jpegtran $3 $IMAGE_PATH$1.jpg > $OUTPUT_PATH$1$2.jpg
        #         djpeg -ppm $OUTPUT_PATH$1$2.jpg > $OUTPUT_PATH$1$2.out
        #         diff $OUTPUT_PATH$1$2.ppm $OUTPUT_PATH$1$2.out
        # fi
         
}

for image in "${IMAGES[@]}"; do 
        touch $OUTPUT_PATH$image$TIMING_SUFFIX
done

echo "Default image reading: "
for operation in "${TRANSFORMATIONS[@]}"; do
        echo "Operation: $operation"
        op=($operation)
        for image in "${IMAGES[@]}"; do
                echo "Image: $image.ppm"
                imageTransform $image "-default${op[0]}${op[1]}" "$operation"
        done 
done

echo "Timing image reading: "
for operation in "${TRANSFORMATIONS[@]}"; do
        echo "Operation: $operation"
        
        op=($operation)
        for image in "${IMAGES[@]}"; do
                echo "Image: $image"

                echo $operation >> "$OUTPUT_PATH$image$TIMING_SUFFIX"
                imageTransform $image "-time${op[0]}${op[1]}" "$operation" \
                                     "-time $OUTPUT_PATH$image$TIMING_SUFFIX"
        done 
done

echo "Timing image with major reading: "
for operation in "${TRANSFORMATIONS[@]}"; do
        echo "Operation: $operation"
        
        op=($operation)
        for image in "${IMAGES[@]}"; do
                echo "Image: $image"
                
                for major in "${MAJORS[@]}"; do
                        echo $major
                        echo "$major$operation" >> \
                                "$OUTPUT_PATH$image$TIMING_SUFFIX$"
                        imageTransform $image "-time${op[0]}${op[1]}" \
                                "$operation" \
                                "-time $OUTPUT_PATH$image$TIMING_SUFFIX" \
                                
                done 
        done 
done

echo "Bad File Reading: "
imageTransform "ThisIsABadFile.ppm" "-badFileOutput"

echo "No Flags Reading: "
for operation in "${TRANSFORMATIONS[@]}"; do
        for image in "${IMAGES[@]}"; do
                echo "Image: $image"
                imageTransform $image "-noFlag${op[0]}${op[1]}" "$operation"
        done 
done