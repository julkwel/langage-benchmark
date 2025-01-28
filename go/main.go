package main

import (
	"fmt"
	"os"
	"path/filepath"
	"time"
)

type Item struct {
	ID    int
	Value string
}

func main() {
	// Simulating the API fetch with 1M items
	startFetch := time.Now()
	array := make([]Item, 1_000_000)
	for i := 0; i < 1_000_000; i++ {
		array[i] = Item{ID: i, Value: fmt.Sprintf("value_%d", i)}
	}
	fetchTime := time.Since(startFetch).Milliseconds()

	// Filtering the array (only even ids)
	startFilter := time.Now()
	filtered := make([]Item, 0, 500_000)
	for _, item := range array {
		if item.ID%2 == 0 {
			filtered = append(filtered, item)
		}
	}
	filterTime := time.Since(startFilter).Milliseconds()

	// Mapping the array (to upper case)
	startMap := time.Now()
	mapped := make([]int, len(filtered))
	for i, item := range filtered {
		mapped[i] = item.ID
	}
	mapTime := time.Since(startMap).Milliseconds()

	// Reducing the array (sum of ids)
	startReduce := time.Now()
	sumIds := 0
	for _, item := range filtered {
		sumIds += item.ID
	}
	reduceTime := time.Since(startReduce).Milliseconds()

	// Output results
	output := fmt.Sprintf(`
Go Benchmark Results:
Time to fetch: %d ms
Time to filter: %d ms
Time to map: %d ms
Time to reduce: %d ms

`, fetchTime, filterTime, mapTime, reduceTime)

	// Write to benchmark.log
	logPath := filepath.Join("..", "benchmark.log")
	file, err := os.OpenFile(logPath, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println("Error writing to benchmark.log:", err)
		return
	}
	defer file.Close()

	if _, err := file.WriteString(output); err != nil {
		fmt.Println("Error appending to benchmark.log:", err)
		return
	}

	fmt.Println("Go benchmark results written to benchmark.log")
}