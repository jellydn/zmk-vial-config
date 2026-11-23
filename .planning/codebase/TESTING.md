# Testing Patterns

**Analysis Date:** 2026-11-21

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
- `build-qmk-silakka54.yml` - Silakka54 Vial firmware compiles; `.uf2` must exist.
- `release.yml` - exactly 3 `.uf2` files collected (PRs that change `release.yml` run this without
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
- Parity between `config/base.keymap`, the Silakka54 `keymap.c` and both `.vil` is not checked in
  CI. The Corne has no `keymap.c`: it runs foostan's stock Vial firmware, and the `.vil` is its only
  source.
- The Silakka54 Vial build is marked UNTESTED on hardware in the README.

## Test Types

**Build tests:** every target, in CI.
**Hardware tests:** manual, Silakka54 ZMK and Corne with `.vil` loaded.
**E2E:** not used.

## Common Patterns

**Verify a keymap change:** push a branch; the path-filtered build workflow runs. Download the
artifact or wait for the `latest` release after merge.

---

*Testing analysis: 2026-11-21*
