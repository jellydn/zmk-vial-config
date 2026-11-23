# Codebase Structure

**Analysis Date:** 2026-11-21

## Directory Layout

```
zmk-vial-config/
├── .github/
│   ├── dependabot.yml        # monthly github-actions updates
│   └── workflows/            # build, release, draw, bump, env test
├── config/                   # ZMK user config (west manifest "self")
│   ├── base.keymap           # all layers, HRMs, shift morphs, mouse tuning
│   ├── combos.dtsi           # ZMK combos (position diagram on top)
│   ├── leader.dtsi           # leader sequences (BOOT, RESET)
│   ├── silakka54.keymap      # board entry keymap
│   ├── silakka54.conf        # board Kconfig
│   ├── west.yml              # pinned ZMK/Zephyr/modules (pin-west)
│   └── boards/shields/silakka54/  # custom shield
├── docs/build-env.md         # local nix build environment guide
├── draw/                     # keymap-drawer config, rendered SVGs, flash diagrams
├── nix/                      # nix derivations for dev-shell tools
├── qmk/
│   ├── corne-v4.1-graphite.vil  # Corne setup for foostan's stock Vial firmware
│   └── silakka54-graphite.vil   # Silakka54 setup for Squalius-cephalus' stock Vial firmware
├── build.yaml                # ZMK build matrix
├── Justfile                  # local tasks
├── flake.nix / flake.lock    # dev shell
├── AGENTS.md                 # customization guide for agents
└── README.md                 # keymap, tap-hold FAQ, flash guide
```

## Directory Purposes

**`config/`:** ZMK configuration. West uses it as the manifest repo (`self.path: config`).
**`config/boards/shields/silakka54/`:** Kconfig, matrix (`silakka54.dtsi`), physical layout
(`silakka54-layouts.dtsi`), left/right overlays (right reverses columns, `col-offset = <6>`).
**`draw/`:** `config.yaml` (keymap-drawer), generated `silakka54.yaml`/`.svg`, hand-made
`flash-*.svg` used in the README.
**`nix/`:** packages for keymap-drawer, dts-format, dts-linter, dts-lsp-server, tree-sitter.

## Key File Locations

**Entry Points:** `config/silakka54.keymap`, `qmk/silakka54-graphite.vil`, `qmk/corne-v4.1-graphite.vil`.
**Configuration:** `build.yaml`, `config/west.yml`, `config/*.conf`.
**Core Logic:** `config/base.keymap`, `config/combos.dtsi`.
**Release:** `.github/workflows/release.yml`.

## Naming Conventions

**Files:**
- ZMK board files: `config/<board>.keymap`, `config/<board>.conf`.
- Vial setups: `qmk/<board>-graphite.vil`.
- Workflows: `build-<target>.yml`.

**Identifiers:**
- ZMK layer indices: `DEF NAV MOUSE SYM NUM FN`; QMK: `_BASE _NAV _MOUSE _SYM _NUM _FN`.
- HRM behaviors: `hml` / `hmr`; shift morphs: `gr_<key>`.
- Key positions: zmk-helpers labels `L/R` + `N/T/M/B/H` + index (0 = innermost).

## Where to Add New Code

**New ZMK board:** `config/<board>.keymap` + `.conf`, entry in `build.yaml` (see `AGENTS.md`).
**Layer/HRM change:** `config/base.keymap`; mirror in both `.vil` if wanted.
**Combo:** `config/combos.dtsi`; for Vial, the `.vil`.
**Leader sequence:** `config/leader.dtsi`.
**New Vial board:** `qmk/<board>/` + `qmk/<board>-graphite.vil` + a `build-qmk-<board>.yml`,
then add it to `release.yml` and update the `.uf2` count.

## Special Directories

**`zmk/`, `zephyr/`, `modules/`, `.west/`:** created by `just init`; gitignored.
**`.build/`, `firmware/`:** local build output; gitignored.
**`.planning/codebase/`:** this codebase map.

---

*Structure analysis: 2026-11-21*
