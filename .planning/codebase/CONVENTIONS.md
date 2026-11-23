# Coding Conventions

**Analysis Date:** 2026-11-21

## Naming Patterns

**ZMK:**
- Layer defines in caps (`DEF`, `NAV`, …); `XXX` = `&none`, `___` = `&trans`.
- Behavior macros in caps (`MAKE_HRM`, `SHIFT_MORPH`); behavior nodes in snake case (`hml`, `gr_sqt`).
- Combos named by output (`esc_l`, `quote`, `meh_r`).

**QMK:**
- Layers `_BASE` … `_FN` in an enum; QMK short keycodes (`KC_QUOT`, `MS_UP`, `QK_LLCK`).
- `XXXXXXX` for unused keys.

## Code Style

**Formatting:**
- Keymap layers are hand-aligned grids with box-drawing comments; each block is one half-row.
- `dts-format` is available; it does not touch preprocessor macros, so the grids stay intact.
- QMK `LAYOUT(...)` rows are right-aligned columns, one physical row per line.
- Markdown: Prettier `proseWrap: always`, about 100 columns.

**Linting:** None configured in CI.

## Import Organization

**ZMK `base.keymap`:** `behaviors.dtsi` → `zmk-helpers/helper.h` → `keys.h` → pointing defines then
`pointing.h` → behaviors → `#include "combos.dtsi"` and `"leader.dtsi"` → layers.
**Board entry:** `ZMK_BASE_LAYER` (optional) → key-labels header → `base.keymap`. `base.keymap`
includes no key-labels header itself.

## Error Handling

Not applicable (no runtime code paths). QMK hooks return safe defaults (`return true`, `false`).

## Logging

None.

## Comments

**When to comment:**
- Explain why a value is chosen and how it maps to the other firmware (for example the mouse-key
  math in `config/base.keymap`, Flow Tap reasoning in `keymap.c`).
- Workflows explain triggers and pins in comments.
- README and comments use short, plain sentences (Simplified Technical English style).

## Function Design

- QMK hooks are small and single-purpose (`combo_should_trigger` in the Silakka54 keymap).

## Module Design

- Shared layout lives once per firmware: `config/base.keymap` (ZMK) and one `keymap.c` per Vial board.
- Commit messages use Conventional Commits with a scope: `fix(corne): …`, `ci: …`, `docs: …`,
  `feat(silakka54-vial): …`. Work lands through pull requests merged into `main`.

---

*Convention analysis: 2026-11-21*
