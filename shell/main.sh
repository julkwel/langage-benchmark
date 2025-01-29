#!/bin/sh


benchmark() {
  local start=$(date +%s%N)
  $1 > /dev/null
  local end=$(date +%s%N)
  echo $(((end - start) / 1000000)) 
}

fetch() {
    local array_size=1000000
    for ((i=0; i<$array_size; i++)); do
        echo "$i,value_$i"
    done
}
filter() {
    local array_size=1000000
    for ((i=0; i<$array_size; i++)); do
        if [ $((i % 2)) -eq 0 ]; then
            echo "$i,value_$i"
        fi
    done
}

map() {
    local array_size=1000000
    for ((i=0; i<$array_size; i++)); do
        echo "$i"
    done
}

reduce() {
    local array_size=1000000
    local sum=0
    for ((i=0; i<$array_size; i++)); do
        sum=$((sum + i))
    done
}



main() {
    log_file="../benchmark.log"
    
    echo "shell script benchmark Results:"  >> $log_file
    echo "Time to fetch: $(benchmark fetch) ms"  >> $log_file
    echo "Time to filter: $(benchmark filter) ms"  >> $log_file
    echo "Time to map: $(benchmark map) ms"  >> $log_file
    echo "Time to reduce: $(benchmark reduce) ms"  >> $log_file
}

main 