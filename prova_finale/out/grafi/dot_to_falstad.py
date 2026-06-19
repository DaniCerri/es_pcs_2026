#!/usr/bin/env python3
"""
dot_to_falstad.py
Converte un .tikz.dot (topologia-only) nel formato testuale del simulatore
Falstad (falstad.com/circuit), RIUSANDO lo stesso layout planare degli schemi
immagine (dot_to_schemdraw): niente cerchio, posizioni crossing-free.

Pipeline posizioni (identica a dot_to_schemdraw, --layout auto):
  fan/bus-bar -> planare (Tutte) -> fallback neato + snap_to_grid.
Poi le coordinate grid sono scalate in pixel Falstad e ogni componente e'
emesso come elemento tra i due "post" dei suoi nodi. In Falstad due elementi
sono connessi solo se condividono le coordinate di un post: dando a ciascun nodo
una coordinata unica e disegnando ogni componente tra i due nodi, la topologia e'
riprodotta esattamente (gli incroci a meta' segmento non connettono).

Importa il risultato in Falstad con "File -> Import From Text" per confrontare la
soluzione del solver con quella del simulatore.

Uso:
    ./dot_to_falstad.py <file.tikz.dot> [-o output.falstad.txt] [--engine neato]
"""

import argparse
import sys
from pathlib import Path

# riuso diretto del layout dello schemdraw: stessa scelta posizioni delle immagini
from dot_to_schemdraw import (
    parse_dot,
    detect_fan,
    fan_layout,
    planar_positions,
    run_layout_plain,
    snap_to_grid,
)

GRID = 16             # passo griglia Falstad
SCALE = 6 * GRID      # unita' grid -> pixel: ~96 px tra nodi adiacenti (spazio per label)
MARGIN = 64           # margine dal bordo


def compute_positions(dotfile, edges, engine="neato"):
    """Stessa scelta di dot_to_schemdraw.main (--layout auto): fan -> planare -> grid."""
    fan = detect_fan(edges)
    if fan is not None:
        rail, order = fan
        positions, _routes, _extra, _meta = fan_layout(edges, rail, order)
        print(f"Layout: bus-bar (rail {rail}, {len(order)} derivazioni)")
        return positions
    positions = planar_positions(edges)
    if positions is not None:
        print("Layout: planare crossing-free (Tutte)")
        return positions
    raw = run_layout_plain(dotfile, engine)
    print(f"Layout: grid (engine {engine})")
    return snap_to_grid(raw)


def to_pixels(positions):
    """Coordinate grid -> pixel interi Falstad: normalizza, scala, snap, flip Y.

    Graphviz/Tutte hanno Y verso l'alto, Falstad verso il basso: si specchia Y
    cosi' lo schema importato ha lo stesso orientamento delle immagini."""
    xs = [p[0] for p in positions.values()]
    ys = [p[1] for p in positions.values()]
    minx, maxy = min(xs), max(ys)
    px = {}
    for node, (x, y) in positions.items():
        gx = MARGIN + (x - minx) * SCALE
        gy = MARGIN + (maxy - y) * SCALE
        px[node] = (int(round(gx / GRID)) * GRID,
                    int(round(gy / GRID)) * GRID)
    return px


def emit_falstad(edges, px):
    """Elementi Falstad. Resistore: r ... 0 <ohm>. Generatore DC: v ... con il
    "+" sul secondo post (Falstad impone V(post2)-V(post1)=val), quindi il nodo
    positivo (attributo pos) deve finire in (x2,y2)."""
    lines = ["$ 1 0.000005 10.20027730826997 50 5 50"]
    for a, b, attr in edges:
        ax, ay = px[a]
        bx, by = px[b]
        val = attr.get("val", "0")
        if attr.get("type", "R") == "R":
            # r x1 y1 x2 y2 flags resistance
            lines.append(f"r {ax} {ay} {bx} {by} 0 {val}")
        else:
            # se il nodo positivo e' il primo post, scambia: "+" deve stare sul post2
            if attr.get("pos") == a:
                ax, ay, bx, by = bx, by, ax, ay
            # v x1 y1 x2 y2 flags waveform freq maxVoltage bias phaseShift dutyCycle
            lines.append(f"v {ax} {ay} {bx} {by} 0 0 40 {val} 0 0 0.5")
    # massa di riferimento sul primo nodo: fissa il potenziale a 0 cosi' le tensioni
    # dei nodi sono assolute e confrontabili (solo il primo post della massa connette)
    first = next(iter(px.values()))
    lines.append(f"g {first[0]} {first[1]} {first[0]} {first[1] + 48} 0")
    return "\n".join(lines) + "\n"


def main():
    ap = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("dotfile", type=Path)
    ap.add_argument("-o", "--output", type=Path)
    ap.add_argument("--engine", default="neato",
                    help="motore Graphviz per il fallback grid (default neato)")
    args = ap.parse_args()

    if not args.dotfile.is_file():
        sys.exit(f"File non trovato: {args.dotfile}")

    edges = parse_dot(args.dotfile)
    if not edges:
        sys.exit("Nessun arco trovato nel .dot")

    positions = compute_positions(args.dotfile, edges, args.engine)
    if positions is None:
        sys.exit("Layout non disponibile (grafo non planare e fallback fallito).")

    px = to_pixels(positions)
    text = emit_falstad(edges, px)

    if args.output:
        out = args.output
    else:
        stem = args.dotfile.name
        if stem.endswith(".tikz.dot"):
            stem = stem[:-len(".tikz.dot")]
        elif stem.endswith(".dot"):
            stem = stem[:-len(".dot")]
        out = args.dotfile.parent / f"{stem}.falstad.txt"

    out.write_text(text)
    print(f"Generato: {out}  ({len(edges)} componenti)")


if __name__ == "__main__":
    main()
