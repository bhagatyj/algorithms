#!/bin/sh
echoerr() { echo "$@" 1>&2; }

DIR="$1"
shift 1
#echoerr Came here "$@"
case "$DIR" in
"" | ".")
gcc -MM -MG "$@" |
sed -e ’s@ˆ\(.*\)\.o:@\1.d \1.o:@’
;;
*)
gcc -MM -MG "$@" |
sed -e "s@ˆ\(.*\)\.o:@$DIR/\1.d \
$DIR/\1.o:@"
;;
esac