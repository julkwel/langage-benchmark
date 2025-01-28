import time
import os

start = time.time()
array = [{'id': i, 'value': f'value_{i}'} for i in range(1000000)]
fetch_time = (time.time() - start) * 1000

# Filtering the array (only even ids)
start = time.time()
filtered = [item for item in array if item['id'] % 2 == 0]
filter_time = (time.time() - start) * 1000

start = time.time()
mapped = [item['id'] for item in filtered]
map_time = (time.time() - start) * 1000

# Reducing the array (sum of ids)
start = time.time()
sum_ids = sum(item for item in mapped)
reduce_time = (time.time() - start) * 1000

output = (
    f"Python Benchmark Results:\n"
    f"Time to fetch: {fetch_time:.2f} ms\n"
    f"Time to filter: {filter_time:.2f} ms\n"
    f"Time to map: {map_time:.2f} ms\n"
    f"Time to reduce: {reduce_time:.2f} ms\n\n"
)

log_path = os.path.join(os.path.dirname(__file__), '../benchmark.log')
with open(log_path, 'a') as log_file:
    log_file.write(output)

print("Python benchmark results written to benchmark.log")