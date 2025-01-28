<?php

$start = microtime(true);

$array = [];
for ($i = 0; $i < 1000000; $i++) {
    $array[] = ['id' => $i, 'value' => 'value_' . $i];
}
$fetch_time = round((microtime(true) - $start) * 1000, 2);

// Filtering the array (only even ids, like )
$start = microtime(true);
$filtered = array_filter($array, function ($item) {
    return $item['id'] % 2 === 0;
});
$filter_time = round((microtime(true) - $start) * 1000, 2);

$start = microtime(true);
$mapped = array_map(function ($item) {
    return $item['id'];
}, $filtered);
$map_time = round((microtime(true) - $start) * 1000, 2);

// Reducing the array (sum of ids)
$start = microtime(true);
$sum = array_sum(array_map(function ($item) {
    return $item;
}, $mapped));
$reduce_time = round((microtime(true) - $start) * 1000, 2);

$output = "PHP Benchmark Results:\n" .
          "Time to fetch: $fetch_time ms\n" .
          "Time to filter: $filter_time ms\n" .
          "Time to map: $map_time ms\n" .
          "Time to reduce: $reduce_time ms\n\n";

$log_file = __DIR__ . '/../benchmark.log';
file_put_contents($log_file, $output, FILE_APPEND);

print("PHP benchmark results written to benchmark.log\n");