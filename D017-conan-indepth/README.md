| Concept                                                              | Note                                            |
| -------------------------------------------------------------------- | ----------------------------------------------- |
| [[CMakeToolchain]]                                                   |                                                 |
| [[CMakeDeps]]                                                        |                                                 |
| [[#Detecting the compiler]]                                          | Asks conan to detect what compiler we are using |
| [[#Declaring the conanfile]]                                         | This like setting up the requirements.txt       |
| [[#Installing the packages from conanfile\|Installing the packages]] | Installing the packages for the C++ project     |
|                                                                      |                                                 |

## Conan

> Package Manager for C++

##### Detecting the compiler

- Asks conan to detect what compiler we are using
- This is done so that the packages are built for the compiler used

```bash
conan profile detect --force
```

```
conan profile detect --force
detect_api: Found msvc 17

Detected profile:
[settings]
arch=x86_64
build_type=Release
compiler=msvc
compiler.cppstd=14
compiler.runtime=dynamic
compiler.version=194
os=Windows

WARN: This profile is a guess of your environment, please check it.
WARN: The output of this command is not guaranteed to be stable and can change in future Conan versions.
WARN: Use your own profile files for stability.
Saving detected profile to C:\Users\sreer\.conan2\profiles\default
```

##### Declaring the conanfile

- Declaring the dependencies and how the user want it to be integrated with [[CMakeDeps]] and [[CMakeToolchain]]

```conanfile
# conanfile.txt
[requires]
poco/1.13.0

[generators]
CMakeToolchain
CMakeDeps

```

##### Installing the packages from conanfile

```bash
conan install . --output-folder=build --build=missing
```

| Part                    | What it means                                                                    |
| ----------------------- | -------------------------------------------------------------------------------- |
| `.`                     | Use the current folder (where `conanfile.txt` is) to read dependencies           |
| `--output-folder=build` | Put all generated files (toolchain + CMake configs) inside the `build/` folder   |
| `--build=missing`       | If required binaries (like Poco) aren’t found in cache, build them automatically |

##### Update the conan profile

> [!warning] Conan 2
> In **Conan 2**, we don’t use `conan profile update` — instead, we **manually edit the profile** file.

1. Go to this file from [[#Detecting the compiler]]
   ```bash
   code ~/.conan2/profiles/default
   ```

```

2. Check the contents
```

[settings]
arch=x86_64
build_type=Release
compiler=msvc
compiler.cppstd=14 << delete this
compiler.cppstd=17 << Update this
compiler.runtime=dynamic
compiler.version=194
os=Windows

````


###### Conan 1
```bash
conan profile update settings.compiler.cppstd=17 default
````

<font color="#ff0000">Do not use this, this is for conan 1.x</font>

```
$ conan profile update settings.compiler.cppstd=17 default
usage: conan profile [-h] [-v [V]] [-cc CORE_CONF] [--out-file OUT_FILE] {detect,list,path,show} ...
conan profile: error: argument subcommand: invalid choice: 'update' (choose from detect, list, path, show)
ERROR: Exiting with code: 2
```

Certainly! Here's a comprehensive Markdown table that outlines common CMake scenarios and the recommended commands to use in each case. This should help clarify when to use `add_executable`, `add_library`, `target_include_directories`, and `target_link_libraries`, along with the appropriate usage of `PUBLIC`, `PRIVATE`, and `INTERFACE` scopes.

---

### 📘 CMake Command Usage Guide

| Scenario                                                                                      | Recommended Command(s)                                                                                                       | Explanation                                                                                                                                                                                                |
| --------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Building an application or test program**                                                   | `add_executable()`, `target_link_libraries()`                                                                                | Use `add_executable()` to define the main application or test binary. Then, use `target_link_libraries()` to link against required libraries.                                                              |
| **Creating a reusable library**                                                               | `add_library()`, `target_include_directories()`, `target_link_libraries()`                                                   | Use `add_library()` to define a library target. `target_include_directories()` specifies the include paths, and `target_link_libraries()` links against other libraries.                                   |
| **Linking a target with its dependencies**                                                    | `target_link_libraries()`                                                                                                    | This command specifies which libraries a target should be linked against. It's applicable for both executables and libraries.                                                                              |
| **Setting include directories for a target**                                                  | `target_include_directories()`                                                                                               | Specifies the include directories to use when compiling a given target.                                                                                                                                    |
| **Propagating include directories and link dependencies to targets that depend on a library** | Use `PUBLIC` or `INTERFACE` scope with `target_include_directories()` and `target_link_libraries()`                          | The `PUBLIC` scope applies the settings to the current target and propagates them to targets that link against it. `INTERFACE` applies settings only to consumers of the target, not to the target itself. |
| **Internal dependencies not exposed to consumers**                                            | Use `PRIVATE` scope with `target_include_directories()` and `target_link_libraries()`                                        | The `PRIVATE` scope applies settings only to the current target and does not propagate them to consumers.                                                                                                  |
| **Header-only libraries**                                                                     | `add_library(<name> INTERFACE)`, `target_include_directories()` with `INTERFACE` scope                                       | For header-only libraries, define them as `INTERFACE` libraries and set include directories with the `INTERFACE` scope.                                                                                    |
| **Shared libraries exposing headers that use types from dependencies**                        | `target_link_libraries()` with `PUBLIC` scope                                                                                | If a shared library's public headers use types from a dependency, link that dependency with `PUBLIC` scope so that consumers are aware of it.                                                              |
| **Static libraries with dependencies used only internally**                                   | `target_link_libraries()` with `PRIVATE` scope                                                                               | If a static library uses a dependency only internally and does not expose it in its public interface, link it with `PRIVATE` scope.                                                                        |
| **Executable depending on a library that itself depends on another library**                  | Link the executable to the intermediate library; the intermediate library should link to its dependency with `PUBLIC` scope  | This ensures that the executable indirectly links against all necessary dependencies through the intermediate library.                                                                                     |
| **Executable depending on a library that uses another library only internally**               | Link the executable to the intermediate library; the intermediate library should link to its dependency with `PRIVATE` scope | The executable does not need to be aware of the internal dependencies of the library it links against.                                                                                                     |
| **Library depending on another library but not using it in its own implementation**           | `target_link_libraries()` with `INTERFACE` scope                                                                             | If a library doesn't use a dependency itself but its consumers need it, link the dependency with `INTERFACE` scope.                                                                                        |
| **Executable linking to a library and needing its include directories**                       | `target_include_directories()` with `PRIVATE` scope                                                                          | Since executables are not linked against by other targets, `PRIVATE` scope is sufficient for include directories.                                                                                          |
| **Library exposing headers that include other libraries' headers**                            | `target_include_directories()` and `target_link_libraries()` with `PUBLIC` scope                                             | This ensures that consumers of the library have access to the necessary include directories and linked libraries.                                                                                          |
| **Library using another library only in its implementation**                                  | `target_include_directories()` and `target_link_libraries()` with `PRIVATE` scope                                            | The dependency is used only internally and is not exposed to consumers.                                                                                                                                    |
| **Library not using a dependency but its consumers need it**                                  | `target_include_directories()` and `target_link_libraries()` with `INTERFACE` scope                                          | The library itself doesn't use the dependency, but it ensures that consumers have access to it.                                                                                                            |
| **Creating an alias for a target**                                                            | `add_library(<alias> ALIAS <target>)`                                                                                        | Allows you to create an alternate name for a target, which can be useful for organizing or simplifying target names.                                                                                       |
| **Adding compile definitions to a target**                                                    | `target_compile_definitions()` with appropriate scope (`PRIVATE`, `PUBLIC`, or `INTERFACE`)                                  | Adds preprocessor definitions to a target. The scope determines whether the definitions are applied to the target itself, its consumers, or both.                                                          |
| **Adding compile options to a target**                                                        | `target_compile_options()` with appropriate scope (`PRIVATE`, `PUBLIC`, or `INTERFACE`)                                      | Adds compiler options to a target. The scope determines whether the options are applied to the target itself, its consumers, or both.                                                                      |
| **Specifying C++ standard for a target**                                                      | `target_compile_features()` with appropriate scope (`PRIVATE`, `PUBLIC`, or `INTERFACE`)                                     | Specifies the required C++ standard features for a target. The scope determines whether the requirement is applied to the target itself, its consumers, or both.                                           |
| **Adding source files to a target after its creation**                                        | `target_sources()` with appropriate scope (`PRIVATE`, `PUBLIC`, or `INTERFACE`)                                              | Adds source files to a target. The scope determines whether the sources are used by the target itself, its consumers, or both.                                                                             |
| **Setting properties on a target**                                                            | `set_target_properties()`                                                                                                    | Sets various properties on a target, such as output name, version, or custom commands.                                                                                                                     |
| **Getting properties of a target**                                                            | `get_target_property()`                                                                                                      | Retrieves the value of a property set on a target.                                                                                                                                                         |
| **Installing a target**                                                                       | `install(TARGETS ...)`                                                                                                       | Specifies how to install a target, including its runtime, library, and archive components.                                                                                                                 |
| **Exporting targets for use in other projects**                                               | `install(EXPORT ...)`, `export()`                                                                                            | Allows targets to be exported and imported by other projects, facilitating reuse and modularity.                                                                                                           |
