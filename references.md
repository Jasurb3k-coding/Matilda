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

