# TradePort Frontend - Design Patterns Analysis

## Introduction

This document provides a comprehensive analysis of the object-oriented design and implementation of the TradePort frontend application, particularly focusing on the Gang of Four (GoF) design patterns utilized throughout the codebase. This analysis aims to defend the implementation choices, explain the object-oriented analysis and design principles applied, and discuss why certain design patterns were selected over others.

## System Overview

TradePort is an e-commerce platform designed to connect retailers and wholesalers, featuring product browsing, cart management, order processing, and user authentication. The application is built using React with TypeScript, Redux for state management, and follows modern frontend architectural principles.

## Object-Oriented Analysis and Design

### Core Classes and Types

The application implements a well-structured object-oriented design with clearly defined types and interfaces:

1. **Product Entity**:

   ```typescript
   type Product = {
     productID: string;
     productCode: string;
     manufacturerID: string;
     productName: string;
     description: string;
     category: string;
     wholesalePrice: number;
     retailPrice: number;
     retailCurrency: string;
     wholeSaleCurrency: string;
     shippingCost: number;
     quantity: number;
     createdOn: string;
     updatedOn: string;
     isActive: boolean;
     productImage: { productImageURL: string }[];
   };
   ```

2. **ShoppingCart Entity**:

   ```typescript
   type ShoppingCart = Product & {
     paymentMode: number;
     CardNumber: string;
     paymentCurrency: string;
     shippingCost: number;
     shippingCurrency: string;
     shippingAddress: string;
     orderQuantity: number;
     productPrice: number;
     totalPrice: number;
     productImage: { productImageURL: string }[];
     cartID: string;
     cartQuantity: number;
   };
   ```

3. **User and Auth Data**:
   ```typescript
   type User = {
     email: string;
     name?: string;
     userID?: string;
     picture?: string;
     role?: "admin" | "retailer" | "manufacturer" | "delivery" | number | null;
     phoneNo?: string;
     address?: string;
     remarks?: string;
     isActive?: boolean;
   };
   ```

## Gang of Four Design Patterns Implementation

The codebase implements several Gang of Four (GoF) design patterns effectively. Below is a detailed analysis of each pattern used:

### 1. Creational Patterns

#### Factory Method Pattern

**Implementation**: The application uses factory-like functions to create and manage API requests.

**Examples**:

- `getPosts()` in `getPost.ts`
- `ShoppingCartPost()` in `shoppingCartPost.ts`

**Benefits**:

- Encapsulates the logic for creating and processing API requests
- Separates the creation logic from the business logic
- Allows for easy modification of request creation process without changing the consumer code

**Code Example**:

```typescript
export async function getPosts(
  productID: string,
  token: string
): Promise<ShoppingCart[]> {
  const apiUrl = ENDPOINTS.PRODUCT.BY_ID(productID);
  const response = await fetch(apiUrl, {
    headers: {
      Authorization: `Bearer ${token}`,
    },
  });
  const data = await response.json();
  assertIsPosts(data.product);

  return data.product;
}
```

#### Singleton Pattern

**Implementation**: Redux store is effectively a singleton that maintains application state.

**Examples**:

- `store.ts` implements a singleton store for the entire application

**Benefits**:

- Ensures a single source of truth for application state
- Provides a global access point to the state
- Controls state modifications through well-defined reducers

**Code Example**:

```typescript
// src/store/store.ts
import { configureStore } from "@reduxjs/toolkit";
import rootReducer from "./rootReducer";

const store = configureStore({
  reducer: rootReducer,
});

export type RootState = ReturnType<typeof store.getState>;
export type AppDispatch = typeof store.dispatch;

export default store;
```

### 2. Structural Patterns

#### Adapter Pattern

**Implementation**: The authentication system uses adapters to convert between external API response formats and the internal user model.

**Examples**:

- `login` reducer in `authSlice.ts` adapts API user data to the internal Redux state format

**Benefits**:

- Makes external API responses compatible with internal data structures
- Isolates the code that needs to change when external APIs change
- Maintains clean interfaces in the application

**Code Example**:

```typescript
login: (
  state,
  action: PayloadAction<{
    token: string;
    user: {
      loginID: string;
      userID: string;
      userName: string;
      role: number;
      // ...other fields
    };
  }>
) => {
  const apiUser = action.payload.user;

  // Convert API response to match Redux state format
  state.isAuthenticated = true;
  state.token = action.payload.token;
  state.user = {
    ...state.user, // Preserve existing details
    email: apiUser.loginID, // Map `loginID` → `email`
    userID: apiUser.userID,
    role: (() => {
      const roleMap: Record<
        number,
        "admin" | "retailer" | "manufacturer" | "delivery" | null
      > = {
        1: "admin",
        2: "retailer",
        3: "manufacturer",
        4: "delivery",
      };
      return roleMap[apiUser.role] || null;
    })(),
    // ...other field mappings
  };
};
```

#### Composite Pattern

**Implementation**: The component hierarchy in React naturally implements the Composite pattern.

**Examples**:

- `App.tsx` composes multiple components to build the application
- `Navbar` composes `NavLinks`, `CartIcon`, `ProfileDropdown`, and `MobileMenu`
- `CatalogGrid` composes filters, `ProductCard`, and `Pagination`

**Benefits**:

- Allows treating individual objects and compositions of objects uniformly
- Enables building complex UIs from simpler components
- Promotes component reusability and separation of concerns

**Code Example**:

```typescript
// Navbar.tsx - Composite component composed of smaller components
const Navbar: React.FC = () => {
  const isAuthenticated = useSelector(
    (state: RootState) => state.auth.isAuthenticated
  );

  return (
    <nav className="sticky top-0 z-50 w-full bg-white shadow-md">
      <div className="mx-auto max-w-7xl px-4 sm:px-6 lg:px-8">
        <div className="flex h-16 items-center justify-between">
          {/* Logo */}
          <div className="flex-shrink-0">
            <Link to="/" className="text-xl font-bold text-gray-800">
              TradePort
            </Link>
          </div>

          {/* Navigation Links */}
          <div className="hidden flex-grow justify-center sm:flex">
            <NavLinks />
          </div>

          {/* Right-side components */}
          <div className="flex items-center space-x-4">
            <CartIcon />
            {isAuthenticated ? (
              <ProfileDropdown />
            ) : (
              <Link to="/login" className="...">
                Log in →
              </Link>
            )}
          </div>

          {/* Mobile Menu */}
          <div className="sm:hidden">
            <MobileMenu />
          </div>
        </div>
      </div>
    </nav>
  );
};
```

#### Decorator Pattern

**Implementation**: The `ProtectedRoute` and `RoleBasedRoute` components decorate the basic routing functionality with additional authentication and authorization checks.

**Examples**:

- `ProtectedRoute.tsx` verifies authentication before rendering routes
- `RoleBasedRoute.tsx` adds role-based access control to routes

**Benefits**:

- Extends the functionality of routes without modifying their core behavior
- Enables adding authorization checks in a modular, composable way
- Separates authorization concerns from component rendering

**Code Example**:

```typescript
// ProtectedRoute.tsx
const ProtectedRoute: React.FC = () => {
  const isLoggedIn = useSelector(
    (state: RootState) => state.auth.isAuthenticated
  );
  const location = useLocation();

  if (!isLoggedIn) {
    return <Navigate to="/login" state={{ from: location }} replace />;
  }

  return <Outlet />;
};

// RoleBasedRoute.tsx
const RoleBasedRoute: React.FC<RoleBasedRouteProps> = ({ allowedRoles }) => {
  const { user, isAuthenticated } = useSelector(
    (state: RootState) => state.auth
  );

  if (!isAuthenticated || !user || !allowedRoles.includes(user.role!)) {
    return <Navigate to="/login" />;
  }

  return <Outlet />;
};
```

### 3. Behavioral Patterns

#### Observer Pattern

**Implementation**: React-Redux implements the Observer pattern through selectors and the `useSelector` hook.

**Examples**:

- Components using `useSelector` automatically re-render when observed state changes
- Redux store serves as the subject that notifies observers (components) of state changes

**Benefits**:

- Decouples state management from UI components
- Enables reactive UI updates based on state changes
- Maintains a unidirectional data flow

**Code Example**:

```typescript
// Component observing auth state
const isAuthenticated = useSelector(
  (state: RootState) => state.auth.isAuthenticated
);

// Component observing cart state
const cart = useSelector((state: RootState) => state.cart.items);
```

#### Command Pattern

**Implementation**: Redux action creators and dispatches implement the Command pattern.

**Examples**:

- Action creators like `addToCart`, `removeFromCart` in `cartSlice.ts`
- Dispatch calls that trigger state changes

**Benefits**:

- Encapsulates state modification requests as objects
- Allows for logging, undoing, and queueing operations
- Separates the concerns of requesting an action and executing it

**Code Example**:

```typescript
// Action creators (Commands)
export const {
  addToCart,
  removeFromCart,
  updateQuantity,
  clearCart,
  increaseQuantity,
} = cartSlice.actions;

// Using dispatch to execute commands
dispatch(addToCart(product));
dispatch(removeFromCart(cartId));
```

#### Strategy Pattern

**Implementation**: The application uses different strategies for handling user roles and route protection.

**Examples**:

- Role-based route protection in `RoleBasedRoute.tsx`
- Different rendering strategies based on authentication state

**Benefits**:

- Encapsulates different algorithms (strategies) for handling various scenarios
- Makes the code more flexible and extensible
- Allows for runtime selection of appropriate strategies

**Code Example**:

```typescript
// Different rendering strategies based on auth state
{isAuthenticated ? (
  <ProfileDropdown />
) : (
  <Link to="/login" className="...">Log in →</Link>
)}

// Role-based strategy in routing
<Route element={<RoleBasedRoute allowedRoles={["retailer"]} />}>
  <Route path="/retailer-dashboard" element={<RetailerDashboard />} />
</Route>

<Route element={<RoleBasedRoute allowedRoles={["wholesaler"]} />}>
  <Route path="/wholesaler-dashboard" element={<WholesalerDashboard />} />
</Route>
```

## Design Patterns Considered But Not Implemented

### Builder Pattern

**Why Considered**: Could have been used for complex object creation, such as form data for creating or updating product listings.

**Why Not Chosen**: React's form libraries (like React Hook Form) and component composition already provide a clean way to build complex objects incrementally. Implementing a dedicated Builder pattern would add unnecessary complexity.

### Chain of Responsibility

**Why Considered**: Could have been used for processing form validations or API request/response middleware.

**Why Not Chosen**: React's component lifecycle, hooks, and existing middleware in Redux provide sufficient capabilities for handling sequential processing. A formal Chain of Responsibility would add overhead without significant benefits.

### State Pattern

**Why Considered**: Could have been used to manage complex UI state transitions.

**Why Not Chosen**: Redux already provides robust state management. Additionally, React's useState and useReducer hooks offer simpler alternatives for component-level state management without the need for a formal State pattern implementation.

### Proxy Pattern

**Why Considered**: Could have been used to add caching or access control to API requests.

**Why Not Chosen**: Modern HTTP libraries like Fetch API and Axios already provide interceptors and middleware capabilities. Additionally, Redux middleware can handle cross-cutting concerns for API requests without implementing a dedicated Proxy pattern.

## Design Decisions Justification

### 1. Redux for State Management

**Decision**: Using Redux for global state management instead of React Context API alone.

**Justification**:

- The application has complex global state needs (authentication, cart, products)
- Redux provides powerful tools for debugging and time-travel (Redux DevTools)
- Redux middleware supports complex async operations
- Redux's immutability pattern ensures predictable state transitions

### 2. Component Composition Over Inheritance

**Decision**: Using composition for UI components rather than class inheritance.

**Justification**:

- Aligns with React's component model and functional approach
- Creates more flexible and reusable components
- Avoids the fragility and limitations of deep inheritance hierarchies
- Makes it easier to refactor and extend the application

### 3. Adapter Pattern for API Integration

**Decision**: Using adapters to convert between API formats and internal data models.

**Justification**:

- Isolates the application from changes in external API contracts
- Creates a clean boundary between the application and external services
- Makes it easier to test components that rely on API data
- Enables gradual API evolution without breaking the UI

### 4. Facade Pattern for API Endpoints

**Decision**: Using a Facade (apiConfig.ts) to centralize API endpoint management.

**Justification**:

- Provides a single point of truth for all API endpoints
- Makes it easier to modify API URLs without changing consumer code
- Encapsulates environment-specific configuration
- Simplifies testing by providing a clear mock point

## Conclusion

The TradePort frontend application demonstrates a thoughtful application of object-oriented design principles and Gang of Four design patterns. The implementation successfully balances several concerns:

1. **Maintainability**: Through clear separation of concerns and encapsulation
2. **Flexibility**: By using composable components and well-defined interfaces
3. **Scalability**: Through architecture that can grow with additional features
4. **Reusability**: With component-based design that encourages code reuse

The design patterns implemented (Factory Method, Singleton, Adapter, Composite, Decorator, Observer, Command, and Strategy) work together to create a robust architecture that addresses the application's unique requirements while maintaining clean, maintainable code.

By consciously choosing which patterns to implement and which to avoid, the application strikes a pragmatic balance between architectural purity and practical considerations, resulting in a codebase that is both elegant and functional.



# TradePort Frontend - Design Patterns Analysis

## Introduction

This document provides a comprehensive analysis of the object-oriented design and implementation of the TradePort frontend application, with a particular focus on the Gang of Four (GoF) design patterns utilized throughout the codebase. For each use case, we examine the design patterns chosen, explain the rationale behind these choices, and discuss why certain design patterns were selected over others.

## System Overview

TradePort is an e-commerce platform designed to connect retailers and wholesalers, featuring product browsing, cart management, order processing, and user authentication. The application is built using React with TypeScript, Redux for state management, and follows modern frontend architectural principles.

## Use Case Analysis and Design Patterns Implementation

### Use Case 1: Login via Google (Multi-role Support)

#### Use Case Summary

| Aspect | Details |
|--------|---------|
| ID | TP-UC-001 |
| Name | Login via Google (Multi-role Support) |
| Description | Allows any user to log in securely using Google OAuth. Upon login, a signed JWT is issued and stored in the frontend Redux store. The token contains user role (retailer, wholesaler, admin), which is used for downstream authorization and dashboard redirection. |
| Actors | Retailer, Wholesaler, Admin |
| Primary Flow | 1. User clicks "Login with Google" <br> 2. Auth0 handles OAuth <br> 3. JWT is returned <br> 4. Token is stored in Redux |
| Alternative Flows | 1. Auth fails → Redirect to login <br> 2. Token missing → Display error <br> 3. Network error → Retry prompt |
| Design Patterns | Singleton Pattern, Factory Method Pattern, Observer Pattern, Command Pattern |
| Status | Done |

#### Design Pattern Implementation

1. **Singleton Pattern**

   **Implementation**: Redux store is implemented as a singleton that maintains global application state.

   **Code Example**:
   ```typescript
   // src/store/store.ts
   import { configureStore } from "@reduxjs/toolkit";
   import rootReducer from "./rootReducer";

   const store = configureStore({
     reducer: rootReducer,
   });

   export type RootState = ReturnType<typeof store.getState>;
   export type AppDispatch = typeof store.dispatch;

   export default store;
   ```

   **Justification**: The Singleton pattern ensures a single point of truth for application state, making it easier to manage authentication state across the application. This pattern was chosen because:
   - It provides centralized state management
   - Ensures consistency across components
   - Prevents duplication of authentication state
   - Simplifies state access through predictable interfaces

2. **Factory Method Pattern**

   **Implementation**: Authentication API calls use factory-like functions to create and process requests.

   **Code Example**:
   ```typescript
   // Example from authentication-related API calls
   export async function validateGoogleUser(token: string): Promise<User> {
     const apiUrl = ENDPOINTS.USER.VALIDATE_GOOGLE;
     const response = await fetch(apiUrl, {
       method: 'POST',
       headers: {
         'Content-Type': 'application/json',
       },
       body: JSON.stringify({ token }),
     });
     
     if (!response.ok) {
       throw new Error('Authentication failed');
     }
     
     const userData = await response.json();
     return userData;
   }
   ```

   **Justification**: The Factory Method pattern encapsulates the creation of API requests, making the authentication flow more maintainable. This pattern was chosen because:
   - It abstracts away the complexity of API communication
   - Creates clean separation between request creation and request handling
   - Allows for easier testing through mocking
   - Provides flexibility to change the implementation details without affecting consumers

3. **Observer Pattern**

   **Implementation**: React-Redux implements the Observer pattern through the use of selectors and the `useSelector` hook.

   **Code Example**:
   ```typescript
   // Component observing auth state
   const isAuthenticated = useSelector(
     (state: RootState) => state.auth.isAuthenticated
   );
   
   // Using auth state for conditional rendering
   {isAuthenticated ? (
     <ProfileDropdown />
   ) : (
     <Link to="/login">Log in →</Link>
   )}
   ```

   **Justification**: The Observer pattern allows components to react to authentication state changes without tight coupling. This pattern was chosen because:
   - It enables reactive UI updates when auth state changes
   - Decouples state management from UI components
   - Maintains a unidirectional data flow
   - Improves component reusability

4. **Command Pattern**

   **Implementation**: Redux action creators and dispatches implement the Command pattern.

   **Code Example**:
   ```typescript
   // Auth slice action creators (Commands)
   export const { login, logout, setUserDetails } = authSlice.actions;
   
   // Using dispatch to execute commands
   dispatch(login({ token, user }));
   dispatch(logout());
   ```

   **Justification**: The Command pattern encapsulates authentication operations as objects, making them easier to manage and track. This pattern was chosen because:
   - It standardizes authentication operations
   - Enables logging and debugging of authentication actions
   - Separates the concerns of requesting an auth action and executing it
   - Allows for centralized handling of authentication state

#### Design Patterns Considered But Not Implemented

1. **Strategy Pattern**
   - **Why Considered**: Could have been used to implement different authentication strategies (Google, email/password, etc.)
   - **Why Not Chosen**: The current application only needed Google authentication, making the added complexity of a Strategy pattern unnecessary. If additional auth methods are added later, refactoring to a Strategy pattern would be appropriate.

2. **Adapter Pattern**
   - **Why Considered**: Could have adapted between different authentication provider responses
   - **Why Not Chosen**: Using Google as the sole provider meant adaptation complexity wasn't necessary. The simple mapping in the reducer was sufficient.

### Use Case 2: Check Registration Status

#### Use Case Summary

| Aspect | Details |
|--------|---------|
| ID | TP-UC-002 |
| Name | Check Registration Status |
| Description | Checks whether a logged-in user has completed their registration based on the presence of a user record in the backend. This determines whether the user should be redirected to complete their profile or to their role-specific dashboard. |
| Actors | Frontend App |
| Primary Flow | 1. Frontend sends JWT to backend <br> 2. Backend validates the JWT <br> 3. Backend queries the user table based on `sub` or `email` claim <br> 4. If user exists, returns `registered: true` <br> 5. If user does not exist, returns `registered: false` |
| Alternative Flows | 1. JWT is invalid <br> 2. Backend returns 401 unauthorized <br> 3. Backend error <br> 4. Frontend shows generic error or retry message |
| Design Patterns | Observer Pattern, Command Pattern, Singleton Pattern |
| Status | Done |

#### Design Pattern Implementation

1. **Observer Pattern**

   **Implementation**: React components observe the registration status through Redux state.

   **Code Example**:
   ```typescript
   // Component monitoring registration status
   const isRegistered = useSelector((state: RootState) => state.auth.isRegistered);
   
   // Conditional rendering based on registration status
   useEffect(() => {
     if (isAuthenticated) {
       if (!isRegistered) {
         navigate('/register');
       } else {
         navigate('/dashboard');
       }
     }
   }, [isAuthenticated, isRegistered, navigate]);
   ```

   **Justification**: The Observer pattern enables reactive navigation based on registration status. This pattern was chosen because:
   - It allows components to react to registration status changes
   - Enables automatic redirection to the appropriate page
   - Keeps UI components decoupled from authentication logic
   - Makes the registration flow testable and maintainable

2. **Command Pattern**

   **Implementation**: Redux actions for registration status updates implement the Command pattern.

   **Code Example**:
   ```typescript
   // Registration-related action creators
   export const { register } = authSlice.actions;
   
   // Reducer handling registration command
   register: (
     state,
     action: PayloadAction<{
       email: string;
       role?: "admin" | "retailer" | "manufacturer" | "delivery" | number | null;
     }>,
   ) => {
     state.isRegistered = true;
     state.user = {
       ...state.user,
       email: action.payload.email,
       role: action.payload.role,
     };
   },
   ```

   **Justification**: The Command pattern encapsulates registration operations, making state transitions explicit and traceable. This pattern was chosen because:
   - It makes registration state changes explicit and atomic
   - Provides a clear record of registration actions
   - Centralizes registration logic in a single place
   - Simplifies testing of registration flows

3. **Singleton Pattern**

   **Implementation**: Redux store acts as a singleton for application state including registration status.

   **Justification**: The Singleton pattern ensures consistent access to registration state throughout the application. This pattern was chosen because:
   - It provides a single source of truth for registration status
   - Prevents inconsistent states across components
   - Simplifies state management in a complex registration flow
   - Makes registration status globally accessible where needed

#### Design Patterns Considered But Not Implemented

1. **State Pattern**
   - **Why Considered**: Could have modeled the user registration process with explicit states
   - **Why Not Chosen**: The registration process was simple enough (registered/not registered) that a full State pattern implementation would have added unnecessary complexity.

2. **Memento Pattern**
   - **Why Considered**: Could have been used to save and restore registration progress
   - **Why Not Chosen**: The registration process was designed to be completed in one step, making the Memento pattern unnecessarily complex for this use case.

### Use Case 3: Browse Product Catalog

#### Use Case Summary

| Aspect | Details |
|--------|---------|
| ID | TP-UC-003 |
| Name | Browse Product Catalog |
| Description | Allows users to view and filter a catalog of available products by category, price range, and other attributes. |
| Actors | Retailer, Wholesaler, Guest User |
| Primary Flow | 1. User navigates to catalog page <br> 2. System loads and displays product listings <br> 3. User applies filters (category, price range, etc.) <br> 4. System updates displayed products based on filters |
| Alternative Flows | 1. No products match filters → Show empty state with message <br> 2. API error → Show error state with retry option |
| Design Patterns | Composite Pattern, Strategy Pattern, Factory Method Pattern |
| Status | Done |

#### Design Pattern Implementation

1. **Composite Pattern**

   **Implementation**: The catalog view uses component composition to build the UI from smaller, reusable components.

   **Code Example**:
   ```typescript
   // CatalogGrid.tsx - Composite component structure
   const CatalogGrid: React.FC = () => {
     // ...state and handlers...
     
     return (
       <div className="mx-auto max-w-7xl px-4 py-12">
         <div className="mb-4 flex flex-col items-center justify-between space-y-4 md:flex-row md:space-x-4 md:space-y-0">
           <SearchBar
             searchText={searchText}
             onSearchChange={handleSearchChange}
           />
           <div className="flex flex-col items-center space-y-4 md:flex-row md:space-x-4 md:space-y-0">
             <CategorySelect
               categories={categories}
               selectedCategory={selectedCategory}
               onChange={handleCategoryChange}
             />
             <CategorySelect
               categories={quantities}
               selectedCategory={selectedQuantity}
               onChange={handleQuantityChange}
             />
             <PriceRangeSelect
               priceRanges={priceRanges}
               selectedPrice={selectedPrice}
               onChange={handleWholesalePriceRangeChange}
             />
             <PriceRangeSelect
               priceRanges={retailPriceRanges}
               selectedPrice={selectedRetailPrice}
               onChange={handleRetailPriceRangeChange}
             />
           </div>
         </div>
         {products.length > 0 ? (
           <div className="grid grid-cols-1 gap-6 sm:grid-cols-2 md:grid-cols-3 lg:grid-cols-4">
             {products.map((product) => (
               <ProductCard key={product.productID} {...product} />
             ))}
           </div>
         ) : (
           <div>No products found. Adjust your filters.</div>
         )}
         <div className="mt-4 flex justify-center">
           <Pagination
             pageNumber={pageNumber}
             totalPages={totalPages}
             onPageChange={handlePageChange}
           />
         </div>
       </div>
     );
   };
   ```

   **Justification**: The Composite pattern allows building complex UIs from simpler components. This pattern was chosen because:
   - It creates a clear hierarchy of UI components
   - Enables reuse of components (like `CategorySelect` used multiple times)
   - Makes the catalog view maintainable and extensible
   - Provides a clean separation of concerns between different UI elements

2. **Strategy Pattern**

   **Implementation**: Different filtering strategies are employed based on user selections.

   **Code Example**:
   ```typescript
   // Strategies for filtering products by price range
   const getWholesalePriceRange = (label: string) => {
     return (
       priceRanges.find((price) => price.label === label) || {
         min: 0,
         max: 1000000,
       }
     );
   };

   const getRetailPriceRange = (label: string) => {
     return (
       retailPriceRanges.find((price) => price.label === label) || {
         min: 0,
         max: 1000000,
       }
     );
   };
   
   // Using selected strategies in API query
   const fetchProducts = async () => {
     try {
       const wholesaleRange = getWholesalePriceRange(selectedPrice);
       const retailRange = getRetailPriceRange(selectedRetailPrice);
       const categoryQuery = selectedCategory !== 0 ? `&category=${selectedCategory}` : " ";
       
       const queryParams = `?pageNumber=${pageNumber}&searchText=${searchText}${categoryQuery}&quantity=${selectedQuantity}&minWholesalePrice=${wholesaleRange.min}&maxWholesalePrice=${wholesaleRange.max}&minRetailPrice=${retailRange.min}&maxRetailPrice=${retailRange.max}`;
       
       // Fetch with constructed query
       // ...
     } catch (error) {
       // ...
     }
   };
   ```

   **Justification**: The Strategy pattern allows selecting different filtering algorithms at runtime. This pattern was chosen because:
   - It encapsulates different filtering strategies (price range, category, quantity)
   - Makes it easy to add new filtering criteria
   - Keeps filtering logic separate from UI components
   - Provides a clean way to translate UI selections into API parameters

3. **Factory Method Pattern**

   **Implementation**: API request creation is encapsulated in factory-like functions.

   **Code Example**:
   ```typescript
   // Creation of API URL from configuration
   const fetchProducts = async () => {
     try {
       // ... parameters construction ...
       
       const response = await fetch(
         ENDPOINTS.PRODUCT.FILTERED(queryParams),
         {
           headers: {
             'Authorization': `Bearer ${token}`,
           },
         }
       );
       const data = await response.json();
       setProducts(data.product || []);
       setTotalPages(data.totalPages || 1);
     } catch (error) {
       console.error("Error fetching products:", error);
       setProducts([]);
     }
   };
   ```

   **Justification**: The Factory Method pattern encapsulates the creation of API requests. This pattern was chosen because:
   - It centralizes the logic for creating and executing product API requests
   - Handles the complexity of parameter construction
   - Makes testing easier through mocking
   - Decouples the UI from API implementation details

#### Design Patterns Considered But Not Implemented

1. **Decorator Pattern**
   - **Why Considered**: Could have been used to add additional filtering behavior dynamically
   - **Why Not Chosen**: The filtering requirements were fixed, making the simpler Strategy pattern sufficient. Decorators would have added unnecessary complexity.

2. **Bridge Pattern**
   - **Why Considered**: Could separate filtering abstraction from implementation
   - **Why Not Chosen**: The current filtering implementation wasn't complex enough to warrant the additional abstraction of a Bridge pattern.

### Use Case 4: Product Detail and Add to Cart

#### Use Case Summary

| Aspect | Details |
|--------|---------|
| ID | TP-UC-004 |
| Name | Product Detail and Add to Cart |
| Description | Displays detailed information about a product and allows users to add it to their shopping cart with specified quantities. |
| Actors | Retailer, Guest User |
| Primary Flow | 1. User selects a product from catalog <br> 2. System displays detailed product information <br> 3. User selects quantity <br> 4. User clicks "Add to Cart" <br> 5. System adds item to cart and confirms |
| Alternative Flows | 1. Product out of stock → Display unavailable message <br> 2. User not logged in → Prompt login or continue as guest <br> 3. API error → Show error with retry option |
| Design Patterns | Factory Method Pattern, Command Pattern, Observer Pattern |
| Status | Done |

#### Design Pattern Implementation

1. **Factory Method Pattern**

   **Implementation**: Product data fetching is encapsulated in factory-like functions.

   **Code Example**:
   ```typescript
   // getPosts.ts
   export async function getPosts(productID: string, token: string): Promise<ShoppingCart[]> {
     const apiUrl = ENDPOINTS.PRODUCT.BY_ID(productID);
     const response = await fetch(apiUrl, {
       headers: {
         'Authorization': `Bearer ${token}`,
       },
     });
     const data = await response.json();
     assertIsPosts(data.product);
     
     return data.product;
   }
   ```

   **Justification**: The Factory Method pattern creates a clean interface for retrieving product data. This pattern was chosen because:
   - It encapsulates the complexity of API communication
   - Handles data validation (through `assertIsPosts`)
   - Provides a reusable method for product data retrieval
   - Decouples data fetching from UI components

2. **Command Pattern**

   **Implementation**: Adding to cart is implemented as dispatching command objects to Redux.

   **Code Example**:
   ```typescript
   // Cart slice with add to cart command
   const cartSlice = createSlice({
     name: "cart",
     initialState,
     reducers: {
       addToCart: (state, action: PayloadAction<ShoppingCart>) => {
         const existingItem = state.items.find(
           (item) => item.cartID === action.payload.cartID,
         );
         if (existingItem) {
           //existingItem.quantity += 1;
         } else {
           state.items.push({ ...action.payload, cartQuantity: 1 });
         }
       },
       // Other cart commands...
     },
   });
   
   // Using the command in component
   const onSubmit = async (order: ShoppingCart): Promise<void> => {
     // ... prepare order ...
     try {
       const body = await ShoppingCartPost(order, token);
       navigate(`/Cart`);
     } catch (error) {
       console.error("Error saving post:", error);
     }
   };
   ```

   **Justification**: The Command pattern encapsulates cart operations as distinct actions. This pattern was chosen because:
   - It makes cart operations explicit and reusable
   - Enables tracking of cart modifications
   - Provides a clear interface for cart state changes
   - Allows for potential undo/redo functionality in the future

3. **Observer Pattern**

   **Implementation**: UI components observe cart state and update accordingly.

   **Code Example**:
   ```typescript
   // Cart state observation in components
   const cart = useSelector((state: RootState) => state.cart.items);
   
   // Display cart count
   const cartCount = cart.length;
   ```

   **Justification**: The Observer pattern allows UI components to react to cart changes. This pattern was chosen because:
   - It enables automatic UI updates when cart state changes
   - Decouples cart state management from display logic
   - Ensures consistent cart information across components
   - Makes cart functionality more maintainable

#### Design Patterns Considered But Not Implemented

1. **Memento Pattern**
   - **Why Considered**: Could have stored cart state history for undo functionality
   - **Why Not Chosen**: Cart operations were straightforward and immediate, making the complexity of maintaining cart history unnecessary. Redux DevTools already provides time-travel debugging if needed.

2. **Chain of Responsibility Pattern**
   - **Why Considered**: Could have processed cart additions through multiple handlers
   - **Why Not Chosen**: The processing requirements for cart operations were simple and direct, making a chain unnecessary. The Redux reducer pattern already provided sufficient structure.

### Use Case 5: User Role-Based Access Control

#### Use Case Summary

| Aspect | Details |
|--------|---------|
| ID | TP-UC-005 |
| Name | User Role-Based Access Control |
| Description | Ensures users can only access parts of the application appropriate for their role (retailer, wholesaler, admin). |
| Actors | Retailer, Wholesaler, Admin |
| Primary Flow | 1. User attempts to access a protected route <br> 2. System checks user's authentication status <br> 3. System checks user's role <br> 4. If role has access, render protected content <br> 5. If role lacks access, redirect to unauthorized page |
| Alternative Flows | 1. User not authenticated → Redirect to login <br> 2. User role not specified → Deny access <br> 3. Token expired → Force re-login |
| Design Patterns | Decorator Pattern, Strategy Pattern |
| Status | Done |

#### Design Pattern Implementation

1. **Decorator Pattern**

   **Implementation**: Route components are decorated with authentication and authorization checks.

   **Code Example**:
   ```typescript
   // ProtectedRoute.tsx - Decorator for authentication
   const ProtectedRoute: React.FC = () => {
     const isLoggedIn = useSelector(
       (state: RootState) => state.auth.isAuthenticated,
     );
     const location = useLocation();
   
     if (!isLoggedIn) {
       return <Navigate to="/login" state={{ from: location }} replace />;
     }
   
     return <Outlet />;
   };
   
   // RoleBasedRoute.tsx - Decorator for authorization
   const RoleBasedRoute: React.FC<RoleBasedRouteProps> = ({ allowedRoles }) => {
     const { user, isAuthenticated } = useSelector(
       (state: RootState) => state.auth,
     );
   
     if (!isAuthenticated || !user || !allowedRoles.includes(user.role!)) {
       return <Navigate to="/login" />;
     }
   
     return <Outlet />;
   };
   
   // Usage in App.tsx
   <Route element={<ProtectedRoute />}>   
     <Route path="/profile" element={<Profile />} />
     <Route path="/thank-you" element={<ThankYouPage />} />
     <Route path="/orders" element={<Orders />} />
   </Route>
   
   <Route element={<RoleBasedRoute allowedRoles={["retailer"]} />}>
     <Route path="/retailer-dashboard" element={<RetailerDashboard />} />
   </Route>
   ```

   **Justification**: The Decorator pattern adds authentication and authorization behavior to routes without modifying them directly. This pattern was chosen because:
   - It cleanly separates authentication logic from route definition
   - Makes route protection reusable across multiple routes
   - Allows for different types of protection (authentication vs. role-based)
   - Enables composition of multiple protection layers

2. **Strategy Pattern**

   **Implementation**: Different route protection strategies based on role requirements.

   **Code Example**:
   ```typescript
   // Different protection strategies based on role
   <Route element={<RoleBasedRoute allowedRoles={["retailer"]} />}>
     <Route path="/retailer-dashboard" element={<RetailerDashboard />} />
   </Route>

   <Route element={<RoleBasedRoute allowedRoles={["wholesaler"]} />}>
     <Route path="/wholesaler-dashboard" element={<WholesalerDashboard />} />
   </Route>
   ```

   **Justification**: The Strategy pattern allows selecting different authorization strategies based on route requirements. This pattern was chosen because:
   - It makes role requirements explicit for each route
   - Enables easy modification of role requirements
   - Keeps route protection logic consistent
   - Makes adding new roles or changing requirements straightforward

#### Design Patterns Considered But Not Implemented

1. **Proxy Pattern**
   - **Why Considered**: Could have acted as a gatekeeper for protected routes
   - **Why Not Chosen**: The combination of Decorator and Strategy patterns already provided sufficient protection without the additional complexity of a proxy.

2. **Chain of Responsibility Pattern**
   - **Why Considered**: Could have processed authentication through a series of handlers
   - **Why Not Chosen**: The authentication and authorization checks were simple enough that a chain wasn't necessary. The clear separation of authentication and role checking was sufficient.

### Use Case 6: Shopping Cart Management

#### Use Case Summary

| Aspect | Details |
|--------|---------|
| ID | TP-UC-006 |
| Name | Shopping Cart Management |
| Description | Allows users to view, update quantities, and remove items from their shopping cart. |
| Actors | Retailer, Guest User |
| Primary Flow | 1. User navigates to shopping cart <br> 2. System displays cart items with quantities and prices <br> 3. User modifies quantities or removes items <br> 4. System updates totals <br> 5. User proceeds to checkout |
| Alternative Flows | 1. Cart is empty → Display empty cart message <br> 2. Item out of stock → Notify user and disable checkout <br> 3. API error → Show error with retry option |
| Design Patterns | Command Pattern, Observer Pattern, Factory Method Pattern |
| Status | Done |

#### Design Pattern Implementation

1. **Command Pattern**

   **Implementation**: Cart operations are implemented as Redux actions.

   **Code Example**:
   ```typescript
   // cartSlice.ts
   const cartSlice = createSlice({
     name: "cart",
     initialState,
     reducers: {
       addToCart: (state, action: PayloadAction<ShoppingCart>) => {
         // ... implementation ...
       },
       removeFromCart: (state, action: PayloadAction<string>) => {
         state.items = state.items.filter(
           (item) => item.cartID !== action.payload,
         );
       },
       increaseQuantity: (state, action: PayloadAction<string>) => {
         const existingItem = state.items.find(
           (item) => item.cartID === action.payload,
         );
         if (existingItem) {
           existingItem.cartQuantity += 1;
         }
       },
       updateQuantity: (
         state,
         action: PayloadAction<{ productId: string; quantity: number }>,
       ) => {
         const existingItem = state.items.find(
           (item) => item.cartID === action.payload.productId,
         );
         if (existingItem) {
           existingItem.cartQuantity = action.payload.quantity;
         }
       },
       clearCart: (state) => {
         state.items = [];
       },
     },
   });
   ```

   **Justification**: The Command pattern encapsulates cart operations, making them explicit and traceable. This pattern was chosen because:
   - It standardizes cart operations into discrete, reusable actions
   - Makes cart state transitions explicit and traceable
   - Enables potential features like undo/redo
   - Centralizes cart logic for easier maintenance

2. **Observer Pattern**

   **Implementation**: Components observe cart state to display updated information.

   **Code Example**:
   ```typescript
   // Cart component observing state
   const cartItems = useSelector((state: RootState) => state.cart.items);
   const dispatch = useDispatch();
   
   // Calculate totals based on observed state
   const calculateTotal = () => {
     return cartItems.reduce((total, item) => {
       return total + (item.wholesalePrice * item.cartQuantity);
     }, 0);
   };
   
   // Handle quantity updates
   const handleQuantityChange = (productId: string, quantity: number) => {
     dispatch(updateQuantity({ productId, quantity }));
   };
   ```

   **Justification**: The Observer pattern allows components to react to cart changes. This pattern was chosen because:
   - It ensures cart UI stays synchronized with cart state
   - Enables automatic recalculation of totals when items change
   - Decouples cart display from cart state management
   - Makes the cart UI responsive to user changes

3. **Factory Method Pattern**

   **Implementation**: Cart API requests use factory methods for creation.

   **Code Example**:
   ```typescript
   // shoppingCartPost.ts
   export async function ShoppingCartPost(newPostData: ShoppingCart, token: string) {
     try {
       const payload = {      
         productID: newPostData.productID,
         retailerID: newPostData.retailerID,
         manufacturerID: newPostData.manufacturerID,
         orderQuantity: newPostData.orderQuantity,
         productPrice: newPostData.wholesalePrice,                
       };
   
       const response = await fetch(apiUrl, {
         method: 'POST',
         headers: { 
           'Content-Type': 'application/json',
           'Authorization': `Bearer ${token}`,
         },
         body: JSON.stringify(payload),
       });
   
       if (!response.ok) {
         throw new Error('Failed to save post');
       }
   
       const body = await response.json();
       return body;
     } catch (error) {
       // Error handling
     }
   }
   ```

   **Justification**: The Factory Method pattern creates cart-related API requests in a standardized way. This pattern was chosen because:
   - It encapsulates the creation of cart API requests
   - Handles the transformation between cart state and API payloads
   - Makes testing easier through mocking
   - Provides a clean interface for cart operations

#### Design Patterns Considered But Not Implemented

1. **Memento Pattern**
   - **Why Considered**: Could have provided cart state history for undo capability
   - **Why Not Chosen**: Cart operations were straightforward with immediate feedback, making history tracking unnecessary complexity.

2. **Composite Pattern**
   - **Why Considered**: Could have modeled complex cart structures (items with bundles, etc.)
   - **Why Not Chosen**: The cart item structure was simple and flat, not requiring hierarchical representation that a Composite would provide.

### Use Case 7: Continuous Integration and Deployment

#### Use Case Summary

| Aspect | Details |
|--------|---------|
| ID | TP-UC-007 |
| Name | Continuous Integration and Deployment |
| Description | Automated CI/CD pipeline for the TradePort application. When code is pushed to GitHub, the pipeline runs tests, security scans, builds Docker images, pushes them to Docker Hub, and deploys to a staging server. |
| Actors | Developer |
| Primary Flow | 1. Developer pushes code to GitHub <br> 2. GitHub Actions triggers CI workflow <br> 3. Tests and linter checks run <br> 4. Security scans execute <br> 5. Docker images build and scan <br> 6. Images push to Docker Hub <br> 7. Deployment occurs via Ansible <br> 8. DAST scan verifies deployment <br> 9. Developer confirms via staging URL |
| Alternative Flows | 1. Tests fail → Build stops, developer notified <br> 2. Security scan fails → Alerts raised <br> 3. Deployment fails → Logs pushed to GitHub <br> 4. DAST finds vulnerabilities → Warnings logged |
| Design Patterns | Builder Pattern, Strategy Pattern, Observer Pattern |
| Status | TODO |

#### Design Pattern Implementation

1. **Builder Pattern**

   **Implementation**: CI/CD pipeline uses builders to construct Docker images and deployment artifacts.

   **Code Example**:
   ```yaml
   # .github/workflows/ci.yml (simplified)
   jobs:
     build:
       runs-on: ubuntu-latest
       steps:
         - uses: actions/checkout@v2
         
         - name: Set up Node.js
           uses: actions/setup-node@v1
           with:
             node-version: '16'
             
         - name: Install dependencies
           run: npm ci
           
         - name: Run tests
           run: npm test
           
         - name: Build Docker image
           run: |
             docker build -t tradeport-frontend:${GITHUB_SHA::7} .
             docker tag tradeport-frontend:${GITHUB_SHA::7} tradeport-frontend:latest
   ```

   **Justification**: The Builder pattern constructs complex objects (Docker images, deployments) step by step. This pattern was chosen because:
   - It breaks down the complex build process into manageable steps
   - Allows for incremental construction of deployment artifacts
   - Makes the build process reproducible and consistent
   - Enables different build configurations for different environments

2. **Strategy Pattern**

   **Implementation**: Different deployment strategies based on the target environment.

   **Code Example**:
   ```yaml
   # Different deployment strategies
   deploy-staging:
     needs: build
     runs-on: ubuntu-latest
     steps:
       # Staging-specific deployment steps
       
   deploy-production:
     needs: [build, deploy-staging]
     if: github.ref == 'refs/heads/main'
     runs-on: ubuntu-latest
     steps:
       # Production-specific deployment steps with additional safeguards
   ```

   **Justification**: The Strategy pattern selects different deployment approaches based on context. This pattern was chosen because:
   - It isolates environment-specific deployment logic
   - Allows for different deployment requirements per environment
   - Makes it easy to add new deployment targets
   - Ensures consistent deployment processes

3. **Observer Pattern**

   **Implementation**: CI/CD process observes code changes and repository events.

   **Code Example**:
   ```yaml
   # GitHub Actions workflow trigger configuration
   on:
     push:
       branches: [main, develop]
     pull_request:
       branches: [main]
   ```

   **Justification**: The Observer pattern allows the CI/CD system to react to code changes. This pattern was chosen because:
   - It enables automated responses to developer actions
   - Makes the CI/CD process event-driven and reactive
   - Decouples development workflow from deployment logic
   - Provides automatic feedback to developers

#### Design Patterns Considered But Not Implemented

1. **Chain of Responsibility Pattern**
   - **Why Considered**: Could have chained deployment validation checks
   - **Why Not Chosen**: GitHub Actions' workflow structure already provides a sequential execution model that satisfied the requirements without adding the complexity of an explicit chain.

2. **Factory Method Pattern**
   - **Why Considered**: Could have created specialized deployment scripts
   - **Why Not Chosen**: The deployment process was straightforward enough that the Builder pattern combined with Strategy was sufficient, making a dedicated Factory unnecessary.

## Overall Design Pattern Analysis

### Dominant Patterns Used Across Use Cases

1. **Observer Pattern**
   - **Frequency**: Used in 5 use cases
   - **Key Benefits**: Enables reactive UI updates, maintains consistency between state and display, decouples components from state management
   - **Implementation**: Primarily through React-Redux's `useSelector` hook and Redux store subscriptions

2. **Command Pattern**
   - **Frequency**: Used in 4 use cases
   - **Key Benefits**: Encapsulates operations as objects, enables tracking and debugging, centralizes state transition logic
   - **Implementation**: Through Redux action creators and dispatch calls

3. **Factory Method Pattern**
   - **Frequency**: Used in 4 use cases
   - **Key Benefits**: Encapsulates object creation, standardizes API communication, simplifies testing
   - **Implementation**: Through API request creation functions and configuration-based endpoint factories

4. **Singleton Pattern**
   - **Frequency**: Used in 3 use cases
   - **Key Benefits**: Ensures single source of truth, provides global access to state, controls state modification
   - **Implementation**: Through Redux store as a global singleton

5. **Strategy Pattern**
   - **Frequency**: Used in 3 use cases
   - **Key Benefits**: Encapsulates different algorithms, allows runtime algorithm selection, keeps behaviors separate from context
   - **Implementation**: Through filter strategies, role-based access strategies, and deployment strategies

### Patterns Considered But Not Prioritized

1. **Proxy Pattern**
   - **Why Not Prioritized**: Most access control needs were well-served by the Decorator pattern combined with Redux state management. Adding Proxy would have introduced unnecessary indirection.

2. **Memento Pattern**
   - **Why Not Prioritized**: State history tracking was handled adequately by Redux DevTools for debugging purposes. Full Memento implementation would have added complexity without sufficient benefit.

3. **Chain of Responsibility Pattern**
   - **Why Not Prioritized**: Most processes in the application had straightforward, non-branching flows that didn't require the complexity of a handling chain.

4. **Bridge Pattern**
   - **Why Not Prioritized**: The abstractions and implementations in the application weren't complex enough to justify the separation that Bridge provides.

## Conclusion

The TradePort frontend application demonstrates a thoughtful application of object-oriented design principles and Gang of Four design patterns. The implementation successfully balances several concerns:

1. **Maintainability**: Through clear separation of concerns and encapsulation
2. **Flexibility**: By using composable components and well-defined interfaces
3. **Scalability**: Through architecture that can grow with additional features
4. **Reusability**: With component-based design that encourages code reuse

The most valuable patterns in this implementation have been:

1. **Observer Pattern**: Enabling reactive UI updates based on state changes
2. **Command Pattern**: Encapsulating operations for clean state management
3. **Factory Method Pattern**: Standardizing object creation, especially for API requests
4. **Composite Pattern**: Building complex UIs from simpler components
5. **Decorator Pattern**: Adding behavior to routes without modifying them directly

By consciously choosing which patterns to implement and which to avoid, the application strikes a pragmatic balance between architectural purity and practical considerations, resulting in a codebase that is both elegant and functional.
