# Codebase Concerns

**Analysis Date:** 2026-11-21

## Tech Debt

**Dead manual-only ZMK workflow:**
- Issue: `build.yml` builds the same `build.yaml` matrix as `build-nix.yml` with the upstream ZMK
  workflow, but only on `workflow_dispatch` (push trigger commented out). Nothing calls it.
- Files: `.github/workflows/build.yml`
- Impact: two "Build ZMK firmware" entries in the Actions tab; confusing for flash guides.
- Status: fixed 2026-11-21, file deleted; `build-nix.yml` is the build that `release.yml` uses.

**Stale local-build guide copied from urob:**
- Issue: mentions urob's Corneish Zen targets, `draw/base.svg` / `draw/overview.svg` (the repo
  renders `draw/silakka54.svg`), clones `urob/zmk-config`, and links README anchors that do not
  exist (`#building-the-firmware`, `#pinning-the-firmware`). `AGENTS.md` links
  `README.md#local-build-environment`, which also does not exist; README points to urob's notes
  instead of `docs/build-env.md`.
- Files: `docs/build-env.md`, `AGENTS.md`, `README.md` (Build section)
- Status: fixed 2026-11-21; links point at `docs/build-env.md` and the examples use Silakka54.

**Layout written five times by hand:**
- Issue: `config/base.keymap`, the Silakka54 `keymap.c` and two `.vil`. No generator, no parity
  check in CI.
- Files: `config/base.keymap`, `qmk/silakka54/keymap.c`, `qmk/*.vil`
- Impact: drift is silent.
- Fix approach: optional CI script that compares `.vil` and `keymap.c`. Not worth it yet.

## Known Bugs

**Nix environment test builds a target that does not exist:**
- Symptoms: `test-build-env.yml` runs `just build planck` (left over from urob's repo).
  `build.yaml` has only `silakka54_left/right`, so `just build` exits 1 with "No matching targets
  found". The workflow has never run here (it triggers only on `nix/**`, `flake.*` changes), so the
  failure is latent.
- Files: `.github/workflows/test-build-env.yml`
- Trigger: any push that changes `flake.lock` or `nix/` (for example a `just bump-nix`).
- Status: fixed 2026-11-21; it builds `silakka54`.

## Security Considerations

**Unpinned reusable workflows:**
- Risk: `urob/zmk-actions@main`, `caksoylar/keymap-drawer@main`, `urob/pin-west@main` run with
  this repo's token; `draw.yml` and `bump-west.yml` have `contents: write`.
- Files: `.github/workflows/build-nix.yml`, `draw.yml`, `bump-west.yml`
- Current mitigation: trusted upstream authors; build workflow is `contents: read`.
- Recommendations: pin to SHAs if the upstreams publish tags; dependabot can then bump them.

**Unpinned pip install in Vial builds:** `pip install qmk -r vial-qmk/requirements.txt` takes the
latest `qmk` CLI (`build-qmk*.yml`). A breaking CLI release would fail the build, not ship bad code.

## Performance Bottlenecks

**Duplicate builds on push to main:** each push to `main` runs the path-filtered build workflows
and `release.yml`, which calls them again. Costs a few CI minutes; harmless.

## Fragile Areas

**Rolling `latest` release:**
- Files: `.github/workflows/release.yml`
- Why fragile: delete-then-create; a run canceled between the two steps (`cancel-in-progress`)
  leaves no release until the newer run finishes, which follows at once.
- Safe modification: keep the `.uf2` count assertion in sync when adding a board.

**Diagram lags one release:** `draw.yml` commits the new SVG after the push with `GITHUB_TOKEN`,
which does not trigger `release.yml`, so the release ships the SVG from before the change until the
next push.

**Vial EEPROM reset:** every new Vial build erases combos, key overrides, macro and QMK Settings.
Load the `.vil` after every flash (Corne and Silakka54 Vial).

## Scaling Limits

Release asserts exactly 3 `.uf2`; adding a board needs that number changed.

## Dependencies at Risk

**vial-qmk pin and the foostan Corne `.uf2` link:** pinned by SHA in `build-qmk-silakka54.yml`,
`release.yml` and the README; must be bumped by hand (dependabot does not see them).

## Missing Critical Features

None blocking.

## Cross-board Inconsistencies (by design or unconfirmed; not changed)

- The stock Corne Vial firmware fires combos on every layer and counts thumbs as their own hand for
  Chordal Hold; the Silakka54 Vial keymap limits combos to the base layer.
- ZMK Nav/Sym/Num carry `&leader`; Vial has no leader (README says so).
These change keymap behavior, so they need the owner's decision.

## Test Coverage Gaps

**Keymap behavior:** only hardware testing. Vial builds are UNTESTED on hardware (README).
Priority: Medium.

---

*Concerns audit: 2026-11-21*
