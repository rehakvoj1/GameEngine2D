# GE2D Engineering Guidelines

## General Philosophy

GE2D prioritizes:

- clarity
- explicit ownership
- maintainability
- scalability
- low hidden complexity

Avoid clever architecture unless justified.

Prefer understandable systems over abstract systems.

---

# Coding Philosophy

## Prefer Explicit Code

Bad:

```cpp
auto x = CreateSomethingComplicated();
```

Good:

```cpp
std::unique_ptr<Texture> texture = CreateTexture();
```

---

## Prefer Explicit Dependencies

Bad:

```cpp
class SpriteSystem
{
    Runtime& m_Runtime;
};
```

Good:

```cpp
class SpriteSystem
{
    Renderer2D& m_Renderer;
    ECSWorld& m_World;
};
```

---

# Memory Ownership Rules

## Use RAII Everywhere

Preferred ownership:

```cpp
std::unique_ptr
std::shared_ptr (only when truly shared)
stack ownership
```

Avoid raw owning pointers.

---

## Ownership Must Be Obvious

Every major object should have:

- one clear owner
- predictable lifetime
- explicit destruction path

---

# Singleton Policy

Avoid singleton-heavy architecture.

Disallowed pattern:

```cpp
Renderer::Get()
Input::Get()
Application::Get()
```

Singletons create:

- hidden dependencies
- global state
- poor testability
- architecture coupling

---

# Runtime Access Policy

Avoid:

```cpp
runtime.GetRenderer()
runtime.GetAssets()
runtime.GetPhysics()
```

inside gameplay and systems.

Prefer constructor injection.

---

# Layer Usage Rules

Layers are acceptable for:

- editor tools
- overlays
- debug systems
- application separation

Layers should NOT become:

- gameplay framework
- simulation architecture
- world management system

---

# Module Rules

Modules should:

- expose minimal APIs
- own their internal systems
- avoid circular dependencies
- initialize explicitly

Avoid implicit communication.

---

# Include Rules

Prefer forward declarations whenever possible.

Avoid unnecessary includes in headers.

Keep compile dependencies small.

---

# Build System Rules

Keep project structure predictable.

Preferred layout:

```text
Engine/
Applications/
ThirdParty/
Assets/
Docs/
```

Avoid deeply nested dependency chains.

---

# ECS Guidelines

Gameplay should move toward:

```text
Systems
Components
World
```

Avoid object-heavy gameplay inheritance hierarchies.

---

# Renderer Guidelines

Renderer code should remain:

- frame-oriented
- cache-conscious
- backend-agnostic
- explicit

Avoid hidden renderer state.

---

# Error Handling

Prefer:

- assertions for impossible states
- recoverable error paths where appropriate
- explicit failure reporting

Avoid silent failures.

---

# Performance Philosophy

Do not prematurely optimize.

But:

- avoid obviously poor allocations
- avoid unnecessary virtual dispatch
- avoid hidden copies
- avoid accidental heap usage

Measure before optimizing.

---

# Architecture Warnings

If the engine starts heavily relying on:

```cpp
Runtime&
Global registries
Service locators
Singleton access
```

Architecture review is required.

---

# Preferred Design Direction

```text
Simple runtime
Explicit ownership
Minimal magic
Scalable modularity
Low hidden state
```

This is the long-term architectural direction of GE2D.