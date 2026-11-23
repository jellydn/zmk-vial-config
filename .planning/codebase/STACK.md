# Technology Stack

**Analysis Date:** 2026-11-21

## Languages

**Primary:**
- Devicetree + C preprocessor (ZMK keymap DSL) - `config/base.keymap`, `config/combos.dtsi`,
  `config/leader.dtsi`, `config/boards/shields/silakka54/*.dtsi|*.overlay`
- C (QMK keymap) - `qmk/silakka54/keymap.c`

**Secondary:**
- JSON - Vial layout definitions (`qmk/*/vial.json`) and saved Vial setups (`qmk/*.vil`)
- YAML - GitHub Actions (`.github/workflows/*.yml`), build matrix (`build.yaml`), west manifest
  (`config/west.yml`), keymap-drawer config (`draw/config.yaml`)
- Kconfig - `config/silakka54.conf`, `config/boards/shields/silakka54/Kconfig.*`
- Nix - dev shell (`flake.nix`, `nix/*.nix`)
- Just - task runner (`Justfile`)

## Runtime

**Environment:**
- Firmware runs on RP2040 microcontrollers: Silakka54 (ZMK board `rpi_pico//zmk`; Vial
  `silakka54`) and Corne v4.1 (foostan's stock Vial firmware plus `qmk/corne-v4.1-graphite.vil`).
- No host runtime. Output is `.uf2` firmware files.

**Package Manager:**
- west (Zephyr) for ZMK and modules; lockfile: revisions pinned in `config/west.yml` by pin-west.
- Nix flakes for the dev shell; lockfile: `flake.lock`.
- QMK/Vial builds use pip (`qmk` + `vial-qmk/requirements.txt`) inside CI only, unpinned.

## Frameworks

**Core:**
- ZMK (zmkfirmware/zmk, pinned `4de3133…`, 2026-11-16) on Zephyr `v4.1.0+zmk-fixes` - Silakka54 firmware
- vial-qmk (vial-kb/vial-qmk, pinned `dd43959…` in workflow env) - Silakka54 Vial firmware
- foostan/kbd_firmware (`7e94242…`) - stock Corne v4.1 Vial `.uf2`, linked from README and release notes

**Testing:**
- None for the keymap. `just test` is a snapshot harness for ZMK modules only (see `TESTING.md`).

**Build/Dev:**
- Zephyr SDK 0.16 (`arm-zephyr-eabi`) via zephyr-nix - local ZMK builds
- `gcc-arm-none-eabi` (apt) - QMK builds in CI
- keymap-drawer (`nix/keymap-drawer.nix`, and the upstream reusable workflow) - `draw/silakka54.svg`
- dts-format / dts-linter (`nix/dts-format.nix`, `nix/dts-linter.nix`) - devicetree formatter
- pin-west - west manifest pinning (`just bump-west`, `.github/workflows/bump-west.yml`)
- Prettier config (`.prettierrc`: `proseWrap: always`) - Markdown wrapping

## Key Dependencies

**Critical:**
- `zmk-helpers` (urob, `modules/zmk/helpers`) - `ZMK_LAYER`, `ZMK_HOLD_TAP`, `ZMK_COMBO`,
  `ZMK_MOD_MORPH` macros and the `54.h` key labels used by every layer, combo and HRM.
- `zmk-leader-key` (urob, `modules/zmk/leader-key`) - `&leader` with `B O O T` / `R E S E T`.

**Infrastructure:**
- Zephyr module allowlist in `config/west.yml` (cmsis, hal_nordic, hal_rpi_pico, hal_stm32, lvgl,
  mbedtls, tinycrypt) keeps the workspace small.

## Configuration

**Environment:**
- No environment variables needed for builds. Optional secret `WEST_UPDATE_TOKEN` (PAT) lets the
  west bump PR trigger CI (`.github/workflows/bump-west.yml`).
- `.envrc` activates the nix flake via direnv; `flake.nix` exports `ZMK_BUILD_DIR`, `ZMK_SRC_DIR`.

**Build:**
- `build.yaml` - ZMK build matrix (Silakka54 left/right).
- `config/silakka54.conf` - `CONFIG_ZMK_POINTING=y`.
- `qmk/silakka54/{config.h,rules.mk}` - Vial defaults.

## Platform Requirements

**Development:**
- None to build: push to GitHub and Actions builds everything.
- Local ZMK builds: nix + direnv, then `just init` and `just build silakka54`. There is no local
  recipe for the Vial builds; they run only in CI.

**Production:**
- Flash `.uf2` files over the RP2040 `RPI-RP2` drive. Load the `.vil` in Vial after each Vial flash.

---

*Stack analysis: 2026-11-21*
