import * as fs from 'fs';
import * as path from 'path';

function runBenchmark() {
    type Item = { id: number; value: string };

    const startFetch: number = performance.now();
    const array: Item[] = Array.from({ length: 1_000_000 }, (_, i): Item => ({ id: i, value: `value_${i}` }));
    const fetchTime: number = performance.now() - startFetch;

    // Filtering the array (only even ids)
    const startFilter: number = performance.now();
    const filtered: Item[] = array.filter((item: Item): boolean => item.id % 2 === 0);
    const filterTime: number = performance.now() - startFilter;

    // Mapping the array ( we need ids only )
    const startMap: number = performance.now();
    const mapped: number[] = filtered.map((item: Item): number => item.id);
    const mapTime: number = performance.now() - startMap;

    // Reducing the array (sum of ids)
    const startReduce: number = performance.now();
    const sumIds: number = filtered.reduce((acc: number, item: Item): number => acc + item.id, 0);
    const reduceTime: number = performance.now() - startReduce;
    const output = `
    TypeScript Benchmark Results:
    Time to fetch: ${fetchTime.toFixed(2)} ms
    Time to filter: ${filterTime.toFixed(2)} ms
    Time to map: ${mapTime.toFixed(2)} ms
    Time to reduce: ${reduceTime.toFixed(2)} ms
    `;

    const logPath = path.join(__dirname, '../benchmark.log');
    fs.appendFileSync(logPath, output, 'utf8');

    console.log("TypeScript benchmark results written to benchmark.log");
}

runBenchmark();