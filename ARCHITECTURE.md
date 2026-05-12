# GE2D Architecture
## Philosophy

GE2D is designed as a modern modular C++ 2D engine focused on:

- explicit ownership
- modular runtime composition
- minimal hidden state
- renderer abstraction
- scalable runtime architecture
- editor/runtime separation
- deterministic-friendly simulation
- long-term maintainability

The engine architecture intentionally avoids:

- heavy singleton usage
- implicit global state
- hidden dependency graphs
- over-abstracted systems
- premature plugin complexity
- service locator patterns

---

# High-Level Architecture

```text
Applications/
    Sandbox/
    Editor/
    Game/
    DedicatedServer/

Engine/
    Core/
    Runtime/
    Renderer/
    ECS/
    Scene/
    Asset/
    Platform/
    Network/
```

Applications are built as independent executables.

The engine owns:

- runtime lifecycle
- frame orchestration
- simulation scheduling
- ECS runtime
- module initialization
- subsystem coordination

Applications own:

- startup composition
- runtime configuration
- module selection
- gameplay/editor composition

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
- simulation coordinator

Runtime must NOT become:

- global dependency container
- universal registry
- singleton replacement
- hidden ownership layer

Bad:

```cpp
runtime.GetRenderer()
runtime.GetPhysics()
runtime.GetAssets()
```

Good:

```cpp
PhysicsSystem(ECSWorld& world, PhysicsWorld& physics)
```

## 3. Composition Root Per Application

Every executable has its own:

```cpp
int main()
```

The executable composes:

- runtime configuration
- modules
- runtime mode
- application instance

Example:

```cpp
int main()
{
    Runtime runtime(config);

    runtime.RegisterModule<WindowModule>();
    runtime.RegisterModule<RendererModule>();
    runtime.RegisterModule<ECSModule>();

    SandboxApp app;

    runtime.Run(app);
}
```

Dedicated server example:

```cpp
int main()
{
    Runtime runtime(config);

    runtime.RegisterModule<ECSModule>();
    runtime.RegisterModule<NetworkServerModule>();

    DedicatedServerApp app;

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

Modules should remain optional whenever possible.

Example:

```text
RendererModule
AudioModule
NetworkModule
WindowModule
```

A runtime may execute without some modules.

---

## 5. Keep Runtime Simple

Avoid creating systems before they are needed.

GE2D intentionally prefers:

- straightforward ownership
- explicit initialization
- simple execution flow
- explicit scheduling

Over:

- reflection-heavy systems
- automatic dependency graphs
- complex plugin infrastructures
- hidden execution order

---

# Runtime Execution Model

GE2D uses:

- fixed timestep simulation
- decoupled rendering
- phase-based frame execution
- modular runtime composition
- headless-compatible execution

The architecture separates:

```text
Render Frame != Simulation Tick
```

This separation is critical for:

- multiplayer
- dedicated servers
- deterministic simulation
- replay systems
- editor tooling
- future rollback networking
- scalable ECS execution

---

# Runtime Ownership Model

```text
Runtime
    owns PlatformRuntime
    owns FrameScheduler
    owns SimulationClock
    owns Worlds
    owns Module Lifecycle
```

Runtime may optionally own:

```text
Window
RendererBackend
AudioDevice
```

depending on active modules.

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

# Runtime Modes

GE2D should support multiple runtime configurations without major architectural changes.

---

## Client Runtime

```text
WindowModule
RendererModule
InputModule
AudioModule
NetworkClientModule
```

Supports:

- gameplay
- rendering
- UI
- multiplayer client execution

---

## Dedicated Server Runtime

```text
ECSModule
SimulationModule
NetworkServerModule
```

Supports:

- headless execution
- simulation-only runtime
- multiplayer server logic

Dedicated server runtime must NOT require:

- renderer
- window
- GPU access
- editor systems

---

## Editor Runtime

```text
WindowModule
RendererModule
EditorModule
```

Supports:

- tooling
- scene editing
- simulation preview
- editor overlays

Editor runtime may:

- pause simulation
- step simulation
- run isolated worlds
- execute editor-only systems

---

# Frame Scheduler

GE2D uses explicit frame phases instead of monolithic update loops.

Avoid:

```cpp
Update(deltaTime);
```

as a universal execution model.

Prefer:

- PreFrame
- PlatformEvents
- Input
- NetworkReceive
- PreSimulation
- FixedSimulation
- PostSimulation
- Animation
- Audio
- RenderPreparation
- Render
- NetworkSend
- EndFrame

Systems register into explicit phases.

This improves:

- execution clarity
- multiplayer synchronization
- editor control
- subsystem isolation
- future multithreading
- deterministic simulation

---

# Fixed Simulation

Gameplay simulation should prefer fixed timestep execution.

Recommended structure:

```cpp
constexpr double FIXED_TIMESTEP = 1.0 / 60.0;

while (running)
{
    accumulator += frameDelta;

    while (accumulator >= FIXED_TIMESTEP)
    {
        RunSimulationTick();
        accumulator -= FIXED_TIMESTEP;
    }

    Render(interpolation);
}
```

Simulation should remain separated from render framerate.

Avoid gameplay logic tightly coupled to variable render delta.

---

# Headless Runtime Philosophy

GE2D must support execution without:

- windows
- rendering
- graphics APIs
- GPU dependencies

This is required for:

- dedicated servers
- automated testing
- command-line tools
- asset processing
- CI pipelines

The runtime architecture must not assume rendering exists.

---

# ECS Philosophy

Gameplay should evolve toward:

- Systems
- Components
- Worlds
- Simulation Phases

Avoid object-heavy gameplay inheritance hierarchies.

Core gameplay execution should prefer:

- ECS systems
- explicit scheduling
- isolated simulation logic

Over:

- deep inheritance chains
- gameplay layer stacks
- monolithic update chains

---

# Layer Philosophy

Layers are intended for:

- editor tooling
- overlays
- debug UI
- application-level separation

Layers are NOT the primary gameplay architecture.

Core gameplay logic should evolve toward:

- ECS systems
- scene systems
- explicit world simulation
- scheduler-driven execution

---

# Dependency Rules

Low-level systems:

- Window
- Renderer
- Input
- Platform

Must not depend on:

- Gameplay
- Editor
- Scene tools

Higher-level systems may depend downward.

Lower-level systems must never depend upward.

---

# Renderer Philosophy

Renderer architecture should remain:

- backend-agnostic
- frame-oriented
- cache-conscious
- explicit
- decoupled from gameplay simulation

Avoid hidden renderer state.

Avoid gameplay systems directly controlling renderer internals.

---

# Networking Philosophy

Networking should integrate through explicit runtime phases.

Networking systems should remain separated from rendering.

Future networking goals include:

- client/server architecture
- prediction/interpolation
- rollback-capable simulation
- deterministic-friendly execution

The runtime architecture should not assume singleplayer-only execution.

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

across module boundaries.

---

# Long-Term Goals

GE2D architecture should eventually support:

- editor/runtime separation
- dedicated server runtime
- headless execution
- modular renderer backends
- deterministic-friendly simulation
- multiplayer-ready execution
- hot reload
- tooling applications
- plugin-capable systems
- scalable ECS scheduling

Without requiring fundamental rewrites.

---

# Preferred Design Direction

```text
Simple runtime
Explicit ownership
Fixed simulation
Phase-based execution
Minimal magic
Scalable modularity
Low hidden state
Deterministic-friendly architecture
Headless-compatible runtime
```

This is the long-term architectural direction of GE2D.