var items = new Item[1_000_000];
var stopwatch = new System.Diagnostics.Stopwatch();

// Create 
stopwatch.Start();
for (uint i = 0; i < 1_000_000; i++)
{
    items[i] = new Item(i, $"value_{i}");
}
stopwatch.Stop();
var fetchTime = stopwatch.ElapsedMilliseconds;

// Filter
stopwatch.Restart();
var filteredItems = items.Where(it => it.Id % 2 == 0).ToArray();
var filterTime = stopwatch.ElapsedMilliseconds;

// Map
stopwatch.Restart();
var mappedItems = filteredItems.Select(it => it.Id).ToArray();
var mapTime = stopwatch.ElapsedMilliseconds;

// Reduce
stopwatch.Restart();
var idsSum = filteredItems.Aggregate(0L, (acc, item) => acc + item.Id);
var reduceTime = stopwatch.ElapsedMilliseconds;

var output = $"""
              C# Benchmark Results:
              Time to fetch: {fetchTime} ms
              Time to filter: {filterTime} ms
              Time to map: {mapTime} ms
              Time to reduce: {reduceTime} ms
              
              """;

var logPath = Path.Combine(AppContext.BaseDirectory, "../../../../benchmark.log");
File.AppendAllText(logPath, output, System.Text.Encoding.UTF8);

Console.WriteLine($"C# benchmark results written to {logPath}");

internal record Item(uint Id, string Value);
