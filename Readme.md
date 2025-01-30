# 🏆 Multi-Language Benchmark

This project benchmarks different programming languages (**C, Python, PHP, TypeScript, Rust, and Go**) by measuring execution time for various operations.

## ⚠️ Environment Consistency

For accurate results, ensure that all benchmarks run on the **same system** under identical conditions (**CPU, memory, and OS**).

## 🚀 Running the Benchmarks

Execute the code for each language as follows:

### **C**
```sh
sh run.sh
```

### **C#**
```sh
dotnet clean && dotnet build -c release && dotnet run -c release
```

### **Python**
```sh
python index.py
```

### **PHP**
```sh
php -f index.php
```

### **TypeScript**
```sh
ts-node index.ts
```

### **Go**
```sh
go run main.go
```

### **Rust**
```sh
cargo run --release
```

### **Shell**
```sh
sh main.sh
```

## 📄 Benchmark Output

Results are logged in the root of the project:

```
benchmark.log
```

## 🤝 Contributing

Feel free to contribute! 🚀 You can:
- **Optimize the existing code**
- **Add new languages for benchmarking**
- **Improve documentation**

Create a pull request, and let's make this even better! 💡