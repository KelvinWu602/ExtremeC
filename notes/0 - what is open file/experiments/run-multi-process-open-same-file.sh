# create 2 processes that open the same file, sleep for 1 second, and then close the file

## use & operator to execute processes in background
## no join point for that process
./lib/open_file &
pid1=$!

./lib/open_file &
pid2=$!

wait $pid1
wait $pid2

# ./run-multi-process-open-same-file.sh 
# Process ID: 344848
# Working Directory: /home/kelvin/system-dev/notes/0 - what is open file/experiments
# Process 344848 opened file
# Process 344848 read 'h'
# Process ID: 344849
# Working Directory: /home/kelvin/system-dev/notes/0 - what is open file/experiments
# Process 344849 opened file
# Process 344849 read 'h'
# Process 344848 closed file
# Process 344849 closed file