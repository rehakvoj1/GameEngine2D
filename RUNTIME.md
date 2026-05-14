# GE2D Runtime Architecture

## Purpose

The Runtime is the central orchestration layer of GE2D.

Its responsibilities are:

- engine initialization
- frame execution
- module lifecycle management
- shutdown coordination

Runtime is NOT:

- a global service locator
- a dependency container
- a gameplay manager
- a universal access object

---

# Runtime Responsibilities

## Runtime Owns

```text
Window
Renderer Backend
Main ECS World
Frame Loop
Module Lifecycle
```

## Runtime Coordinates

```text
Initialization
Frame Begin
Update
Render
Frame End
Shutdown
```

---

# Runtime Flow

```text
main()
    ↓
Create RuntimeConfig
    ↓
Register Modules
    ↓
Create Application
    ↓
Runtime.Initialize()
    ↓
Runtime.Run()
    ↓
Runtime.Shutdown()
```

---

# Example Entry Point

```cpp
int main()
{
    RuntimeConfig config;
    config.AppName = "Sandbox";

    Runtime runtime(config);

    runtime.RegisterModule<RendererModule>();
    runtime.RegisterModule<ECSModule>();

    SandboxApp app;

    runtime.Run(app);

    return 0;
}
```

---

# Runtime Lifecycle

## Initialization Phase

Runtime initializes:

1. Platform systems
2. Window
3. Renderer backend
4. Asset systems
5. ECS world
6. Registered modules
7. Application

---

## Frame Loop

Typical frame structure:

```text
PreFrame
PlatformEvents
Input
NetworkReceive
PreSimulation
FixedSimulation
PostSimulation
Animation
Audio
RenderPreparation
Render
NetworkSend
EndFrame
```

`FixedSimulation` runs with a fixed timestep and may execute zero or more times
per rendered frame. Rendering is optional and skipped for headless runtimes.

---

## Shutdown Phase

Shutdown order should be reversed.

Example:

```text
Application
Gameplay Systems
Renderer
Window
Platform
```

---

# Module System

Modules are runtime extensions.

Example:

```cpp
class IModule
{
public:
    virtual void Initialize(Runtime& runtime) = 0;
    virtual void Shutdown() = 0;
};
```

Modules should:

- own their internal state
- initialize explicitly
- avoid hidden cross-module communication

---

# Runtime Design Rules

## Rule 1

Runtime may OWN systems.

Runtime should NOT expose everything globally.

---

## Rule 2

Never pass Runtime& unless orchestration access is truly needed.

Prefer:

```cpp
Renderer2D&
ECSWorld&
AssetManager&
```

Instead.

---

## Rule 3

Initialization order should remain explicit.

Avoid automatic dependency graphs early.

---

## Rule 4

Runtime should remain small.

If Runtime becomes:

- huge
- dependency-heavy
- globally referenced

Architecture degradation has started.

---

# Frame Contexts

GE2D uses scoped contexts for frame and simulation callbacks.

Examples:

```cpp
FrameContext
SimulationContext
```

Purpose:

- reduce coupling
- narrow dependency scope
- avoid Runtime leakage

---

# ECS Philosophy

Gameplay should evolve toward:

```text
World
Systems
Components
```

Instead of:

```text
Layer-heavy gameplay architecture
```

Layers remain useful for:

- tooling
- debug overlays
- application-level separation

---

# Renderer Philosophy

Renderer architecture should remain:

- backend-agnostic
- explicit
- low-overhead
- frame-oriented

Planned backend split:

```text
Renderer.Core
Renderer.OpenGL
Renderer.Vulkan
```
