### 1. The Usage of statement initializer to get use a default value when existing map key is provided<br/>

- [Source](https://stackoverflow.com/questions/51667662/default-value-of-static-stdunordered-map)

```
if (auto apple = map.find("Apple"); apple != map.end()) {
    std::cout << apple->second.num << '\n';
    std::cout << apple->second.state << '\n';
}
```

- My Code

```
if (auto command = CommandMap.find(command_str); command != CommandMap.end()) {
    return command->second;
} else {
    return INVALID;
}
```

### 2. Conversion between two differnet clocks

- [Source](https://stackoverflow.com/a/61067330)

```
template <typename TP>
std::time_t to_time_t(TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
              + system_clock::now());
    return system_clock::to_time_t(sctp);
}
```

- My Code

```
template<typename TP>
tm *to_local_time(TP tp) {
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
    std::time_t tt = system_clock::to_time_t(sctp);
    auto local_time = std::localtime(&tt);
    return local_time;
}
```

## 3. BMP FILE Stracture

[link](https://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm)

## 4. Usage of #pragma pack

[link](https://stackoverflow.com/a/37242865)
[more info](https://stackoverflow.com/questions/3318410/pragma-pack-effect)