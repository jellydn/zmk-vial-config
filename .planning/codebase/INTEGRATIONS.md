# External Integrations

**Analysis Date:** 2026-11-21

## APIs & External Services

**Source repositories fetched at build time:**
- zmkfirmware/zmk, zmkfirmware/zephyr and Zephyr HAL repos - via west (`config/west.yml`)
- urob/zmk-helpers, urob/zmk-leader-key - ZMK modules via west
- Squalius-cephalus/silakka54 v1.4led - stock Silakka54 Vial `.uf2` files (`LEFT` for the left half, `RIGHT` for the right), linked with sha256 (`SILAKKA54_LEFT_UF2_URL` / `SILAKKA54_RIGHT_UF2_URL` in `release.yml`, README)
- foostan/kbd_firmware - stock Corne v4.1 Vial `.uf2`, linked (`CORNE_UF2_URL` in `release.yml`, README)

**Reusable GitHub workflows (unpinned, `@main`):**
- `zmkfirmware/zmk/.github/workflows/build-user-config.yml` - ZMK build in Docker (`build.yml`)
- `caksoylar/keymap-drawer/.github/workflows/draw-zmk.yml` - keymap SVG (`draw.yml`)
- `urob/pin-west@main` action - weekly west bump PR (`bump-west.yml`)

**Vial desktop/web app (get.vial.today):** users load `qmk/*.vil` after flashing. Not called by CI.

## Data Storage

**Databases:** None.

**File Storage:**
- GitHub Actions artifacts: `firmware` (ZMK).
- GitHub Release `latest` (rolling): rebuilt on every push to `main` by `release.yml`; holds 2
  `.uf2`, both `.vil` and `draw/*.svg`.

**Caching:** Handled inside the reusable ZMK workflow; QMK workflows do not cache.

## Authentication & Identity

**Auth Provider:** GitHub `GITHUB_TOKEN` only.
- `release.yml` release job: `contents: write` (delete + recreate the `latest` release/tag).
- `draw.yml`: `contents: write` (commits `chore(draw): render keymap`).
- `bump-west.yml`: `contents: write`, `pull-requests: write`; optional `WEST_UPDATE_TOKEN` PAT.
- Other workflows: `contents: read`.

## Monitoring & Observability

**Error Tracking:** None. CI status in the GitHub Actions tab is the only signal.

**Logs:** Actions run logs.

## CI/CD & Deployment

**Hosting:** GitHub (jellydn/zmk-vial-config).

**CI Pipeline (`.github/workflows/`):**
- `build.yml` - ZMK build with ZMK's official Docker workflow (its image has `protoc` for ZMK
  Studio); push/PR on `config/**`, `build.yaml`; also `workflow_call`.
- `release.yml` - calls the ZMK build and publishes the `latest` release on push to `main`.
- `draw.yml` - renders and commits `draw/silakka54.svg` on keymap pushes.
- `bump-west.yml` - Mondays 05:00 UTC, opens a pin-west bump PR.
- `test-build-env.yml` - nix dev shell smoke test on Linux/macOS x86_64 and arm64.
- `.github/dependabot.yml` - monthly grouped github-actions updates, 14-day cooldown.

## Environment Configuration

**Required env vars:** None.

**Secrets location:** GitHub repository secrets (`WEST_UPDATE_TOKEN`, optional).

## Webhooks & Callbacks

**Incoming:** None.

**Outgoing:** None.

---

*Integration audit: 2026-11-21*
