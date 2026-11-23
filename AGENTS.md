# Customization guide

Instructions for working on this ZMK config — written for coding agents, but equally usable by
humans adapting this repo as a starting point for their own keymap. For background on the keymap
and the build pipeline, see the [README](README.md).

## Ground rules

- **Building needs no local setup.** Pushing to a fork builds every target in `build.yaml` through
  GitHub Actions (`.github/workflows/build-nix.yml`, triggered by pushes and PRs touching
  `config/**` or `build.yaml`); the firmware is downloaded from the Actions tab. A fresh fork has
  Actions disabled — enable them once from the fork's Actions tab.
- **Building locally** requires the nix-based dev environment (nix + direnv, see the
  [docs/build-env.md](docs/build-env.md)) plus a one-time `just init`, which turns the
  repository into a west workspace by pulling in ZMK, Zephyr and the modules. Then verify keymap
  changes with `just build <target>` (`just list` shows valid targets, `just build all` builds
  everything); compiled firmware lands in `firmware/`. If `just` or `west` are missing, the
  environment isn't active — run commands through `nix develop --command <cmd>` or activate with
  `direnv allow`.
- `config/west.yml` is maintained by [pin-west](https://github.com/urob/pin-west): never hand-edit
  pinned revisions, run `pin-west bump` instead. Adding or removing a module is fine — edit the
  entry itself and re-run `pin-west pin` to (re)pin.
- `dts-format` (packaged in the dev environment) formats devicetree files. It does not reformat
  C-preprocessor macros, so on the keymaps it is close to a no-op — the hand-aligned grids inside
  `ZMK_LAYER` are safe and need no guarding. It earns its keep on plain devicetree, i.e. when
  developing modules or board definitions. Without arguments it recurses over the working
  directory; pass files explicitly to narrow it.
- After keymap changes that affect the layout, regenerate the diagram with `just draw` (renders
  `draw/silakka54.svg`). The `Draw keymap` workflow also renders and commits it on push.
- `just test` is a snapshot-test harness for developing the ZMK **modules** checked out under
  `modules/zmk/`. It does not test this repo's keymap; the keymap is validated by building, and
  its behavior by hand on hardware (README "Test status": per-build status and checklist). Update
  that section when a hardware test is done or a change makes a past test stale.

## How the multi-board layout works

`config/base.keymap` defines all layers exactly once, for the 54-key Silakka54, using the
standardized key labels from [zmk-helpers](https://github.com/urob/zmk-helpers): `LN0`–`LN5` for the
number row, `LT0`–`LT5`, `LM0`–`LM5`, `LB0`–`LB5` and `LH0`–`LH2` for the left top/middle/bottom rows
and thumbs, mirrored with `R` on the right (`0` is innermost). HRM trigger positions and combos
(`config/combos.dtsi`) are written against these labels — so they adapt to any board automatically.

`base.keymap` intentionally includes **no** key-labels header itself. Each board has a small entry
keymap that must, in this order:

1. define a `ZMK_BASE_LAYER(name, LN, RN, LT, RT, LM, RM, LB, RB, LH, RH)` macro that places the
   ten 54-key blocks onto the board's physical grid, dropping blocks the board lacks (e.g. the
   number row on a Corne) and filling extra keys with `&none` or extra bindings,
2. include the matching key-labels header from zmk-helpers,
3. `#include "base.keymap"`.

`config/silakka54.keymap` needs no adapter: `base.keymap` falls back to a pass-through
`ZMK_BASE_LAYER`. `base.keymap` adds the opposite number row to the HRM trigger keys only when the
key labels define `LN0`.

## Adding a new board (e.g. the Corne)

1. **Identify the ZMK board/shield names** for the hardware, from the ZMK docs or the board's
   vendor config. For hardware ZMK does not ship, add a shield under `config/boards/shields/<name>/`
   (see `silakka54/`: matrix pins from the QMK `keyboard.json`, a physical layout, and the
   `zmk,wired-split` node for wired splits).
2. **Pick a key-labels header** from
   [zmk-helpers](https://github.com/urob/zmk-helpers/tree/main/include/zmk-helpers/key-labels)
   (`42.h` for a 3x6+3 Corne, `54.h` for the Silakka54), or write the defines yourself following
   [key_labels.md](https://github.com/urob/zmk-helpers/blob/main/docs/key_labels.md#standardization).
3. **Create `config/<board>.keymap`** with the three-step structure above. Keep the base positions in
   their relative locations and spend spare keys on extras.
4. **Create `config/<board>.conf`**; all boards want `CONFIG_ZMK_POINTING=y` for the Mouse layer.
5. **Register the build target** in `build.yaml` under `include:`, as `board:` plus `shield:`.
6. **Build and check** in CI (or `just build <name>`), then add the board to the `Draw keymap`
   workflow if you want a diagram for it.

## Where to change what

| Change                            | File                                                     |
| --------------------------------- | -------------------------------------------------------- |
| Layers, HRMs, thumb keys          | `config/base.keymap`                                     |
| HRM timing                        | `config/base.keymap` (`MAKE_HRM`: `tapping-term-ms`, `quick-tap-ms`) |
| Combos                            | `config/combos.dtsi` (position diagram at the top)       |
| Leader sequences                  | `config/leader.dtsi`                                     |
| Per-board keys, physical mapping  | `config/<board>.keymap`                                  |
| Board settings                    | `config/<board>.conf`                                    |
| Custom shields                    | `config/boards/shields/<name>/`                          |
| Corne v4.1 (stock Vial firmware)  | `qmk/corne-v4.1-graphite.vil` only (load it in Vial)     |
| Build targets                     | `build.yaml`                                             |
| Keymap diagram                    | `draw/config.yaml`, `.github/workflows/draw.yml`         |
| ZMK/module versions               | `config/west.yml` (via `pin-west bump` only)             |
| Dev environment                   | `flake.nix`, `nix/` (test with `nix develop`)            |

Removing a feature: delete its `#include` and bindings from `base.keymap`, and if it was the only
consumer of a module, drop the module's entry from `config/west.yml`.
