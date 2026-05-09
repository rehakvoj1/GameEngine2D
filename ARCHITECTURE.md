# GE2D Architecture

## Philosophy

GE2D is designed as a modern modular C++ 2D engine focused on:

- explicit ownership
- modular runtime composition
- minimal hidden state
- renderer abstraction
- scalable runtime architecture
- editor/runtime separation
- long-term maintainability

The engine architecture intentionally avoids:

- heavy singleton usage
- implicit global state
- hidden dependency graphs
- over-abstracted systems
- premature plugin complexity

---

# High-Level Architecture

```text
Applications/
    Sandbox/
    Editor/
    Game/

Engine/
    Core/
    Renderer/
    ECS/
    Scene/
    Asset/
    Platform/
```

Applications are built as independent executables.

The engine owns:

- runtime lifecycle
- main loop
- renderer backend
- ECS runtime
- module initialization
- frame coordination

Applications own:

- startup composition
- runtime configuration
- module selection
- gameplay/editor layers

---

# Architectural Principles

## 1. Explicit Ownership

Ownership must always be visible.

Bad:

```cpp
Renderer::Get()
Application::Get()
Runtime::GetAssets()
```

Good:

```cpp
SpriteSystem(Renderer2D& renderer, ECSWorld& world)
```

Dependencies are passed explicitly.

---

## 2. Runtime Is NOT a Service Locator

Runtime is only:

- orchestration layer
- lifecycle coordinator
- frame execution manager

Runtime must NOT become:

- global dependency container
- universal registry
- singleton replacement

---

## 3. Composition Root Per Application

Every executable has its own:

```cpp
int main()
```

The executable composes:

- runtime config
- modules
- application instance

Example:

```cpp
int main()
{
    Runtime runtime(config);

    runtime.RegisterModule<RendererModule>();
    runtime.RegisterModule<ECSModule>();

    SandboxApp app;

    runtime.Run(app);
}
```

---

## 4. Modules Should Be Independent

Modules should expose:

- minimal APIs
- explicit dependencies
- isolated responsibilities

Avoid:

- cyclic dependencies
- hidden cross-module coupling
- runtime-wide access patterns

---

## 5. Keep Runtime Simple

Avoid creating systems before they are needed.

GE2D intentionally prefers:

- straightforward ownership
- explicit initialization
- simple execution flow

Over:

- reflection-heavy systems
- automatic dependency graphs
- complex plugin infrastructures

---

# Runtime Ownership Model

```text
Runtime
    owns Window
    owns RendererBackend
    owns Main ECS World
    owns Main Loop
    owns Module Lifecycle
```

Systems receive only the dependencies they require.

Example:

```cpp
class PhysicsSystem
{
public:
    PhysicsSystem(ECSWorld& world, JobSystem& jobs);
};
```

NOT:

```cpp
PhysicsSystem(Runtime& runtime)
```

---

# Layer Philosophy

Layers are intended for:

- editor tooling
- overlays
- debug UI
- app-level separation

Layers are NOT the primary gameplay architecture.

Core gameplay logic should evolve toward:

- ECS systems
- scene systems
- explicit world simulation

---

# Dependency Rules

Low-level systems:

```text
Window
Renderer
Input
```

Must not depend on:

```text
Gameplay
Editor
Scene tools
```

Higher-level systems may depend downward.

Lower-level systems must never depend upward.

---

# DLL Philosophy

GE2D is designed to be DLL-safe long-term.

However:

Early-stage development should prefer static libraries until:

- module boundaries stabilize
- runtime architecture matures
- hot reload becomes necessary

Avoid unstable ABI exposure.

Be careful with:

```cpp
std::string
std::vector
exceptions
RTTI
```

Across module boundaries.

---

# Long-Term Goals

GE2D architecture should eventually support:

- editor/runtime separation
- hot reload
- modular renderer backends
- dedicated server runtime
- tooling applications
- plugin-capable systems

Without requiring fundamental rewrites.