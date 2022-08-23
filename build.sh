SOURCE="../user/"    #your dir path
DESTINATION="./"

cp -u "$SOURCE"*.bpf.c $DESTINATION"client.bpf.c"
cp -u "$SOURCE"*.bpf.h $DESTINATION"event.h"
cp -u "$SOURCE"config.json $DESTINATION"config.json"

sudo make

cp .output/package.json $SOURCE
