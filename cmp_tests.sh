if [ "$#" -ne 2 ]; then
    echo "Usage: $0 [inp] [out]"
    exit 1
fi
gcc -g -Iapi -Ilib -Lbin_db -lclopter -Llib -llogger "$1" -o "$2"
