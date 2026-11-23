# Architecture

**Analysis Date:** 2026-11-21

## Pattern Overview

**Overall:** Declarative keyboard firmware configuration with three parallel firmware targets that
share one layout:

1. Silakka54 on ZMK (`config/`) - the main build (current settings untested; see README "Test status").
2. Corne v4.1 on foostan's stock Vial firmware + `qmk/corne-v4.1-graphite.vil` (no firmware here).
3. Silakka54 on QMK/Vial (`qmk/silakka54/` + `qmk/silakka54-graphite.vil`), never tested on hardware.

**Key Characteristics:**
- The layout is written by hand twice (ZMK devicetree, the Silakka54 `keymap.c`), plus two `.vil`
  files. Nothing generates one from the other; sync is manual.
- ZMK holds all behavior (combos, HRMs, leader) in the firmware. Vial keeps combos, key overrides,
  macro M0 and QMK Settings in EEPROM; the `.vil` is their source of truth.
- CI builds everything; local builds are optional (ZMK only).

## Layers

**ZMK board adapter layer:**
- Purpose: map the 54-key base layout to a physical board.
- Location: `config/<board>.keymap` (only `config/silakka54.keymap` today).
- Contains: optional `ZMK_BASE_LAYER` macro, key-labels header include, `#include "base.keymap"`.
- Depends on: zmk-helpers key labels (`zmk-helpers/key-labels/54.h`).

**ZMK keymap layer:**
- Purpose: layers, HRMs, shift morphs, mouse tuning.
- Location: `config/base.keymap`, with `config/combos.dtsi` and `config/leader.dtsi`.
- Depends on: zmk-helpers macros, zmk-leader-key, ZMK pointing.

**ZMK hardware layer:**
- Purpose: Silakka54 shield (matrix pins, transform, physical layout, wired split on UART0).
- Location: `config/boards/shields/silakka54/`.
- Used by: `build.yaml` (`silakka54_left`, `silakka54_right` on `rpi_pico//zmk`).

**QMK/Vial layer:**
- Purpose: Vial firmware with default keymap plus small C hooks Vial cannot store.
- Location: `qmk/silakka54/`.
- Hooks: `combo_should_trigger` (base layer only).

**CI/release layer:** `.github/workflows/*.yml` (see `INTEGRATIONS.md`).

## Data Flow

**ZMK build:**
1. `build.yaml` matrix → reusable `urob/zmk-actions` workflow → west fetches `config/west.yml` pins.
2. Zephyr builds `zmk/app` with `-DZMK_CONFIG=config -DSHIELD=silakka54_left|right`.
3. Output: `silakka54-zmk-left.uf2`, `silakka54-zmk-right.uf2` (artifact `firmware`).

**Vial build:**
1. Check out vial-qmk at its pinned SHA.
2. Copy the repo keymap into the keyboard's `keymaps/jellydn/`; `qmk compile`.
3. Output: `silakka54-vial.uf2` plus the `.vil`, uploaded as an artifact.

**Release:**
1. `release.yml` on push to `main` calls the two build workflows (`workflow_call`).
2. Collects `*.uf2`, `*.vil` (plus the Corne `.vil` from `qmk/`), `draw/*.svg`; asserts exactly 3
   `.uf2`. The release notes link foostan's stock Corne `.uf2`.
3. Deletes and recreates the `latest` release and tag at `GITHUB_SHA`.

**Keymap diagram:**
1. `draw.yml` (or `just draw`) parses `config/silakka54.keymap` with `draw/config.yaml`.
2. Writes `draw/silakka54.yaml` and `draw/silakka54.svg`, commits on push.

## Key Abstractions

**`ZMK_BASE_LAYER(name, LN, RN, LT, RT, LM, RM, LB, RB, LH, RH)`:**
- Purpose: one row block per half so other boards can drop or add keys.
- Location: default in `config/base.keymap`; boards may override before including it.

**`MAKE_HRM(NAME, HOLD, TAP, TRIGGER_POS)`:** urob "timeless" home-row mods (`config/base.keymap`).

**`SHIFT_MORPH`:** Graphite shifted pairs, mirrored by Vial key overrides.

**Key labels (`LT0`…`RH2`):** position names that combos and HRM triggers use.

## Entry Points

- `config/silakka54.keymap` - ZMK keymap entry (draw also parses this file).
- `qmk/silakka54/keymap.c` - Silakka54 Vial keymap.
- `.github/workflows/release.yml` - end-to-end build and publish.
- `Justfile` - local tasks (`init`, `build`, `draw`, `bump-west`, `test`).

## Error Handling

**Strategy:** Build failure is the only check. Release fails if the `.uf2` count is not 4. QMK
workflows use `if-no-files-found: error` and a 20-minute timeout.

## Cross-Cutting Concerns

**Layout parity:** ZMK, both `keymap.c` and both `.vil` must stay in sync by hand.
**Tap-hold tuning:** documented in README "Home-row mods" and FAQ; ZMK 280 ms, Vial 200 ms.
**Vial EEPROM reset:** every new Vial build wipes Vial settings; user must load the `.vil`.

---

*Architecture analysis: 2026-11-21*
