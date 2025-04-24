| Variable | Initialization Type        | Value | Safe from Garbage? | Allows Narrowing? | Notes                             |
| -------- | -------------------------- | ----- | ------------------ | ----------------- | --------------------------------- |
| `a`      | Default Initialization     | ???   | ❌ No              | ✅ Yes            | Garbage value; avoid using        |
| `b`      | Copy Initialization        | 5     | ✅ Yes             | ✅ Yes            | Common but allows narrowing       |
| `c`      | Direct Initialization      | 6     | ✅ Yes             | ✅ Yes            | Clear intent; common with objects |
| `d`      | Direct List Initialization | 7     | ✅ Yes             | ❌ No             | Modern, safe, no narrowing        |
| `e`      | Value Initialization       | 0     | ✅ Yes             | ❌ No             | Best for default zero-value       |

| **Type**                       | **Description**                                                                              | **Code Example** |
| ------------------------------ | -------------------------------------------------------------------------------------------- | ---------------- |
| **Copy Initialization**        | Initial value provided using `=`. Inherited from C.                                          | `int b = 5;`     |
| **Default Initialization**     | No initializer is provided; value is undefined for fundamental types.                        | `int a;`         |
| **Direct Initialization**      | Value provided in parentheses. Mostly used for objects and constructors.                     | `int c(6);`      |
| **Direct-list Initialization** | Modern form using curly braces; avoids narrowing conversions. Also called list/uniform init. | `int d{7};`      |
| **Value Initialization**       | Empty braces initialize the variable to zero (for fundamental types).                        | `int e{};`       |
