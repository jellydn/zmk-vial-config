# Testing Patterns

**Analysis Date:** 2026-11-23

## Test Framework

**Runner:** None for the keymaps. The builds are the tests.

**Available harness:** `just test <path> [--verbose|--auto-accept|--no-build]` (`Justfile`). It
builds a ZMK test config for `native_sim//zmk_test_mock`, runs it and diffs keycode events against
`keycode_events.snapshot`. It is meant for developing the modules under `modules/zmk/`, not for this
keymap. The repo has no test cases.

**Run Commands:**
```bash
just build all        # local ZMK build of every build.yaml target (nix shell)
just draw             # parse + render the keymap
just test <dir>       # module snapshot test (no tests in this repo)
```

## Test File Organization

None in the repo.

## Test Structure

CI checks, by workflow:
- `build-nix.yml` - ZMK compiles for both halves.
- `release.yml` - exactly 2 `.uf2` files collected (PRs that change `release.yml` run this without
  publishing).
- `draw.yml` - keymap parses (`fail_on_error: true`).
- `test-build-env.yml` - nix shell on 4 platforms: `just init`, `just build silakka54`, `just draw`.

## Mocking

Not applicable.

## Fixtures and Factories

Not applicable.

## Coverage

**Requirements:** None.

**Gaps:**
- Keymap behavior (HRM timing, combos, leader) is verified only on hardware, by hand.
- Parity between `config/base.keymap` and both `.vil` is not checked in CI. Both Vial boards run
  stock prebuilt firmware; each `.vil` is the only source for its board.
- Hardware status per build, with dates and the checklist, is in the README section
  "Test status". Summary: none of the current settings is tested on hardware. Silakka54 ZMK was
  last tested on 2026-11-22 with urob's 280/150 settings (before PR #18); its Leader key was never
  confirmed. Silakka54 Vial was never tested. The Corne was tested on 2026-11-21 with the old
  custom firmware only, not the stock firmware + `.vil`.

## Test Types

**Build tests:** every target, in CI.
**Hardware tests:** manual, with the README checklist (home-row Shift after a letter, rolls, thumb
layers, combos, shift overrides, Leader, removed keys).
**E2E:** not used.

## Common Patterns

**Verify a ZMK keymap change:** push a branch; the path-filtered build workflow runs.
Download the artifact or wait for the `latest` release after merge.
**Verify a `.vil` change:** no build runs (no Vial firmware is built here). Load the `.vil` in
Vial on the keyboard; the `latest` release gets it after merge.

---

*Testing analysis: 2026-11-23*
