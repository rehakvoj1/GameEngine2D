# GE2D Agent Instructions

Read before making architectural changes:

- ARCHITECTURE.md
- RUNTIME.md
- ENGINE_GUIDELINES.md

Critical rules:
- Runtime is orchestration only
- Avoid singleton-heavy patterns
- Prefer explicit dependency injection
- Avoid Runtime& as universal dependency
- Keep renderer backend-agnostic
- ECS is preferred over gameplay inheritance hierarchies
- Do not introduce service locator patterns
- Avoid hidden ownership

Preferred style:
- Explicit ownership
- Minimal hidden state
- Low abstraction count
- Modular architecture