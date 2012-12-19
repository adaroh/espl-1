filename=$1
count=$2
skipped="0"

if [ ! -r $filename ] ; then
  echo "$0: Can not find the source file $filename" >&2
  exit 1
fi

while [ -r $1.$(( $count - 1 )) ] && [ $count != 1 ] ;do # make sure the count-1 version exists and back it up, then continue to back up each prior version
  cp $1.$(( $count - 1 )) $1.$count
  count=$(( $count - 1 ))
  while [ ! -r $1.$(( $count - 1 )) ] && [ $count != 1 ]; do # skip any former versions that do not exist
    count=$(( $count - 1 ))
    skipped=$skipped,$count
  done
done
if [ $count > 1 ]; then #the oldest version to back up does not exist, operation exits
  echo "could not find version $(( $count - 1 )) to back up"
  exit 0
elif [ "$skipped" != "" ]; then # some of the versions did not exist
  echo "could not find versions $skipped to back up..."
fi
cp $filename $filename.1

exit 0  