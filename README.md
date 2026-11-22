# jellydn's zmk-config

ZMK firmware for my split keyboards, forked from
[urob/zmk-config](https://github.com/urob/zmk-config). The keymap is a port of my Vial layout
([miryoku-silakka54-layout](https://github.com/jellydn/miryoku-silakka54-layout),
[visual reference](https://kb.itman.fyi/index-graphite.html)): Graphite base, GACS home-row mods,
Miryoku-style thumb layers.

![Keymap](draw/silakka54.svg)

**[Download firmware](https://github.com/jellydn/zmk-vial-config/releases/tag/latest)**: every push to
`main` builds all firmware (Silakka54 ZMK left/right, Silakka54 Vial, Corne v4.1 Vial) and puts the
`.uf2` files, both `.vil` files and the keymap images in the `latest` release.

## Keyboards

| Keyboard  | Status    | Build target                             | Notes                                       |
| --------- | --------- | ---------------------------------------- | ------------------------------------------- |
| Silakka54 | supported | `rpi_pico//zmk` + `silakka54_left/right` | Onboard RP2040, full-duplex wired split     |
| Corne v4.1 | QMK/Vial | `crkbd/rev4_1/standard` (see `qmk/`)    | ZMK lacks single-wire (half-duplex) split on RP2040, so it runs Vial |
| Silakka54 | QMK/Vial (untested) | `silakka54` (see `qmk/silakka54/`) | Same layout as the ZMK build, for Vial users |

## Keymap

- **Base**: Graphite with home-row mods `Gui Alt Ctrl Shift` on `N R T S` and the mirror,
  `Shift Ctrl Alt Gui`, on `H A E I`. They use urob's "timeless" setup without its idle rule; see
  [Home-row mods](#home-row-mods) and the [FAQ](#faq-tap-hold-settings).
- **Thumbs** (left to right): `=`, `Space`/Nav, `Tab`/Mouse, `Enter`/Sym, `Bksp`/Num, `;`.
- **Layers**: Nav (arrows, Home/End, PgUp/PgDn), Mouse (mouse keys, Cmd shortcuts, one-shot Fn),
  Sym (shifted Num), Num (numpad), Fn (F-keys, media). `Lock` keeps the current layer on until you
  press it again.
- **Combos** (base layer only):

  | Keys    | Output       | Keys  | Output       |
  | ------- | ------------ | ----- | ------------ |
  | B L     | Esc          | F O   | sticky Meh   |
  | L D     | sticky Gui   | F U   | Esc          |
  | B L D   | Cmd+Q        | O U   | `'`          |
  | L W     | Enter        | . -   | sticky Meh   |
  | D W     | sticky Hyper | Q X   | Cmd+X        |
  | X M     | Cmd+C        |       |              |

- **Graphite shifted pairs** (base layer): Shift+`'` = `_`, Shift+`,` = `?`, Shift+`-` = `"`,
  Shift+`/` = `<`.
- **Leader key** ([urob/zmk-leader-key](https://github.com/urob/zmk-leader-key)): tap `Leader`, then
  type `B O O T` (bootloader) or `R E S E T` (restart). It acts on the half where you tapped
  `Leader`: the right one is on Nav (outer bottom-right key), the left one on Sym and Num (outer
  bottom-left key). See [How to flash](#silakka54-zmk).
- **Mouse keys** match the Vial mouse key settings (linear ramp to 4000 px/s in 600 ms; wheel to
  100 steps/s in 3.2 s).

## Home-row mods

Plain home-row mods decide by time: hold past the tapping term for a mod, release before it for a
letter. Fast rolls then give stray mods, and slow letters give stray taps. urob's
["timeless" setup](https://github.com/urob/zmk-config#timeless-homerow-mods) decides by what you
do instead. This repo uses steps 2, 4 and 5 on every board; steps 1 and 3 are urob's, left out here:

1. **Long tapping term** (urob: 280 ms; here 200 ms). Holding a letter a bit too long does not give
   a mod.
2. **Mod as soon as another key is tapped.** Hold a mod, then press *and release* another key:
   the mod applies at once, without waiting for the tapping term.
3. **Letter at once while typing** (urob: 150 ms; here off). A home-row key pressed within 150 ms
   after a typing key is a letter at once. It removes most misfires on fast rolls, but it also
   blocked home-row Shift right after a letter (see below).
4. **Other hand only.** The mod applies only when the next key is on the other hand or a thumb,
   so same-hand rolls such as `rt` in "start" stay letters.
5. **Same-hand mods still stack.** The hand check waits for the next key's *release*, so
   Ctrl+Shift on one hand works.

A key held past the tapping term on its own also becomes the mod, for a mod with a key on the same
hand, or a mod on its own.

| Step                      | Silakka54 (ZMK, `config/base.keymap`) | Corne and Silakka54 Vial (QMK Settings in the `.vil`) |
| ------------------------- | ------------------------------------- | ---------------------------------------- |
| 1. Tapping term           | 200 ms                                | 200 ms                                   |
| 2. Mod on another tap     | `flavor = "balanced"`                 | Permissive Hold: on                      |
| 3. Letter while typing    | off (no `require-prior-idle-ms`)      | Flow Tap: off                            |
| 4. Other hand only        | `hold-trigger-key-positions`: other hand, all thumbs (and the other number row) | Chordal Hold: on |
| 5. Same-hand mods stack   | `hold-trigger-on-release`             | Chordal Hold: a run of same-hand mods followed by an other-hand key all become mods |
| Quick tap (tap, then hold to repeat) | 200 ms                     | 200 ms                                   |

- All builds have step 3 off, as in the original Corne Vial setup
  ([graphite.vil](https://github.com/jellydn/dotfiles/blob/master/mics/corne/graphite.vil)). With
  it on (Vial Flow Tap or ZMK `require-prior-idle-ms`, both 150 ms), `S`/`H` pressed right after a
  letter typed a letter, so Shift needed a pause first; on the ZMK Silakka54 this showed on
  hardware too. Without it, a fast roll that nests an other-hand key inside a home-row key can give
  a stray mod; the other-hand rule still keeps same-hand rolls as letters.
- On the Corne, Chordal Hold counts the thumb layer-taps as neither hand (`chordal_hold_handedness`
  in `keymap.c`). So holding `Space` for Nav works with Nav keys on the same hand (Esc, the left
  mods), and a home-row mod plus any thumb key is a chord, as on the Silakka54. A thumb layer turns
  on when the other key is released or after the 200 ms tapping term (Vial's QMK Settings owns the
  per-key hold callbacks, so the thumbs cannot turn on at the press).
- The ZMK combos use the same 150 ms idle rule, so fast rolls such as `bl` type letters, not
  Esc. Vial combos have no idle rule.
- Vial resets Permissive Hold, Chordal Hold and Flow Tap to off on every new build. Load the `.vil`
  after every flash.

## FAQ: tap-hold settings

Corne values come from Vial's QMK Settings (load the `.vil`; check them under **QMK Settings →
Tap-Hold**).

| Setting | What it does | Why / trade-off | Example |
| --- | --- | --- | --- |
| Tapping term 200 ms | A key held longer than this on its own is a hold. | Fallback only; the rules below decide most presses sooner. Shorter means faster mods but more stray mods. | Rest on `S` 250 ms → Shift. |
| Permissive Hold | Another key pressed *and released* inside a held key makes it a hold at once. | Fast shortcuts (ZMK `balanced`). A sloppy other-hand roll can give a mod; Chordal Hold catches same-hand rolls. | `T`↓ `C`↓ `C`↑ → Ctrl+C. |
| Flow Tap off | Home-row mods are decided by the rules above, also right after a letter. | As in the original `.vil`. At 150 ms, `S`/`H` right after a letter gave a letter, not Shift. | `e`, then `S`↓ `O`↓ `O`↑ → `O`. |
| Chordal Hold | A hold needs the next key on the *other* hand. | Same-hand rolls stay letters. A same-hand mod needs the full 200 ms. Thumb layer-taps count as neither hand, so Nav keys on the thumb's own hand work. | `S` `T` (same hand) → `st`. |
| Combo term 50 ms | Combo keys must go down within 50 ms. | Chords fire, rolls type. Vial has no idle rule, so a very fast `bl` can still give Esc. | `B`+`L` together → Esc. |
| Base-layer combos | Combos fire only on the base layer (`combo_should_trigger`). | Stops `.` `-` on Num from firing sticky Meh. | — |

**Why does my thumb layer wait ~200 ms?** Hold a thumb key and *hold* the next key (for example
`Space` + an arrow): the layer turns on only at the 200 ms term. A tapped next key is instant. Vial's
QMK Settings owns "hold on other key press" for all keys, so `keymap.c` cannot turn it on for the
thumbs only (PR #9). Turning it on globally in Vial would also give stray home-row mods.

**Silakka54 (ZMK):** the home-row mods now match Vial, with ZMK names: a 200 ms term, `balanced`
(Permissive Hold), `hold-trigger-key-positions` on the other hand and all thumbs plus
`hold-trigger-on-release` (Chordal Hold), and no `require-prior-idle-ms` (Flow Tap off). urob's
upstream 280 ms term and 150 ms idle rule made home-row Shift wait after a letter. The ZMK combos
keep their own 150 ms idle rule.

## Layout of the repo

| What                               | Where                                |
| ---------------------------------- | ------------------------------------ |
| Layers, HRMs, thumb keys           | `config/base.keymap`                 |
| Combos                             | `config/combos.dtsi`                 |
| Leader sequences                   | `config/leader.dtsi`                 |
| Per-board entry keymap and config  | `config/<board>.keymap`, `.conf`     |
| Silakka54 shield (pins, layout)    | `config/boards/shields/silakka54/`   |
| Build targets                      | `build.yaml`                         |
| Keymap drawing                     | `draw/` (rendered by the Draw workflow or `just draw`) |

`base.keymap` holds every layer once, for the 54-key Silakka54. Another board (such as the Corne)
gets a small `config/<board>.keymap` that defines `ZMK_BASE_LAYER` to drop the number row or add
extra keys, then includes `base.keymap`. Combos and HRM trigger keys use the
[zmk-helpers](https://github.com/urob/zmk-helpers) key labels, so they move with the layout.

## Corne v4.1 (QMK/Vial)

`qmk/` holds the Corne v4.1 build. It keeps the same layout as the Silakka54, minus the number row:

- `qmk/keymaps/jellydn/`: QMK keymap with Vial enabled, built on foostan's Corne v4.1 Vial build.
  The `Build Corne v4.1 Vial firmware` workflow builds the `.uf2`.
- `qmk/corne-v4.1-graphite.vil`: the full Vial setup (layers, combos, key overrides, macro, QMK
  settings). Load it in Vial after you flash; see [How to flash](#corne-v41-vial).

The extra keys hold ←/→ (EX1) and Play/Pause / Next Track (EX2). The `.vil` is the single source of truth for
combos, key overrides, macro M0 and QMK Settings: Vial keeps them in EEPROM, not in `keymap.c`, and
erases them on the first boot of every new build; the firmware then writes the `.vil` values back. The firmware
itself only adds what Vial cannot store: combos fire on the base layer only, Chordal Hold counts
the thumb layer-taps as neither hand, and the LEDs start on Typing Heatmap. On that first boot it
also writes the `.vil` combos, Graphite shift overrides, macro M0 and QMK Settings (Permissive Hold,
Chordal Hold, tap code delay 0; Flow Tap stays off) back,
so they work before you load the `.vil` (`default_combos`, `default_key_overrides`,
`default_macros` and `write_default_qmk_settings` in `keymap.c`; keep them in sync with the `.vil`).

Tested on hardware (2026-11-21): the firmware from `main` with `corne-v4.1-graphite.vil` loaded.
Holding a thumb key for its layer right after typing works, and the combos, Graphite shift overrides
and macro M0 work straight after a flash.

> [!NOTE]
> Flow Tap off on the Corne (home-row Shift right after a letter) is not yet tested on hardware.
> After you flash, load the new `.vil` too: an older copy still sets Flow Tap to 150 ms.

## Silakka54 (QMK/Vial)

> [!WARNING]
> **The Silakka54 Vial firmware is UNTESTED on hardware.** The ZMK build is the main one for this
> board.

A Vial build of the same layout, next to the ZMK one:

- `qmk/silakka54/`: QMK keymap with Vial enabled, built on the Silakka54 definition in vial-qmk
  (RP2040-Zero, full-duplex serial on GP0/GP1). The `Build Silakka54 Vial firmware` workflow builds
  one `.uf2` for both halves.
- `qmk/silakka54-graphite.vil`: the full Vial setup: the 6 layers of `config/base.keymap`, the 11
  combos at 50 ms, the 4 Graphite shift overrides and macro M0 (area screenshot). Load it in Vial
  after you flash; see [How to flash](#silakka54-vial).

As on the Corne, the `.vil` is the single source of truth for combos, key overrides, macro M0 and
QMK Settings, and Vial erases them on the first boot of every new build. **Load the `.vil` after
every flash.** `keymap.c` matches the `.vil` layers key for key and only adds one thing Vial cannot
store: combos fire on the base layer only. Flow Tap is off, as on the Corne (see
[Home-row mods](#home-row-mods)); an older `.vil` still sets it to 150 ms. The board has no LEDs to set. There is no Leader or
bootloader key; enter the bootloader with the buttons or bootmagic.

## Build

Every push or pull request that touches `config/**` or `build.yaml` builds the firmware in GitHub
Actions (`Build ZMK firmware (nix)`).

For a local build environment, see [docs/build-env.md](docs/build-env.md) (`just init`, then
`just build silakka54`). The Vial firmware builds only in GitHub Actions.

## How to flash

The [latest release](https://github.com/jellydn/zmk-vial-config/releases/tag/latest) has every file
built from `main`. Use it instead of the Actions artifacts in step 1 below, unless you want a build
from another branch.

### Silakka54 (ZMK)

**Where the buttons are.** Each half has an
[RP2040-Zero](https://www.waveshare.com/wiki/RP2040-Zero) controller at the inner top corner. Its
BOOT and RESET buttons sit next to its USB-C port. On the original Silakka54 build the right
controller is mounted upside down, so its buttons face the PCB. Press them with a non-metal stick
(the [Silakka54 wiki](https://github.com/Squalius-cephalus/silakka54/wiki/Firmware-Update) has a
3D-printable tool). Check the BOOT/RESET labels printed on your controller.

![Silakka54 top view: BOOT and RESET on each controller, Leader keys and their layer thumbs, USB-C to the computer on the left half, TRRS cable between the halves](draw/flash-silakka54.svg)

**Without the BOOT button (Leader key).** Use this once the halves already run this firmware. Keep
the TRRS cable connected and plug the USB cable into the half you want to flash:

- **Right half:** move the USB cable to the right half. Hold `Space` (Nav), tap the outer
  bottom-right key (`Leader`), let go, and type `B O O T`.
- **Left half:** with the USB cable in the left half, hold `Bksp` (Num) or `Enter` (Sym), tap the
  outer bottom-left key (`Leader`), let go, and type `B O O T`.

That half restarts as the `RPI-RP2` drive. Copy its `.uf2` (see step 1) to it; after the right
half, move the USB cable back to the left half. The drive appears only over the USB port of the
half that restarted, because the TRRS cable carries no USB data. `R E S E T` instead of `B O O T`
just restarts that half.

**Steps** (with the BOOT button)

1. In the Actions tab, filter `Build ZMK firmware (nix)` by your branch (`main` once merged), open
   the green run for the commit you want, and download the `firmware` artifact. It holds
   `silakka54_left-rpi_pico__zmk-zmk.uf2` and `silakka54_right-rpi_pico__zmk-zmk.uf2`.
2. Unplug the USB cable, then unplug the TRRS cable between the halves.
3. Left half: hold BOOT and plug the USB cable into the left half, then let go of BOOT. If it is
   already plugged in, hold BOOT, press RESET, then let go of BOOT.
4. A drive named `RPI-RP2` opens. Copy `silakka54_left-…uf2` to it. The drive closes by itself when
   the flash is done.
5. Unplug the USB cable. Do steps 3 and 4 on the right half with `silakka54_right-…uf2`.
6. With the USB cable unplugged, connect the TRRS cable.
7. Plug the USB cable into the **left** half. The left half is the central; the right half gets
   power and sends its keys through the TRRS cable.

**Troubleshooting**

- One half does not type: flash that half again with its own file. Left and right files are
  different; do not swap them.
- No `RPI-RP2` drive: use a USB cable that carries data, plug in straight to the computer, and try
  BOOT + RESET again.
- Never plug in or unplug the TRRS cable while the USB cable is connected. This can short the
  controllers.

### Silakka54 (Vial)

> [!WARNING]
> UNTESTED on hardware. If it does not work, flash the [ZMK firmware](#silakka54-zmk) again.

The buttons are the same as for ZMK (see the diagram above). The Vial firmware also has bootmagic:
hold the **outer top key** of a half (`` ` `` on the left, `⏩` on the right) while you plug the USB
cable into that half.

1. In the Actions tab, filter `Build Silakka54 Vial firmware` by your branch (`main` once merged),
   open the green run for the commit you want, and download the `silakka54-vial` artifact. It holds
   `silakka54_jellydn.uf2` and `silakka54-graphite.vil`. Both halves use the same `.uf2`.
2. Unplug the USB cable, then unplug the TRRS cable between the halves.
3. Left half: hold BOOT (or the outer top key) and plug the USB cable into the left half, then let
   go. A drive named `RPI-RP2` opens. Copy `silakka54_jellydn.uf2` to it; the drive closes by
   itself when the flash is done.
4. Unplug the USB cable. Do step 3 on the right half with the same file.
5. With the USB cable unplugged, connect the TRRS cable.
6. Plug the USB cable into the **left** half. QMK treats the half with USB as the left half.
7. Open [Vial](https://get.vial.today) (desktop app or web), choose **File → Load saved layout** and
   pick `silakka54-graphite.vil`. Without this step there are **no combos**, no Graphite shift
   symbols and no M0 screenshot macro. Do it again after every new flash.

To go back to ZMK, put each half in the bootloader the same way and copy its ZMK `.uf2`.

### Corne v4.1 (Vial)

**Where the buttons are.** Each half has two small buttons, RESET and BOOT, next to the controller
chip, just below the bottom key of the ring-finger column (the 3rd column from the outer edge). On
the left half RESET is the outer button; on the right half BOOT is the outer one. If a keycap
covers them, press them with a non-metal stick between the keys.

![Corne v4.1 top view: RESET and BOOT below the ring-finger column, bootmagic keys B and J, USB-C to the computer on the left half, TRS/TRRS cable between the halves](draw/flash-corne.svg)

<sub>Button positions from foostan's
[Corne v4 PCB picture](https://github.com/foostan/kbd_firmware/assets/736191/05fd9c4b-12c7-4a32-9606-8fea27bfe7b4)
([firmware guide](https://github.com/foostan/crkbd/blob/main/docs/firmware/rev4/firmware_en.md)).</sub>

**Steps**

1. In the Actions tab, filter `Build Corne v4.1 Vial firmware` by your branch (`main` once merged),
   open the green run for the commit you want, and download the `corne-v4.1-vial` artifact. It holds `corne-v4.1-vial.uf2` and
   `corne-v4.1-graphite.vil`. Both halves use the same `.uf2`; each half knows its side from the PCB.
2. Unplug the USB cable, then unplug the TRS/TRRS cable between the halves.
3. Left half: hold BOOT and plug the USB cable into the left half, then let go of BOOT. If it is
   already plugged in, hold BOOT, press RESET, then let go of BOOT.
4. A drive named `RPI-RP2` opens. Copy the `.uf2` to it. The drive closes by itself when the flash
   is done.
5. Unplug the USB cable. Do steps 3 and 4 on the right half with the same `.uf2`.
6. With the USB cable unplugged, connect the TRS/TRRS cable (v4.1 takes either).
7. Plug the USB cable into the **left** half. (The right half also works: the half with USB becomes
   the main half.)
8. Optional: open [Vial](https://get.vial.today/), choose **File → Load saved layout** and pick
   `corne-v4.1-graphite.vil`. Each new build erases Vial's EEPROM, but the firmware writes the
   combos, Graphite shift overrides, macro M0 and QMK Settings back on first boot, so this step only
   restores anything you changed in Vial.

Other way into the bootloader: hold the top-row key second from the outer edge (`B` on the left,
`J` on the right) while you plug in that half. This also erases the Vial settings, so load the
`.vil` again afterwards.

**Troubleshooting**

- One half does not type: flash that half again.
- Combos or the Graphite shift symbols do not work: check that you are on the base layer (both work
  only there). If you changed them in Vial, load the `.vil` again to restore them.
- A half stops working at random: Corne v4 PCBs are sensitive to radio noise, most often from a
  phone ([foostan/crkbd#265](https://github.com/foostan/crkbd/issues/265)). Plug the USB cable in
  again and keep phones more than 30 cm from the keyboard.
- Never plug in or unplug the TRS/TRRS cable while the USB cable is connected. This can damage the
  controllers.
